/* seriallib.h

  Fran Taylor, HITL
  
  Library functions for sensor interfaces */
#define POSIX 1
#ifndef _sensorlibh_
#define _sensorlibh_

#include <errno.h>

#ifdef THINK_C
#define __ANSI__
#endif

/* function definitions */

#ifdef __ANSI__

int serial_open(char *port, unsigned speed, unsigned bits, unsigned stops,
		int timeout);
int serial_close(int fd);
int serial_vmin(int fd, int n);
int serial_config(int fd, unsigned speed, unsigned bits, unsigned stops);
unsigned serial_getspeed(int fd);
long serial_msecs(void);
int serial_timeout_read(int fd, char *buf, int n, int timeout);
int serial_odrain(int fd);

#else
int serial_open();
int serial_close();
int serial_vmin();
int serial_config();
unsigned serial_getspeed();
unsigned serial_speed2bits();
unsigned serial_bits2speed();
long serial_msecs();
int serial_timeout_read();
int serial_odrain();
#endif /* __ANSI__ */

#define s_open(f,p,s,b,st,t) if (((*(f))=serial_open(p,s,b,st,t))<0) return -1;
#define s_close(f) if (serial_close(f) < 0) return -1;
#define s_write(f,b,s) if(serial_write(f,b,s)<0){serial_close(f);return -1;}
#define s_read(f,b,s) if(serial_read(f,b,s)<0){serial_close(f);return -1;}
#define s_iflush(f) if (serial_iflush(f) < 0) return -1;
#define s_oflush(f) if (serial_oflush(f) < 0) return -1;
#define s_odrain(f) if (serial_odrain(f) < 0) return -1;
#define s_config(f,c) if (serial_config(f,c) < 0) return -1;

#ifdef THINK_C

/****************** Macintosh specific stuff ****************************/

#include <SerialDvr.h>
#include <math.h>
#include <unix.h>
#include <string.h>

#define EALIGN -36 /* I/O Error */

#define bcopy(s, d, n) BlockMove(s, d, n)

#define wp(fd) ((fd == 6) ? sPortA : sPortB)

#define serial_read(f,b,n) (s_sz=(n),(((errno=FSRead(-(f),&s_sz,(b)))<0)?-1:(int)s_sz))
#define serial_write(f,b,n) (s_sz=(n),(((errno=FSWrite(-(f+1),&s_sz,(b)))<0)?-1:(int)s_sz))
#define serial_iflush(fd) KillIO(-fd)
#define serial_oflush(fd) KillIO(-(fd+1))
#define s_vmin(fd, n)
#define serial_vmin(fd, n)

extern long s_sz;

int fstat(int f, struct stat *s);

#endif /* THINK_C */

#ifdef POSIX

/********************** Posix specific stuff *******************************/

#include <signal.h>
#include <setjmp.h>
#include <sys/file.h>
#include <sys/time.h>
#include <termios.h>
/* #include <unistd.h> */

#ifndef EALIGN
#define EALIGN 74 /* alignment error */
#endif

#ifndef CBAUD
#define CBAUD 0x000f
#endif

#ifdef SHOW_IO
#define serial_write(f, b, s) serial_debug_write(f, b, s)
#define serial_read(f, b, s) serial_debug_read(f, b, s)
#else
#define serial_write(f, b, s) write(f, b, s)
#define serial_read(f, b, s) read(f, b, s)
#endif

#define serial_iflush(fd) tcflush(fd, TCIFLUSH)
#define serial_oflush(fd) tcflush(fd, TCOFLUSH)
#define serial_odrain(fd) tcdrain(fd)

#define s_vmin(fd, n) if (serial_vmin(fd, n) < 0) \
                      {serial_close(fd); return -1; }

#endif /* POSIX */

#ifdef SYSTEM_FIVE

/******************** System Five Specific Stuff *****************************/

#include <termio.h>
#include <signal.h>
#include <setjmp.h>
#include <sys/file.h>
#include <sys/time.h>

#ifndef EALIGN
#define EALIGN 74 /* alignment error */
#endif

#ifndef CBAUD
#define CBAUD 0x000f
#endif

#define serial_write(f, b, s) write(f, b, s)
#define serial_read(f, b, s) read(f, b, s)

#define serial_iflush(fd) ioctl(fd, TCFLSH, 0)
#define serial_oflush(fd) ioctl(fd, TCFLSH, 1)
#define serial_odrain(fd) ioctl(fd, TCSBRK, 1)

#define s_vmin(fd, n) if (serial_vmin(fd, n) < 0) \
                      {serial_close(fd); return -1; }

#endif /* SYSTEM_FIVE */

#endif /* _SENSORLIBH_ */
