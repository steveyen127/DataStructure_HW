#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MALLOC(p,s)\
	if(!((p)=malloc(s))){\
		fprintf(stderr, "Insufficient Memory.");\
		exit(EXIT_FAILURE);\
	}


struct node{
	int sum;
	int prefixSum;
	int suffixSum;
	int maxSum;
};

struct node tree[1500000];
int max(int x, int y);
int *array1D(int size);
struct node SumMax(int arr[], int index, int low, int high, int qstart, int qend);
void build(int arr[], int low, int high, int index);
int findUltimateMax(int arr[], int numInt, int x1, int y1, int x2, int y2);
int findMaxSum(int arr[], int start, int end);

int main(){
	FILE *rf, *wf;
	
	rf = fopen("test3.txt", "r");
	wf = fopen("outputmine.txt", "w");
	
	if(rf == NULL || wf == NULL){
		printf("File opening error!\n");
		return -1;
	}else{
		printf("Reading file...\n");
		int workTime;
		int numInt;
		
		int comNum;
		fscanf(rf, "%d\n", &workTime);
		for(int j = 0; j < workTime; j++){
			int *arr;
			fscanf(rf, "%d\n", &numInt);
			arr = array1D(numInt);
			for(int i = 0; i < numInt; i++){
				fscanf(rf,"%d", &arr[i]);
			}
			build(arr, 0, numInt-1, 0);
			
			fscanf(rf, "%d\n", &comNum);
			int x1, x2, y1, y2;
			for(int i = 0; i < comNum; i++){
				fscanf(rf, "%d %d %d %d\n", &x1, &y1, &x2, &y2);
				fprintf(wf, "%d\n", findUltimateMax(arr, numInt, x1-1, y1-1, x2-1, y2-1));
			}	
		}
		
	}
	printf("Program Completed.\n");
	fclose(rf);
	fclose(wf);
	return 0;
}
int *array1D(int size){
	int *x;
	x = (int *)malloc(size*sizeof(int));
	return x;
}
int max(int x, int y){
	return (x>y)? x:y;
}

int findMaxSum(int arr[], int start, int end){
	int max_so_far = INT_MIN, max_ending_here = 0;
	
	if(start == end){
		return arr[start];
	}else if(start < end){
		for(int i = start; i <= end; i++){
			max_ending_here = max_ending_here + arr[i];
			if(max_so_far < max_ending_here){
				max_so_far = max_ending_here;
			}
		}
		return max_so_far;
	}else{
		for(int i = start; i >= end; i--){
			max_ending_here = max_ending_here + arr[i];
			if(max_so_far < max_ending_here){
				max_so_far = max_ending_here;
			}
		}
		return max_so_far;
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

int findUltimateMax(int arr[], int numInt, int x1, int y1, int x2, int y2){
	
	if(x2<=y1){
		int case1, case2, case3;
		case1 = case2 = case3 = INT_MIN;
		case1 = SumMax(arr, 0, 0,numInt-1, x2, y1).maxSum;
		if(x2-1 >= x1){
			case2 = 0;
			case2 = findMaxSum(arr, x2-1, x1) + findMaxSum(arr, x2, y2);
		}
		
		if(y1+1 <= y2){
			case3 = 0;
			case3 = findMaxSum(arr, y1, x1) + findMaxSum(arr, y1+1, y2);
		}
		
		return max(case1,max(case2, case3));
		
	}else{
			int middle=0;
			for(int i = y1+1; i < x2; i++){
				middle = middle + arr[i];
			}
		return findMaxSum(arr, y1, x1) + findMaxSum(arr, x2, y2) + middle;
	}
}

