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
void printTheWay(char*** maze3D, int*** distance, char*** thisIsTheWay, int n, int moves);

	
int main(){
	FILE *rf;
	char fileName[50];
	
	for(int fileNumber = 1; fileNumber <= 100; fileNumber++){
		shortest=9999999;
		sprintf(fileName, "test%d.txt", fileNumber);
		rf = fopen(fileName, "r");
		if(rf == NULL){
			printf("File not found.\n");
			return 1;
		}else{
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
			
			FILE *wf;		
			sprintf(fileName, "test%d_ans.txt", fileNumber);
			wf = fopen(fileName, "w");
			if(wf == NULL){
				printf("Error creating Write file\n");
				return 1;
			}else{
				struct Q* queue;
				queue = creatQueue(MAX_QUEUE_SIZE);
				if(ShortestPath3D(queue,maze3D,distance, n, start)){
					//printf("%d\n", shortest);
					printTheWay(maze3D, distance, thisIsTheWay, n, shortest);
					fprintf(wf, "Path length: %d\n", shortest);
					fprintf(wf, "=====outMaze=====\n");
					nextN = n+2;
					for(int i = 0; i < n/2 +1; i++){
						for(int j = 0; j < nextN; j++){
							for(int k = 0; k < nextN; k++){
								//printf("%c ", thisIsTheWay[i][j][k]);
								if(j==0 || j == nextN-1 || k == 0 || k == nextN-1){
									continue;
								}
								fprintf(wf, "%c ", thisIsTheWay[i][j][k]);
							}
							//printf("\n");
							if(j==0 || j == nextN-1){
									continue;
								}
							fprintf(wf, "\n");
						}
						nextN = nextN -2; // when going up one floor n = n-2
						//printf("\n");
						fprintf(wf,"\n");
					}
				}else{
					fprintf(wf, "The path does not exist.\n");
				}
				fclose(wf);
				free(maze3D);
				free(thisIsTheWay);
				free(firstline);
				free(distance);
			
			}
			
		}
		
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
			int zMove = 1;
			nextPoint.x = point.x-1;
			nextPoint.y = point.y-1;
			if(maze3D[point.z][point.x][point.y] == 'D'){
				zMove = -1;
				nextPoint.x = point.x+1;
				nextPoint.y = point.y+1;
			}
			
			//nextPoint.x = point.x-1;
		//	nextPoint.y = point.y-1;
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
	
		
		//MOVES IN 4 DIRECTIONS
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

void printTheWay(char*** maze3D, int*** distance, char*** thisIsTheWay, int n, int moves){ // backtracking the way from F to S

	struct Node next;
	struct Node currentPoint = {1, 1, (n/2)};
	thisIsTheWay[n/2][1][1] = '*'; // set F to *
	
	while(moves != 0){
		
		//try first if can go down
		if(currentPoint.z > 0 && maze3D[currentPoint.z-1][currentPoint.x+1][currentPoint.y+1] == 'U' && ((moves == distance[currentPoint.z-1][currentPoint.x+1][currentPoint.y+1] +1) 
		|| (maze3D[currentPoint.z][currentPoint.x][currentPoint.y] == 'T' && moves == distance[currentPoint.z-1][currentPoint.x+1][currentPoint.y+1] +3))){
			//if cell at lower level is U and move difference is of 1 then can move down. When current cell is T then move differennce is 3.
				moves= moves -1;
				if(maze3D[currentPoint.z][currentPoint.x][currentPoint.y] == 'T'){
					moves = moves-2;
				}// move - 3 in total when current cell is T
				
				currentPoint.z = currentPoint.z -1;
				currentPoint.x = currentPoint.x +1;
				currentPoint.y = currentPoint.y +1;
				thisIsTheWay[currentPoint.z][currentPoint.x][currentPoint.y] = '*';
			
		}else if(maze3D[currentPoint.z+1][currentPoint.x-1][currentPoint.y-1] == 'D' && ((moves == distance[currentPoint.z+1][currentPoint.x-1][currentPoint.y-1] +1)
		|| (maze3D[currentPoint.z][currentPoint.x][currentPoint.y] == 'T' && moves == distance[currentPoint.z+1][currentPoint.x-1][currentPoint.y-1] +3))){
			//if cell at upper level is D and move difference is of 1 then can move up. When current cell is T then move differennce is 3.
			moves = moves -1;
			if(maze3D[currentPoint.z][currentPoint.x][currentPoint.y] == 'T'){
					moves = moves-2;
				}// move - 3 in total when current cell is T
				
			currentPoint.z = currentPoint.z +1;
			currentPoint.x = currentPoint.x -1;
			currentPoint.y = currentPoint.y -1;
			thisIsTheWay[currentPoint.z][currentPoint.x][currentPoint.y] = '*';
		}else{
			//if no up or down movement then try  x and y movements (4 total).
			for(int i = 0; i < 4; i++){
				next.x = rowMove[i] + currentPoint.x;
				next.y = colMove[i] + currentPoint.y;
				next.z = levelMove[i] + currentPoint.z;
				
				if(maze3D[next.z][next.x][next.y] != 'X' && (moves == distance[next.z][next.x][next.y] +1 && maze3D[currentPoint.z][currentPoint.x][currentPoint.y]!='T') 
				|| (moves == distance[next.z][next.x][next.y] +3 && maze3D[currentPoint.z][currentPoint.x][currentPoint.y]=='T')){
					//can move to next cell if move difference is of 1, if current cell id T then move difference is of 3.
					
					if(maze3D[currentPoint.z][currentPoint.x][currentPoint.y] == 'T'){
						moves = moves-2;
					} // move - 3 in total when current cell is T
					
					moves = moves -1;
					currentPoint.z = next.z;
					currentPoint.x = next.x;
					currentPoint.y = next.y;
					thisIsTheWay[currentPoint.z][currentPoint.x][currentPoint.y] = '*';
					
					
					break;
				}                                                                              
			
			}
		}
		if(moves == 0){
			thisIsTheWay[currentPoint.z][currentPoint.x][currentPoint.y] = '*';
		}
		//printf("Moves: %d\n", moves);
		//printf("position: %d, %d, %d\n\n", currentPoint.x, currentPoint.y, currentPoint.z);
		
	}
	
	
}


struct Q* creatQueue(unsigned capacity){
	struct Q* queue = (struct Q*)malloc(sizeof(struct Q)); 
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
		printf("queue is empty11\n");
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
		printf("queue is full\n");
		
	}
	queue->rear = (queue->rear +1) % queue->capacity;
	queue->array[queue->rear] = data;
	queue->size = queue->size + 1;
}

struct queueNode dequeue(struct Q* queue){
	if(isEmpty(queue)){
	printf("queue is empty22\n");
	
	}
	struct queueNode item = queue->array[queue->front];
	queue->front = (queue->front + 1) % queue->capacity;
	queue->size = queue->size - 1;
	return item;
}













