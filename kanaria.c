// Dungeon crawler

/*
TODO:
weapons, armor, sets of armor, monster drops, chests, special effects, mutated monsters
more importance on def
*/

/*
Errors:
none :D
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

/*
-----------------------------------------------------------------------------------------------------------------------------------------------------------------
*/

#define TITLE "KANARIA"
#define or ||
#define and &&
#define elif else if


#define class_num 4


#define debug_printf(...) printf("DEBUG: " __VA_ARGS__);
#define TITLE_ART "     .                     _..._                     .--.           \n\
   .\'|                   .\'     \'.                   |__|           \n\
 .\'  |                  .   .-.   .          .-,.--. .--.           \n\
<    |            __    |  \'   \'  |    __    |  .-. ||  |    __     \n\
 |   | ____    .:--.\'.  |  |   |  | .:--.\'.  | |  | ||  | .:--.\'.   \n\
 |   | \\ .\'   / |   \\ | |  |   |  |/ |   \\ | | |  | ||  |/ |   \\ |  \n\
 |   |/  .    `\" __ | | |  |   |  |`\" __ | | | |  \'- |  |`\" __ | |  \n\
 |    /\\  \\    .\'.\'\'| | |  |   |  | .\'.\'\'| | | |     |__| .\'.\'\'| |  \n\
 |   |  \\  \\  / /   | |_|  |   |  |/ /   | |_| |         / /   | |_ \n\
 \'    \\  \\  \\ \\ \\._,\\ \'/|  |   |  |\\ \\._,\\ \'/|_|         \\ \\._,\\ \'/ \n\
\'------\'  \'---\'`--\'  `\" \'--\'   \'--\' `--\'  `\"              `--\'  `\"  \n\
"
//Regular text
#define BLK "\e[0;30m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"
#define WHT "\e[0;37m"

//Regular bold text
#define BBLK "\e[1;30m"
#define BRED "\e[1;31m"
#define BGRN "\e[1;32m"
#define BYEL "\e[1;33m"
#define BBLU "\e[1;34m"
#define BMAG "\e[1;35m"
#define BCYN "\e[1;36m"
#define BWHT "\e[1;37m"

//Regular underline text
#define UBLK "\e[4;30m"
#define URED "\e[4;31m"
#define UGRN "\e[4;32m"
#define UYEL "\e[4;33m"
#define UBLU "\e[4;34m"
#define UMAG "\e[4;35m"
#define UCYN "\e[4;36m"
#define UWHT "\e[4;37m"

//Regular background
#define BLKB "\e[40m"
#define REDB "\e[41m"
#define GRNB "\e[42m"
#define YELB "\e[43m"
#define BLUB "\e[44m"
#define MAGB "\e[45m"
#define CYNB "\e[46m"
#define WHTB "\e[47m"

//High intensty background
#define BLKHB "\e[0;100m"
#define REDHB "\e[0;101m"
#define GRNHB "\e[0;102m"
#define YELHB "\e[0;103m"
#define BLUHB "\e[0;104m"
#define MAGHB "\e[0;105m"
#define CYNHB "\e[0;106m"
#define WHTHB "\e[0;107m"

//High intensty text
#define HBLK "\e[0;90m"
#define HRED "\e[0;91m"
#define HGRN "\e[0;92m"
#define HYEL "\e[0;93m"
#define HBLU "\e[0;94m"
#define HMAG "\e[0;95m"
#define HCYN "\e[0;96m"
#define HWHT "\e[0;97m"

//Underline high intensity text
#define UHBLK "\e[4;90m"
#define UHRED "\e[4;91m"
#define UHGRN "\e[4;92m"
#define UHYEL "\e[4;93m"
#define UHBLU "\e[4;94m"
#define UHMAG "\e[4;95m"
#define UHCYN "\e[4;96m"
#define UHWHT "\e[4;97m"

//Bold high intensity text
#define BHBLK "\e[1;90m"
#define BHRED "\e[1;91m"
#define BHGRN "\e[1;92m"
#define BHYEL "\e[1;93m"
#define BHBLU "\e[1;94m"
#define BHMAG "\e[1;95m"
#define BHCYN "\e[1;96m"
#define BHWHT "\e[1;97m"

//Style
#define UNDERLINE "\e[4m"
#define BOLD "\e[1m"

//Reset
#define RESET "\e[0m"

//Cursor
#define cursor_hide "\e[?25l"
#define cursor_show "\e[?25h"

/*
-----------------------------------------------------------------------------------------------------------------------------------------------------------------
*/

/*
name: name
class_name: name of class
max_HP: max HP
HP: current health points
max_MP: max MP
MP: current magic points
ATK: attack power
DEF: defense
DEX: dexterity (accuracy, evasion, crit)
LUCK: luck (loot, chests, random event)
*/

typedef struct {
	char attack_name[24];
	char attack_name_color[32];
	int mana_use;
	int attack_percent;
} Attack;

typedef struct {
	char action_name[24];
	char action_name_color[32];
	int mana_use;
	void (*act)(int);
} Action;

typedef struct {
	int index;
	char name[24];
	char name_color[32];
	char class_name[16];
	char class_name_color[32];
	int attack_num;
	Attack *attack;
	int action_num;
	Action *action;
	int max_HP;
	int HP;
	int max_MP;
	int MP;
	int ATK;
	int DEF;
	int DEX;
	int LUCK;
} Character;

typedef struct {
	char name[32];
	char name_color[48];
	int max_HP;
	int HP;
	int ATK;
	int DEF;
	int DEX;
} Enemy;

/*
-----------------------------------------------------------------------------------------------------------------------------------------------------------------
*/

int i, j;
char *y_n;
Character Player;
Character *classes;
Enemy enemy;
char **colors;
int *enemy_type_num;
int *encounter_num;
int *temp_ATK;
int *temp_DEF;
int *temp_DEX;
int *temp_LUCK;

/*
-----------------------------------------------------------------------------------------------------------------------------------------------------------------
*/

