#include <stdio.h>
#include <stdlib.h>

struct node{
	int prisoner;
	char liar;
	struct node* next;
};
struct node* last[600]={0};
struct node* array[600]={0};
int *realLiar;
int liarNum;
struct node* newNode2(int prisoner, char liar);
void insertEnd2(int arrayNum, int prisoner, char liar);
void printCombination(int arr[], int n, int r);
void combinationUtil(int arr[], int data[], int start, int end, int index, int r, int totalArray);
void initialize();

int main(){
	
	FILE *rf;
	FILE *wf;
	char fileName[50];
	int filenumber;
	wf = fopen("output.txt", "w");
	for(filenumber = 1; filenumber <= 3; filenumber++){
		sprintf(fileName, "test%d.txt", filenumber);
		rf = fopen(fileName, "r");
		if(rf == NULL){
			printf("Failed opening file.\n");
			return -1;
		}else{
			printf("Reading %s...\n", fileName);
			initialize();
			int prisonerNum;
			char ch;
			int chInt;
			int arrayNum=0;
			int totalArray=0;
			fscanf(rf, "%d\n", &prisonerNum);
			fscanf(rf, "%d\n", &liarNum);
			int prisoner[prisonerNum];
			for(int i = 0; i < prisonerNum; i++){
				prisoner[i]= i;
			}
			
			ch = fgetc(rf);
			while(ch!=EOF){
				if(ch == 'T' || ch== 'L'){
					insertEnd2(arrayNum,-1, ch);
					ch = fgetc(rf);
				}else if(ch >= 48 && ch <= 57){
					char number[2]={0};
					for(int i = 0; ch != '=' && ch!= '>'; i++){
						number[i] = ch;
						ch = fgetc(rf);
					}
					chInt = atoi(number);
					insertEnd2(arrayNum, chInt, 'T');
				}else if(ch == '\n'){
					arrayNum++;
					ch = fgetc(rf);
				}else{ 
					ch= fgetc(rf);
				}
			}
			realLiar = (int*)malloc(liarNum* sizeof(int));
			
	    	int data[liarNum]; 
			totalArray = arrayNum+1;
			combinationUtil(prisoner, data, 0, prisonerNum-1, 0, liarNum, totalArray);
			if(wf == NULL){
				printf("Failed creating output file.\n");
				return -1;
			}else{
				fprintf(wf, "test%d: ", filenumber);
				for(int p = 0; p < liarNum; p++){
				fprintf(wf,"%d ", realLiar[p]);
		 }
			fprintf(wf,"\n");	
			}
			fclose(rf);
		}	
	}
	printf("Program complete.\n");
	fclose(wf);
	return 0;
}
void initialize(){
	for(int i = 0; i < 600; i++){
		array[i]=0;
		last[i]=0;
	}
}

struct node* newNode2(int prisoner, char liar){
	struct node* n;
	n = (struct node*)malloc(sizeof(struct node));
	n->prisoner = prisoner;
	n->liar = liar;
	return n;
}
void insertEnd2(int arrayNum, int prisoner,  char liar){
	struct node *temp = newNode2(prisoner, liar);
	
	if(array[arrayNum] == NULL){
		array[arrayNum] = temp;
		last[arrayNum] = temp;
	}else{
		last[arrayNum]->next = temp;
		last[arrayNum] = temp;
	}
}
int isLiar(int *data, int prisoner){
	for(int i = 0; i < liarNum; i++){
		if(data[i]==prisoner){
			return 1;
		}
	}
	return 0;
}
int findLiar(int *data, int j){
	struct node* temp;
	temp = array[j];
	if(isLiar(data,temp->prisoner)){
			temp->liar = 'L';	
		}else{
			temp->liar = 'T';
		}
		//printf("first: %d ", temp->prisoner);
	while(1){
		if(temp->liar == 'L'){
			if(isLiar(data,temp->next->prisoner)){
				temp->next->liar = 'T';
			}else{
				temp->next->liar = 'L';
			}
		}else{
			if(isLiar(data,temp->next->prisoner)){
				temp->next->liar = 'L';
			}else{
				temp->next->liar = 'T';
			}
		}
		//printf("%c ", temp->liar);
		temp= temp->next;
		if(temp->next == last[j]){
		
			if(temp->liar == temp->next->liar){
				
				return 1;
			}else{
				return 0;
			}
		}	
	}
}
void combinationUtil(int arr[], int data[], int start, int end, int index, int r, int totalArray) 
{ 	int ans = 0;
    // Current combination is ready to be printed, print it 
    if (index == r) 
    { 	
////    for(int p = 0; p < liarNum; p++){
////        	printf("%d ", data[p]);
////		}
////		printf("\n");
    	int ans;
        for (int j=0; j<totalArray; j++){
        	ans = findLiar(data, j);
//        	printf("ans: %d ", ans);
//        	printf("\n");
        	if(!ans){
        		return;
			}
		}
        for(int p = 0; p < liarNum; p++){
        	realLiar[p] = data[p];
		}
        return; 
    } 
  
    for (int i=start; i<=end && end-i+1 >= r-index; i++) 
    { 
        data[index] = arr[i]; 
        combinationUtil(arr, data, i+1, end, index+1, r, totalArray); 
    } 
} 
