#include <stdio.h>
#include <stdlib.h> 
#define MAX_QUEUE_SIZE 300
#define COUNT 5
#define MALLOC(p,s)\
    if(!((p)=malloc(s))){\
        fprintf(stderr,"Insufficient memory");\
        exit(EXIT_FAILURE);\
    }

struct node{
	int data;
	struct node* left;
	struct node* right;
};

struct Q{
	int rear, front, size;
	struct node* nodeQ;
};
struct node* root = NULL;
int baseCount = 0;
int min(int x, int y);
struct node* newNode(int data);
void insertV(int value, struct Q* queue);

void base(struct node* root);
void findBase(struct node *root);
void clearTree(struct node *root);

struct Q* creatQueue(unsigned capacity);
int isFull(struct Q* queue);
int isEmpty(struct Q* queue);
int front(struct Q* queue);
int rear(struct Q* queue);
void enqueue(struct Q* queue, struct node* data);
struct node* dequeue(struct Q* queue);

int main(){
	FILE *rf;
	FILE *wf;
	char filename[50];
	int filenumber;
	wf = fopen("output.txt", "w"); // change name of output file
	if(wf == NULL){
		printf("Failed creating output.txt\n");
		return 1;
	}else{
		for(filenumber = 1; filenumber<=3; filenumber++){ // change for to go through files 
														// if want only one file filenumber = 1; filenumber<= 1;
			baseCount = 0;
			root = NULL;
			sprintf(filename, "test%d.txt", filenumber);
			printf("Reading %s...\n", filename);
			fprintf(wf,"Test %d: ", filenumber);
			rf = fopen(filename, "r");
			if(rf == NULL){
			printf("Failed Reading file %s", filename);
			return 1;
			}else{
				
				struct Q* queue;
				queue = creatQueue(MAX_QUEUE_SIZE);
				char ch;
				ch = fgetc(rf);
				while(ch != EOF){
					ch = fgetc(rf);
					if(ch == '0'){
						insertV(1, queue);
					}
					if(ch == 'n'){
						insertV(0, queue);
						
					}
					
				}
				findBase(root);
				fprintf(wf,"%d\n", baseCount);
				//printf("base num: %d\n", baseCount);
				clearTree(root);
				fclose(rf);

			}
		}
		fclose(wf);
	
	printf("Program Completed.\n");
	}
	
	
	
	return 0;	
}

int min(int x, int y){ 
	return (x < y)? x: y; 
	} 
struct node* newNode(int data){
	struct node* node;
	MALLOC(node, sizeof(struct node));
	node->data = data;
	node->left = NULL;
	node->right = NULL;
	return(node);
}

void base(struct node* root){	
	if(root != NULL){
		if(root->data == 0){
			return;
		}else{
			if(root->left == NULL && root->right == NULL){
				return;
			}
			if(root->left->data == 0 && root->right->data == 0){
				return;
			}else{
				
				if(root->left->data == 1 || root->right->data == 1){
					//set current node as base==2
					root->data = 2;
					baseCount++;
					//making current node's childrens covered==3 if they are not bases if they exist
					if(root->left){
						if(root->left->data == 1){
							root->left->data = 3;
						}
					}
					if(root->right){
						if(root->right->data ==1){
							root->right->data = 3;
						}	
					}
							
				}else{
					if(root->left->data == 2 || root->right->data ==2){
						//making current node covered==3 if it has a child as base==2;
						root->data = 3;	
					}
				}	
			}
		}
	}
}

void findBase(struct node* root){
	if(root!= NULL){
	    findBase(root->left);
		findBase(root->right);
		base(root);
	}
}
void clearTree(struct node *root){
	if(root!= NULL){
	    clearTree(root->left);
		clearTree(root->right);
		free(root);
	}
}


void insertV(int data, struct Q* queue){
	
	
	struct node* node = newNode(data);
	//if root is empty set the first node as root;
	if(root == NULL){
		root = node;
		
	//if left child of node is empty set new node as left child
	}else if(queue[front(queue)].nodeQ->left == NULL){
		queue[front(queue)].nodeQ->left = node;
		//printf("in funct: %d\n", root->left->data);
		
	//if left child is already taken
	//set new node as right child and dequeue the father node from queue
	}else{
		queue[front(queue)].nodeQ->right = node;
		dequeue(queue);
	}
	
	//add new node to queue for adding his child nodes.
	if(node->data != 0){
		enqueue(queue,node);
	}
}

struct Q* creatQueue(unsigned capacity){
	struct Q* queue = (struct Q*)malloc(capacity * sizeof(struct Q)); 
    queue->front = queue->size = 0; 
    queue->rear = capacity - 1; 
    return queue; 
}
int isFull(struct Q* queue){
	return (queue->rear == queue->front);
}
int isEmpty(struct Q* queue){
	return (queue->size == 0);
}
int front(struct Q* queue){
	if(isEmpty(queue)){
		//printf("queue is empty11\n");
	}
	return queue->front;
}
int rear(struct Q* queue){
	if(isEmpty(queue)){
		printf("queue is empty\n");
	}
	return queue->rear;
}
void enqueue(struct Q* queue, struct node* data){
	if(isFull(queue)){
		//printf("queue is full\n");	
	}
	queue->rear = (queue->rear +1) % MAX_QUEUE_SIZE;
	queue[queue->rear].nodeQ = data;
	queue->size = queue->size + 1;
}
struct node* dequeue(struct Q* queue){
	if(isEmpty(queue)){
	//printf("queue is empty22\n");
	
	}
	struct node* item = queue[queue->front].nodeQ;
	queue->front = (queue->front + 1) % MAX_QUEUE_SIZE;
	queue->size = queue->size - 1;
	return item;
}

