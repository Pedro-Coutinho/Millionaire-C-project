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

struct questions{
    char question[128];
    char answers[4][128]; 
    enum {Entertainment, Science, Mythology, Sports, Geography, History, Politics, Art, Celebrities, Animals, Vehicles, General_Knowledgde} category;
    enum {easy, medium, hard} difficulty;
} ;
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
struct questions open_questions(char * nome_do_ficheiro){
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
  
    struct questions q1;

    strncpy(q1.answers[0], array_de_strings[1]+ 8,64);
    strncpy(q1.answers[1], array_de_strings[2]+ 8,64);
    strncpy(q1.answers[2], array_de_strings[3]+ 8,64);
    strncpy(q1.answers[3], array_de_strings[4]+ 8,64);
    strncpy(q1.question, array_de_strings[0]+ 9,64);

    printf("*** Question: %s", q1.question);
    printf("*** A: %s", q1.answers[0]);
    printf("*** B: %s", q1.answers[1]);
    printf("*** C: %s", q1.answers[2]);
    printf("*** D: %s", q1.answers[3]);

return q1;
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

void newbie_print() {
    printf("*** Hi newbie, let's get started!\n");
    puts("********************************************");
    printf("*** Name: newbie                           *\n");
    printf("*** Level: 0                               *\n");
    puts("*** j50: YES                               *");
    puts("*** j25: YES                               *");
    puts("********************************************");
}

int main() {
    /*
    //int seed;
    //if (argc < 2 || sscanf(argv[1], "%d", &seed) != 1) {
    //  seed = time(NULL);
    //srand(seed);
    */
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
    int number_of_choices = 0;
    print_menu();
    //game loop
    while (quit_game == false){
        //Escolha do user
        printf(">");
        fgets(players_choice, 100, stdin);
        sscanf(players_choice, "%c %s", &escolha, &string); 

        //Defenir o que é para fazer   
        if (escolha == '\n'){
            continue;
        }
        else if (players_choice[0] == 'n'){
            int c;
            (c = strcmp(&string, "\0"));
            if (c == 0) {
                newbie_print();
                open_questions("perguntas");
            }
            else {
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
                        open_questions("perguntas");
                    }
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