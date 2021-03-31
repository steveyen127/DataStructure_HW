#include <stdio.h> 
#include <stdlib.h> 
#define MAX_QUEUE_SIZE 300
#define MAX_N 14
#define MALLOC(p,s)\
    if(!((p)=malloc(s))){\
        fprintf(stderr,"Insufficient memory");\
        exit(EXIT_FAILURE);\
    }

struct Node{
	int x;
	int y;
	int z;
};

struct queueNode{
	struct Node point;
	int distance;
};

struct Q{
	int rear, front, size;
	unsigned capacity;
	struct queueNode* array;
};

char* creatArr1D(int n);
char*** creatArr3D(int row, int col, int height);
int*** creatArr3Dint(int row, int col, int height);

struct Q* creatQueue(unsigned capacity);
int isFull(struct Q* queue);
int isEmpty(struct Q* queue);
struct queueNode front(struct Q* queue);
struct queueNode rear(struct Q* queue);
void enqueue(struct Q* queue, struct queueNode data);
struct queueNode dequeue(struct Q* queue);

int rowMove[6] = {-1,0,0,1,0,0};
int colMove[6] = {0,-1,1,0,0,0};
int levelMove[6] = {0,0,0,0,1,-1};
int shortest= 9999999;

int ShortestPath3D(struct Q* queue, char*** maze3D, int*** distance, int n, struct Node start);
int dfs(char*** maze3D, char*** visitdePath, struct Node start, int maxSteps);

	
int main(){
	FILE *rf;
	FILE *wf;
	char fileName[50];
	
	wf = fopen("output.txt", "w");
	if(wf == NULL){
		printf("Failed at creating output.txt\n");
		return 1;
	}else{
		for(int fileNumber = 1; fileNumber <= 100; fileNumber++){
			shortest=9999999;
			sprintf(fileName, "test%d.txt", fileNumber);
			rf = fopen(fileName, "r");
			if(rf == NULL){
				printf("File not found.\n");
				return 1;
			}else{
				fprintf(wf, "test %d start now.\n", fileNumber);
				printf("test %d start now.\n", fileNumber);
				printf("Reading File %s.\n", fileName);
				char* firstline = creatArr1D(MAX_N);
				struct Node start;
				int n=0; // lenght of first line
				char c;
				//read first line of file and save in firstline arr while counting n
				
				firstline[n] = fgetc(rf);
				while(firstline[n]!= '\n'){
					n++;
					fgetc(rf);
					firstline[n] = fgetc(rf);
				}
				
				char*** maze3D = creatArr3D(n+2, n+2, (n/2)+1);
				char*** visitedPath = creatArr3D(n+2, n+2, (n/2)+1);
				char*** thisIsTheWay = creatArr3D(n+2, n+2, (n/2)+1);
				int*** distance = creatArr3Dint(n+2, n+2, (n/2)+1);
				
				int nextN = n+2;
				for(int i = 0; i < n/2 +1; i++){
					for(int j = 0; j < nextN; j++){
						for(int k = 0; k < nextN; k++){
							if(j==0 || j == nextN-1 || k == 0 || k == nextN-1){
								maze3D[i][j][k] = 'X'; // surround every floor with X
							}
							else if(i==0 && j==1){
								maze3D[i][j][k] = firstline[k-1];
							}
							else {
								fscanf(rf, "%c ", &maze3D[i][j][k]);
							}
							if(maze3D[i][j][k] == 'S'){
								start.x = j;
								start.y = k;
								start.z = i;
							}
							//printf("%c ", maze3D[i][j][k]);
							visitedPath[i][j][k] = maze3D[i][j][k];
							thisIsTheWay[i][j][k] = maze3D[i][j][k];
						}
						//printf("\n");
					}
					nextN = nextN -2; // when going up one floor n = n-2
					//printf("\n");
				}
				fclose(rf);
				
				
				struct Q* queue;
				queue = creatQueue(MAX_QUEUE_SIZE);
				if(ShortestPath3D(queue,maze3D,distance, n, start)){
					int pathNumber;
					pathNumber = dfs(maze3D, visitedPath, start, shortest+5);
					fprintf(wf, "Shortest path: %d, Limit: %d, The number of different paths: %d\n\n", shortest, shortest+5, pathNumber);
					printf("Shortest path: %d, Limit: %d, The number of different paths: %d\n\n", shortest, shortest+5, pathNumber);
					//printf("%d\n", pathNumber);
				}
				free(maze3D);
				free(thisIsTheWay);
				free(firstline);
				free(distance);	
				
			}
		}
		fclose(wf);
	}
	return 0;	
}
	

