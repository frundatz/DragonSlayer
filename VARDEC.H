/* Variable Declarations for Dragon Slayer */

struct {
  char type[15];        /* Dragon Type */
  char health;		/* Health Adjustment */
  char b_adjust;        /* Breath Weapon Adjustment */
  char t_adjust;	/* Teeth Adjustment */
  char c_adjust;	/* Claw Adjustment */
  char b_chance;	/* Chance in 100 to use Breath Weapon */
  char t_chance;	/* Chance in 100 to use Teeth */
  char c_chance;	/* Chance in 100 to use Claws */
  char f_adjust;	/* Bow Fire Adjustment */
  char s_adjust;	/* Sword Adjustment */
  int hoard;		/* Gold dragon is storing */
  char attack[30];      /* Attack Announcement */
} dragon;

struct {
  char bbs_name[30];       /* BBS Name */
  char registration[20];   /* Registration Number */
  char plays;	           /* Plays Per Day */
} info;
