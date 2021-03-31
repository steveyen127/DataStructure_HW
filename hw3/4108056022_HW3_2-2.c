#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXSIZE 100000
#define MALLOC(p,s)\
	if(!((p)=malloc(s))){\
		fprintf(stderr, "InsufficientMemory");\
		exit(EXIT_FAILURE);\
	}

struct string{
	char word[MAXSIZE];
	char morse[MAXSIZE];
};

char *toMorse(char word[]);
void findPrefix(struct string word1, struct string wordTest, FILE *wf);

	
int main(){
	
	FILE *rf, *wf;
	wf = fopen("output1Mine.txt", "w"); //<--- edit output file name here
	rf = fopen("test2.txt", "r"); //<----------edit input file name here

	if(wf == NULL || rf == NULL){
		printf("File opening error.\n");
		return -1;
	}else{
		printf("Reading file...\n");
		struct string word1, wordTest;
		int wordNum;
		
		fgets(word1.word, MAXSIZE, rf);
		word1.word[strlen(word1.word)-1] = '\0'; // removes \n from fgets
		strcpy(word1.morse, toMorse(word1.word));
		
		fscanf(rf,"%d\n", &wordNum);
		for(int i = 0; i < wordNum; i++){
			fgets(wordTest.word, MAXSIZE, rf);
			if(i < wordNum-1){
				wordTest.word[strlen(wordTest.word)-1] = '\0'; // remove \n from fgets except for last word since no \n;
			}
			strcpy(wordTest.morse, toMorse(wordTest.word));
			findPrefix(word1, wordTest, wf);
		}

	}
	printf("Program completed.\n");
	fclose(wf);
	fclose(rf);
}

char *toMorse(char word[]){
	
	
	char *morseWord;
	MALLOC(morseWord, MAXSIZE*sizeof(char*));
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
				printf("Character not found.\n");
				return "";
		}
	}
	return morseWord;	
}	

void findPrefix(struct string word1, struct string wordTest, FILE *wf){
	//if wordTest morse code is longer than word1 morse code then doesnt have the same prefix
	if(strlen(wordTest.morse) > strlen(word1.morse)){
		fprintf(wf, "%s doesn't have the same prefix as %s.\n", wordTest.word, word1.word);
	}
	//if they are the same strcmp == 0;
	else if(strcmp(wordTest.morse, word1.morse)==0){
		fprintf(wf, "%s is the same as %s.\n", wordTest.word, word1.word);
	}
	else{
		//copy word1 morse with same lenght as wordTest morse code and compare
		char word1Cut[MAXSIZE]="";
		strncpy(word1Cut, word1.morse, (strlen(wordTest.morse)));
		//if word1 cutted morse code is the same as wordTest morse code then have same prefix;
		if(strcmp(word1Cut, wordTest.morse) == 0){
			fprintf(wf, "%s has the same prefix as %s.\n", wordTest.word, word1.word);
		}else{
			fprintf(wf, "%s doesn't have the same prefix as %s.\n", wordTest.word, word1.word);
		}
	}
}
