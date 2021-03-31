#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 50000000
#define MALLOC(p,s)\
	if(!((p)=malloc(s))){\
	fprintf(stderr,"Insufficient memory\n");\
	exit(EXIT_FAILURE);\
	}





struct node{
	char digits[5];
	int count;
	struct node *next;
};

struct node queue[MAX_SIZE];
int front = -1, rear = -1;

char visited[MAX_SIZE][4];
int visitedCounter=0;

struct node deque();
struct node* enque(struct node point,char digits[5], struct node *root);
void backtrack(FILE *wf,char *password, int steps, int N);
int BFSs(char *current, char *password);

int main(){
	FILE *rf, *wf;
	
	rf = fopen("test4.txt","r");///////////////////////////////CHANGE FILE NAMES;
	wf = fopen("output.txt", "w");////////////////////////
	
	if(rf == NULL || wf == NULL){
		printf("File openning error\n");
		exit(1);
	}
	printf("Program started.\n");
	char ch;
	char current[5]={'\0'};
	char password[5]={'\0'};
	int i =0, N;
	while(1){
		ch = fgetc(rf);
		if(ch==EOF || ch =='\n') break;
		else if(ch == ' ') continue;
		current[i] = ch;
		i++;
	}
	i=0;
	while(1){
		ch = fgetc(rf);
		if(ch==EOF || ch =='\n') break;
		else if(ch == ' ') continue;
		password[i] = ch;
		i++;
	}
	fscanf(rf,"%d\n",&N);
	for(int j = 0; j < N; j++){
		i=0;
		while(1){
			ch = fgetc(rf);
			if(ch==EOF || ch =='\n') break;
			else if(ch == ' ') continue;
			visited[visitedCounter][i++] = ch;
		}
		visitedCounter++;
		if(strcmp(current,visited[j]) == 0){
			fprintf(wf, "Impossible\n");
			exit(1);
		}
		if(strcmp(password, visited[j]) == 0){
			fprintf(wf, "Impossible\n");
			exit(1);
		}
	}
	int ans = BFSs(current, password);
	if(ans==-1){
		fprintf(wf,"Impossible.\n");
	}else{
		fprintf(wf,"%d\n", ans);
		backtrack(wf,password, ans, N);	
	}
	
	printf("Program Completed\n");
	
	fclose(rf);
	fclose(wf);
	return 0;
}
struct node deque(){
	struct node temp;
	if(rear==front){
		printf("queue is empty!\n");
		exit(1);
	}
	temp = queue[++front];
	return temp;
}
struct node* enque(struct node point,char digits[5], struct node *root){
	if(rear == MAX_SIZE-1){
		printf("queue is full!\n");
		return NULL;
	}
	rear++;
	strncpy(queue[rear].digits,digits,4);
	queue[rear].count = point.count;
	return (queue[rear].next = root);
	
}
void backtrack(FILE *wf,char *password, int steps, int N){
	int k = steps, flag=0, found=0,j,i;
	char current[5];
	char **stack;
	MALLOC(stack,(steps+1)*sizeof(char**));
	for(int l=0;l<steps+1;l++){
		MALLOC(stack[l],5*sizeof(char*));
	}
	strncpy(stack[k],password,4);
	k--;
	strncpy(current, password,4);
	while(k>0){
		for(j = 0; j < MAX_SIZE; j++){
			if(queue[j].count == k){
				for( i = 0; i < 4; i++){
					char nextcombi[5];
					strncpy(nextcombi, current,4);
				//	printf("1\n");
					switch(i){
				case 0:
					if(nextcombi[i]=='9')
						nextcombi[i]='0';
					else	
						nextcombi[i]++;
						
					if(nextcombi[i+1]=='9')
						nextcombi[i+1]='0';
					else
						nextcombi[i+1]++;
					break;
				case 1: case 2:
					if(nextcombi[i-1]=='9')
						nextcombi[i-1]='0';
					else
						nextcombi[i-1]++;
						
					if(nextcombi[i]=='9')
						nextcombi[i]='0';
					else	
						nextcombi[i]++;
						
					if(nextcombi[i+1]=='9')
						nextcombi[i+1]='0';
					else
						nextcombi[i+1]++;
				
					break;
				case 3:
					if(nextcombi[i-1]=='9')
						nextcombi[i-1]='0';
					else
						nextcombi[i-1]++;
						
					if(nextcombi[i]=='9')
						nextcombi[i]='0';
					else	
						nextcombi[i]++;
					break;
			}
					flag =0;
					for(int h = 0; h < N; h++){
						if(strncmp(visited[h],nextcombi,4)==0){
							flag=1;
							break;
						}
					}
					if(flag==0){
						found=0;
						if(strncmp(nextcombi, queue[j].digits,4)==0){
							found =1;
							strncpy(current, nextcombi,4);
							strncpy(stack[k], nextcombi,4);
							break;
						}	
					}
					
					memset(nextcombi,'\0',4);
					strncpy(nextcombi, current,4);
					switch(i){
				case 0:
					if(nextcombi[i]=='0')
						nextcombi[i]='9';
					else	
						nextcombi[i]--;
						
					if(nextcombi[i+1]=='0')
						nextcombi[i+1]='9';
					else
						nextcombi[i+1]--;
					break;
				case 1: case 2:
					if(nextcombi[i-1]=='0')
						nextcombi[i-1]='9';
					else
						nextcombi[i-1]--;
						
					if(nextcombi[i]=='0')
						nextcombi[i]='9';
					else	
						nextcombi[i]--;
						
					if(nextcombi[i+1]=='0')
						nextcombi[i+1]='9';
					else
						nextcombi[i+1]--;
					break;
				case 3:
					if(nextcombi[i-1]=='0')
						nextcombi[i-1]='9';
					else
						nextcombi[i-1]--;
						
					if(nextcombi[i]=='0')
						nextcombi[i]='9';
					else	
						nextcombi[i]--;
					break;
			}
					flag =0;
					for(int h = 0; h < N; h++){
						if(strncmp(visited[h],nextcombi,4)==0){
							flag=1;
							break;
						}
					}
					if(flag==0){
						found=0;
						if(strncmp(nextcombi, queue[j].digits,4)==0){
							found =1;
							strncpy(current, nextcombi,4);
							strncpy(stack[k], nextcombi,4);
							break;
						}	
					}
				}
				if(found ==1){
					k--;
					break;
				}
			}
			
		}
	}
	for(int m=1; m <= steps; m++){
		fprintf(wf,"%s\n", stack[m]);
	}
}


