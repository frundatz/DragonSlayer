#include "skel.c"
#include "dra_fcns.h"
#include "vardec.h"

#define VER "v2.0"
char temps[81];
int tempi,menu,strength=3,agility=3,health=3,u_weapon,u_armor,u_bow,package,
    done,damage,d_health=43,paces=9,dragon_type,advancing;
static char sword[3][15] =
      {  "Dragonlance",
         "Long Sword",
         "Dagger" };
static char armor[3][15] =
      {  "Chain Mail",
         "Solamnic Plate",
         "Cloth" };
static char bow[3][15] =
      {  "Short Bow",
         "Long Bow",
         "Enchanted Bow" };
struct {
  char user_name[30];
  int result;
} log;

FILE *fptr;

#include "dra_util.c"

void main()
{
  char s[81];
  int points_dist,times=0,count;

  if (read_in_data("chain.txt")==-1) {
    printf("\nData file not found\n\n");
    abort();
  }

  randomize();
  fptr = fopen("DRAGON\\DRAGON.CFG","rb");
    fread(&info,sizeof(info),1,fptr);
  if(access("DRAGON\\DRAGON.LOG",0) !=0)
    write_new_day();
  else {
    if(compare_date()) {
      fptr=fopen("DRAGON\\DRAGON.LOG","rb");
      while(fread(&log,sizeof(log),1,fptr)==1)
        if(strcmp(name,log.user_name)==0)
          ++times;
      fclose(fptr);
    }
  }

  gold -= 1000;
  if (gold < 0)
    gold = 0;
  outchr(12);
  pl("7=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
  pl("0                         Dragon Slayer v2.0");
  pl("                        By The Archaic Knight");
  pl("7=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
  nl();
  if((times > (info.plays - 1)) && sl < 255) {
    sprintf(temps,"Sorry, ye may play but %d times per day!",info.plays);
    pl(temps);
    nl();
    exit(0);
  }
  outstr("0Instructions7?0 ");
  if (yn()) {
    outchr(12);
    printfile("DRAGON\\DRAGON.DOC");
    nl();
    pausescr();
  }
  nl();
  points_dist=41;
  outchr(12);
  do {
  nl();
  sprintf(temps,"Ye have %i points to distribute.",points_dist);
  pl(temps);
  nl();
  sprintf(temps,"017.0  Health7:0   -7>0 %i",health);
  pl(temps);
  sprintf(temps,"027.0  Strength7:0 -7>0 %i",strength);
  pl(temps);
  sprintf(temps,"037.0  Agility7:0  -7>0 %i",agility);
  pl(temps);
  pl("0Q7.0  Quit back to BBS");
  nl();
  outstr("Choose -7>0 ");
  menu = onek("123Q");
  switch (menu) {
    case '1':
      tempi=stat_change("health",points_dist);
      if((tempi + health) > 30) {
	nl();
	pl("Nobody's THAT healthy!");
	nl();
      }
      else {
        points_dist -= tempi;
        health += tempi;
      }
      break;
    case '2':
      tempi=stat_change("strength",points_dist);
      points_dist -= tempi;
      strength += tempi;
      break;
    case '3':
      tempi=stat_change("agility",points_dist);
      points_dist -= tempi;
      agility += tempi;
      break;
    case 'Q':
      exit(0);
      break;
    }
  } while (points_dist > 0);
  nl();
  done=1;
  do {
    outstr("Which package dost thou wish 7(3?0 - List7)0? ");
    menu = onek("123?");
    if (menu == '?') {
      outchr(12);
      nl();
      pl("The Solamnic Council offers thee three equipment packages.  They are:");
      nl();
      tempi=0;
      do {
        sprintf(temps,"7[0Package #%d7]0",tempi+1);
        pl(temps);
        sprintf(temps,"  Sword     7:0  %s",sword[tempi]);
        pl(temps);
        sprintf(temps,"  Bow       7:0  %s",bow[tempi]);
        pl(temps);
        sprintf(temps,"  Armor     7:0  %s",armor[tempi]);
        pl(temps);
        nl();
        ++tempi;
      } while (tempi < 3);
      done=1;
    }
    switch(menu) {
      case '1':
        u_weapon=3;
        u_armor=2;
        u_bow=1;
        package=0;
        done=0;
        break;
      case '2':
        u_weapon=1;
        u_armor=3;
        u_bow=2;
        package=1;
        done=0;
        break;
      case '3':
        u_weapon=2;
        u_armor=1;
        u_bow=3;
        package=2;
        done=0;
        break;
    }
  }  while (done);
  outchr(12);
  print_stats(0);
  count = 0;
  fptr = fopen("DRAGON\\DRAGON.DAT","rb");
  while(fread(&dragon,sizeof(dragon),1,fptr) != 0)
    ++count;
  dragon_type = random(count);
  tempi = dragon_type * sizeof(dragon);
  fseek(fptr, tempi, SEEK_SET);
  fread(&dragon,sizeof(dragon),1,fptr);
  fclose(fptr);
  d_health += dragon.health;
  nl();
  nl();
  outstr("Ye descend into the depths...");
  nl();
  nl();
  sprintf(temps,"Thou see'st a %s Dragon!",dragon.type);
  pl(temps);
  done=0;
  do {
    print_stats(1);
    nl();
    outstr("Thy Move 7[1A0,1R0,7F0,1T0,1?7]0-> ");
    menu=onek("ARFT?");
    switch (menu) {
      case '?':
	nl();
	pl("A7]0dvance one pace.");
        pl("R7]0etreat one pace.");
	pl("F7]0ire bow");
	pl("T7]0hrust with sword.");
	pl("?7]0 This Menu");
	break;
      case 'A':
	if (paces<2) {
	  nl();
	  pl("Thou'rt as close as ye want to get3!0");
	  break;
	}
	else {
	  --paces;
          nl();
	  pl("Ye advance upon the dragon...");
          nl();
          advancing = 1;
          dragon_turn();
          advancing = 0;
	}
        break;
      case 'R':
	if (paces>8) {
	  nl();
	  pl("Coward!  Ye run away!");
	  done=1;
          nl();
	  break;
	}
	else {
	  ++paces;
          nl();
	  pl("Ye retreat from the dragon...");
	  dragon_turn();
	}
        break;
      case 'F':
	nl();
        if (paces > 6) {
        damage=(agility/4.65) + (u_bow * 2)+random(4);
        damage += dragon.b_adjust;
        if(damage < 1)
	  damage = 1;
        sprintf(temps,"Ye fire thy %s for %d damage...",bow[package],damage);
	pl(temps);
        nl();
	d_health -= damage;
        dragon_turn();
        } else
          pl("Thou art too close to use thy bow3!0");
	break;
      case 'T':
	nl();
        if (paces < 7) {
	  damage=(strength/3.35) + (u_weapon * 3)+random(3);
          damage += dragon.s_adjust;
          if(damage < 1)
	    damage = 1;
          sprintf(temps,"Ye thrust with thy %s for %d damage...",sword[package],damage);
          pl(temps);
          nl();
          d_health=d_health-damage;
          dragon_turn();
	}
        else
	  pl("Ye must be within 6 paces to thrust3!0");
	break;
    }
  } while ((health > 0) && (d_health >0) && (!done));
  if (d_health < 1) {
    nl();
    pl("The Dragon falls dead at thy feet...");
    nl();
    pl("The Solamnic Council awards thee 5,000 gold pieces for thy deed.");
    tempi = dragon.hoard + (random(200)+1);
    tempi -= (random(200)+1);
    nl();
    sprintf(temps,"Ye find %d gold in the dragon's lair!",tempi);
    pl(temps);
    gold += 6000;
    gold += tempi;
    log.result = 1;
  }
  if (health < 1) {
    nl();
    pl("Ye fall to thy knees...6DEAD0...");
    log.result = 2;
  }
  if (done == 1) {
    nl();
    pl("The Solamnic Council refuses to refund thy money for the equipment!");
    log.result = 3;
  }
  nl();
  end_session();
}

void dragon_turn()
{
  int attack;
  char method[30];

  if (d_health > 0) {
  attack=random(100);
  if(attack < dragon.b_chance)
    attack = 1;
  if((attack >= dragon.b_chance) &&
     (attack < (dragon.b_chance + dragon.c_chance)))
    attack = 2;
  if((attack >= (dragon.b_chance + dragon.c_chance)) &&
     (attack < (dragon.b_chance + dragon.c_chance + dragon.t_chance)))
    attack = 3;
  switch (attack) {
    case 1:
      strcpy(method,dragon.attack);
      tempi=random(5);
      damage=6+tempi-u_armor;
      damage += dragon.b_adjust;
      break;
    case 2:
      strcpy(method,"rakes his claws on thee");
      tempi=random(3);
      damage=5+tempi-u_armor;
      damage += dragon.c_adjust;
      break;
    case 3:
      strcpy(method,"bites thee");
      tempi=random(4);
      damage=5+tempi-u_armor;
      damage += dragon.t_adjust;
      break;
  }

  if(advancing == 1)
    damage -= random(3);
  if(damage < 1)
    damage = 1;

  sprintf(temps,"The dragon %s for %d damage...",method,damage);
  pl(temps);
  health -= damage;
  }
}


void print_stats(int i)
{
  nl();
  if (!i) {
    pl("Thy Statistics3:0");
    nl();
  }
  sprintf(temps,"Health   7:0 %d Hit Points",health);
  pl(temps);
  if (!i) {
    sprintf(temps,"Strength 7:0 %d",strength);
    pl(temps);
    sprintf(temps,"Agility  7:0 %d",agility);
    pl(temps);
  }
  if (i) {
    sprintf(temps,"Dragon   3:0 %d Hit Points",d_health);
    pl(temps);
    nl();
    sprintf(temps,"Paces    1:0 %d",paces);
    pl(temps);
  }
  else {
    nl();
    pl("Thy Equipment7:0");
    nl();
    sprintf(temps,"Sword    7:0 %s",sword[package]);
    pl(temps);
    sprintf(temps,"Armor    7:0 %s",armor[package]);
    pl(temps);
    sprintf(temps,"Bow      7:0 %s",bow[package]);
    pl(temps);
    nl();
    pausescr();
  }
}

int stat_change(char *stat,int max)
{
  char add[3];
  int addi;

  nl();
  sprintf(temps,"3[0Max = %d3]0 Add how much to %s? ",max,stat);
  outstr(temps);
  input(add,2);
  addi=atoi(add);
  if ((addi < 1) || (addi > max)) {
    nl();
    pl("6- 0\x1B[4mAborted\x1B[0m 6-0");
    return(0);
  }
  return (addi);
}

void write_new_day()
{
  struct date date;

  getdate(&date);
  sprintf(log.user_name,"%d%d%d",date.da_day,date.da_mon,date.da_year);
  log.result = 0;

  fptr=fopen("DRAGON\\DRAGON.LOG","wb");
  fwrite(&log, sizeof(log), 1, fptr);
  fclose(fptr);
}

int compare_date()
{
  char comp_date[15];
  struct date date;

  getdate(&date);
  sprintf(comp_date,"%d%d%d",date.da_day,date.da_mon,date.da_year);
  fptr=fopen("DRAGON\\DRAGON.LOG","rb");
  fread(&log,sizeof(log),1,fptr);
  fclose(fptr);
  if(strcmp(comp_date,log.user_name)==0)
    return(1);
  write_new_day();
  return(0);
}

void end_session()
{
  nl();
  sprintf(temps,"Returning to %s...",info.bbs_name);
  outstr(temps);
  write_points();
  strcpy(log.user_name, name);
  fptr=fopen("DRAGON\\DRAGON.LOG","ab");
  fwrite(&log, sizeof(log), 1, fptr);
  fclose(fptr);
  nl();
}