char* creatArr1D(int n){
	char* arr1d;
	MALLOC(arr1d, n*sizeof(char*));
	return arr1d;
}
char*** creatArr3D(int row, int col, int height){
	char*** arr3d;
	MALLOC(arr3d, row* sizeof(char**));
	for(int i = 0; i < row; i++){
		MALLOC(arr3d[i], col* sizeof(char**));
		for(int j = 0; j < col; j++){
			MALLOC(arr3d[i][j], height* sizeof(char***));
		}
	}
	return arr3d;
}
int*** creatArr3Dint(int row, int col, int height){
	int*** arr3d;
	MALLOC(arr3d, row* sizeof(int**));
	for(int i = 0; i < row; i++){
		MALLOC(arr3d[i], col* sizeof(int**));
		for(int j = 0; j < col; j++){
			MALLOC(arr3d[i][j], height* sizeof(int***));
		}
	}
	return arr3d;
}

int ShortestPath3D(struct Q* queue, char*** maze3D, int*** distance, int n, struct Node start){
	
	int pathFound =0; // set no path found as default
	struct Node nextPoint;
	
	//setting all cells as maximum ditance possibl; 455 steps for max n =13
	for(int i = 0 ; i < (n/2)+1; i++){
		for(int j = 0; j < n+2; j++){
			for(int k = 0; k < n+2; k++){
				distance[i][j][k] = 455;
			}
		}
	}
	
	distance[start.z][start.x][start.y] = 0;
	
	//Starting distance set to 0
	struct queueNode s = {start, 0};
	
	//adds starting point to the queue
	enqueue(queue, s);
	while(queue->size!=0){
		
		struct queueNode curr = front(queue);
		//struct queueNode curr = dequeue(queue);
		struct Node point = curr.point;
		dequeue(queue);
		//printf("current point: %d, %d, %d\n", point.x, point.y, point.z);
		//printf("current distance: %d\n\n", distance[point.z][point.x][point.y]);
		
		//if reached the end F, compares path lenght and save the shortest
		if(maze3D[point.z][point.x][point.y] == 'F'){
			if(shortest > distance[point.z][point.x][point.y]){
				shortest = distance[point.z][point.x][point.y];
			}
			pathFound = 1; // set path as found;
		}
		
		//When D or U is found
		
		if(maze3D[point.z][point.x][point.y] == 'D' || maze3D[point.z][point.x][point.y] == 'U'){
			//printf("found D or U\n");
			nextPoint.x = point.x-1;
			nextPoint.y = point.y-1;
			int zMove = 1;
			if(maze3D[point.z][point.x][point.y] == 'D'){
				nextPoint.x = point.x+1;
				nextPoint.y = point.y+1;
				zMove = -1;
			}
			
			//nextPoint.x = point.x-1;
			//nextPoint.y = point.y-1;
			nextPoint.z = point.z + zMove;
			
			if(nextPoint.z >= 0){
				if(maze3D[nextPoint.z][nextPoint.x][nextPoint.y] != 'X' && distance[nextPoint.z][nextPoint.x][nextPoint.y] > distance[point.z][point.x][point.y]+1){
					distance[nextPoint.z][nextPoint.x][nextPoint.y] = distance[point.z][point.x][point.y]+1;
					curr.distance = curr.distance +1;
					if(maze3D[nextPoint.z][nextPoint.x][nextPoint.y] == 'T'){
						distance[nextPoint.z][nextPoint.x][nextPoint.y] = distance[nextPoint.z][nextPoint.x][nextPoint.y] +2;
						curr.distance = curr.distance+2;
					}
					struct queueNode nextCell = {{nextPoint.x, nextPoint.y, nextPoint.z}, curr.distance};
					enqueue(queue, nextCell);
				}
			}
			
		}
	
		
		//MOVES IN ALL DIRECTIONS
		for(int i = 0; i < 4; i++){
			 nextPoint.x = point.x + rowMove[i];
			 nextPoint.y = point.y + colMove[i];
			 nextPoint.z = point.z + levelMove[i];
			
			if(maze3D[nextPoint.z][nextPoint.x][nextPoint.y] != 'X' && distance[nextPoint.z][nextPoint.x][nextPoint.y] > distance[point.z][point.x][point.y]+1 ){
				
				distance[nextPoint.z][nextPoint.x][nextPoint.y] = distance[point.z][point.x][point.y]+1;
				curr.distance = curr.distance +1;
				
				if(maze3D[nextPoint.z][nextPoint.x][nextPoint.y] == 'T'){
					distance[nextPoint.z][nextPoint.x][nextPoint.y] = distance[nextPoint.z][nextPoint.x][nextPoint.y] +2;
					curr.distance = curr.distance+2;
				}
				
				struct queueNode nextCell = {{nextPoint.x, nextPoint.y, nextPoint.z}, curr.distance};
				enqueue(queue, nextCell);
			}	
		}
			
	}
	
	return pathFound;
}

