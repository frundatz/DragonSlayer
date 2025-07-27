#include <stdio.h>
#include <fcntl.h>
#include <sys\stat.h>
#include "vardec.h"

void main();
void set_up_data();
void set_up_cfg();
void show_dragon(int number);
void list_dragons();
void edit_dragons();
int load_dragon(int number);
void configure_game();
FILE *datptr;
FILE *cfgptr;
char changes;

void main()
{
  unsigned char ch,done=1;
  char temps[81];

  if(access("DRAGON.DAT", 4) != 0)
    set_up_data();
  if(access("DRAGON.CFG", 4) != 0)
    set_up_cfg();

 cfgptr = fopen("DRAGON.CFG", "r+b");
 datptr = fopen("DRAGON.DAT", "r+b");

  fread(&info,sizeof(info),1,cfgptr);
  clrscr();
  printf("\nDragon Slayer Initialization - (C) 1991  The Archaic Knight");
  do {
    printf("\n\nSelection > ");
    ch = getche();
    switch(ch) {
      case 'l':
      case 'L':
        list_dragons();
        break;
      case 'q':
      case 'Q':
        fclose(datptr);
        fclose(cfgptr);
	printf("\n\n");
        done = 0;
        break;
      case '?':
        printf("\n\nC>onfiguration Editor");
        printf("\nE>dit Dragon");
	printf("\nL>ist Dragons");
	printf("\nQ>uit");
	break;
      case 'e':
      case 'E':
        edit_dragons();
        break;
      case 'c':
      case 'C':
	configure_game();
	break;
    }
  } while(done);
}

void set_up_data()
{
  FILE *fptr;

  fptr = fopen("DRAGON.DAT", "wb");
  strcpy(dragon.type,"Red");
  dragon.health = 3;
  dragon.b_adjust = 0;
  dragon.t_adjust = 2;
  dragon.c_adjust = 0;
  dragon.b_chance = 30;
  dragon.t_chance = 50;
  dragon.c_chance = 20;
  dragon.f_adjust = -3;
  dragon.s_adjust = 2;
  dragon.hoard = 1200;
  strcpy(dragon.attack,"breathes fire upon thee");
  fwrite(&dragon, sizeof(dragon), 1, fptr);
  strcpy(dragon.type,"Black");
  dragon.health = -2;
  dragon.b_adjust = 2;
  dragon.t_adjust = -1;
  dragon.c_adjust = 1;
  dragon.b_chance = 50;
  dragon.t_chance = 24;
  dragon.c_chance = 26;
  dragon.f_adjust = -2;
  dragon.s_adjust = -1;
  dragon.hoard = 1500;
  strcpy(dragon.attack,"spits acid upon thee");
  fwrite(&dragon,sizeof(dragon),1,fptr);
  strcpy(dragon.type,"Green");
  dragon.health = 0;
  dragon.b_adjust = -1;
  dragon.t_adjust = 1;
  dragon.c_adjust = 3;
  dragon.b_chance = 20;
  dragon.t_chance = 20;
  dragon.c_chance = 60;
  dragon.f_adjust = 1;
  dragon.s_adjust = -2;
  dragon.hoard = 1000;
  strcpy(dragon.attack,"envelopes thee in gas");
  fwrite(&dragon,sizeof(dragon),1,fptr);
  fclose(fptr);
}

void set_up_cfg()
{
  FILE *fptr;

  fptr = fopen("DRAGON.CFG", "wb");
  strcpy(info.bbs_name, "The BBS");
  strcpy(info.registration,"None");
  info.plays = 3;
  fwrite(&info, sizeof(info),1,fptr);
  fclose(fptr);
}



void show_dragon(int number)
{
  printf(" 1] Dragon Type:          %s #%d\n",dragon.type,number);
  printf(" 2] Health Adjustment: %4d      ",dragon.health);
  printf(" 3] Breath Adjustment: %4d\n",dragon.b_adjust);
  printf(" 4] Teeth Adjustment:  %4d      ",dragon.t_adjust);
  printf(" 5] Claw Adjustment:   %4d\n",dragon.c_adjust);
  printf(" 6] Breath Chance:     %4d%     ",dragon.b_chance);
  printf(" 7] Teeth Chance:      %4d%\n",dragon.t_chance);
  printf(" 8] Claw Chance:       %4d%     ",dragon.c_chance);
  printf(" 9] Bow Adjustment:    %4d\n",dragon.f_adjust);
  printf("10] Sword Adjustment:  %4d      ",dragon.s_adjust);
  printf("11] Gold in Hoard:     %4d\n",dragon.hoard);
  printf("12] Attack String:       %s",dragon.attack);
}

