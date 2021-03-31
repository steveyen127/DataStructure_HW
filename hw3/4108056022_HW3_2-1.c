#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define WORDLENGTH 1000
#define MALLOC(p,s)\
    if(!((p)=malloc(s))){\
        fprintf(stderr,"Insufficient memory");\
        exit(EXIT_FAILURE);\
    }
    


char **creat2Darr(int size);
char *toMorse(char word[]);
void findWord(char **words, char morse[], int numWords, FILE *wf);

int main(){
	FILE *rf, *wf;

	rf = fopen("test2.txt", "r");
	wf = fopen("output1Mine.txt", "w");

	if(wf == NULL || rf == NULL){
		printf("Failed opening file.\n");
		return -1;
	}else{
		int numWords;
		int numMorse;
		fscanf(rf, "%d\n", &numWords);

		char **words;
		words = creat2Darr(numWords);
		char temp[50];
		for(int i = 0; i < numWords; i++){
			fgets(temp, 50, rf);
			strcpy(words[i], toMorse(temp));
		//	printf("morse: %s\n", words[i]);
		
		}

		fscanf(rf, "%d\n", &numMorse);
		char morse[WORDLENGTH];

		for(int i = 0; i < numMorse; i++){
			fgets(morse, WORDLENGTH, rf);
			morse[strlen(morse)-1] = '\0';
			findWord(words, morse, numWords, wf);
		}
		


	}
	fclose(rf);
	fclose(wf);

	return 0;
}

char **creat2Darr(int size){
	char **x;
	MALLOC(x, size* sizeof(char*));
	for(int i = 0; i < size; i++){
		MALLOC(x[i], WORDLENGTH*sizeof(char**));
	}
	
	return x;
}

char *toMorse(char word[]){
	char *morseWord;
	MALLOC(morseWord, 1000*sizeof(char*));
	strcpy(morseWord, "");
	int i = 0;
	while(i < strlen(word)){
		if(word[i] == '\0' || word[i] == '\n'){
			strcat(morseWord, "\0");
			printf("morse: %s\n", morseWord);
			return morseWord;
		}
		switch(word[i]){
			case 'A':
				strcat(morseWord, ".-");
				i++;
				break;
			
			case 'B':
				strcat(morseWord, "-...");
				i++;
				break;
			
			case 'C':
				strcat(morseWord, "-.-.");
				i++;
				break;
				
			case 'D':
				strcat(morseWord, "-..");
				i++;
				break;
			
			case 'E':
				strcat(morseWord, ".");
				i++;
				break;
				
			case 'F':
				strcat(morseWord, "..-.");
				i++;
				break;
			
			case'G':
				strcat(morseWord, "--.");
				i++;
				break;
			
			case'H':
				strcat(morseWord, "....");
				i++;
				break;
				
			case'I':
				strcat(morseWord, "..");
				i++;
				break;
				
			case'J':
				strcat(morseWord, ".---");
				i++;
				break;
				
			case'K':
				strcat(morseWord, "-.-");
				i++;
				break;
				
			case'L':
				strcat(morseWord, ".-..");
				i++;
				break;
				
			case'M':
				strcat(morseWord, "--");
				i++;
				break;
				
			case'N':
				strcat(morseWord, "-.");
				i++;
				break;
				
			case'O':
				strcat(morseWord, "---");
				i++;
				break;
				
			case'P':
				strcat(morseWord, ".--.");
				i++;
				break;
				
			case'Q':
				strcat(morseWord, "--.-");
				i++;
				break;
				
			case'R':
				strcat(morseWord, ".-.");
				i++;
				break;
				
			case'S':
				strcat(morseWord, "...");
				i++;
				break;
				
			case'T':
				strcat(morseWord, "-");
				i++;
				break;
				
			case'U':
				strcat(morseWord, "..-");
				i++;
				break;
				
			case'V':
				strcat(morseWord, "...-");
				i++;
				break;
				
			case'W':
				strcat(morseWord, ".--");
				i++;
				break;
				
			case'X':
				strcat(morseWord, "-..-");
				i++;
				break;
				
			case'Y':
				strcat(morseWord, "-.--");
				i++;
				break;
				
			case'Z':
				strcat(morseWord, "--..");
				i++;
				break;
			
			default:
				printf("Letter not found.\n");
				return "";
		}
	}
	return morseWord;
}

void findWord(char **words, char morse[], int numWords, FILE *wf){
	for(int i = 0; i < numWords; i++){
		if((strcmp(words[i], morse)) == 0){
			fprintf(wf,"%s is found in the dictionary.\n", morse);
			return;
		}
	}
	fprintf(wf,"%s is not found in the dictionary.\n", morse);
	return;
}
