//讀檔的地方在line 223左右 
#include <stdio.h>
#include <stdlib.h>
#define MAXQUEUE 10000000

struct TreeNode {
	int data;
	struct TreeNode* left;
	struct TreeNode* right;
};

int index=1, minCost=0, ans[15001]={0}, t=0;

struct Queue{
	int rear;
	int front;
	int size;
	int capacity;
	struct TreeNode* n;
};

int min(int x, int y) { return (x <= y)? x: y; } 

struct TreeNode* newNode(int item){
	struct TreeNode* node=(struct TreeNode*) malloc(sizeof(struct TreeNode));
	node->left= NULL;
	node->right=NULL;
	node->data= item;
	return node;
}

struct Queue* creatQ()
{
	struct Queue* queue= (struct Queue*)malloc(MAXQUEUE * sizeof(struct Queue));
	queue->rear=MAXQUEUE-1;
	queue->front=0;
	queue->size=0;
	queue->capacity= MAXQUEUE;
	return queue;
}

void push(struct Queue* queue, struct TreeNode* item)
{
	if(queue->size==queue->capacity){
	//	printf("Queue full\n");
	}
	else{
		queue->rear= (queue->rear+1)%queue->capacity;
		queue[queue->rear].n=item;
		queue->size++;
	}
}

struct TreeNode* pop(struct Queue* queue)
{
	struct TreeNode* item;
	if (queue->size==0){
	//	printf("Empty queue\n");
	}
	else{
		item=queue[queue->front].n;
		queue->front= (queue->front+1)%queue->capacity;		
		queue->size--;		
		return item;
	}
}

struct TreeNode* front(struct Queue* queue)		//查看queue最前面的資料 
{
	struct TreeNode* item;
	if(queue->size!=0){
		item=queue[queue->front].n;
		return item;
	}
}

struct TreeNode* newRoot(int item, struct Queue* queue){
	struct TreeNode* node=(struct TreeNode*) malloc(sizeof(struct TreeNode));
	node->left= NULL;
	node->right=NULL;
	node->data= item;
	push(queue, node);
	return node;
}

struct TreeNode* insertValue(struct TreeNode* node, int value, struct Queue* queue)
{
	//建立樹 
	//測試queue裡的front node，如果他的左邊或右邊是null，就在左邊或右邊接上新的node， 並把該node push進去queue(代表該點合法且存在) 
	//當我的node左右兩邊都有接東西時，就會pop出queue 
	struct TreeNode* item= front(queue);
	
	if (queue->size==0){
		return NULL;
	}
	else if(item->left==NULL){		//左邊空 
		item->left=node;		//左邊接上node 
//		printf ("Add %d left: %d \n", item->data, item->left->data);
		if (item->left->data!=(-1)){		//我不要把null的node加到queue裡面 (因為它的後面不能接東西，如果push進去的話，之後就會被pop出來，然後被接上left and right) 			
			push(queue, node);
		}
	}
	else if (item->right==NULL){		//右邊空 
		item->right=node;		//右邊接上node
//		printf("Add %d right: %d \n", item->data, item->right->data);
		if (item->right->data!=(-1)){		//我不要把null的node加到queue裡面
			push(queue, node);
		}
		pop(queue);
	}
	else{
//		printf("ERROR\n");
	}	
	return node;
}