void delay(int);								// delays the program (milliseconds)
int random_num(int, int, int);					// generates a random number (min, max, diff)
int str_in_array(char*, char**, int);			// checks if a string is in an array; returns -1: not in array, else returns index of first occurence; (string, array, array length)
int yn_yes();									// converts y_n to true or false; 1:true, 0:false, -1:invalid input
void welcome();									// welcoming screen
void initialize();								// prints area, enemy stats, player stats, options
void clear();									// clears screen
int play_start();								// prints "Play? [y/n]" and takes input; returns 1:play, 0: quit
void character_select();						// character selection screen and character initialization
void class_info(Character);							// prints class info (class index)
void clear_newline();							// clears '\n' character so fgets() doesn't read it
void delete_leading_newline(char*);				// clears leading '\n' character from fgets() input; (string)
//char *change_color(char*, char*);				// returns string with different color; (string, color)
void generate_enemy();							// randomly generates an enemy between pre-determined choices
int player_action();							// the player does an action; returns -1: unable to do action / repeat, 0: enemy dead , 1:success, 2: ran away; (action name)
int enemy_action();								// the enemy does a random action; returns 0: player dead, 1: success
int battle();									// initiates battle with enemy; returns 0: dead, 1: victory, 2: ran away
void fgets_reset(char*, int);					// resets stdin after using fgets; (string, input length)
int player_attack(Attack);						// attacks with given attack type; returns 0: win, 1: success; (attack type)
void low_heal(int);								// heals the player a little bit; (mana use)
void high_heal(int);							// heals the player a decent amount; (mana use)
void mana_restore(int);							// restores mana; (mana use)
void strengthen(int);							// increases attack; (mana use)
void reinforce(int);							// increases defense; (mana use)
void focus(int);								// increases dexterity; (mana use)
void pray(int);									// increases luck; (mana use)

/*
-----------------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------------
*/

