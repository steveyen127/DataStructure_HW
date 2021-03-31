#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE_QUEUE 50000
#define MALLOC(p,s)\
	if(!((p)=malloc(s))){\
	fprintf(stderr,"Insufficient memory\n");\
	exit(EXIT_FAILURE);\
	}

struct qnode{
	char digits[4];
	int count;
};
struct node{
	char digits[4];
	struct node *next;
};
struct Q{
	int rear, front, size;
	unsigned capacity;
	struct qnode *array;
};
struct Q *creatQ(unsigned capacity){
	struct Q *queue;
	MALLOC(queue,sizeof(struct Q*));
	queue->capacity = capacity;
	queue->front= queue->size = 0;
	queue->rear = capacity-1;
	MALLOC(queue->array, queue->capacity*sizeof(struct qnode*));
	return queue;
}

int isFull(struct Q *queue){
	return(queue->size==queue->capacity);
}
int isEmpty(struct Q *queue){
	return (queue->size==0);
}

void enq(struct Q *queue, struct qnode data){
	if(isFull(queue)){
		printf("queue is full\n");
		return;
	}
	queue->rear = (queue->rear+1)%queue->capacity;
	queue->array[queue->rear] = data;
	queue->size = queue->size+1;
}

struct qnode deq(struct Q *queue){
	if(isEmpty(queue)){
		printf("queue is empty");
	}
	struct qnode data = queue->array[queue->front];
	queue->front = (queue->front+1) % queue->capacity;
	queue->size = queue->size-1;
	return data;
}
struct node *creatNode(char digits[4]){
	struct node *temp;
	MALLOC(temp, sizeof(struct node*));
	strncpy(temp->digits, digits,4);
	temp->next = NULL;
	return temp;
}
struct node *insertListF(struct node *head, char digits[4]){
	struct node *temp;
	temp = creatNode(digits);
	temp->next = head;
	return temp;
}
void printList(struct node *temp){
	for(;temp; temp = temp->next){
		printf("%s\n", temp->digits);
	}
}

