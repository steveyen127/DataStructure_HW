#include <stdio.h>
#include <stdlib.h> 
#include <ctype.h>
#define MAX_QUEUE_SIZE 15000
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
int totalCost = 0;
int min(int x, int y);
struct node* newNode(int data);
void insertV(int value, struct Q* queue);

void base(struct node* root);
void findBase(struct node *root);
void clearTree(struct node *root);

int read_buffer(char *buffer, int *sz);
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
	wf = fopen("output1.txt", "w");
	if(wf == NULL){
		printf("Failed creating output.txt\n");
		return 1;
	}else{
		for(filenumber = 2; filenumber<=2; filenumber++){
			totalCost = 0;
			root = NULL;
			sprintf(filename, "test%d.txt", filenumber);
			fprintf(wf,"Test %d: ", filenumber);
			printf("test%d: ",filenumber);
			rf = fopen(filename, "r");
			if(rf == NULL){
			printf("Failed Reading file %s", filename);
			return 1;
			}else{
				
				struct Q* queue;
				queue = creatQueue(MAX_QUEUE_SIZE);
				char ch;
				char buffer[1000];
				int number;
				int sz = 0;
				
				ch = fgetc(rf);
				while((ch=fgetc(rf)) != EOF){
					
					if(ch == 'n'){
						insertV(-1001,queue);
					}else{
						if(ch>= 48 && ch <= 57){
								buffer[sz++] = ch;
						}else{
							if(sz!=0){
								insertV(read_buffer(buffer,&sz), queue);
							}
							
						}	
					}
							
					
				}
				findBase(root);
				fprintf(wf,"%d\n", totalCost);
				printf("base cost: %d\n", totalCost);
				clearTree(root);
				fclose(rf);

			}
		}
		fclose(wf);
	
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
	int costSolo = 9999;
	int costChildL = 9999;
	int costChildR = 9999;
	//if root not base(!=-1002)
	if(root->data == 0){
		//root->data = -1002; //making node with 0 cost base;
		if(root->left!= NULL && root->left->data >=0){
			root->left->data = root->left->data * -1;
		}
		if(root->right!= NULL && root->right->data >=0){
			root->right->data = root->right->data * -1;
		}
	}else if(root->data == -1002){
		if(root->left!= NULL && root->left->data > 0){
			root->left->data = root->left->data*-1;
		}
		if(root->right!=NULL && root->right->data>0){
			root->right->data = root->right->data * -1;
		}
	}else if(root->data>0){
		//cost if making root base==-2
		costSolo = root->data;
		if((root->left!=NULL && root->left->data > 0)|| (root->right!=NULL && root->right->data > 0)){
			if(root->left!=NULL && root->left->data > 0){
				costChildL = root->left->data;
			}
			if(root->right!=NULL && root->right->data > 0){
				costChildR = root->right->data;
			}
		}
		if(costChildR>1000){
			costChildR = 0;
		}
		if(costChildL>1000){
			costChildL = 0;
		}
		if(costSolo < (costChildL+costChildR)){
			totalCost = totalCost + costSolo;
			root->data = -1002; // making root == base;
			//making sure left and right child exist and are not already covered.
			//making data negative if its covered by a base;
			if(root->left!=NULL && root->left->data > 0){
				root->left->data = root->left->data * -1;
			}
			if(root->right!=NULL && root->right->data > 0){
				root->right->data = root->right->data * -1;
			}
		}else{
			totalCost = totalCost + costChildR+costChildL;
			if(root->left!=NULL && root->left->data>0){
				root->left->data = -1002;
			}
			if(root->right!=NULL && root->right->data>0){
				root->right->data = -1002;
			}
		}
	}
//		if(costSolo == costChildL){
//			if(costSolo < costChildR){
//				root->data = -1002;
//				if(root->left->data >=0){
//					root->left->data = (root->left->data * -1);
//				}
//				if(root->right->data >= 0){
//					root->right->data = (root->right->data * -1);
//				}
//			}else{
//				root->right->data = -1002;
//				root->data = root->data*-1;
//			}
//		}else if(costSolo == costChildR){
//			if(costSolo < costChildL){
//				root->data = -1002;
//				if(root->left->data >=0){
//					root->left->data = (root->left->data * -1);
//				}
//				if(root->right->data >= 0){
//					root->right->data = (root->right->data * -1);
//				}
//			}else{
//				root->left->data = -1002;
//				root->data = root->data*-1;
//			}
//				
//		}else if(costChildL == costChildR && costChildL != 9999){
//			if(costSolo < costChildL){
//				root->data = -1002;
//				if(root->left->data >=0){
//					root->left->data = (root->left->data * -1);
//				}
//				if(root->right->data >= 0){
//					root->right->data = (root->right->data * -1);
//				}
//			}else{
//				root->left->data = -1002;
//				root->data = root->data*-1;
//			}
//		}else if(costSolo == costChildR == costChildL){
//			totalCost = totalCost + costSolo;
//			root->data = -1002;
//			if(root->left->data >=0){
//				root->left->data = (root->left->data * -1);
//			}
//			if(root->right->data >= 0){
//				root->right->data = (root->right->data * -1);
//			}
//		}else if(costChildL > costSolo && costChildR > costSolo){
//			totalCost = totalCost + costSolo;
//			root->data = -1002; // making root == base;
//			//making sure left and right child exist and are not already covered.
//			//making data negative if its covered by a base;
//			if(costChildL!=9999 && root->right->data > 0){
//				root->left->data = root->left->data * -1;
//			}
//			if(costChildR!=9999 && root->right->data > 0){
//				root->right->data = root->right->data * -1;
//			}
//		}else if(costChildL< costSolo && costChildL < costChildR){
//			totalCost = totalCost + costChildL;
//			root->left->data = -1002; //making root->left base.
//			root->data = root->data * -1;
//			//covering root->left childs if they exist.
//			if(root->left->left!=NULL && root->left->left->data != -1001 && root->left->left->data >=0){
//				root->left->left->data = root->left->left->data * -1;
//			}
//			if(root->left->right!=NULL && root->left->right->data!= -1001 && root->left->right->data >=0){
//				root->left->right->data = root->left->right->data * -1;
//			}
//		}else if(costChildR < costSolo && costChildR < costChildL){
//			totalCost = totalCost + costChildR;
//			root->right->data = -1002; // making root->right base.
//			root->data = root->data * -1;
//			if(root->right->left!=NULL && root->right->left->data != -1001 && root->right->left->data >= 0){
//				root->right->left->data = root->right->left->data * -1;
//			}
//			if(root->right->right!=NULL && root->right->right->data != -1001 && root->right->right->data >= 0){
//				root->right->right->data = root->right->right->data * -1;
//			}
//		}
//		//if root is already covered by other base.
//		}
//		else if(root->data > -1001 && root->data < 0){
//			costSolo = (root->data*-1);
//			if(root->left!= NULL || root->right!= NULL){
//				if(root->left!=NULL && root->left->data>=0){
//					costChildL = root->left->data;
//				}
//				if(root->right!=NULL && root->right->data>=0){
//					costChildR = root->right->data;
//				}
//				if(costSolo < costChildL && costSolo < costChildR){
//					totalCost = totalCost + costSolo;
//					root->data = -1002; //making covered root base.
//					if(root->left!=NULL && root->left->data>=0){
//						root->left->data = root->left->data * -1;
//					}
//					if(root->right!=NULL && root->right->data >=0){
//						root->right->data = root->right->data * -1;
//					}
//					
//				}
//				if(costSolo > costChildL && costChildL < costChildR){
//					totalCost = totalCost + costChildL;
//					root->left->data = -1002;
//					if(root->left->left!=NULL && root->left->left->data >=0){
//						root->left->left->data = root->left->left->data * -1;
//					}
//					if(root->left->right!=NULL && root->left->right->data >=0){
//						root->left->right->data = root->left->right->data * -1;
//					}
//					
//				}
//				if(costSolo > costChildR && costChildL > costChildR){
//					totalCost = totalCost + costChildR;
//					root->right->data = -1002;
//					if(root->right->left!=NULL && root->right->left->data >=0){
//						root->right->left->data = root->right->left->data * -1;
//					}
//					if(root->right->right!=NULL && root->right->right->data >=0){
//						root->right->right->data = root->right->right->data * -1;
//					}
//					
//				}
//			}
//	}
}

void findBase(struct node* root){
	if(root!= NULL){
		//printf("%d \n", root->data);
		base(root);
	    findBase(root->left);
		findBase(root->right);
		//printf("%d \n", root->data);
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

int read_buffer(char *buffer, int *sz){
	int ret;
	if(*sz == 0) return 0;
	buffer[*sz] = '\0';//end the string
	sscanf(buffer, "%d", &ret);
	*sz = 0;
	return ret;	
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

