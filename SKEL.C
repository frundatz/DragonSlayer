
#include <stdio.h>
#include <string.h>
#include <io.h>
#include <fcntl.h>
#include <dos.h>
#include <stdlib.h>
#include <time.h>

int    usernum,             /* user number for the user */
       age,                 /* age of the user */
       screenchars,         /* chars/line user has specified */
       screenlines,         /* lines/screen user has specified */
       sl,                  /* sec lev for user (0-255) */
       so,                  /* non-zero if user is sysop (sl=255) */
       cs,                  /* non-zero if user is co-sysop */
       okansi,              /* non-zero if user can support ANSI */
       incom,               /* non-zero if user is calling remotely */
       comport;             /* com port user is on */
char   name[81],            /* name/alias of user */
       realname[81],        /* real name of user */
       callsign[10],        /* amateur radio callsign of user */
       sex,                 /* sex of user, M or F */
       laston[81],          /* date user was last on */
       gfiles[81],          /* directory for text files, ends in \ */
       data[81],            /* directory for non-text files, ends in \ */
       sysoplog[81],        /* full path & filename for sysop log */
       curspeed[81];        /* speed user is on at, "KB" if local */
double gold,                /* gold user has */
       timeallowed,         /* number of seconds before user logged off */
       version;             /* version of WWIV running under */


int read_in_data(char *fn)
{
  char buf[1024];
  char *ptr[30],*ss,s[81];
  int i,f,len,i1;
  float fl;

  f=open(fn,O_RDONLY | O_BINARY);
  if (f<0) {
    return(-1);
  }
  i1=1;
  ptr[0]=buf;
  len=read(f,(void *)buf,1024);
  close(f);
  for (i=0; i<len; i++)
    if (buf[i]==13) {
      buf[i]=0;
      ptr[i1++]=&buf[i+2];
    }
  while (*ptr[6]==32)
    ++(ptr[6]);
  while (*ptr[15]==32)
    ++(ptr[15]);
  usernum=atoi(ptr[0]);
  strcpy(name,ptr[1]);
  strcpy(realname,ptr[2]);
  strcpy(callsign,ptr[3]);
  age=atoi(ptr[4]);
  sex=*ptr[5];
  sscanf(ptr[6],"%f",&fl);
  gold=(double)fl;
  strcpy(laston,ptr[7]);
  screenchars=atoi(ptr[8]);
  screenlines=atoi(ptr[9]);
  sl=atoi(ptr[10]);
  so=atoi(ptr[11]);
  cs=atoi(ptr[12]);
  okansi=atoi(ptr[13]);
  incom=atoi(ptr[14]);
  sscanf(ptr[15],"%f",&fl);
  timeallowed=(double)fl;
  strcpy(gfiles,ptr[16]);
  strcpy(data,ptr[17]);
  strcpy(sysoplog,gfiles);
  strcat(sysoplog,ptr[18]);
  strcpy(curspeed,ptr[19]);
  comport=atoi(ptr[20]);
  return(0);
}