int main(int argc, char *argv[])
{
	int battle_result;
	y_n = (char*)malloc(sizeof(char));
	classes = (Character*)malloc(class_num * sizeof(Character));
	enemy_type_num = (int*)malloc(sizeof(int));
	encounter_num = (int*)malloc(sizeof(int));
	temp_ATK = (int*)malloc(sizeof(int));
	temp_DEF = (int*)malloc(sizeof(int));
	temp_DEX = (int*)malloc(sizeof(int));
	temp_LUCK = (int*)malloc(sizeof(int));
	colors = (char**)malloc(8 * sizeof(char*));

	char *colors_temp[8] = {BLK, RED, GRN, YEL, BLU, MAG, CYN, WHT};
	for(i = 0; i < 8; i++)
	{
		colors[i] = (char*)malloc(16 * sizeof(char));
		strcpy(colors[i], colors_temp[i]);
	}

	int low_heal_mana = 200,
		high_heal_mana = 500,
		mana_restore_mana = 0,
		strengthen_mana = 100,
		reinforce_mana = 100,
		focus_mana = 100,
		pray_mana = 100;

	*enemy_type_num = 3;
	*encounter_num = 0;

	Player.attack = (Attack*)malloc(sizeof(Attack));
	Player.action = (Action*)malloc(sizeof(Action));

	//--------------------------------------
	classes[0].index = 0;
	strcpy(classes[0].class_name_color, HBLU);
	strcat(classes[0].class_name_color, "Knight");
	strcpy(classes[0].class_name, "Knight");
	strcat(classes[0].class_name_color, RESET);


	classes[0].attack_num = 2;
	classes[0].attack = (Attack*)malloc(classes[0].attack_num * sizeof(Attack));

	strcpy(classes[0].attack[0].attack_name, "slash");
	strcpy(classes[0].attack[0].attack_name_color, HWHT);
	strcat(classes[0].attack[0].attack_name_color, classes[0].attack[0].attack_name);
	strcat(classes[0].attack[0].attack_name_color, RESET);
	classes[0].attack[0].mana_use = 0;
	classes[0].attack[0].attack_percent = 100;

	strcpy(classes[0].attack[1].attack_name, "magic slash");
	strcpy(classes[0].attack[1].attack_name_color, HBLU);
	strcat(classes[0].attack[1].attack_name_color, classes[0].attack[1].attack_name);
	strcat(classes[0].attack[1].attack_name_color, RESET);
	classes[0].attack[1].mana_use = 150;
	classes[0].attack[1].attack_percent = 150;


	classes[0].action_num = 4;
	classes[0].action = (Action*)malloc(classes[0].action_num * sizeof(Action));

	strcpy(classes[0].action[0].action_name, "low heal");
	strcpy(classes[0].action[0].action_name_color, GRN);
	strcat(classes[0].action[0].action_name_color, classes[0].action[0].action_name);
	strcat(classes[0].action[0].action_name_color, RESET);
	classes[0].action[0].mana_use = low_heal_mana;
	classes[0].action[0].act = low_heal;

	strcpy(classes[0].action[1].action_name, "mana restore");
	strcpy(classes[0].action[1].action_name_color, CYN);
	strcat(classes[0].action[1].action_name_color, classes[0].action[1].action_name);
	strcat(classes[0].action[1].action_name_color, RESET);
	classes[0].action[1].mana_use = mana_restore_mana;
	classes[0].action[1].act = mana_restore;

	strcpy(classes[0].action[2].action_name, "reinforce");
	strcpy(classes[0].action[2].action_name_color, HBLU);
	strcat(classes[0].action[2].action_name_color, classes[0].action[2].action_name);
	strcat(classes[0].action[2].action_name_color, RESET);
	classes[0].action[2].mana_use = reinforce_mana;
	classes[0].action[2].act = reinforce;

	strcpy(classes[0].action[3].action_name, "pray");
	strcpy(classes[0].action[3].action_name_color, HYEL);
	strcat(classes[0].action[3].action_name_color, classes[0].action[3].action_name);
	strcat(classes[0].action[3].action_name_color, RESET);
	classes[0].action[3].mana_use = pray_mana;
	classes[0].action[3].act = pray;


	classes[0].max_HP = 2500;
	classes[0].HP = classes[0].max_HP;
	classes[0].max_MP = 1100;
	classes[0].MP = classes[0].max_MP;
	classes[0].ATK = 210;
	classes[0].DEF = 250;
	classes[0].DEX = 140;
	classes[0].LUCK = 90;

	//--------

	classes[1].index = 1;
	strcpy(classes[1].class_name_color, CYN);
	strcat(classes[1].class_name_color, "Wizard");
	strcpy(classes[1].class_name, "Wizard");
	strcat(classes[1].class_name_color, RESET);

	classes[1].attack_num = 3;
	classes[1].attack = (Attack*)malloc(classes[1].attack_num * sizeof(Attack));

	strcpy(classes[1].attack[0].attack_name, "mana blast");
	strcpy(classes[1].attack[0].attack_name_color, HBLU);
	strcat(classes[1].attack[0].attack_name_color, classes[1].attack[0].attack_name);
	strcat(classes[1].attack[0].attack_name_color, RESET);
	classes[1].attack[0].mana_use = 50;
	classes[1].attack[0].attack_percent = 100;

	strcpy(classes[1].attack[1].attack_name, "fire ball");
	strcpy(classes[1].attack[1].attack_name_color, HRED);
	strcat(classes[1].attack[1].attack_name_color, classes[1].attack[1].attack_name);
	strcat(classes[1].attack[1].attack_name_color, RESET);
	classes[1].attack[1].mana_use = 100;
	classes[1].attack[1].attack_percent = 150;

	strcpy(classes[1].attack[2].attack_name, "staff bash");
	strcpy(classes[1].attack[2].attack_name_color, HWHT);
	strcat(classes[1].attack[2].attack_name_color, classes[1].attack[2].attack_name);
	strcat(classes[1].attack[2].attack_name_color, RESET);
	classes[1].attack[2].mana_use = 0;
	classes[1].attack[2].attack_percent = 50;


	classes[1].action_num = 6;
	classes[1].action = (Action*)malloc(classes[1].action_num * sizeof(Action));

	strcpy(classes[1].action[0].action_name, "low heal");
	strcpy(classes[1].action[0].action_name_color, GRN);
	strcat(classes[1].action[0].action_name_color, classes[1].action[0].action_name);
	strcat(classes[1].action[0].action_name_color, RESET);
	classes[1].action[0].mana_use = low_heal_mana;
	classes[1].action[0].act = low_heal;

	strcpy(classes[1].action[1].action_name, "high heal");
	strcpy(classes[1].action[1].action_name_color, HGRN);
	strcat(classes[1].action[1].action_name_color, classes[1].action[1].action_name);
	strcat(classes[1].action[1].action_name_color, RESET);
	classes[1].action[1].mana_use = high_heal_mana;
	classes[1].action[1].act = high_heal;

	strcpy(classes[1].action[2].action_name, "mana restore");
	strcpy(classes[1].action[2].action_name_color, CYN);
	strcat(classes[1].action[2].action_name_color, classes[1].action[2].action_name);
	strcat(classes[1].action[2].action_name_color, RESET);
	classes[1].action[2].mana_use = mana_restore_mana;
	classes[1].action[2].act = mana_restore;

	strcpy(classes[1].action[3].action_name, "strengthen");
	strcpy(classes[1].action[3].action_name_color, HRED);
	strcat(classes[1].action[3].action_name_color, classes[1].action[3].action_name);
	strcat(classes[1].action[3].action_name_color, RESET);
	classes[1].action[3].mana_use = strengthen_mana;
	classes[1].action[3].act = strengthen;

	strcpy(classes[1].action[4].action_name, "reinforce");
	strcpy(classes[1].action[4].action_name_color, HBLU);
	strcat(classes[1].action[4].action_name_color, classes[1].action[4].action_name);
	strcat(classes[1].action[4].action_name_color, RESET);
	classes[1].action[4].mana_use = reinforce_mana;
	classes[1].action[4].act = reinforce;

	strcpy(classes[1].action[5].action_name, "pray");
	strcpy(classes[1].action[5].action_name_color, HYEL);
	strcat(classes[1].action[5].action_name_color, classes[1].action[5].action_name);
	strcat(classes[1].action[5].action_name_color, RESET);
	classes[1].action[5].mana_use = pray_mana;
	classes[1].action[5].act = pray;


	classes[1].max_HP = 1800;
	classes[1].HP = classes[1].max_HP;
	classes[1].max_MP = 1500;
	classes[1].MP = classes[1].max_MP;
	classes[1].ATK = 250;
	classes[1].DEF = 130;
	classes[1].DEX = 180;
	classes[1].LUCK = 110;

	//--------

	classes[2].index = 2;
	strcpy(classes[2].class_name_color, HGRN);
	strcat(classes[2].class_name_color, "Thief");
	strcpy(classes[2].class_name, "Thief");
	strcat(classes[2].class_name_color, RESET);

	classes[2].attack_num = 2;
	classes[2].attack = (Attack*)malloc(classes[2].attack_num * sizeof(Attack));

	strcpy(classes[2].attack[0].attack_name, "slash");
	strcpy(classes[2].attack[0].attack_name_color, HWHT);
	strcat(classes[2].attack[0].attack_name_color, classes[2].attack[0].attack_name);
	strcat(classes[2].attack[0].attack_name_color, RESET);
	classes[2].attack[0].mana_use = 0;
	classes[2].attack[0].attack_percent = 100;

	strcpy(classes[2].attack[1].attack_name, "backstab");
	strcpy(classes[2].attack[1].attack_name_color, RED);
	strcat(classes[2].attack[1].attack_name_color, classes[2].attack[1].attack_name);
	strcat(classes[2].attack[1].attack_name_color, RESET);
	classes[2].attack[1].mana_use = 100;
	classes[2].attack[1].attack_percent = 150;


	classes[2].action_num = 4;
	classes[2].action = (Action*)malloc(classes[2].action_num * sizeof(Action));

	strcpy(classes[2].action[0].action_name, "low heal");
	strcpy(classes[2].action[0].action_name_color, GRN);
	strcat(classes[2].action[0].action_name_color, classes[2].action[0].action_name);
	strcat(classes[2].action[0].action_name_color, RESET);
	classes[2].action[0].mana_use = low_heal_mana;
	classes[2].action[0].act = low_heal;

	strcpy(classes[2].action[1].action_name, "mana restore");
	strcpy(classes[2].action[1].action_name_color, CYN);
	strcat(classes[2].action[1].action_name_color, classes[2].action[1].action_name);
	strcat(classes[2].action[1].action_name_color, RESET);
	classes[2].action[1].mana_use = mana_restore_mana;
	classes[2].action[1].act = mana_restore;

	strcpy(classes[2].action[2].action_name, "strengthen");
	strcpy(classes[2].action[2].action_name_color, HRED);
	strcat(classes[2].action[2].action_name_color, classes[2].action[2].action_name);
	strcat(classes[2].action[2].action_name_color, RESET);
	classes[2].action[2].mana_use = strengthen_mana;
	classes[2].action[2].act = strengthen;

	strcpy(classes[2].action[3].action_name, "focus");
	strcpy(classes[2].action[3].action_name_color, HWHT);
	strcat(classes[2].action[3].action_name_color, classes[2].action[3].action_name);
	strcat(classes[2].action[3].action_name_color, RESET);
	classes[2].action[3].mana_use = focus_mana;
	classes[2].action[3].act = focus;


	classes[2].max_HP = 2100;
	classes[2].HP = classes[2].max_HP;
	classes[2].max_MP = 900;
	classes[2].MP = classes[2].max_MP;
	classes[2].ATK = 220;
	classes[2].DEF = 150;
	classes[2].DEX = 210;
	classes[2].LUCK = 130;

	//--------

	classes[3].index = 3;
	strcpy(classes[3].class_name_color, RED);
	strcat(classes[3].class_name_color, "Berserker");
	strcpy(classes[3].class_name, "Berserker");
	strcat(classes[3].class_name_color, RESET);

	classes[3].attack_num = 2;
	classes[3].attack = (Attack*)malloc(classes[3].attack_num * sizeof(Attack));

	strcpy(classes[3].attack[0].attack_name, "slash");
	strcpy(classes[3].attack[0].attack_name_color, HWHT);
	strcat(classes[3].attack[0].attack_name_color, classes[3].attack[0].attack_name);
	strcat(classes[3].attack[0].attack_name_color, RESET);
	classes[3].attack[0].mana_use = 0;
	classes[3].attack[0].attack_percent = 100;

	strcpy(classes[3].attack[1].attack_name, "rage");
	strcpy(classes[3].attack[1].attack_name_color, RED);
	strcat(classes[3].attack[1].attack_name_color, classes[3].attack[1].attack_name);
	strcat(classes[3].attack[1].attack_name_color, RESET);
	classes[3].attack[1].mana_use = 200;
	classes[3].attack[1].attack_percent = 200;


	classes[3].action_num = 4;
	classes[3].action = (Action*)malloc(classes[3].action_num * sizeof(Action));

	strcpy(classes[3].action[0].action_name, "low heal");
	strcpy(classes[3].action[0].action_name_color, GRN);
	strcat(classes[3].action[0].action_name_color, classes[3].action[0].action_name);
	strcat(classes[3].action[0].action_name_color, RESET);
	classes[3].action[0].mana_use = low_heal_mana;
	classes[3].action[0].act = low_heal;

	strcpy(classes[3].action[1].action_name, "mana restore");
	strcpy(classes[3].action[1].action_name_color, CYN);
	strcat(classes[3].action[1].action_name_color, classes[3].action[1].action_name);
	strcat(classes[3].action[1].action_name_color, RESET);
	classes[3].action[1].mana_use = mana_restore_mana;
	classes[3].action[1].act = mana_restore;

	strcpy(classes[3].action[2].action_name, "strengthen");
	strcpy(classes[3].action[2].action_name_color, HRED);
	strcat(classes[3].action[2].action_name_color, classes[3].action[2].action_name);
	strcat(classes[3].action[2].action_name_color, RESET);
	classes[3].action[2].mana_use = strengthen_mana;
	classes[3].action[2].act = strengthen;

	strcpy(classes[3].action[3].action_name, "focus");
	strcpy(classes[3].action[3].action_name_color, HWHT);
	strcat(classes[3].action[3].action_name_color, classes[3].action[3].action_name);
	strcat(classes[3].action[3].action_name_color, RESET);
	classes[3].action[3].mana_use = focus_mana;
	classes[3].action[3].act = focus;


	classes[3].max_HP = 2800;
	classes[3].HP = classes[3].max_HP;
	classes[3].max_MP = 750;
	classes[3].MP = classes[3].max_MP;
	classes[3].ATK = 320;
	classes[3].DEF = 170;
	classes[3].DEX = 90;
	classes[3].LUCK = 90;
	//--------------------------------------

	while(true)
	{
		*temp_ATK = 0;
		*temp_DEF = 0;
		*temp_DEX = 0;
		*temp_LUCK = 0;

		welcome();
		character_select();
		generate_enemy();
		battle_result = battle();
		while(battle_result != 0)
		{
			clear();
			Player.HP += Player.max_HP/4;
			if(Player.HP > Player.max_HP) Player.HP = Player.max_HP;
			Player.MP += Player.max_MP/4;
			if(Player.MP > Player.max_MP) Player.MP = Player.max_MP;
			printf("Your stats have been partially restored.\n");
			delay(5000);
			clear();

			generate_enemy();
			battle_result = battle();
		}

		// when you die
		clear();
		printf("Restart? [y/n] : ");
		while(scanf(" %c", y_n) == 0 or yn_yes() == -1)
		{
			clear_newline();
			printf("invalid input.\n");
			printf("Restart? [y/n]: ");
		}

		if(yn_yes() == 0)
		{
			printf("Thank you for playing.\n");
			delay(3000);
			clear();

			printf(HCYN);
			printf(TITLE_ART);
			printf(RESET);
			delay(5000);
			exit(0);
		}
		else
		{
			delay(1000);
			continue;
		}
	}

	free(y_n);
	free(enemy_type_num);
	free(encounter_num);
	free(classes);
	free(colors);

	return 0;
}

