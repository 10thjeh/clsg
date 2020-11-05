#include<stdio.h>
#include<stdlib.h>
#include<strings.h>
#include<conio.h>
#include<malloc.h>
#include<time.h>
#include<unistd.h>
//Boolean
#define TRUE 1
#define FALSE 0
//Fighters
#define AELITA 0
#define YUMI 1
#define ODD 2
#define ULRICH 3
#define WILLIAM 4
//Stats
#define FORCE 0
#define SPEED 1
#define HEALTH 2
//Monsters
#define KANKRELATS 0
#define BLOK 1
#define HORNET 2
#define KRAB 3
#define MEGATANK 4
#define TARANTULA 5
//data
#define MAX_BUFFER 256

typedef struct chars{
  char name[MAX_BUFFER];
  int charId;
  int level;
  int force;
  int speed;
  int health;
}chars;

int statsGrowth[5][3] = { {3,2,5},  //[charId][stats]
                          {3,3,4},  //0=Force,1=Speed,2=Health
                          {2,5,3},
                          {3,4,3},
                          {5,2,3}
                        };
int baseStats[5][3] = { {10,12,48}, //idem
                        {8,49,16},
                        {2,56,12},
                        {25,20,25},
                        {45,7,18}
                      };


void pause(){
  printf("\nPress any key to proceed...");
  fflush(stdin);
  getchar();
}

void clearScreen(){
  system("cls");
}

chars summonFighter(int charId){      //Self explanatory, i think
  char fighterName[5][MAX_BUFFER];
  strcpy(fighterName[0],"Aelita Schaeffer");
  strcpy(fighterName[1],"Ishiyama Yumi");
  strcpy(fighterName[2],"Odd Della Robbia");
  strcpy(fighterName[3],"Ulrich Stern");
  strcpy(fighterName[4],"William");

  chars fighter;
  strcpy(fighter.name,fighterName[charId]);
  fighter.charId = charId;
  fighter.force = baseStats[charId][FORCE];
  fighter.speed = baseStats[charId][SPEED];
  fighter.health = baseStats[charId][HEALTH];

  return fighter;

}

//function to update character stats based on their level
void updateStats(chars *fighters,int lvl,int charId){ //updateStats(&fighters,[target level],[CharId])

  fighters[charId].level = lvl;
  fighters[charId].force = baseStats[charId][FORCE] + (((fighters[charId].level)-1)*statsGrowth[charId][FORCE]);
  fighters[charId].speed = baseStats[charId][SPEED] + (((fighters[charId].level)-1)*statsGrowth[charId][SPEED]);
  fighters[charId].health = baseStats[charId][HEALTH] + (((fighters[charId].level)-1)*statsGrowth[charId][HEALTH]);
}
/*Chars code :                          level growth :
  0) Aelita   : Guardian (1-1.2-4.8)    |3-2-5
  1) Yumi     : Ninja (0.8-4.9-1.6)     |3-3-4
  2) Odd      : Feline (0.2-5.6-1.2)    |2-5-3
  3) Ulrich   : Samurai (2.5-2-2.5)     |3-4-3
  4) William  : Warrior (4.5-0.7-1.8)   |5-2-3
  */

int chooseFighterMenu(){
  int loop=TRUE,input;
  while(loop){
  printf("Welcome to Code Lyoko Social Game [Text-based]\n");
  printf("This game is still under development\n");
  printf("\nPlease choose your character : [Character name][Force][Speed][Health]\n");
  printf("1. Aelita Schaeffer[%d][%d][%d]-Guardian\n",baseStats[AELITA][FORCE],baseStats[AELITA][SPEED],baseStats[AELITA][HEALTH]);
  printf("2. Ishiyama Yumi[%d][%d][%d]-Ninja\n",baseStats[YUMI][FORCE],baseStats[YUMI][SPEED],baseStats[YUMI][HEALTH]);
  printf("3. Odd Della Robbia[%d][%d][%d]-Feline\n",baseStats[ODD][FORCE],baseStats[ODD][SPEED],baseStats[ODD][HEALTH]);
  printf("4. Ulrich Stern[%d][%d][%d]-Samurai\n",baseStats[ULRICH][FORCE],baseStats[ULRICH][SPEED],baseStats[ULRICH][HEALTH]);
  printf("5. William[%d][%d][%d]-Warrior\n",baseStats[WILLIAM][FORCE],baseStats[WILLIAM][SPEED],baseStats[WILLIAM][HEALTH]);
  scanf("%d",&input);
  if(input>=1 && input<=5){
    loop=FALSE;
  }
  else {
    printf("Please choose between 1-5!");
    pause();
    }
  }
  system("cls");
  return input-1;
}

void mainMenu(chars lyokoWarrior){
  clearScreen();
  printf("Main menu             \t\t\t|Choosen Character\n");
  printf("1. Practice           \t\t\t|%s\n",lyokoWarrior.name);
  printf("2. Check stats growth \t\t\t|Force  = %d\n",lyokoWarrior.force);
  printf("3. About              \t\t\t|Speed  = %d\n",lyokoWarrior.speed);
  printf("4. Exit               \t\t\t|Health = %d\n",lyokoWarrior.health);
  printf("Input : ");
}

