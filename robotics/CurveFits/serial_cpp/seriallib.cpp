/* seriallib.c

   A portable RS-232 communications library

   by Fran Taylor, at the HITLab, Seattle

   Copyright (C) 1991  Human Interface Technology Lab, Seattle

   SensorLib is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 1, or (at your option)
   any later version.

   SensorLib is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with SensorLib; see the file COPYING.  If not, write to
   the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.

   C Library routines for 8-bit raw RS-232 I/O
   No handshaking
   Blocking reads for minimal overhead (Unix)
   Supports vmin for System Five and Posix

   (the Mac version polls in its timeout read; I was lazy) */

#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "seriallib.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#ifdef SHOW_IO

#define strcinc(ptr, str) (strcpy(ptr, str), ptr += strlen(str))

static char visprstr[1024];

static char *nlprint(str, n)
unsigned char *str;
int n;
{
  unsigned char *ptr;
  int i;
  char ns[10];
  for(ptr = visprstr, i = 0; i < n; str++, i++)
  {
    sprintf(ns, "0x%02x ", *str);
    strcinc(ptr, ns);
  }
  *ptr = '\0';
  return visprstr;
}

int serial_debug_write(fd, buf, n)
int fd;
char *buf;
int n;
{
  int err;
  if ((err = write(fd, buf, n)) == n)
    printf("Writing: \"%s\"\n", nlprint(buf, n));
  return err;
}

int serial_debug_read(fd, buf, n)
int fd;
char *buf;
int n;
{
  int err;
  if ((err = read(fd, buf, n)) == n)
    printf("Read: \"%s\"\n", nlprint(buf, n));
  return err;
}

#endif

#ifdef THINK_C

/***************************** Macintosh *****************************/

static unsigned speedtab[][2] = 
{
{  300, baud300},
{  600, baud600},
{ 1200, baud1200},
{ 1800, baud1800},
{ 2400, baud2400},
{ 3600, baud3600},
{ 4800, baud4800},
{ 7200, baud7200},
{ 9600, baud9600},
{19200, baud19200},
{57600, baud57600}
};

#define NSPEEDS 11

static unsigned speeds[2];

/* ----------------- translate speed to bits ----------------------- */

static unsigned serial_speed2bits(speed)
unsigned speed;
{
  int i;
  for(i = 0; i < NSPEEDS; i++)
      if (speedtab[i][0] == speed)
	return speedtab[i][1];
  return 0xffff;
}

/* ------------------ translate bits to speed ------------------------ */

static unsigned serial_bits2speed(bits)
unsigned bits;
{
  int i;

  bits &= 0x3ff;
  for(i = 0; i < NSPEEDS; i++)
    if (speedtab[i][1] == bits)
      return speedtab[i][0];
  return 0xffff;
}

/*---------------- translate config info to bits ------------------- */

static int serial_config2bits(speed, bits, stops)
unsigned speed;
int bits, stops;
{
}

/*------------- open the serial port ---------------------------*/

int serial_open(char *port,unsigned speed,unsigned bits,unsigned stops,int timeout)
{
  int wp, fd;
  
  if (strstr(port, "modem"))
    fd = 6;
  else if (strstr(port, "printer"))
    fd = 8;
  else
    return -1;

  if (RAMSDOpen(wp(fd)) < 0)
    return -1;
  
  if ((SerReset(-fd, speed | stop20 | data8) < 0) | 
      (SerReset(-(fd+1), speed | stop20 | data8) < 0))
  {
    RAMSDClose(wp(fd));
    return -1;
  }
  speeds[wp(fd)] = speed;
 
  return fd;
}

/*---------------------- close the serial port ----------------------*/

int serial_close(fd)
int fd;
{
  RAMSDClose(wp(fd));
}

/* --------------------- get the speed bits ------------------------- */

unsigned serial_getspeed(fd)
int fd;
{
  if (fd == fileno(stdout))
    return baud57600;
  return speeds[wp(fd)];
}

/*------------------------- timeout read ---------------------------*/

int serial_timeout_read(fd, buf, n, timeout)
int fd;
char *buf;
int n;
int timeout;
{
  long c, s;
	
  s = serial_msecs();
  for(;;)
  {
    if (SerGetBuf(-fd, &c) < 0)
      return -1;
    if (c == n)
      break;
    if ((serial_msecs() - s) / 1000 > timeout)
    {
      errno = ETIMEDOUT;
      return -1;
    }
  }
  if ((FSRead(-fd, &c, buf) < 0) || (c != n))
    return -1;
  return (int) c;
}