/*
-----------------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------------
*/

void delay(int milliseconds)
{
	time_t start_time = clock();
	while(clock() < start_time + milliseconds);
}

int random_num(int min, int max, int diff)
{
	srand(time(0));
	int num = ( rand() * (diff+1) ) % ( max - min + 1 ) + min;
	if(diff != 0) num = ( random_num(1, 100, 0)*num ) % ( max - min + 1 ) + min;

	return num;
}

int yn_yes()
{
	if(*y_n == 'y' or *y_n == 'Y') return 1;
	else if(*y_n == 'n' or *y_n == 'N') return 0;
	else return -1;
}

int str_in_array(char *string, char **array, int n)
{
	for(i = 0; i < n; i++)
	{
		if(strcmp(array[i], string) == 0)
		{
			return i;
		}
	}

	return -1;
}

void class_info(Character character)
{
	printf("%sClass%s: %s\n%sHealth%s: %s%d%s\n%sMana%s: %s%d%s\n%sStrength%s: %s%d%s\n%sDefense%s: %s%d%s\n%sDexterity%s: %s%d%s\n%sLuck%s: %s%d%s\n",
				HCYN, RESET, character.class_name_color,
				HRED, RESET, HWHT, character.max_HP, RESET,
				HBLU, RESET, HWHT, character.max_MP, RESET,
				RED, RESET, HWHT, character.ATK, RESET,
				BLU, RESET, HWHT, character.DEF, RESET,
				GRN, RESET, HWHT, character.DEX, RESET,
				HYEL, RESET, HWHT, character.LUCK, RESET);

	printf("\n%sAttacks%s:\n", UWHT, RESET);
	for(i = 0; i < character.attack_num; i++)
		printf("%-24s||\t%sattack%s: %4d%%\t%smana%s: %4d%smp%s\n", character.attack[i].attack_name_color, RED, RESET, character.attack[i].attack_percent, HCYN, RESET, character.attack[i].mana_use, CYN, RESET);

	printf("\n");
	for(i = 0; i < character.action_num; i++)
	{
		printf("| %s |  ", character.action[i].action_name_color);
		if(i%3 == 2) printf("\n");
	}
	if(i%3 != 0) printf("\n");
}