int vCover(struct TreeNode *root, int flag) 
{ 
	//when root is base: root->data= root->data+2000
	//when root is a marked point next to the base: root->data= root->data-2000
	int ans;
    if (!root || root->data==(-1)) 
        return 0; 
    if ((!root->left || root->left->data==(-1)) && (!root->right || root->right->data==(-1))) 
        return 0; 
  	
    int size_incl=0;	//when root node is included
    if (root->data>=2000){
    	size_incl = root->data -2000 + vCover(root->left, flag+1) + vCover(root->right, flag+1); 
	}
	else if (root->data<0){
		size_incl = root->data +2000 + vCover(root->left, flag+1) + vCover(root->right, flag+1); 
	}
	else {
		size_incl = root->data + vCover(root->left, flag+1) + vCover(root->right, flag+1); 
	}
  
    int size_excl = 0;		//when root node is excluded
    if (root->left && root->left->data!=(-1) && root->left->data<2000) {
    	
    	if (root->left->data>=2000){
    		size_excl += root->left->data -2000 + vCover(root->left->left, flag+1) + vCover(root->left->right, flag+1); 
		}
		else if (root->left->data<0){
			size_excl += root->left->data +2000 + vCover(root->left->left, flag+1) + vCover(root->left->right, flag+1);
		}
		else{
			size_excl += root->left->data + vCover(root->left->left, flag+1) + vCover(root->left->right, flag+1);
		}
	}
    if (root->right && root->right->data!=(-1) && root->right->data<2000) {
    	
    	if (root->right->data>=2000){
    		size_excl += root->right->data -2000 + vCover(root->right->left, flag+1) + vCover(root->right->right, flag+1); 
		}
		else if (root->right->data<0){
			
			size_excl += root->right->data +2000 + vCover(root->right->left, flag+1) + vCover(root->right->right, flag+1); 
		}
		else{
			size_excl += root->right->data + vCover(root->right->left, flag+1) + vCover(root->right->right, flag+1); 
		}
	}
	
    minCost= min(size_incl, size_excl);		//compare which is smaller
 
    if (minCost==size_incl){	//include root is smaller
    	if (root->data>=2000) root->data-=2000;
    	else if (root->data<0) root->data+=2000;
    	
		root->data+=2000;	//mark root as base
		
    	if (root->left && root->left->data!=(-1)){   		
    		if (root->left->data>=2000) root->left->data-=2000;
    		else if (root->left->data<0) root->left->data+=2000;
    		
			root->left->data-=2000;		
		}
		if (root->right && root->right->data!=(-1)){
					
			if (root->right->data>=2000) root->right->data-=2000;
  		  	else if (root->right->data<0) root->right->data+=2000;
  		  	
			root->right->data-=2000;
		}
	}
	else {		//exclude root is smaller
		
		if (root->data>=2000) root->data-=2000;
    	else if (root->data<0) root->data+=2000;
    	
		root->data-=2000;
		
		if (root->left && root->left->data!=(-1)) {
			
			if (root->left->data>=2000) root->left->data-=2000;
    		else if (root->left->data<0) root->left->data+=2000;
    		
			root->left->data+=2000;		//mark left child a base
		}
		if (root->right && root->right->data!=(-1)){
			
			if (root->right->data>=2000) root->right->data-=2000;
  		  	else if (root->right->data<0) root->right->data+=2000;
  		  	
			root->right->data+=2000;		//mark right child as base
		}
	}
	return minCost;
} 

int main(void )
{
	FILE *fp;
	FILE *write;
	write= fopen("output.txt", "w");
	if(write == NULL) {
  		perror("Error opening file");
   		return(-1);
   	}

	char file_name[60];
	for(int fileNum = 1; fileNum <= 1; fileNum++){
		sprintf(file_name, "test%d.txt", fileNum);		//Read file
		fp = fopen(file_name, "r");
		if(fp == NULL){
			perror("Error opening file");
      		return(-1);
		}
		else{	
			printf("Reading test%d.txt...\n", fileNum);	
			struct Queue* queue1= creatQ();
			
			char n=NULL, bound=NULL;
			int count=1, i, j, flag=0;		//count: 用來判斷是否為root   	dataNum: 每一個nodes傳入的值 
			struct TreeNode* root; struct TreeNode* node; struct TreeNode* temp;  
			minCost=0; t=0;
			bound=fgetc(fp);	//把最左邊的'['讀掉 
			while(1){
				if (n==']'){		//終止條件
					break;
				}	
									
				n=fgetc(fp);
				if (n=='n'){		//node為null 
					if (count==1){
						printf("Empty tree!\n"); break;
					}
					node=newNode(-1);
					temp= insertValue(node, -1, queue1);				
					count++;
				}	
				else if (n==']'){		//終止條件
					break;
				}
				else if (n>=48 && n<=57){	//node為數字(0~9) 				
					char str[10]={0}; 
					str[0]=n;
					n=fgetc(fp);				
					for (i=1; (n!=',' && n!=']'); i++){		//讀入剩下的數字				
						if (n==',' || n==']') break;
						str[i]=n;
						n=fgetc(fp);
					}
					int dataNum=atoi(str);		//將讀入的字元從char轉成int
				
					if (count==1){
						root= newRoot(dataNum, queue1);		//設為root 
					}
					else{
						node=newNode(dataNum);
						temp= insertValue(node, dataNum, queue1);
			
					}
					count++;
				}											
				while(n!=',' && n!=']' && n!='n' && n<48 && n>57){		//把剩下沒用的字母讀完，例如',' and 'ull' 
					n=fgetc(fp);
				}
			}
			minCost= vCover(root, flag);
			printf("minCost= %d\n\n", minCost);
			fprintf(write, "test%d: %d\n", fileNum, minCost);
			free(queue1);
			fclose(fp);			
		}			
	}
	fclose(write);		
	system("PAUSE");
	return 0;
}