/*------------------ millisecond timer -------------------------------------*/

long serial_msecs()
{
  return (TickCount() * (1000 / 60));
}

/*------------------ block till output drains ------------------------------*/

int serial_odrain(fd)
int fd;
{
  SerStaRec sr;

  for(;;)
  {
    if (SerStatus(-(fd+1), &sr) < 0)
      return -1;
    if(!sr.wrPend)
      break;
  }
  return 0;
}


#endif /* THINK_C */

#ifdef POSIX

/***************************** Posix *************************************/

static unsigned speedtab[][2] = 
{
{   75, B75},
{  110, B110},
{  134, B134},
{  150,	B150},
{  300,	B300},
{  600,	B600},
{ 1200,	B1200},
{ 2400,	B2400},
{ 4800,	B4800},
{ 9600,	B9600},
#ifndef B19200
{19200, EXTA},
{38400, EXTB}
#else
{19200,	B19200},
{38400, B38400}
#endif
};

#define NSPEEDS 12

static struct termios t[FD_SETSIZE];

/*-------------- translate speed to bits -----------------------*/

unsigned serial_speed2bits(unsigned speed)
{
  int i;
  for(i = 0; i < NSPEEDS; i++)
      if (speedtab[i][0] == speed)
	return speedtab[i][1];
  return 0;
}

/* ------------------ translate bits to speed ------------------*/


unsigned serial_bits2speed(unsigned bits)
{
  int i;
  bits &= CBAUD;

  for(i = 0; i < NSPEEDS; i++)
    if (speedtab[i][1] == bits)
      return speedtab[i][0];
  return -1;
}

/*---------------- translate config info to bits ------------------- */

static int serial_config2bits(unsigned speed, int bits, int stops)
{
  unsigned config;

  /* fill in the speed part */

  if (((config = serial_speed2bits(speed)) == -1) ||
      (bits < 5) || (bits > 8) || (stops < 1) || (stops > 2))
  {
    errno = EINVAL;
    return -1;
  }
  
  /* transmit speed = receive speed */

  config |= config << 16;

  /* fill in the data bits part */

  switch(bits)
  {
  case 5:
    config |= CS5;
    break;
  case 6:
    config |= CS6;
    break;
  case 7:
    config |= CS7;
    break;
  case 8:
    config |= CS8;
    break;
  default:
    errno = EINVAL;
    return -1;
  }

  /* fill in the stop bits */

  if (stops == 2)
    config |= CSTOPB;
  else if (stops != 1)
  {
    errno = EINVAL;
    return -1;
  }
  config |= CREAD | CLOCAL;
  return config;
}

/*------------- open the serial port ---------------------------*/

int serial_open(char *port,unsigned speed,int bits,int stops,int timeout)
{
  int fd, config;
  //int close(int);
  if ((config = serial_config2bits(speed, bits, stops)) == -1){
    printf("\n config %d",config);
    return -1;
  }  
  /* open the port */

  if ((fd = open(port, O_RDWR, 0)) < 0){
    printf("\n fd %d",fd);
    return -1;
  }

  /* set the control bits for the port */

  if (tcgetattr(fd, &(t[fd])) < 0)
  {
    close(fd);
    return -1;
  }

  t[fd].c_iflag = 0;
  t[fd].c_oflag = 0;
  t[fd].c_cflag = config;
  t[fd].c_lflag = 0;

  /* set up to read back 1 byte */

  t[fd].c_cc[VMIN] = 1;
  t[fd].c_cc[VTIME] = timeout*10;

  if (tcsetattr(fd, TCSANOW, &(t[fd])) < 0)
  {
    close(fd);
    return -1;
  }

  return fd;
}

/*------------- open the serial port and does not wait ---------------------------*/