int dfs(char*** maze3D, char*** visitedPath, struct Node point, int maxSteps){
	int count=0;
	struct Node nextPoint;
	
	// returns 0 if maxSteps runs out and still dont find F
	if( (maxSteps<=0 && maze3D[point.z][point.x][point.y] != 'F') || maxSteps < 0 || maze3D[point.z][point.x][point.y] == 'X' || visitedPath[point.z][point.x][point.y] == 'X'){
		return 0;
	}
	
	// return 1 if found F == 1 path found
	if(maze3D[point.z][point.x][point.y] == 'F' && maxSteps >= 0){
		return 1;
	}
	
	visitedPath[point.z][point.x][point.y] = 'X'; // marking  path already taken
	
	if(maze3D[point.z][point.x][point.y] == 'T'){ // -3 steps when pass T
		maxSteps = maxSteps - 3;
	}else{
		maxSteps = maxSteps -1;
	}
	
	//printf("%d\n", maxSteps);
	//printf("point: %d, %d, %d\n\n", point.x, point.y, point.z);
	
	//try to move in all 4 directions ultil return 0
	for(int i = 0; i < 4; i++){
		nextPoint.x = point.x + rowMove[i];
		nextPoint.y = point.y + colMove[i];
		nextPoint.z = point.z + levelMove[i];
		
        count = count + dfs(maze3D, visitedPath, nextPoint, maxSteps);
	}
	
	// move up if at U or move down at D, and keep moving until return 0 
	if(maze3D[point.z][point.x][point.y] == 'U'){
		nextPoint = point;
		nextPoint.x = point.x -1;
		nextPoint.y = point.y -1;
		nextPoint.z = nextPoint.z +1;
		
    	count = count + dfs(maze3D, visitedPath, nextPoint, maxSteps);
	}
	else if(maze3D[point.z][point.x][point.y] == 'D' && point.z > 0){
		nextPoint = point;
		nextPoint.x = point.x +1;
		nextPoint.y = point.y +1;
		nextPoint.z = nextPoint.z -1;
		
        count = count + dfs(maze3D, visitedPath, nextPoint, maxSteps);
	}
	
	//reset visitedPath for other posible paths
	visitedPath[point.z][point.x][point.y] = maze3D[point.z][point.x][point.y];
	
	return count;
}


struct Q* creatQueue(unsigned capacity){
	struct Q* queue = (struct Q*)malloc( 
        sizeof(struct Q)); 
    queue->capacity = capacity; 
    queue->front = queue->size = 0; 
  
    queue->rear = capacity - 1; 
    queue->array = (struct queueNode*)malloc(queue->capacity * sizeof(struct queueNode)); 
    return queue; 
}
int isFull(struct Q* queue){
	return (queue->size == queue->capacity);
}
int isEmpty(struct Q* queue){
	return (queue->size == 0);
}
struct queueNode front(struct Q* queue){
	if(isEmpty(queue)){
		//printf("queue is empty11\n");
	}
	return queue->array[queue->front];
}
struct queueNode rear(struct Q* queue){
	if(isEmpty(queue)){
		printf("queue is empty\n");
	}
	return queue->array[queue->rear];
}
void enqueue(struct Q* queue, struct queueNode data){
	if(isFull(queue)){
		//printf("queue is full\n");
		
	}
	queue->rear = (queue->rear +1) % queue->capacity;
	queue->array[queue->rear] = data;
	queue->size = queue->size + 1;
}
struct queueNode dequeue(struct Q* queue){
	if(isEmpty(queue)){
	//printf("queue is empty22\n");
	
	}
	struct queueNode item = queue->array[queue->front];
	queue->front = (queue->front + 1) % queue->capacity;
	queue->size = queue->size - 1;
	return item;
}













