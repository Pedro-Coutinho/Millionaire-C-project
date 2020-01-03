#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#define MSG_CORRECT "Correct answer!"
#define MSG_WRONG "Wrong answer."
#define MSG_WIN "You won! Congratulations!"
#define MSG_GAMEOVER "You lost!"
#define MSG_BYE "Oh okay... Sad to see you go..."
#define MSG_INVALID "Wait... That's illegal"
#define MSG_CREDITS "Game made by:\nMiguel Martinho\nPedro Coutinho"

void remove_spaces(char* s) {
    const char* d = s;
    do {
        while (*d == ' ') {
            ++d;
        }
    } while (*s++ == *d++);
}

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

void create_file(char * nome_do_ficheiro, char * name, int points, bool j50, bool j25){


    FILE * filepointer = fopen(nome_do_ficheiro, "w");
    char paragrafo[2] = "\n";
    /*tratar do nome*/

    char string_name[100] = "Name : ";
    strncat(string_name, name, strlen(name));
    strncat(string_name, paragrafo, 2);

    /*tratar do nivel*/

    char nivel[50];
    char level_string[100] = "Nivel : ";
    sprintf(nivel, "%d", points);
    strncat(level_string, nivel, strlen(nivel));
    strncat(level_string, paragrafo, 2);

    /*tratar dos bools*/


    char bool50[15] = "J50 : ";
    char bool25[15] = "J25 : ";
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
    fclose(filepointer);

}


int main(){
    char players_choice[16];
    bool quit_game = false;
    bool j_25 = true;
    bool j_50 = true;
    char name[16] = "newbie";
    int i;
    print_menu();
    while (quit_game == false){

        gets(players_choice);
        
        if (*players_choice == '\n'){
            continue;
        }
        else if (players_choice[0] == 'n'){
            for (i = 1; players_choice[i] != '\0'; i++){
                strcpy(&name[i-1], &players_choice[i]);
            }
            printf("*** Hi %s, let's get started!\n", name);
            puts("********************************************");
            printf("*** Name: %s                             *\n", name);
            puts("*** Level: 0                               *");
            puts("*** j50: YES                               *");
            puts("*** j25: YES                               *");
            puts("********************************************");
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
            char nome_do_ficheiro [] = "ficheiroxpto.txt";
            int points = 420;
            create_file(nome_do_ficheiro, name, points, j_50, j_25);
        }
        else{
            puts(MSG_INVALID);
        }
    }
    return 0;
}
