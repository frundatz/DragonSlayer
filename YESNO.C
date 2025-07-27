
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