void list_dragons()
{
  char count=1;

  fseek(datptr,0L,SEEK_SET);
  while(fread(&dragon,sizeof(dragon),1,datptr) == 1) {
    printf("\n\n");
    show_dragon(count);
    printf("\nHit Any Key.");
    getch();
    ++count;
  }
}


void edit_dragons()
{
  char temps[30],done=1;
  int dragon_number,tempi;

  changes = 0;
  printf("\n\nEnter Dragon Number to Edit]> ");
  gets(temps);
  strupr(temps);
  dragon_number = atoi(temps);
  if((dragon_number > 15) || (dragon_number < 1))
    return;
  load_dragon(dragon_number);
  do {
    clrscr();
    show_dragon(dragon_number);
    printf("\nEnter # to Edit -> ");
    gets(temps);
    strupr(temps);
    if(strlen(temps) < 1)
      done = 0;
    else {
      tempi = atoi(temps);
      switch(tempi) {
        case 1:
          printf("\n\nEnter new type> ");
          gets(temps);
          if(strlen(temps) > 2) {
           strcpy(dragon.type, temps);
           changes = 1;
 	  }
          break;
        case 2:
          dragon.health = edit_value("health");
          break;
        case 3:
          dragon.b_adjust = edit_value("breath adjustment");
          break;
        case 4:
	  dragon.t_adjust = edit_value("teeth adjustment");
	  break;
	case 5:
	  dragon.c_adjust = edit_value("claw adjustment");
	  break;
        case 6:
	  dragon.b_chance = edit_value("breath weapon chance");
	  break;
	case 7:
	  dragon.t_chance = edit_value("teeth chance");
	  break;
	case 8:
	  dragon.c_chance = edit_value("claw chance");
	  break;
	case 9:
          dragon.f_adjust = edit_value("bow adjustment");
	  break;
	case 10:
	  dragon.s_adjust = edit_value("sword adjustment");
	  break;
	case 11:
	  dragon.hoard = edit_value("gold in hoard");
	  break;
        case 12:
          printf("\n\nEnter new attack> ");
	  gets(temps);
          if(strlen(temps) > 2) {
	    strcpy(dragon.attack,temps);
	    changes = 1;
	  }
	  break;
      }
    }
  } while(done);
  if(changes) {
    printf("\n\nSave changes [Y/n]? ");
    done = getche();
    if((done == 'n') || (done == 'N'))
      return;
    tempi = (dragon_number - 1) * sizeof(dragon);
    fseek(datptr,tempi,SEEK_SET);
    fwrite(&dragon,sizeof(dragon),1,datptr);
  }
}


int load_dragon(int number)
{
  int offset;

  offset = (number-1) * sizeof(dragon);

  if(fseek(datptr,offset,SEEK_SET) != 0) {
    printf("\n\nInvalid Dragon Number!");
    return(1);
  }
  fread(&dragon,sizeof(dragon),1,datptr);
}

int edit_value(char *stats)
{
  char temps[10];

  changes = 1;
  printf("\n\nEnter new value for %s : ",stats);
  gets(temps);
  return(atoi(temps));
}

void configure_game()
{
  char done=1,tempc,temps[30];

  clrscr();
  printf("\nDragon Slayer Game Configuration");
  do {
    printf("\n\n[Config] Selection > ");
    tempc = getche();
    switch(tempc) {
      case '?':
	printf("\n\n1] BBS Name            : %s",info.bbs_name);
	printf("\n2] Registration Number : %s",info.registration);
	printf("\n3] Plays Per Day       : %d\n",info.plays);
	break;
      case '1':
	printf("\n\nEnter BBS Name: ");
	gets(temps);
	if(strlen(temps) > 2)
	  strcpy(info.bbs_name,temps);
	break;
      case '2':
	printf("\n\nEnter Registration Number: ");
	gets(temps);
	if(strlen(temps) > 2)
	  strcpy(info.registration,temps);
        else
	  strcpy(info.registration,"None");
	break;
      case '3':
	printf("\n\nEnter plays per day: ");
	gets(temps);
        if((atoi(temps) > 0) && (atoi(temps) < 11))
	  info.plays = atoi(temps);
	break;
      case 'q':
      case 'Q':
	done = 0;
	break;
    }
  } while(done);

  fseek(cfgptr, 0, SEEK_SET);
  fwrite(&info, sizeof(info), 1, cfgptr);
}

