#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int *array1D(int size);
int maxSoFar, maxHere;
int getMaxSum(int *st, int start, int end, int qs, int qe, int index);
void modValue(int arr[], int *st, int n, int i, int mod_val);
void modValueUtil(int *st, int start, int end, int i, int diff, int index);
int getMidIndex(int start, int end);
int creatST(int array[], int sstart, int send, int *st, int sindex);
int *newST(int array[], int n);

void operation(char command, int num1, int num2, int *numArray, int num, FILE *wf);

int main(){
	FILE *rf;
	FILE *wf;
	
	rf = fopen("test1.txt", "r");
	wf = fopen("output1mine.txt", "w");
	if(rf == NULL || wf == NULL){
		printf("Failed opening file.\n");
		return 1;
	}else{
		printf("Reading file...\n");
		int taskTime;
		int num;
		
		int commandNum;
		char command;
		int num1;
		int num2;
		
		fscanf(rf, "%d\n", &taskTime);		
		for( int i = 0; i < taskTime; i++){
			int *numArray;
			fscanf(rf, "%d\n", &num);
			numArray = array1D(num);
			for(int j = 0; j < num; j++){
				fscanf(rf, "%d", &numArray[j]);
			}
			
			int *st;
			st = newST(numArray, num);
			
			fscanf(rf, "%d\n", &commandNum);
			for(int k = 0; k < commandNum; k++){
				command = fgetc(rf);
				fscanf(rf,"%d", &num1);
				fscanf(rf,"%d\n", &num2);
				if(command == 'P'){
					maxSoFar = INT_MIN;
					maxHere = 0;
					printf("%d \n", getMaxSum(st, 0, num-1, num1, num2, 0));
				}else{
					modValue(numArray, st, num-1, num1-1, num2);
				}
			}
			free(st);
			
		}
		printf("Program completed.\n");
		fclose(rf);
		fclose(wf);		
	}
	return 0;
} 

int *array1D(int size){
	int *x;
	x = (int *)malloc(size*sizeof(int));
	return x;
}

int getMaxSum(int *st, int start, int end, int qs, int qe, int index){
	if(qs <= start && qe >= end){
		maxHere = maxHere + st[index];
		if(maxSoFar < maxHere){
			maxSoFar = maxHere;
		}
		if(maxHere < 0){
			maxHere = 0;
		}
		return maxSoFar;
	}
		
		
	if(end < qs || start > qe)
		return 0;
		
	int mid = getMidIndex(start, end);
	
	return getMaxSum(st, start, mid, qs, qe, 2*index+1) +
			getMaxSum(st, mid+1, end, qs, qe, 2*index+2);
}
void modValueUtil(int *st, int start, int end, int i, int diff, int index){
	if(i < start || i > end){
		return;
	}
	
	st[index] = st[index] + diff;
	if(end!=start){
		int mid = getMidIndex(start, end);
		modValueUtil(st, start, mid, i, diff, 2*index+1);
		modValueUtil(st, mid+1, end, i, diff, 2*index+2);
	}
}

void modValue(int arr[], int *st, int num, int i, int mod_val){
	if(i < 0 || i > num){
		printf("Invalid inputed index.\n");
		return;
	}
	
	int diff = mod_val - arr[i];
	arr[i] = mod_val;
	
	modValueUtil(st, 0, num, i, diff, 0);
}


 
 int getMidIndex(int start, int end){
	return start + (end - start)/2;
}

int creatST(int array[], int start, int end, int *st, int index){
	if(start == end){
		st[index] = array[start];
		return array[start];
	}
	
	int mid = getMidIndex(start, end);
	st[index] = creatST(array, start, mid, st, index*2+1) +creatST(array, mid+1, end, st, index*2+2);
	
	return st[index];
}

int *newST(int array[], int num){
	//height of Segment tree
	int logNum = log(num)/log(2);
	int x = (int)(ceil(logNum));
	
	int max_size = 2*(int)pow(2,x) -1;
	
	int *segmentTree = (int*)malloc(max_size*sizeof(int));
	
	creatST(array, 0, num-1, segmentTree, 0);
	
	printf("\ntree\n");
	for(int i = 0; i < max_size; i++){
		printf("%d ", segmentTree[i]);
	}
	
	
	return segmentTree;
}
 
 
void operation(char command, int num1, int num2, int *numArray, int num, FILE *wf){
	int maxSoFar = INT_MIN, maxHere = 0;
	switch(command){
		case 'P':
			for(int i = num1; i <= num2 ;i++){
				maxHere = maxHere + numArray[i-1];
				
				if(maxSoFar < maxHere)
					maxSoFar = maxHere;
					
				if(maxHere < 0)
					maxHere = 0;
			}
			fprintf(wf, "%d\n", maxSoFar);
			break;
			
		case 'M':
			numArray[num1-1] = num2;
			break;
	}
}


