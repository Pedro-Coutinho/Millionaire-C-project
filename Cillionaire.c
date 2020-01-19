#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>

#define MSG_CORRECT "***Correct answer!"
#define MSG_WRONG "***Wrong answer."
#define MSG_WIN "***You won! Congratulations!"
#define MSG_GAMEOVER "***You lost!"
#define MSG_BYE "***Sad to see you go..."
#define MSG_INVALID "***Wait... That's illegal"
#define MSG_SAVE "***Ok, your progress has been saved. See you later!"
#define MSG_CREDITS "***Game made by:\nMiguel Martinho\nPedro Coutinho" 

struct questions {
	char question[128];
	char answers0[128];
	char answers1[128];
	char answers2[128];
	char answers3[128];
	enum category { TV, GAMES, SHIT } cat;
	enum difficulty { easy, medium, hard, deleted } level;
};
struct questions arraydeperguntas[1000];

int rand_number() {
	int n = abs(3) + 1;
	return (rand() % n);
}


//Print menu
void print_menu() {

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
void open_questions(char * nome_do_ficheiro) {

	FILE* fp;
	char buffer[3500];
	char array_de_strings[3500][255];
	fp = fopen(nome_do_ficheiro, "r");
	int i = 0;
	int j = 0;
	while (fgets(buffer, 3500, (FILE*)fp)) {
		strcpy(array_de_strings[i], buffer);
		i++;
		j++;
	}

	fclose(fp);
	i = 0;
	int k = 0;

	for (i = 0; i < j; i += 7) {
		strncpy(arraydeperguntas[k].question, array_de_strings[i] + 9, 256);
		strncpy(arraydeperguntas[k].answers0, array_de_strings[i + 1] + 8, 128);
		strncpy(arraydeperguntas[k].answers1, array_de_strings[i + 2] + 8, 128);
		strncpy(arraydeperguntas[k].answers2, array_de_strings[i + 3] + 8, 128);
		strncpy(arraydeperguntas[k].answers3, array_de_strings[i + 4] + 8, 128);
		strncpy(array_de_strings[i + 5], array_de_strings[i + 5] + 9, 128);
		arraydeperguntas[k].cat = *array_de_strings[i + 5];
		strncpy(array_de_strings[i + 6], array_de_strings[i + 6] + 11, 128);
		arraydeperguntas[k].level = *array_de_strings[i + 6];
		k++;
	}
}

//Abrir save
void open_save_file(char * nome_do_ficheiro) {

	FILE* fp;
	char buffer[255];
	char array_de_dados[10][50];
	fp = fopen(nome_do_ficheiro, "r");
	int i = 0;
	while (fgets(buffer, 255, (FILE*)fp)) {
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
void create_file(char * nome_do_ficheiro, char * name, int points, bool j50, bool j25) {
	FILE * filepointer = fopen(nome_do_ficheiro, "w");
	char paragrafo[2] = "\n";

	//tratar do nome
	char string_name[100] = "Name:  ";
	strncat(string_name, name, strlen(name));
	strncat(string_name, paragrafo, 2);

	//tratar do nivel
	char nivel[50];
	char level_string[100] = "Nivel: ";
	sprintf(nivel, "%d", points);
	strncat(level_string, nivel, strlen(nivel));
	strncat(level_string, paragrafo, 2);

	//tratar dos bools
	char bool50[15] = "J50:   ";
	char bool25[15] = "J25:   ";
	char strTRUE[6] = "true\n";
	char strFALSE[7] = "false\n";

	if (j50 == true) {
		strncat(bool50, strTRUE, 6);
	}
	else {
		strncat(bool50, strFALSE, 7);
	}

	if (j25 == true) {
		strncat(bool25, strTRUE, 6);
	}
	else {
		strncat(bool25, strFALSE, 7);
	}

	//Escrever tudo no ficheiro
	fprintf(filepointer, "%s", string_name);
	fprintf(filepointer, "%s", level_string);
	fprintf(filepointer, "%s", bool50);
	fprintf(filepointer, "%s", bool25);
	fclose(filepointer);
}

void newbie_print() {
	printf("*** Hi Newbie, let's get started!\n");
	puts("********************************************");
	printf("*** Name:  Newbie                           *\n");
	printf("*** Level: 0                               *\n");
	puts("*** j50:   YES                             *");
	puts("*** j25:   YES                             *");
	puts("********************************************");
}

int main(int argc, char **argv) {
	// || sscanf(argv[1], "%d", &seed) != 1
	open_questions("Ficheiroteste.txt");
	int seed;
	if (argc < 2) {
		seed = time(NULL);
		srand(seed);
		int seed_respostas;
		seed_respostas = rand_number();
	}
	else if (argc == 3) {

		if (strcmp(argv[1], "-s") == 0) {
			seed = atoi(argv[2]);
			srand(seed);
		}
		else if (strcmp(argv[1], "-f") == 0) {
			open_questions(argv[2]);
			srand(seed);
		}

	}
	else if (argc == 4) {

		if (strcmp(argv[1], "-s") == 0) {
			seed = atoi(argv[2]);
			srand(seed);
			open_questions(argv[4]);
		}
		else if (strcmp(argv[1], "-f") == 0) {
			open_questions(argv[2]);
			seed = atoi(argv[4]);
			srand(seed);
		}
	}
	else if (argc > 4) {
		printf("To many arguments!");
	}
	else if ((argc > 1 && argc < 3) || (argc > 3 && argc < 5)) {
		printf("Not enough arguments!");
	}
	else {
		srand(time(0));
	}

	//Variaveis de input
	char escolha;
	char string;
	char right_answer = 'a';
	char players_choice[16];
	bool quit_game = false;
	//Jokers
	bool j_25 = true;
	bool j_50 = true;
	bool continuarjogo = false;
	bool gamestarted = false;

	char file_name[100];
	int level = 0;
	char name[16] = "Newbie";
	bool nameisgiven = false;

	int i;
	int number_of_choices = 0;

	bool encontroupergunta = false;
	int dificuldadeatual = 101;
	print_menu();
	//game loop
	while (quit_game == false) {
		//Escolha do user

		if (gamestarted == false) {

			printf(">");
			fgets(players_choice, 100, stdin);
			sscanf(players_choice, "%c %s", &escolha, &string);
		}


		//gcc main.c -o main
		//./main -f Ficheiroteste.txt
		//Defenir o que é para fazer   
		if (escolha == '\n') {
			continue;
		}
		else if (players_choice[0] == 'n' || (continuarjogo == true && (escolha == 'a' || escolha == 'b' || escolha == 'c' || escolha == 'd'))) {
			int c;
			(c = strcmp(&string, "\0"));
			if (c == 0) {
				newbie_print();
			}
			else {
				if (nameisgiven == false) {
					strcpy(name, &string);
					nameisgiven = true;
					gamestarted = true;
					printf("*** Hi %s, let's get started!\n", name);
				}

				puts("********************************************");
				printf("*** Name:  %s                              *\n", name);
				printf("*** Level: %d                               *\n", level);
				if (j_50 == true) {
					puts("*** j50:   YES                             *");
				}
				else {
					puts("*** j50:   NO                             *");
				}
				if (j_25 == true) {
					puts("*** j25:   YES                             *");
				}
				else {
					puts("*** j50:   NO                             *");
				}
				puts("********************************************");

				int i = 0;

				while (encontroupergunta == false) {
					if (arraydeperguntas[i].level == dificuldadeatual) {
						encontroupergunta = true;
					}
					else {
						i++;
					}
				}
				int randnumber = rand_number();
				printf("*** Question: %s", arraydeperguntas[i].question);
				if (randnumber == 0) {
					printf("*** A: %s", arraydeperguntas[i].answers0);
					printf("*** B: %s", arraydeperguntas[i].answers1);
					printf("*** C: %s", arraydeperguntas[i].answers2);
					printf("*** D: %s", arraydeperguntas[i].answers3);
					right_answer = 'a';
				}
				else if (randnumber == 1) {
					printf("*** A: %s", arraydeperguntas[i].answers1);
					printf("*** B: %s", arraydeperguntas[i].answers0);
					printf("*** C: %s", arraydeperguntas[i].answers2);
					printf("*** D: %s", arraydeperguntas[i].answers3);
					right_answer = 'b';
				}
				else if (randnumber == 2) {
					printf("*** A: %s", arraydeperguntas[i].answers1);
					printf("*** B: %s", arraydeperguntas[i].answers2);
					printf("*** C: %s", arraydeperguntas[i].answers0);
					printf("*** D: %s", arraydeperguntas[i].answers3);
					right_answer = 'c';
				}
				else if (randnumber == 3) {
					printf("*** A: %s", arraydeperguntas[i].answers1);
					printf("*** B: %s", arraydeperguntas[i].answers2);
					printf("*** C: %s", arraydeperguntas[i].answers3);
					printf("*** D: %s", arraydeperguntas[i].answers0);
					right_answer = 'd';
				}

				encontroupergunta = false;
				size_t n = sizeof(arraydeperguntas) / sizeof(arraydeperguntas[0]);
				for (c = i; c < n - 1; c++) {
					arraydeperguntas[c] = arraydeperguntas[c + 1];
				}
			}
		}

		printf(">");
		fgets(players_choice, 100, stdin);
		sscanf(players_choice, "%c %s", &escolha, &string);

		if (escolha == '\n') {
			continue;
		}

		if (players_choice[0] == right_answer) {
			printf("*** Hooray !\n");
			level += 500;
			continuarjogo = true;
		}
		else if (players_choice[0] == 'b') {
			printf("*** Whoops... That's not correct.");
			printf("The correct answer was %c:%s", toupper(right_answer), arraydeperguntas[i].answers0);
			continuarjogo = true;
		}
		else if (players_choice[0] == 'c') {
			printf("*** Whoops... That's not correct.");
			printf("The correct answer was A:%s", arraydeperguntas[i].answers0);
			continuarjogo = true;
		}
		else if (players_choice[0] == 'd') {
			printf("*** Whoops... That's not correct.");
			printf("The correct answer was A:%s", arraydeperguntas[i].answers0);
			continuarjogo = true;
		}
		else if (players_choice[0] == 'q') {
			puts(MSG_BYE);
			quit_game = true;
		}
		else if (players_choice[0] == 'h') {
			print_menu();
		}
		else if (players_choice[0] == 'c') {
			puts(MSG_CREDITS);
		}
		else if (players_choice[0] == 's') {
			strcpy(file_name, &string);
			int points = 420;
			create_file(file_name, name, points, j_50, j_25);
		}
		else if (players_choice[0] == 'r' && number_of_choices == 0) {
			strcpy(file_name, &string);
			open_save_file(file_name);
			puts(MSG_SAVE);
			return 0;
		}
		else {
			puts(MSG_INVALID);
		}
	}
	return 0;
}