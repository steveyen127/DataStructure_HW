#include <stdio.h>
#include <stdlib.h>

struct node{
	char letter;
	struct node* next;
	struct node* prev;
};
struct bestNode{
	int flag;
	int plusCost;
	int distance;
	struct node* Node;
};

struct node* head, *last, *current;
int minCost = 99999999;
int totalCost= 0;


void creatPlat();
void insertEnd(char letter);
struct bestNode* findNode(char letter);
int platDistance(struct node* testNode);
void printNode (struct bestNode* temp, FILE *wf);


int main(){
	FILE *rf;
	FILE *wf;
	wf = fopen("outputmine.txt", "w"); // <---- change output file name here.
	int filenumber;
	filenumber = 9; // <------- change filenumber for test1, test2, test3...
	char fileName[50];
	sprintf(fileName, "test%d.txt", filenumber);
	rf = fopen(fileName, "r");
	
	if(rf == NULL){
		printf("Failed opening test File.\n");
		return 1;
	}else{
		printf("Reading %s...\n", fileName);
		struct bestNode* tempIN;
		creatPlat();
		char ch;
		fprintf(wf,"test%d: \n", filenumber);
		fprintf(wf,"actual output: ");
		ch = fgetc(rf);
		while(ch!=EOF){
			minCost = 99999999;
			printNode(findNode(ch),wf);
			//printCommands(tempIN, ch);
			ch=fgetc(rf);
	 	}
		fprintf(wf,"\n");
		printf("length: %d\n", totalCost);
		fprintf(wf,"Length: %d\n", totalCost);
		
		fclose(rf);
		fclose(wf);
		printf("Program Completed.\n");
		return 0;  
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
int platDistance(struct node* testNode){
	struct node* temp;
	temp = current;
	int distance=0;
	int flag = 0; // 0 = right >, 1 = left <
	if(testNode == temp){
		return 0;
	}
	while(testNode != temp){
		if(distance > 9){
			flag = 1;
			distance = 0;
			temp = current;
		}
		if(flag == 0){
			temp = temp->next;
			distance++;
		}else{
			temp = temp->prev;
			distance--;
		}
	}
	return distance;
}


struct bestNode* findNode(char letter){
	struct node* testNode;
	//struct node* minNode;
	struct bestNode* minNode;
	minNode = (struct bestNode*)malloc(sizeof(struct bestNode));
	
	int plusCost=0;
	int distance=0;
	int minCost=999999;
	char currentLetter;
	
	testNode = current;
//	printf("\nletter %c\n", letter);
	while(1){
		currentLetter = testNode->letter;
		plusCost = 0;
		int flag = 0; // 0 = plus sign , 1 = minus sign
		while(currentLetter!=letter){
			if(currentLetter == ' '){
				currentLetter = 'A';
				plusCost++;
			}else if(currentLetter== 'Z'){
				currentLetter = ' ';
				plusCost++;
			}else{
				currentLetter++;
				plusCost++;
			}
			if(plusCost > 13){
				flag = 1;
			}
		}
		if(flag == 1){
			plusCost =  27 - plusCost;
		}
		distance = platDistance(testNode);
	//	printf("\ndistance is: %d\n", distance);
		if(distance < 0){
			distance = distance * -1;
		}
		if(minCost > (plusCost + distance)){
			minCost = (plusCost+ distance);
			minNode->flag = flag;
			minNode->plusCost = plusCost;
			minNode->Node = testNode;
			minNode->distance = platDistance(testNode);
		}
		
		if(testNode->next == current){
			break;
		}else{
			testNode = testNode->next;
		}
	}
//	printf("min PLUS %d\n",minNode->plusCost );
	current = minNode->Node;
	current->letter = letter;
//	printf("\nnew current letter %c\n", current->letter);
	return minNode;
	
}

void printNode (struct bestNode* temp, FILE *wf){
	int distance;
	distance = temp->distance;
	if(distance < 0){
		distance = distance * -1;
		for(int i = 0; i < distance; i++){
			fprintf(wf,"<");
		}
	}else{
		for(int i = 0; i < distance; i++){
			fprintf(wf,">");
		}
	}
	
	if(temp->flag == 1){//minus
		for(int j = 0; j < temp->plusCost; j++){
			fprintf(wf,"-");
		}
	}else{
		for(int j = 0; j < temp->plusCost; j++){
			fprintf(wf,"+");
		}
	}
	totalCost = totalCost + (temp->plusCost+distance+1);
	fprintf(wf,".");
}