int BFSs(char *current, char *password){
	int i, flag;
	struct node start;
	struct node *root;
	MALLOC(root, sizeof(struct node*));
	
	start.count = 0;
	enque(start,current, root);
	
	while(rear!=front){
		char nextcombi[5]={'\0'};
		struct node nextPoint;
		struct node curr;
		curr = deque();
		for(i = 0; i < 4; i++){
			
			char nextcombi[4]={'\0'};
			strncpy(nextcombi, curr.digits,4);
			
			switch(i){
				case 0:
					if(nextcombi[i]=='9')
						nextcombi[i]='0';
					else	
						nextcombi[i]++;
						
					if(nextcombi[i+1]=='9')
						nextcombi[i+1]='0';
					else
						nextcombi[i+1]++;
					break;
				case 1: case 2:
					if(nextcombi[i-1]=='9')
						nextcombi[i-1]='0';
					else
						nextcombi[i-1]++;
						
					if(nextcombi[i]=='9')
						nextcombi[i]='0';
					else	
						nextcombi[i]++;
						
					if(nextcombi[i+1]=='9')
						nextcombi[i+1]='0';
					else
						nextcombi[i+1]++;
				
					break;
				case 3:
					if(nextcombi[i-1]=='9')
						nextcombi[i-1]='0';
					else
						nextcombi[i-1]++;
						
					if(nextcombi[i]=='9')
						nextcombi[i]='0';
					else	
						nextcombi[i]++;
					break;
			}
			
			//strncpy(nextPoint.digits, nextcombi,4);
			nextPoint.count = curr.count +1;
				
			if(strncmp(nextcombi,password,4)==0){
				enque(nextPoint, nextcombi, root);
				return nextPoint.count;
			}
			flag=0;
			for(int k = 0; k < visitedCounter; k++){
				if(strncmp(visited[k], nextcombi,4)==0){
					flag=1;
					break;
				}
			}
			if(flag==0){
				enque(nextPoint,nextcombi, root);
				strncpy(visited[visitedCounter], nextcombi,4);
				visitedCounter++;
			}
			memset(nextcombi,'\0',4);
			strncpy(nextcombi, curr.digits,4);
			
			switch(i){
				case 0:
					if(nextcombi[i]=='0')
						nextcombi[i]='9';
					else	
						nextcombi[i]--;
						
					if(nextcombi[i+1]=='0')
						nextcombi[i+1]='9';
					else
						nextcombi[i+1]--;
					break;
				case 1: case 2:
					if(nextcombi[i-1]=='0')
						nextcombi[i-1]='9';
					else
						nextcombi[i-1]--;
						
					if(nextcombi[i]=='0')
						nextcombi[i]='9';
					else	
						nextcombi[i]--;
						
					if(nextcombi[i+1]=='0')
						nextcombi[i+1]='9';
					else
						nextcombi[i+1]--;
					break;
				case 3:
					if(nextcombi[i-1]=='0')
						nextcombi[i-1]='9';
					else
						nextcombi[i-1]--;
						
					if(nextcombi[i]=='0')
						nextcombi[i]='9';
					else	
						nextcombi[i]--;
					break;
			}
			
			//strncpy(nextPoint.digits, nextcombi,4);
			nextPoint.count = curr.count +1;
				
			if(strncmp(nextcombi,password,4)==0){
				enque(nextPoint,nextcombi, root);

				return nextPoint.count;
			}
			flag=0;
			for(int k = 0; k < visitedCounter; k++){
				if(strncmp(visited[k], nextcombi,4)==0){
					flag=1;
					break;
				}
			}
			if(flag==0){
				enque(nextPoint,nextcombi, root);
				strncpy(visited[visitedCounter], nextcombi,4);
				visitedCounter++;
			}
			
		}
	}
	return -1;
}