void clear_newline()
{
	scanf("%*[^\n]");
	scanf("%*c");
}

void delete_leading_newline(char *str)
{
	str[strcspn(str, "\n")] = '\0';
}

void fgets_reset(char *string, int length)
{
	char temp_char;
	if(strcspn(string, "\0") >= length-1 and scanf("%c", &temp_char) == 1 and temp_char != '\n')
	{
		clear_newline();
	}
}

void initialize()
{
	printf("_________________________________________\n");
	printf("| %-23s\tclass: %-23s\t|\n", Player.name_color, Player.class_name_color);
	printf("| HP: %s%5d/%s%-5d%s  |||\tMP: %s%4d/%s%-4d%s\t|\n", URED, Player.HP, URED, Player.max_HP, RESET, UHBLU, Player.MP, UHBLU, Player.max_MP, RESET);
	printf("|_______________________________________|\n");
	printf("|  %sattack%s  |  %saction%s  |  %sinfo%s  |  %srun%s   |\n", URED, RESET, UHCYN, RESET, UHYEL, RESET, UWHT, RESET);
	printf("|_______________________________________|\n");
	printf(" _______________________ \n");
	printf("/ %-33s\\\n", enemy.name_color);
	printf("| HP: %s%5d/%s%-5d%s\t|\n", URED, enemy.HP, URED, enemy.max_HP, RESET);
	printf("\\_______________________/\n\n");
}

void character_select()
{
	int selection;
	i = 0;
	while(true)
	{
		printf("What is your name?\n");
		printf(HBLU);
		if(i == 0) clear_newline();
		fgets(Player.name, 13, stdin);
		printf(RESET);
		delete_leading_newline(Player.name);
		fgets_reset(Player.name, 13);

		strcpy(Player.name_color, HBLU);
		strcat(Player.name_color, Player.name);
		strcat(Player.name_color, RESET);

		if(strlen(Player.name) < 4)
		{
			clear();
			printf("Name must be at least 4 characters long.\n");
			i = 1;
			continue;
		}
		else
		{
			i = 0;
			printf("\nAre you sure you want your name to be %s?\nYou cannot change this later. [y/n]: ", Player.name_color);
			while(scanf(" %c", y_n) == 0 or yn_yes() == -1)
			{
				printf("invalid input.\n[y/n]: ");
				clear_newline();
			}
			if(yn_yes() == 1)
			{
				clear();
				printf("Welcome %s. \n", Player.name_color);
				break;
			}
			else
			{
				clear();
				continue;
			}
		}
	}

	while(true)
	{
		printf("Choose your %sclass%s.\n", HCYN, RESET);
		printf("1: %s", classes[0].class_name_color);
		for(i = 1; i < class_num; i++)
			printf(", %d: %s", i+1, classes[i].class_name_color);
		printf("\n");

		while(scanf("%d", &selection) == 0 or selection < 1 or selection > class_num)
		{
			clear_newline();
			printf("invalid input\n");
		}

		clear_newline();
		printf("\n");
		class_info(classes[selection-1]);
		printf("\nDo you want to become a %s? [y/n]: ", classes[selection-1].class_name_color);
		while(scanf(" %c", y_n) == 0 or yn_yes() == -1)
		{
			clear_newline();
			printf("invalid input.\n");
			printf("Do you want to become a %s? [y/n]: ", classes[selection-1].class_name_color);
		}
		if(yn_yes() == 0)
		{
			clear();
			continue;
		}
		else
		{
			clear();
			break;
		}
	}

	Player.index = classes[selection-1].index;
	strcpy(Player.class_name, classes[selection-1].class_name);
	strcpy(Player.class_name_color, classes[selection-1].class_name_color);

	Player.attack_num = classes[selection-1].attack_num;
	Player.attack = (Attack*)realloc(Player.attack, Player.attack_num * sizeof(Attack));
	for(i = 0; i < Player.attack_num; i++)
	{
		strcpy(Player.attack[i].attack_name, classes[selection-1].attack[i].attack_name);
		strcpy(Player.attack[i].attack_name_color, classes[selection-1].attack[i].attack_name_color);
		Player.attack[i].attack_percent = classes[selection-1].attack[i].attack_percent;
		Player.attack[i].mana_use = classes[selection-1].attack[i].mana_use;
	}

	Player.action_num = classes[selection-1].action_num;
	Player.action = (Action*)realloc(Player.action, Player.action_num * sizeof(Action));
	for(i = 0; i < Player.action_num; i++)
	{
		strcpy(Player.action[i].action_name, classes[selection-1].action[i].action_name);
		strcpy(Player.action[i].action_name_color, classes[selection-1].action[i].action_name_color);
		Player.action[i].mana_use = classes[selection-1].action[i].mana_use;
		Player.action[i].act = classes[selection-1].action[i].act;
	}

	Player.max_HP = classes[selection-1].max_HP;
	Player.HP = Player.max_HP;
	Player.max_MP = classes[selection-1].max_MP;
	Player.MP = Player.max_MP;
	Player.ATK = classes[selection-1].ATK;
	Player.DEF = classes[selection-1].DEF;
	Player.DEX = classes[selection-1].DEX;
	Player.LUCK = classes[selection-1].LUCK;
}

