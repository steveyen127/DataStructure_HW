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

int min(int x, int y);
struct node* newNode(int data);
void insertV(int value, struct Q* queue);
void print2D(struct node* root, int space);
void printTree(struct node* root);
void pre_order_traversal(struct node* root);
int vCover(struct node *root);

struct Q* creatQueue(unsigned capacity);
int isFull(struct Q* queue);
int isEmpty(struct Q* queue);
int front(struct Q* queue);
int rear(struct Q* queue);
void enqueue(struct Q* queue, struct node* data);
struct node* dequeue(struct Q* queue);

int main(){
	FILE *rf;
	
	rf = fopen("test2.txt", "r");
	char ch;
	int nodecount =0;
	struct Q* queue = creatQueue(MAX_QUEUE_SIZE);
	
	ch = fgetc(rf);
	
	while(ch != EOF){
		ch = fgetc(rf);
		if(ch == '0'){
			nodecount++;
			insertV(nodecount, queue);
		}
		if(ch == 'n'){
			insertV(0, queue);
			
		}
		
	}
	printTree(root);
	pre_order_traversal(root);
	int baseNum;
	baseNum = vCover(root);
	printf("base num: %d\n", baseNum);
	
	free(queue);
	
	
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

void print2D(struct node* root, int space){
	if(root == NULL)
		return;
	
	space += COUNT;
	
	print2D(root->right, space);
	
	//printf("\n");
	for(int i = COUNT; i < space; i++){
		printf(" ");
	}
	printf("%d\n", root->data);
	print2D(root->left, space);
}

void printTree(struct node* root){
	print2D(root,0);
}

void pre_order_traversal(struct node* root){
	if(root != NULL){
		pre_order_traversal(root->left);
		pre_order_traversal(root->right);
		printf("%d ", root->data);
	}
}

void in_order(struct node* root){
	if(root!= NULL){
		in_order(root->left);
		printf("%d ", root->data);
		in_order(root->right);
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

int vCover(struct node *root) 
{ 
    // The size of minimum vertex cover is zero if tree is empty or there 
    // is only one node 
    if (root == NULL) 
        return 0; 
    if (root->left == NULL && root->right == NULL) 
        return 0; 
    if (root->left->data == 0 && root->right->data == 0) 
        return 0; 
    if(root->data == 0)
    	return 0;
    	
    // Calculate size of vertex cover when root is part of it 
    int size_incl = 1 + vCover(root->left) + vCover(root->right);
	//printf("include root: %d, at: %d\n", size_incl, root->data); 
  
    // Calculate size of vertex cover when root is not part of it 
    int size_excl = 0; 
    if (root->left && root->left->data != 0) {
    	size_excl += 1 + vCover(root->left->left) + vCover(root->left->right);
    	//printf("excl root left: %d, at: %d\n", size_excl, root->data); 
	}
    if (root->right && root->right->data != 0) {
        size_excl += 1 + vCover(root->right->left) + vCover(root->right->right); 
	    //printf("excl root right : %d, at: %d\n", size_excl, root->data); 

	}
  	//printf("excl root : %d, at: %d\n", size_excl, root->data);
    // Return the minimum of two sizes 
    return min(size_incl, size_excl); 
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