int serial_open_no_wait(char *port,unsigned speed,unsigned bits,unsigned stops,int  timeout)
{
  int fd, config;
  //int close(int);

  /* open the port */

  if ((fd = open(port, O_RDWR)) < 0)
    return -1;

  /* set the control bits for the port (man termios explains this) */

  if (ioctl(fd, TCGETA, &(t[fd])) < 0)
  {
    close(fd);
    return -1;
  }
  
  /* fill in the speed part */

  if (((config = serial_speed2bits(speed)) == -1) ||
      (bits < 5) || (bits > 8) || (stops < 1) || (stops > 2))
  {
    errno = EINVAL;
    return -1;
  }
  
  /* transmit speed = receive speed */

  config |= config << 16;

  /* fill in the data bits part */

  switch(bits)
  {
  case 5:
    config |= CS5;
    break;
  case 6:
    config |= CS6;
    break;
  case 7:
    config |= CS7;
    break;
  case 8:
    config |= CS8;
    break;
  }

  /* fill in the stop bits */

  if (stops == 2)
    config |= CSTOPB;

  config |= CREAD | CLOCAL;

  t[fd].c_iflag = 0;
  t[fd].c_oflag = 0;
  t[fd].c_cflag = config;
  t[fd].c_lflag = 0;

  /* set up to read back 0 byte */

  t[fd].c_cc[VMIN] = 0;
  t[fd].c_cc[VTIME] = timeout*10;

  t[fd].c_lflag &= ~ICANON;


  if (ioctl(fd, TCSETA, &(t[fd])) < 0)
  {
    close(fd);
    return -1;
  }

  return fd;
}


/*---------------------- close the serial port ----------------------*/

int serial_close(int fd)
{
  //int close(int);

  return close(fd);
}

int serial_config(int fd,unsigned speed,int bits,int stops)
{
  int config;
  //int close(int);
 
  if ((config = serial_config2bits(speed, bits, stops)) == -1)
    return -1;

  t[fd].c_cflag = config;
  if (tcsetattr(fd, TCSANOW, &(t[fd])) < 0)
  {
    close(fd);
    return -1;
  }
  return 0;
}

/* --------------------- get the speed bits ------------------------- */

unsigned serial_getspeed(int fd)
{
  struct termios t;
  
  if (tcgetattr(fd, &t) < 0)
    return -1;
  
  return (serial_bits2speed(((unsigned) t.c_cflag & CBAUD)));
}

/*------------- set the # of characters in a packet ------------------*/

int serial_vmin(int fd,int n)
{
  char str[256];

  t[fd].c_cc[VMIN] = n;

  if (tcsetattr(fd, TCSANOW, &(t[fd])) < 0)
  {
    serial_close(fd);
    return -1;
  }

  return 0;
}

/*------------------------- timeout read ---------------------------*/

static jmp_buf tenv;

static void catch_timeout()
{
  longjmp(tenv, 1);
}


/*
int serial_timeout_read(int fd,char *buf,int n,unsigned timeout)
{
  int len;
  void alarm(unsigned);
  int read(int,char *, int);
  sighandler_t signal(int signum, static void ());
 
  // set up to come back here if timeout 

  if (setjmp(tenv))
  {
    alarm(0);
    signal(SIGALRM, SIG_DFL);
    errno = ETIMEDOUT;
    return -1;
  }

  // set the alarm and the signal catching procedure 

  signal(SIGALRM, catch_timeout);
  alarm(timeout);

  / do the read 

  if ((len = read(fd, buf, n)) != n)
  {
    alarm(0);
    signal(SIGALRM, SIG_DFL);

#ifdef SHOW_IO
    printf("Received: \"%s\"\n", nlprint(buf, len));
#endif

    serial_close(fd);
    return len;
  }

  // we made it! Turn off the alarm 

  alarm(0);
  signal(SIGALRM, SIG_DFL);
  errno = 0;

#ifdef SHOW_IO
  printf("Received: \"%s\"\n", nlprint(buf, n));
#endif


  return len;
}
*/


/*------------------ millisecond timer -------------------------------------*/

long serial_msecs()
{
  struct timeval t;
  gettimeofday(&t, NULL);
  return (((long)t.tv_sec) * 1000) + (((long)t.tv_usec) / 1000);
}

#endif /* POSIX */

#ifdef SYSTEM_FIVE

/************************* System Five *************************************/

static struct termio t[FD_SETSIZE];

static unsigned speedtab[][2] = 
{
{   75, B75},
{  110, B110},
{  134, B134},
{  150,	B150},
{  300,	B300},
{  600,	B600},
{ 1200,	B1200},
{ 2400,	B2400},
{ 4800,	B4800},
{ 9600,	B9600},
#ifndef B19200
{19200, EXTA},
{38400, EXTB}
#else
{19200,	B19200},
{38400, B38400}
#endif
};