void welcome()
{
	clear();
	printf(CYN);
	printf(TITLE_ART);
	printf(RESET);
	delay(1000);
	printf("\n");

	printf("Play? [y/n]: ");

	while(scanf(" %c", y_n) == 0 or yn_yes() == -1)
	{
		clear_newline();
		printf("invalid input.\nPlay? [y/n]: ");
	}

	if(yn_yes() == 0)
	{
		delay(500);
		clear();
		exit(0);
	}

	clear();
	printf(CYN);
	printf(TITLE_ART);
	delay(400);
	clear();
	printf(TITLE_ART);
	printf(RESET);
	printf("\nPlay? [y/n] : y\n");
	delay(600);
	clear();

	printf(CYN);
	printf(TITLE_ART);
	delay(400);
	clear();
	printf(TITLE_ART);
	printf(RESET);
	printf("\nPlay? [y/n] : y\n");
	delay(700);
	clear();
	delay(1000);
}

void low_heal(int mana_use)
{
	Player.MP -= mana_use;

	if(Player.HP >= Player.max_HP*3/4) Player.HP = Player.max_HP;
	else Player.HP += Player.max_HP/4;

	clear();
	initialize();
	printf("25%% of your health has been restored.\n");
	delay(2500);
	clear();
	initialize();
}

void high_heal(int mana_use)
{
	Player.MP -= mana_use;

	if(Player.HP >= Player.max_HP/2) Player.HP = Player.max_HP;
	else Player.HP += Player.max_HP/2;

	clear();
	initialize();
	printf("50%% of your health has been restored.\n");
	delay(2500);
	clear();
	initialize();
}

void mana_restore(int mana_use)
{
	Player.MP -= mana_use;

	if(Player.MP >= Player.max_MP*3/4) Player.MP = Player.max_MP;
	else Player.MP += Player.max_MP/4;

	clear();
	initialize();
	printf("25%% of your mana has been restored.\n");
	delay(2500);
	clear();
	initialize();
}

void strengthen(int mana_use)
{
	Player.MP -= mana_use;

	*temp_ATK += Player.ATK/4;

	clear();
	initialize();
	printf("Your attack increased by 25%%.\n");
	delay(2500);
	clear();
	initialize();
}

void reinforce(int mana_use)
{
	Player.MP -= mana_use;

	*temp_DEF += Player.DEF/4;

	clear();
	initialize();
	printf("Your defense increased by 25%%.\n");
	delay(2500);
	clear();
	initialize();
}

void focus(int mana_use)
{
	Player.MP -= mana_use;

	*temp_DEX += Player.DEX/4;

	clear();
	initialize();
	printf("Your dexterity increased by 25%%.\n");
	delay(2500);
	clear();
	initialize();
}

void pray(int mana_use)
{
	Player.MP -= mana_use;

	*temp_LUCK += Player.LUCK/4;

	clear();
	initialize();
	printf("Your luck increased by 25%%.\n");
	delay(2500);
	clear();
	initialize();
}

int player_attack(Attack attack)
{
	int damage=0;

	int ATK = Player.ATK + *temp_ATK;
	int DEF = Player.DEF + *temp_DEF;
	int DEX = Player.DEX + *temp_DEX;
	int LUCK = Player.LUCK + *temp_LUCK;

	clear();
	initialize();
	printf("You used %s!\n", attack.attack_name_color);
	delay(2000);
	clear();
	initialize();

	Player.MP -= attack.mana_use;

	if( random_num(1, 10000, random_num(0, 10, 1)) <= ( 1500 - (pow(DEX/10, 2) * 3 - (DEX * 2)) - (LUCK * 2) + (enemy.DEX * 2) ) )
	{
		clear();
		initialize();
		printf("You missed.\n");
		delay(1500);
		clear();
		initialize();

		return 1;
	}
	else if( random_num(1, 10000, random_num(0, 10, 2)) <= ( ( 750 + (pow(DEX/10, 2) * 3 - (DEX * 2)) + LUCK * 2) - (enemy.DEX * 2) ) )
	{
		damage = ATK * attack.attack_percent / 100;
		damage = damage + random_num(-damage/10, damage/10, 2) + (damage+DEX)/2 - (enemy.DEF*2 / 5);
		enemy.HP -= damage;
		if(damage <= 0) damage = random_num(1, 3, 3);
		if(enemy.HP < 0) enemy.HP = 0;
		clear();
		initialize();
		printf("%sCrit%s!\n", HYEL, RESET);
		printf("You dealt %s%d%s damage!\n", RED, damage, RESET);
	}
	else
	{
		damage = ATK * attack.attack_percent / 100;
		damage = damage + random_num(-damage/10, damage/10, random_num(0, 10, 3)) - (enemy.DEF / 5);
		enemy.HP -= damage;
		if(damage <= 0) damage = random_num(0, 2, 3);
		if(enemy.HP < 0) enemy.HP = 0;
		clear();
		initialize();
		printf("You dealt %s%d%s damage!\n", RED, damage, RESET);
	}

	delay(3000);

	if(enemy.HP == 0)
	{
		clear();
		initialize();
		printf("You have slain the %s!\n", enemy.name_color);
		delay(5000);
		clear();

		return 0;
	}

	clear();
	initialize();

	return 1;
}