void characterGrowth(chars lyokoWarrior){
  clearScreen();
  printf("Your Character : %s\n",lyokoWarrior.name);
  printf("Force = %d\nSpeed = %d\nHealth = %d\n",statsGrowth[lyokoWarrior.charId][FORCE],statsGrowth[lyokoWarrior.charId][SPEED],statsGrowth[lyokoWarrior.charId][HEALTH]);
  pause();
}

void printAbout(){
  printf("Code Lyoko Social Game[Text-based]\n");
  printf("Q : Buat dari scratch?\nA : Iya,mungkin.\n");
  printf("Q : Progress bisa di save?\nA : Belom dibuat,tapi nanti pasti ada\n");
  printf("Q : Bisa online ga?\nA : Sabar atuh,nanti dipikir caranya wkwk\n");
  printf("Q : Virus ga nih ?\nA : Menurutlu?\n");
  printf("Q : Character cuma bisa pilih satu doang nih?\nA : Nanti masih dipikirin dlu kwkw\n");
  printf("Q : Gamenya ada rencana apa berikutnya?\nA : Mau diganti turn based aja\n");
  printf("Q : Tengkiu\nA : Sama-sama");
  pause();
}

int whoseTurn(int playerSpeed,int cpuSpeed){
  srand(time(0));
  int random = rand()%(playerSpeed+cpuSpeed)+1;
  if(random<=playerSpeed){
    return 1;
  }
  else return 0;
}

void practice(chars lyokoWarrior){
  //In practice,Fighter fight against dummy
  //Dummy has 4 force,7 speed,10 health
  //Fighting type is automatic
  //Same as CLSG,but less dramatic
  clearScreen();
  int dummy[3];
  int initialLyokoHealth,initialDummyHealth;
  initialDummyHealth = dummy[HEALTH];
  initialLyokoHealth = lyokoWarrior.health;
  dummy[FORCE]=4;
  dummy[SPEED]=7;
  dummy[HEALTH]=100;
  int turn;

  while(lyokoWarrior.health>0 && dummy[HEALTH]>0){
    turn = whoseTurn(lyokoWarrior.speed,dummy[SPEED]); //1 Means player attack and 0 means CPU attack
    if(turn==1){
      printf("%s attacked dummy with %d damage!\n",lyokoWarrior.name,lyokoWarrior.force);
      dummy[HEALTH] -= lyokoWarrior.force;
    }
    else {
      printf("Dummy attacked %s with %d damage!\n",lyokoWarrior.name,dummy[FORCE]);
      lyokoWarrior.health -= dummy[FORCE];
    }
    printf("%s's HP = %d\t\t\tDummy's HP = %d\n",lyokoWarrior.name,lyokoWarrior.health,dummy[HEALTH]);
    sleep(2);
    printf("\n");
  }
  if(lyokoWarrior.health>0){
    printf("%s win!\n",lyokoWarrior.name);
  }
  else if(dummy[HEALTH]>0){
    printf("Dummy win!\n");
  }
  lyokoWarrior.health = initialLyokoHealth;
  dummy[HEALTH] = initialDummyHealth;
  pause();
}


int main(int argc, char const *argv[]) {
  int menuInput,mainMenuLoop=TRUE;
  chars lyokoWarrior = summonFighter(chooseFighterMenu());
  while(mainMenuLoop){
  mainMenu(lyokoWarrior);
  scanf("%d",&menuInput);
    switch (menuInput) {
      case 1:
        practice(lyokoWarrior);       //Done
        break;
      case 2:
        characterGrowth(lyokoWarrior); //Done
        break;
      case 3:
        printAbout();                 //Done
        break;
      case 4: mainMenuLoop=FALSE;
        break;
      default :
        printf("Please enter between 1-4!");
        pause();
        break;
    }//End of main menu switch

  }
  return 0;
}

/*
chars fighters[5];

strcpy(fighters[AELITA].name,"Aelita Schaeffer");
fighters[AELITA].level = 1;
fighters[AELITA].force = 10;// + (fighters[AELITA].level*3);
fighters[AELITA].speed = 12;// + (fighters[AELITA].level*2);
fighters[AELITA].health = 48;// + (fighters[AELITA].level*5);
//Yumi
strcpy(fighters[YUMI].name,"Yumi Ishiyama");
fighters[YUMI].level = 1;
fighters[YUMI].force = 8;
fighters[YUMI].speed = 49;
fighters[YUMI].health = 16;
//Odd
strcpy(fighters[ODD].name,"Odd Della Robbia");
fighters[ODD].level = 1;
fighters[ODD].force = 2;
fighters[ODD].speed = 56;
fighters[ODD].health = 12;
//Ulrich
strcpy(fighters[ULRICH].name,"Ulrich Stern");
fighters[ULRICH].level = 1;
fighters[ULRICH].force = 25;
fighters[ULRICH].speed = 20;
fighters[ULRICH].health = 25;
//William
strcpy(fighters[WILLIAM].name,"William");
fighters[WILLIAM].level = 1;
fighters[WILLIAM].force = 45;
fighters[WILLIAM].speed = 7;
fighters[WILLIAM].health = 18;
May be useful for other thingy idk
*/
