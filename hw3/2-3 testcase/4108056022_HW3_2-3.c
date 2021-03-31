#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MALLOC(p,s)\
	if(!((p)=malloc(s))){\
		fprintf(stderr, "Insuficient memory.");\
		exit(EXIT_FAILURE);\
	}
#define MAXSIZE 100000
struct string{
	char word[20];
	char morse[MAXSIZE];
};

int combis =0;
void findComb(struct string *words, struct string morse, int index, int wordNum);
int findPrefix(struct string word1, struct string wordTest, int index);
char *toMorse(char word[]);

int main(){
	FILE *rf, *wf;
	
	wf = fopen("output1Mine.txt", "w");
	rf = fopen("test2.txt", "r");
	
	if(rf == NULL || wf == NULL){
		printf("File opening error.\n");
		return -1;
	}else{
		printf("Program started...\n");
		struct string morse1;
		int wordNum;
		
		fgets(morse1.morse, MAXSIZE, rf);
		fscanf(rf,"%d\n", &wordNum);
		//MALLOC(words, wordNum*sizeof(struct string*));
		struct string words[wordNum];

		for(int i = 0; i < wordNum; i++){
			fgets(words[i].word, 20, rf);
			if(i < wordNum-1){
				words[i].word[strlen(words[i].word)-1] = '\0';//removes \n of fgets
			}			

			strcpy(words[i].morse, toMorse(words[i].word));
		}
		printf("Program completed.\n");
		findComb(words, morse1, 0, wordNum);
		fprintf(wf, "Test: %d\n", combis);
	}
	fclose(rf);
	fclose(wf);
}

int findPrefix(struct string word1, struct string wordTest, int index){
	//if wordTest morse code is longer than word1 morse code then doesnt have the same prefix
	if(strlen(wordTest.morse) > strlen(word1.morse)){
		//fprintf(wf, "%s doesn't have the same prefix as %s.\n", wordTest.word, word1.word);
		return 3;
	}
	//if they are the same strcmp == 0;
	else if(strcmp(wordTest.morse, word1.morse)==0){
		//fprintf(wf, "%s is the same as %s.\n", wordTest.word, word1.word);
		return 2;
	}
	else{
		//copy word1 morse with same lenght as wordTest morse code and compare
		char word1Cut[MAXSIZE]="";
		memcpy(word1Cut, &word1.morse[index], strlen(wordTest.morse));
		//if word1 cutted morse code is the same as wordTest morse code then have same prefix;
		if(strcmp(word1Cut, wordTest.morse) == 0){
		return 1;	
	}else{
			//fprintf(wf, "%s doesn't have the same prefix as %s.\n", wordTest.word, word1.word);
			return 0;
		}
	}
}
void combii(struct string *words, struct string morse, int wordNum){
	
}
void findComb(struct string *words, struct string morse, int index, int wordNum){
	if(index == strlen(morse.morse)-1){
		combis++;
	}
	for(int i = 0; i < wordNum; i++){
		
			if(findPrefix(morse, words[i], index)==2){
				combis++;
			}else if(findPrefix(morse, words[i], index)==1){
				index = index + strlen(words[i].morse);
				findComb(words, morse, index, wordNum);
			}	
	}
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