void generate_enemy()
{
	int selection = random_num(1, *enemy_type_num, 0);

	int mutated = (random_num(1, 10000, random_num(0, 10, 7)) <= 500) ? 1 : 0;
	strcpy(enemy.name, "\0");


	switch(selection)
	{
		case 1:
			if(mutated == 1) strcpy(enemy.name, "Mutated ");
			strcat(enemy.name, "Slime");
			strcpy(enemy.name_color, HGRN);
			strcat(enemy.name_color, enemy.name);
			strcat(enemy.name_color, RESET);
			enemy.max_HP = 900 + random_num(-900/10, 900/10, random_num(0, 10, 0));
			enemy.HP = enemy.max_HP;
			enemy.ATK = 160 + random_num(-160/10, 160/10, random_num(0, 10, 1));
			enemy.DEF = 110 + random_num(-110/10, 110/10, random_num(0, 10, 2));
			enemy.DEX = 130 + random_num(-130/10, 130/10, random_num(0, 10, 3));

			break;
		case 2:
			if(mutated == 1) strcpy(enemy.name, "Mutated ");
			strcat(enemy.name, "Skeleton");
			strcpy(enemy.name_color, HWHT);
			strcat(enemy.name_color, enemy.name);
			strcat(enemy.name_color, RESET);
			enemy.max_HP = 1400;
			enemy.HP = enemy.max_HP;
			enemy.ATK = 180;
			enemy.DEF = 140;
			enemy.DEX = 140;

			break;
		case 3:
			if(mutated == 1) strcpy(enemy.name, "Mutated ");
			strcat(enemy.name, "Goblin");
			strcpy(enemy.name_color, GRN);
			strcat(enemy.name_color, enemy.name);
			strcat(enemy.name_color, RESET);
			enemy.max_HP = 1200;
			enemy.HP = enemy.max_HP;
			enemy.ATK = 150;
			enemy.DEF = 120;
			enemy.DEX = 160;

			break;
	}

	if(mutated == 1)
	{
		enemy.max_HP += random_num(enemy.max_HP/3, 2*enemy.max_HP/3, random_num(0, 10, 0));
		enemy.HP = enemy.max_HP;
		enemy.ATK += random_num(enemy.ATK/3, 2*enemy.ATK/3, random_num(0, 10, 1));
		enemy.DEF += random_num(enemy.DEF/3, 2*enemy.DEF/3, random_num(0, 10, 2));
		enemy.DEX += random_num(enemy.DEX/3, enemy.DEX/2, random_num(0, 10, 3));
	}
	else
	{
		enemy.max_HP += random_num(-enemy.max_HP/10, enemy.max_HP/10, random_num(0, 10, 0));
		enemy.HP = enemy.max_HP;
		enemy.ATK += random_num(-enemy.ATK/10, enemy.ATK/10, random_num(0, 10, 1));
		enemy.DEF += random_num(-enemy.DEF/10, enemy.DEF/10, random_num(0, 10, 2));
		enemy.DEX += random_num(-enemy.DEX/10, enemy.DEX/10, random_num(0, 10, 3));
	}
}

