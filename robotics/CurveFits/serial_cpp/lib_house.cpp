/************************************************
*	lib_house.cpp				*
*                                               *
*               J. Savage                       *
*               UNAM                            *
*                                               *
*                                               *
*                       8/22/14                 *
*************************************************/


#include <stdio.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <termio.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>



#define STDIN  0
#define STDOUT 1

static struct termio save;
 
extern int fd1,fd2;   


void *read_serial_port(void *arg)
{
   char c;
 
   while (1) {       /* loop for input */
      read(fd2,&c,(size_t) 1);
      putchar(c);
      //printf("%x\n",c);
      fflush(stdout);
   }
}
                                                                                


int open_terminal(char *device, int baud)
{
    int serial_open(char *port,unsigned speed,int bits,int stops,int timeout);

    //int len,j;
    int fd;

    if ( (fd = serial_open(device,(unsigned)baud,(unsigned)8,(unsigned)1,10)) < 0 )
    {
        printf("\n Error on opening %s\n",device);
        return 0;
    }
    return fd;
}



void close_terminal()
{
 void serial_close(int);

 serial_close(fd2);
}


void send_terminal_char(char word1)
{
 int text1[30],t1[10];

 t1[0]=(int)(0xff & word1);
 printf("\n t1 %c 0x%x\n",t1[0],t1[0]);
 write(fd2,t1,1);
 /*read(fd2,text1,1);
 printf(" received %c",text1[0]);*/
}




void send_terminal(char *word1)
{
 int flag,len,text1[30],j,t1[10];
 char nl[300];

 strcpy(nl,word1);
 len = strlen(nl);

 for(j=0;j<len-1;j++){
	t1[0]= 0xff & nl[j];
 	write(fd2,t1,1);
	/*printf("%d send %x %c ",j,t1[0],t1[0]);*/
 	//read(fd2,text1,1);
	/*printf("received %x %c\n",0xff&text1[0],0xff&text1[0]);*/
	/*printf("%c",text1[0]);*/
 }
 t1[0]=0xd;
 write(fd2,t1,1);

}

void send_terminal_no_echo(char *word1)
{
 int flag,len,text1[30],j,t1[10];
 char nl[300];

 strcpy(nl,word1);
 len = strlen(nl);

 for(j=0;j<len;j++){
	t1[0]= 0xff & nl[j];
 	write(fd2,t1,1);
	/*printf("%c",t1[0]);*/
 }
 t1[0]=0xd;
 write(fd2,t1,1);
 t1[0]=0xa;
 write(fd2,t1,1);
 /*printf("\n");*/

}


#define MAX_NUM_CHARACTERS 600
#define MAX_NUM_LINES 10
/* This function will receive data from the serial port until
it receives "-> " (space after >) */
char receive_terminal(char *rec)
{
 int flag,len,text1[MAX_NUM_CHARACTERS],j,num;
 char nl[MAX_NUM_CHARACTERS],c1;
 unsigned char c;
 int repeat,num_lines;
 
 num_lines=0;
 repeat=0;
 flag=1;
 j=0; 
 while(flag){
         num=read(fd2, text1,1);
	 //printf("num %d text *** %c ***\n",num,text1[0]);
         //printf("terminal %x %c ",0xff & text1[0],0xff & text1[0]); 

	 nl[j]=(char)(0xff & text1[0]);

	 j++;
	 if((0xff & text1[0])== '\n'){
		flag=0;
	 }
 	// printf("j %d\n",j);
 }

 nl[j]=0;
 //printf("data from serial port: %s\n",nl);
 strcpy(rec,nl);
 //printf("data from serial port: %s\n",rec);
 return(repeat);

}



char receive_terminal_char(char nl)
{
 int flag,len,text1[300],j,res;
 unsigned char c;


 printf("\n receive \n");
 flag=1;
 j=0; 
 while(flag){
         res=read(fd2, text1,1);
	 printf("\n res %d\n",res);
	 if(res){
	 	nl=(char)(0xff & text1[0]);
	 	printf("nl %c %x ",nl,0xff & nl);
	 	printf("%c",nl);
         	if((0xff & text1[0])== '\n')flag = 0;
	 	j++;
	 	/*if(read(STDIN, &c, 1)){
			send_terminal_char(c);
			if(c=='q')flag=0;
	 	}*/
	 	flag=0;
	}
 }


}


/**********************************************
*
* 	Checks if a key is hit in the keyboard
*	and reads it.
*
*********************************************/



void modify_term(void)
{
  struct termio term;

  /* make sure we're connected to a terminal and get terminal state */
  if ( ioctl( STDIN, TCGETA, &term) == -1 )
    {
      fprintf(stderr," standard input is not a terminal\n");
      exit (errno);
    }

  /* save old state */
  save = term; 

  /* turn off canonical processing i.e. don't buffer terminal */
  term.c_lflag &= ~ICANON;

  /* read waits for one character */
  term.c_cc[VMIN] = 0;

  /* no minimum time */
  term.c_cc[VTIME] = 0;

  /* set terminal to new state */
  ioctl( STDIN, TCSETA, &term );

}


void restore_term(void)
{

  /* reset */
  ioctl( STDIN, TCSETA, &save );

  exit(0);
}

/* Get a line from the keyword, and give its size */
int getline(char *s,int lim)
{
 int c,i;

 for(i=0;i<lim-1 && (c=getchar() ) != EOF && c != '\n'; ++i){
        s[i]=c;
 }
 s[i]='\0';
 return(i);

}


