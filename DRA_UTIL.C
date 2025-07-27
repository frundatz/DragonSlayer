char uti_temps[81];

void printfile(char *s)
{
  char string[95];
  int abort=0;

  if ( (fptr=fopen(s,"r")) == NULL) {
    sprintf(string,"\"%s\" File Not Found.\n",s);
    pl(string);
    return;
  }

  while((fgets(string,94,fptr) != NULL) && (!abort)) {
    string[strlen(string)-1] = '\0';
    pla(string,&abort);
  }
  fclose(fptr);
}

void pausescr()
{

  if (okansi) {
    outstr("7®®0 \x1B[4mHit Any Key\x1B[0m 7¯¯0\x1b[17D");
    getkey();
    outstr("0                 \x1b[17D");
  } else {
    outstr("[Hit Any Key]");
    getkey();
    backspace(13);
  }
}

void backspace (int number)
{
  int count=1;

  do {
    outstr("\b \b");
    ++count;
  } while (count < number);
}

void write_points()
{
  fptr=fopen("READ.PNT","w");
  fputs("1",fptr);
  fclose(fptr);
  fptr=fopen("POINTS.PNT","w");
  fprintf(fptr,"%f",gold);
  fclose(fptr);
}

void outstr(char *s)
{
  int count;

  for(count = 0; count < strlen(s); count++)
    printf("%c",s[count]);
}

void nl()
{
  printf("\n");
}

void pl(char *s)
{
  outstr(s);
  nl();
}

char onek(char *s)
{
  char ch;

  do {
    ch = getkey();
    if((ch > 96) && (ch < 123))
      ch -= 32;
  } while(strchr(s,ch)==0);
  printf("%c\n",ch);
  return(ch);
}


void input1(char *s, int length, int type)
{
  int curpos=0,ok;
  char ch;

  do {
    ch = getkey();
    ok = 0;
    if((ch == 8) && (curpos > 0)) {
      backspace(1);
      --curpos;
    }
    if((ch == 23) && (curpos > 0))
      do {
        backspace(1);
	--curpos;
      } while((s[curpos] != 32) && (curpos > 0));
    if((ch == 24) && (curpos > 0)) {
      backspace(curpos+1);
      curpos = 0;
    }
    if(ch == 13) {
      s[curpos] = '\0';
      nl();
    }
    if(type == 0) {
      if((ch > 31) && (ch < 123))
	ok = 1;
    }
    if(type == 1) {
      if((ch > 96) && (ch < 123))
	ch -= 32;
      if((ch > 64) && (ch < 91))
	ok = 1;
    }
    if(type == 2) {
      if((ch > 47) && (ch < 58))
	ok = 1;
    }
    if(ch == 32)
      ok = 1;
    if(curpos > length)
      ok = 0;
    if(ok) {
      printf("%c",ch);
      s[curpos] = ch;
      ++curpos;
    }
  } while (ch != 13);
}

void input(char *s, int length)
{
  input1(s,length,0);
}

char getkey()
{
  return(getch());
}

int yes_no(int yn)
{
  char ok[4],ch;

  strcpy(ok,"YN");
  ok[2] = 13;
  ok[3] = '\0';
  ch = onek(ok);
  if(ch == 'Y')
    return(1);
  if(ch == 'N')
    return(0);
  return(yn);
}

int yn()
{
  yes_no(0);
}

int ny()
{
  yes_no(1);
}

void pla(char *s, int *abort)
{
  int i,next;

  i=0;
  while ((s[i]) && (!(*abort))) {
    printf("%c",s[i++]);
    if(kbhit() != 0)
      if(getch() == 32)
        *abort = 1;
  }
  if (!(*abort))
    nl();
}

void outchr(char ch)
{
  printf("%c",ch);
}
