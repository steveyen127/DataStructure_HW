#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct node{
	int sum;
	int prefixSum;
	int suffixSum;
	int maxSum;
};

int max(int x, int y);

struct node tree[1500000];

int *array1D(int size);
void modify(int arr[], int index, int low, int high, int i, int mod_value);
struct node SumMax(int arr[], int index, int low, int high, int qstart, int qend);
void build(int arr[], int low, int high, int index);
void operation(char command, int num1, int num2, int *numArray, int num, FILE *wf);

int main(){
	FILE *rf;
	FILE *wf;
	
	rf = fopen("test3.txt", "r");
	wf = fopen("output3mine.txt", "w");
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
			build(numArray, 0, num-1, 0);
				
			fscanf(rf, "%d\n", &commandNum);
			for(int k = 0; k < commandNum; k++){
				command = fgetc(rf);
				fscanf(rf,"%d", &num1);
				fscanf(rf,"%d\n", &num2);
				if(command == 'P'){
					fprintf(wf, "%d \n", SumMax(numArray, 0, 0, num-1, num1-1, num2-1).maxSum);
				}else{
					modify(numArray, 0, 0, num-1, num1-1, num2);
				}
			}
			
		}
		printf("Program completed.\n");
		fclose(rf);
		fclose(wf);		
	}
	return 0;
} 

int max(int x, int y){
	return (x>y)? x:y;
}


int *array1D(int size){
	int *x;
	x = (int *)malloc(size*sizeof(int));
	return x;
}


void build(int arr[], int low, int high, int index){
	if(low == high){
		tree[index].sum = arr[low];
		tree[index].prefixSum = arr[low];
		tree[index].suffixSum = arr[low];
		tree[index].maxSum = arr[low];
	}else{
		int mid = (low+high) / 2;
		
		build(arr, low, mid, 2*index + 1);
		
		build(arr, mid+1, high, 2*index +2);
		
		tree[index].sum = tree[2*index +1].sum + tree[2*index+2].sum;
		
		tree[index].prefixSum = max(tree[2*index+1].prefixSum, 
									tree[2*index+1].sum + tree[2*index+2].prefixSum);
		
		tree[index].suffixSum = max(tree[2*index+2].suffixSum, 
									tree[2*index+2].sum + tree[2*index+1].suffixSum);
		
		tree[index].maxSum = max(tree[index].prefixSum, 
								max(tree[index].suffixSum, 
									max(tree[2 * index + 1].maxSum, 
										max(tree[2 * index + 2].maxSum, 
											tree[2 * index + 1].suffixSum +  tree[2 * index + 2].prefixSum)))); 
	}
}

void modify(int arr[], int index, int low, int high, int i, int mod_value){
	if(low == high){
		tree[index].sum = mod_value;
		tree[index].prefixSum = mod_value;
		tree[index].suffixSum = mod_value;
		tree[index].maxSum = mod_value;
	}else{
		int mid = (low + high) / 2;
		
		if(i <= mid){
			modify(arr, 2*index +1, low, mid, i, mod_value);
		}else{
			modify(arr, 2*index+2, mid+1, high, i, mod_value);
		}
		
		tree[index].sum = tree[2*index +1].sum + tree[2*index +2].sum;
		
		tree[index].prefixSum = max(tree[2*index +1].prefixSum, 
									tree[2*index +1].sum + tree[2*index +2].prefixSum);
									
		tree[index].suffixSum = max(tree[2*index +2].suffixSum,
									tree[2*index +2].sum + tree[2*index +1].suffixSum);
									
		tree[index].maxSum = max(tree[index].prefixSum, 
                    			max(tree[index].suffixSum, 
                   					 max(tree[2 * index + 1].maxSum, 
                    					max(tree[2 * index + 2].maxSum, 
                    						tree[2 * index + 1].suffixSum + tree[2 * index + 2].prefixSum))));
	}
}

struct node SumMax(int arr[], int index, int start, int end, int qstart, int qend){
	struct node result;
	result.sum = result.prefixSum = result.suffixSum = result.maxSum = INT_MIN;
	
	//inputed range is not in this subtree
	if(qend < start || qstart > end){
		printf("invalid range.\n");
		return result;
	}
	//complete overlap of range
	if(qstart <= start && end <= qend){
		return tree[index];
	}
	
	int mid = (start + end) / 2;
	
	if(qstart > mid){
		return SumMax(arr, 2*index +2, mid +1, end, qstart, qend);
	}
	if(qend <= mid){
		return SumMax(arr, 2*index +1, start, mid, qstart, qend);
	}
	
	struct node left = SumMax(arr, 2*index +1, start, mid, qstart, qend);
	struct node right = SumMax(arr, 2*index +2, mid+1, end, qstart, qend);
	
	result.sum = left.sum + right.sum;
	result.prefixSum = max(left.prefixSum, left.sum + right.prefixSum);
	result.suffixSum = max(right.suffixSum, right.sum + left.suffixSum);
	result.maxSum = max(result.prefixSum, 
                    	max(result.suffixSum, 
                    		max(left.maxSum, 
                    			max(right.maxSum, left.suffixSum + right.prefixSum))));
                    			
    return result;
	
}
 


