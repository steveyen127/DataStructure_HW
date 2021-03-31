#include <stdio.h>
#include <stdlib.h>


struct node{
	char letter;
	struct node* next;
	struct node* prev;
};

struct node* head, *last, *current;

void creatPlat();
void insertEnd(char letter);
void commands(char command, FILE* wf);

int main(){
	FILE *rf;
	FILE *wf;
	char ch;
	wf = fopen("output.txt", "w");
	rf = fopen("test.txt", "r"); //INPUT FILE
	if(rf == NULL){
		printf("Failed opening file.\n");
		return 1;
	}else{
		printf("Reading file...\n");
		creatPlat();
		
		ch = fgetc(rf);
		while(ch != EOF){
			commands(ch,wf);
			ch = fgetc(rf);
		}
		fprintf(wf,"\n");
		fclose(rf);
		fclose(wf);
		printf("Program Completed.\n");
	}
	
	
}

struct node* newNode(char letter){
	struct node *temp = (struct node*)malloc(sizeof(struct node));
	temp->letter = letter;
	temp->next = temp;
	temp->prev = temp;
	
	return temp;
}
void insertEnd(char letter){
	struct node *temp = newNode(letter);
	
	if(head == NULL){
		head = temp;
		last = temp;
		current = temp;
	}else{
		temp->next = head;
		head->prev = temp;
		temp->prev = last;
		last->next = temp;
		last = temp;
	}
}

void creatPlat(){
	for(int i = 0; i < 20; i++){
		insertEnd(' ');
	}
}

void commands(char command, FILE* wf){
	
	switch(command){
		case '+':
			if(current->letter == ' '){
				current->letter = 'A';
				break;
			}
			else if(current->letter == 'Z'){
				current->letter = ' ';
				break;
			}
			else{
				current->letter = current->letter +1;
				break;
			}
		
		case '-':
			if(current->letter == ' '){
				current->letter = 'Z';
				break;
			}
			else if(current->letter == 'A'){
				current->letter = ' ';
				break;
			}
			else{
				current->letter = current->letter -1;
				break;
			}
			
		case '>':
			current = current->next;
			break;
			
		case '<':
			current = current->prev;
			break;
		
		case'.':
			fprintf(wf,"%c", current->letter);
			break;
			
		case' ':
			fprintf(wf," ");
			break;
	}
}