int BFS(struct Q* queue,char *current, char *password, char **forbid, int forbidNum){
	struct qnode nextCombNode;	
	struct node *head, *last;
	if(strcmp(current, password)==0){
		return 0;
	}
	int flag, k=0;
	int visitedCount=0;
	char **visited;
	MALLOC(visited, MAX_SIZE_QUEUE*sizeof(char**));
	for(int i = 0; i < MAX_SIZE_QUEUE;i++){
		MALLOC(visited[i], 4*sizeof(char*));
	}
	for(int i = 0; i < forbidNum; i++){
		strncpy(visited[k], forbid[i],4);
		k++;
		if(strncmp(current,forbid[i],4)==0){
			//start is forbid
			return -1;
		}
		if(strncmp(password,forbid[i],4)==0){
			//password is forbid
			return -1;
		}
	}
	struct qnode start;
	strncpy(start.digits, current,4);
	start.count=0;
	enq(queue,start);
	
	while(queue->size!=0){
		struct qnode curr = deq(queue);
		head = creatNode(curr.digits);
		
		//printf("%s, %d\n", curr.digits, curr.count);
		char *nextcomb;
		MALLOC(nextcomb,4*sizeof(char*));
		//moving UP
		for(int i = 0; i < 4; i++){
			memset(nextcomb, '\0', 4);
			strncpy(nextcomb,curr.digits,4);
			switch(i){
				case 0:
					nextcomb[i]++;
					nextcomb[i+1]++;
					if(nextcomb[i]>'9') nextcomb[i] = '0';
					if(nextcomb[i+1]>'9') nextcomb[i+1] = '0';
					break;
					
				case 1:
					nextcomb[i-1]++;
					nextcomb[i]++;
					nextcomb[i+1]++;
					if(nextcomb[i-1]>'9')nextcomb[i-1] = '0';
					if(nextcomb[i]>'9')nextcomb[i] = '0';
					if(nextcomb[i+1]>'9')nextcomb[i+1] = '0';
					break;
				
				case 2:
					nextcomb[i-1]++;
					nextcomb[i]++;
					nextcomb[i+1]++;
					if(nextcomb[i-1]>'9')nextcomb[i-1] = '0';
					if(nextcomb[i]>'9')nextcomb[i] = '0';
					if(nextcomb[i+1]>'9')nextcomb[i+1] = '0';
					break;
				
				case 3:
					nextcomb[i]++;
					nextcomb[i-1]++;
					if(nextcomb[i]>'9') nextcomb[i] = '0';
					if(nextcomb[i-1]>'9') nextcomb[i-1] = '0';
					break;	
				
			}
			if(strncmp(nextcomb, password,4)==0){
				curr.count++;
				printList(insertListF(head,nextcomb));
				return curr.count;
			}
			flag =0;
			for(int j = 0; j < k; j++){
				if(strncmp(nextcomb,visited[j],4)==0){
					flag = 1; break;
				}
			}
			if(flag == 0){
				strncpy(nextCombNode.digits, nextcomb,4);
				nextCombNode.count = curr.count+1;
				enq(queue,nextCombNode);
				insertListF(head,nextcomb);
				printf("enque: %s, %d\n", nextcomb, nextCombNode.count);
				strncpy(visited[k], nextcomb,4);
				k++;
			}
			
			//moving down
			memset(nextcomb, '\0', 4);
			strncpy(nextcomb,curr.digits,4);
			switch(i){
				case 0:
					nextcomb[i]--;
					nextcomb[i+1]--;
					if(nextcomb[i]<'0') nextcomb[i] = '9';
					if(nextcomb[i+1]<'0') nextcomb[i+1] = '9';
					break;
					
				case 1:
					nextcomb[i-1]--;
					nextcomb[i]--;
					nextcomb[i+1]--;
					if(nextcomb[i-1]<'0')nextcomb[i-1] = '9';
					if(nextcomb[i]<'0')nextcomb[i] = '9';
					if(nextcomb[i+1]<'0')nextcomb[i+1] = '9';
					break;
				
				case 2:
					nextcomb[i-1]--;
					nextcomb[i]--;
					nextcomb[i+1]--;
					if(nextcomb[i-1]<'0')nextcomb[i-1] = '9';
					if(nextcomb[i]<'0')nextcomb[i] = '9';
					if(nextcomb[i+1]<'0')nextcomb[i+1] = '9';
					break;
				
				case 3:
					nextcomb[i]--;
					nextcomb[i-1]--;
					if(nextcomb[i]<'0') nextcomb[i] = '9';
					if(nextcomb[i-1]<'0') nextcomb[i-1] = '9';
					break;	
				
			}
			if(strncmp(nextcomb, password,4)==0){
				curr.count++;
				printList(insertListF(head,nextcomb));
				return curr.count;
			}
			flag =0;
			for(int j = 0; j < k; j++){
				if(strncmp(nextcomb,visited[j],4)==0){
					flag = 1; break;
				}
			}
			if(flag == 0){
				strncpy(nextCombNode.digits, nextcomb,4);
				nextCombNode.count = curr.count+1;
				enq(queue,nextCombNode);
				insertListF(head,nextcomb);
				printf("enque: %s, %d\n", nextcomb, nextCombNode.count);
				strncpy(visited[k], nextcomb,4);
				k++;
			}
			
		}
	}
	return -1;
	
}


int main(){
	FILE *rf, *wf;
	rf = fopen("test4.txt", "r");
	wf = fopen("outputMine.txt", "w");
	
	if(rf == NULL || wf == NULL){
		printf("File openning error\n");
		exit(1);
	}else{
		char ch;
		int i, forbNum;
		char *current, **forbid;
		MALLOC(current, 4*sizeof(char));
		char password[4];
		
		i = 0;
		while(1){
			ch = fgetc(rf);
			if(ch=='\n' || ch == EOF) break;
			else if(ch ==' ') continue;
			current[i] = ch;
			i++;		
		}
		i=0;
		while(1){
			ch=fgetc(rf);
			if(ch=='\n')break;
			else if(ch == ' ') continue;
			password[i] = ch;
			i++;
		}
		fscanf(rf,"%d\n", &forbNum);
		
		MALLOC(forbid, forbNum*sizeof(char*));
		for(int j = 0; j < forbNum; j++){
			MALLOC(forbid[j], 4*sizeof(char));
		}
		for(int j = 0; j < forbNum; j++){
			i=0;
			while(1){
				ch = fgetc(rf);
				if(ch== EOF || ch=='\n')break;
				else if(ch ==' ') continue;
				forbid[j][i] = ch; 
				i++;
			}
			printf("forbid: %s\n", forbid[j]);
		}
		struct Q *queue = creatQ(MAX_SIZE_QUEUE);
		int ans = BFS(queue, current, password, forbid, forbNum);
		if(ans == -1){
			printf("Impossible");
		}else{
			printf("%d\n", ans);
		}
		
	}
	fclose(rf);
	fclose(wf);
}
