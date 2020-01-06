#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#define MSG_CORRECT "Correct answer!"
#define MSG_WRONG "Wrong answer."
#define MSG_WIN "You won! Congratulations!"
#define MSG_GAMEOVER "You lost!"
#define MSG_BYE "Oh okay... Sad to see you go..."
#define MSG_INVALID "Wait... That's illegal"
#define MSG_SAVE "Ok, your progress has been saved. See you later!"
#define MSG_CREDITS "Game made by:\nMiguel Martinho\nPedro Coutinho"

int anwser_seed = 

struct answers{
  char option0[64];
  char option1[64];
  char option2[64];
  char option3[64];
};

struct questions{
  char question[128];
  struct answers answers_; 
  enum {Entertainment, Science, Mythology, Sports, Geography, History, Politics, Art, Celebrities, Animals, Vehicles, General_Knowledgde} category;
  enum {easy, medium, hard} difficulty;
};
//Print menu
void print_menu(){

  puts("********************************************");
  puts("***             CILLIONAIRE                *");
  puts("********************************************");
  puts("*** n <name>     - new game                *");
  puts("*** q            - quit                    *");
  puts("*** h            - show this menu          *");
  puts("*** r <filename> - resume game             *");
  puts("*** s <filename> - save progress and quit  *");
  puts("*** j 50         - play 50:50 joker        *");
  puts("*** j 25         - play 25:75 joker        *");
  puts("*** c            - show credits            *");
  puts("********************************************");

}
//Abrir perguntas
void open_questions(char * nome_do_ficheiro){
  FILE* fp;
  char buffer[3500];
  char array_de_strings[3500][255];
  fp = fopen(nome_do_ficheiro, "r");
  int i = 0;
  while(fgets(buffer, 3500, (FILE*) fp)) {
    strcpy(array_de_strings[i], buffer);
    i++;
  }
  fclose(fp);
  printf("%s", array_de_strings[0]);
  printf("%s", array_de_strings[1]);
  printf("%s", array_de_strings[2]);
  printf("%s", array_de_strings[3]);
  printf("%s", array_de_strings[4]);
  printf("%s", array_de_strings[5]);
  printf("%s", array_de_strings[6]);
  printf("\n");
  printf("%s", array_de_strings[3493]);
  printf("%s", array_de_strings[3494]);
  printf("%s", array_de_strings[3495]);
  printf("%s", array_de_strings[3496]);
  printf("%s", array_de_strings[3497]);
  printf("%s", array_de_strings[3498]);
  printf("%s", array_de_strings[3499]);
  printf("\n");
}
//Abrir save
void open_save_file(char * nome_do_ficheiro){

  FILE* fp;
  char buffer[255];
  char array_de_dados[10][50];
  fp = fopen(nome_do_ficheiro, "r");
  int i = 0;
  while(fgets(buffer, 255, (FILE*) fp)) {
    strcpy(array_de_dados[i], buffer);
    i++;
  }
  char *name = array_de_dados[0] + 5;
  char *level = array_de_dados[1] + 7;
  char *j50 = array_de_dados[2] + 5;
  char *j25 = array_de_dados[3] + 5;
  printf("%s\n", name);
  printf("%s\n", level);
  printf("%s\n", j50);
  printf("%s\n", j25);
  fclose(fp);

}
//create save
void create_file(char * nome_do_ficheiro, char * name, int points, bool j50, bool j25){
  FILE * filepointer = fopen(nome_do_ficheiro, "w");
  char paragrafo[2] = "\n";

  /*tratar do nome*/
  char string_name[100] = "Name:  ";
  strncat(string_name, name, strlen(name));
  strncat(string_name, paragrafo, 2);

  /*tratar do nivel*/
  char nivel[50];
  char level_string[100] = "Nivel: ";
  sprintf(nivel, "%d", points);
  strncat(level_string, nivel, strlen(nivel));
  strncat(level_string, paragrafo, 2);
  
  /*tratar dos bools*/
  char bool50[15] = "J50:   ";
  char bool25[15] = "J25:   ";
  char strTRUE[6] = "true\n";
  char strFALSE[7] = "false\n";

  if (j50 == true){
    strncat(bool50, strTRUE, 6);
  }
  else{
    strncat(bool50, strFALSE,7);
  }

  if (j25 == true){
    strncat(bool25, strTRUE, 6);
  }
  else{
    strncat(bool25, strFALSE, 7);
  }

  /*Escrever tudo no ficheiro*/
  fprintf(filepointer, "%s", string_name);
  fprintf(filepointer, "%s", level_string);
  fprintf(filepointer, "%s", bool50);
  fprintf(filepointer, "%s", bool25);
  puts(MSG_SAVE);
  fclose(filepointer);
}


int main(){

  char escolha;
  char string;
  char players_choice[16];
  bool quit_game = false;
  bool j_25 = true;
  bool j_50 = true;
  int level = 0;
  char name[16] = "newbie";
  char file_name[100];
  int i;
  char asterisk[2] = "*";
  char space[2] = " ";
  char space_asterisk[32] = " ";
  print_menu();
  int number_of_choices = 0;
  //game loop
  while (quit_game == false){
    //Escolha do user
    fgets(players_choice, 100, stdin);
    sscanf(players_choice, "%c %s", &escolha, &string); 

    //Defenir o que é para fazer   
    if (escolha == '\n'){
      continue;
    }
    else if (players_choice[0] == 'n'){
        
      strcpy(name, &string);
      for (i = strlen(name); i != 33 ; i++){

        if (i != 32){
          strncat(space_asterisk, space, 1);
        }
        else {
          strncat(space_asterisk, asterisk, 1);
          printf("*** Hi %s, let's get started!\n", name);
          puts("********************************************");
          printf("*** Name: %s%s                          \n", name, space_asterisk);
          printf("*** Level: %-6d                          *\n", level);
          if (j_50 == true){
              puts("*** j50: YES                               *");
          }
          else {
            puts("*** j50: NO                                *");
          }
          if (j_25 == true){
            puts("*** j25: YES                               *");
          }
          else {
            puts("*** j50: NO                                *");
          }
          
          puts("********************************************");
         /* GG*/ 
        }
      }
    }    
    else if (players_choice[0] == 'q'){
      puts(MSG_BYE);
      quit_game = true;
    }
    else if (players_choice[0] == 'h'){
      print_menu();
    }
    else if (players_choice[0] == 'c'){
      puts(MSG_CREDITS);
    }
    else if (players_choice[0] == 's'){
      strcpy(file_name, &string);
      int points = 420;
      create_file(file_name, name, points, j_50, j_25);
    }
    else if (players_choice[0] == 'r' && number_of_choices == 0){
      strcpy(file_name, &string);
      open_save_file(file_name);
    }
    else if (players_choice[0] == 'p'){
      strcpy(file_name, &string);
      open_questions(file_name);
    }
    else{
      puts(MSG_INVALID);
    }

  }
  return 0;
}