int player_action(char *action)
{
	int selection;
	int attack_type=-1;
	char attack[32];
	int action_type=-1;
	char act[32];

	int ATK = Player.ATK + *temp_ATK;
	int DEF = Player.DEF + *temp_DEF;
	int DEX = Player.DEX + *temp_DEX;
	int LUCK = Player.LUCK + *temp_LUCK;

	if(strcmp(action, "attack") == 0) selection = 1;
	else if(strcmp(action, "action") == 0) selection = 2;
	else if(strcmp(action, "info") == 0) selection = 3;
	else if(strcmp(action, "run") == 0) selection = 4;
	else
	{
		printf("%sunknown action%s\n", BWHT, RESET);
		delay(2000);
		clear();
		initialize();
		return -1;
	}

	switch(selection)
	{
		case 1:
			// attack

			while(true)
			{
				attack_type = -1;

				for(i = 0; i < Player.attack_num; i++)
				{
					printf("| %s |   ", Player.attack[i].attack_name_color);
					if(i%2 == 1) printf("\n");
				}
				if(Player.attack_num%2 != 0) printf("\n");
				printf(" %sback%s\n", UHWHT, RESET);
				printf("> ");

				fgets(attack, 24, stdin);
				delete_leading_newline(attack);
				fgets_reset(attack, 24);

				if(strcmp(attack, "back") == 0)
				{
					return -1;
				}
				for(i = 0; i < Player.attack_num; i++)
				{
					if(strcmp(attack, Player.attack[i].attack_name) == 0)
					{
						attack_type = i;
						break;
					}
				}

				if(attack_type != -1)
				{
					if(Player.attack[attack_type].mana_use > Player.MP)
					{
						printf("insufficient mana.\n");
						continue;
					}
					break;
				}
				else
				{
					printf("unknown attack type\n");
					continue;
				}
			}

			return player_attack(Player.attack[attack_type]);

			break;
		case 2:
			//action

			while(true)
			{
				action_type = -1;

				for(i = 0; i < Player.action_num; i++)
				{
					printf("| %s |  ", Player.action[i].action_name_color);
					if(i%3 == 2) printf("\n");
				}
				if(i%3 != 0) printf("\n");
				printf(" %sback%s\n", UHWHT, RESET);
				printf("> ");

				fgets(act, 24, stdin);
				delete_leading_newline(act);
				fgets_reset(act, 24);

				if(strcmp(act, "back") == 0)
				{
					return -1;
				}
				for(i = 0; i < Player.action_num; i++)
				{
					if(strcmp(act, Player.action[i].action_name) == 0)
					{
						action_type = i;
						break;
					}
				}

				if(action_type != -1)
				{
					if(Player.action[action_type].mana_use > Player.MP)
					{
						printf("insufficient mana.\n");
						continue;
					}
					break;
				}
				else
				{
					printf("unknown action type\n");
					continue;
				}
			}

			clear();
			initialize();
			printf("You used %s.\n", Player.action[action_type].action_name_color);
			delay(2000);
			clear();
			initialize();
			Player.action[action_type].act(Player.action[action_type].mana_use);

			return 1;

			break;
		case 3:
			//info

			class_info(Player);
			printf("\npress enter to continue.");
			clear_newline();

			return -1;

			break;
		case 4:
			//run

			clear();
			initialize();
			printf("you attempt to run.\n");
			delay(2500);
			clear();
			initialize();

			if(random_num(1, 10000, random_num(0, 10, 0)) <= ( 1500 - (pow(DEX/10, 2) * 3 - (DEX * 2)) - (LUCK * 2) + (enemy.DEX * 2) ) )
			{
				printf("you failed to escape.\n");
				delay(2500);
				clear();
				initialize();
				break;
			}
			else
			{
				printf("you successfully ran away.\n");
				delay(2000);
				clear();
				initialize();
				return 2;
			}

			break;
		default:
			//WIP

			printf("This function is a WIP.\nIt has been treated as not doing anything.\n");
			delay(3000);

			clear();
			initialize();
	}

	return 1;
}

int enemy_action()
{
	int selection;
	int damage=0;

	int ATK = Player.ATK + *temp_ATK;
	int DEF = Player.DEF + *temp_DEF;
	int DEX = Player.DEX + *temp_DEX;
	int LUCK = Player.LUCK + *temp_LUCK;

	selection = random_num(1, 1, 0);

	switch(selection)
	{
		case 1:
			printf("%s attacked you.\n", enemy.name_color);
			delay(2000);

			if( random_num(1, 10000, random_num(0, 10, 1)) <= ( 1500 - (pow(enemy.DEX/10, 2) * 3 - (enemy.DEX * 2) ) + (DEX * 2) ) )
			{
				clear();
				initialize();
				printf("%s missed.\n", enemy.name_color);
				delay(3000);
				clear();
				initialize();

				break;
			}
			else if( random_num(1, 10000, random_num(0, 10, 2)) <= ( 750 + (pow(enemy.DEX/10, 2) * 3 - (enemy.DEX * 2)) - (DEX * 2) ) )
			{
				damage = enemy.ATK + random_num(-enemy.ATK/10, enemy.ATK/10, 2) + (enemy.ATK+enemy.DEX)/2 - (DEF*2 / 5);
				Player.HP -= damage;
				if(damage <= 0) damage = random_num(1, 3, 3);
				if(Player.HP < 0) Player.HP = 0;
				clear();
				initialize();
				printf("%sCrit%s!\n", HYEL, RESET);
				printf("You took %s%d%s damage.\n", RED, damage, RESET);
			}
			else
			{
				damage = enemy.ATK + random_num(-enemy.ATK/10, enemy.ATK/10, random_num(0, 10, 3)) - (DEF / 5);
				Player.HP -= damage;
				if(damage <= 0) damage = random_num(0, 2, 3);
				if(Player.HP < 0) Player.HP = 0;
				clear();
				initialize();
				printf("You took %s%d%s damage.\n", RED, damage, RESET);
			}

			delay(3000);

			if(Player.HP == 0)
			{
				clear();
				initialize();
				printf("You have died.\n");
				delay(2000);

				return 0;
			}

			clear();
			initialize();

			break;
	}

	return 1;
}

int battle()
{
	char action[32];
	int action_result;

	*temp_ATK = 0;
	*temp_DEF = 0;
	*temp_DEX = 0;
	*temp_LUCK = 0;

	initialize();
	printf("You encountered a %s.\n", enemy.name_color);
	*encounter_num += 1;
	delay(2000);
	clear();
	initialize();
	if(*encounter_num == 1)
		clear_newline();

	do
	{
		clear();
		initialize();
		printf("> ");
		fgets(action, 32, stdin);
		delete_leading_newline(action);
		fgets_reset(action, 32);
		action_result = player_action(action);
	} while(action_result == -1);

	clear();
	initialize();

	if(action_result == 0)
	{
		return 1;
	}
	else if(action_result == 2)
	{
		return 2;
	}

	if(enemy_action() == 0)
	{
		return 0;
	}

	while(true)
	{
		printf("> ");
		fgets(action, 32, stdin);
		delete_leading_newline(action);
		fgets_reset(action, 32);

		action_result = player_action(action);
		clear();
		initialize();
		while(action_result == -1)
		{
			printf("> ");
			fgets(action, 32, stdin);
			delete_leading_newline(action);
			fgets_reset(action, 32);

			action_result = player_action(action);
			clear();
			initialize();
		}

		if(action_result == 0)
		{
			return 1;
		}
		else if(action_result == 2)
		{
			return 2;
		}

		if(enemy_action() == 0)
		{
			return 0;
		}
	}
}

void clear()
{
	system("cls");
}

/*
-----------------------------------------------------------------------------------------------------------------------------------------------------------------
*/