#define NSPEEDS 12

/*-------------- translate speed to bits -----------------------*/

unsigned serial_speed2bits(unsigned speed)
{
  int i;
  for(i = 0; i < NSPEEDS; i++)
      if (speedtab[i][0] == speed)
	return speedtab[i][1];
  return -1;
}

/* ------------------ translate bits to speed ------------------*/

unsigned serial_bits2speed(unsigned bits)
{
  int i;
  bits &= CBAUD;

  for(i = 0; i < NSPEEDS; i++)
    if (speedtab[i][1] == bits)
      return speedtab[i][0];
  return -1;
}




int serial_open(char *port,unsigned speed,unsigned bits,unsigned stops,int timeout)
{
  int fd, config;
  //int close(int );

  /* open the port */

  if ((fd = open(port, O_RDWR)) < 0)
    return -1;

  /* set the control bits for the port (man termios explains this) */

  if (ioctl(fd, TCGETA, &(t[fd])) < 0)
  {
    close(fd);
    return -1;
  }
  
  /* fill in the speed part */

  if (((config = serial_speed2bits(speed)) == -1) ||
      (bits < 5) || (bits > 8) || (stops < 1) || (stops > 2))
  {
    errno = EINVAL;
    return -1;
  }
  
  /* transmit speed = receive speed */

  config |= config << 16;

  /* fill in the data bits part */

  switch(bits)
  {
  case 5:
    config |= CS5;
    break;
  case 6:
    config |= CS6;
    break;
  case 7:
    config |= CS7;
    break;
  case 8:
    config |= CS8;
    break;
  }

  /* fill in the stop bits */

  if (stops == 2)
    config |= CSTOPB;

  config |= CREAD | CLOCAL;

  t[fd].c_iflag = 0;
  t[fd].c_oflag = 0;
  t[fd].c_cflag = config;
  t[fd].c_lflag = 0;

  /* set up to read back 1 byte */

  t[fd].c_cc[VMIN] = 1;
  t[fd].c_cc[VTIME] = timeout*10;

  if (ioctl(fd, TCSETA, &(t[fd])) < 0)
  {
    close(fd);
    return -1;
  }

  return fd;
}




/*---------------------- close the serial port ----------------------*/

int serial_close(int fd)
{
  return close(fd);
}

/* --------------------- get the speed bits ------------------------- */

unsigned serial_getspeed(int fd)
{
  struct termio t;
  
  if (ioctl(fd, TCGETA, &t) < 0)
    return -1;
  return (serial_bits2speed(t.c_cflag & CBAUD));
}

int serial_config(int fd,int config)
{
  t[fd].c_cflag = CREAD | CLOCAL | config | ((config & CBAUD) << 16);

  if (ioctl(fd, TCSETA, &(t[fd])) < 0)
  {
    close(fd);
    return -1;
  }
  return 0;
}

/*------------- set the # of characters in a packet ------------------*/

int serial_vmin(int fd,int n)
{
  char str[256];

  t[fd].c_cc[VMIN] = n;

  if (ioctl(fd, TCSETA, &(t[fd])) < 0)
  {
    serial_close(fd);
    return -1;
  }

  return 0;
}

/*------------------------- timeout read ---------------------------*/

static jmp_buf tenv;

static void catch_timeout()
{
  longjmp(tenv, 1);
}

int serial_timeout_read(int fd,char *buf,int n,int timeout)
{
  int len;

  /* set up to come back here if timeout */

  if (setjmp(tenv))
  {
    alarm(0);
    signal(SIGALRM, SIG_DFL);
    serial_close(fd);
    errno = ETIMEDOUT;
    return -1;
  }

  /* set the alarm and the signal catching procedure */

  signal(SIGALRM, catch_timeout);
  alarm(timeout);

  /* do the read */

  if (read(fd, buf, n) != n)
  {
    alarm(0);
    signal(SIGALRM, SIG_DFL);
    return -1; 
  }

  /* we made it! Turn off the alarm */

  alarm(0);
  signal(SIGALRM, SIG_DFL);
  return 0;
}

/*------------------ millisecond timer -------------------------------------*/

long serial_msecs()
{
  struct timeval t;
  gettimeofday(&t, NULL);
  return (((long)t.tv_sec) * 1000) + (((long)t.tv_usec) / 1000);
}

#endif

