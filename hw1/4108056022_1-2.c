#include <stdio.h>
#define MAX_QUEUE_SIZE 400

struct Node{
	int x;
	int y;
};

struct queueNode{
	struct Node point;
	int distance;
};

int front= -1;
int rear= -1;
int n;
struct queueNode queue[MAX_QUEUE_SIZE];



//movements of from cell
int rowMove[4] = {-1,0,0,1};
int colMove[4] = {0,-1,1,0};
int ShortestPath(char maze[n][n], struct Node start, struct Node fin);
void addq(struct queueNode data);
struct queueNode deleteq();
struct queueNode pathtaken[MAX_QUEUE_SIZE];
int moveNumber =0;


int main(){
	FILE *rf;
	
	rf = fopen("test3.txt","r");
	if(rf == NULL){
		printf("Could not open file.\n");
		return 1;
	}
	
	fscanf(rf,"%d", &n);
	
	int steps;
	char maze[n][n]; // MAIN MAZE
	struct Node start; // STARTING POSITION
	struct Node fin;  // END POSITION
	
	// SCAN MAZE FROM TXT
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			fscanf(rf," %c ", &maze[i][j]);
			if(maze[i][j] == 'S'){
				start.x = i;
				start.y = j;
			}
			if(maze[i][j] == 'F'){
				fin.x = i;
				fin.y = j;
			}
		}
	}
	
	fclose(rf);
	
	struct Node laststep = fin; //THE STARTING POINT (END) OF BACKTRACKING
	
	//FIND SHORTEST PATH AND SAVE THE PATH TAKEN IN TOTAL
	if(ShortestPath(maze, start, fin) != -1){
		steps = ShortestPath(maze, start, fin);
		struct Node thisIsTheWay[steps];
		int backstep = steps-1;
		int stepcounter = 0;
		
		//BACKTRACKING THE CORRECT PATH
		for(int s = moveNumber; s >= 0; s--){
			if(pathtaken[s].distance == backstep && ((pathtaken[s].point.x == laststep.x - 1 && pathtaken[s].point.y == laststep.y) || (pathtaken[s].point.x == laststep.x && pathtaken[s].point.y == laststep.y - 1) || (pathtaken[s].point.x == laststep.x && pathtaken[s].point.y == laststep.y + 1) || (pathtaken[s].point.x == laststep.x + 1 && pathtaken[s].point.y == laststep.y))){
				thisIsTheWay[stepcounter++] = pathtaken[s].point;
				laststep = pathtaken[s].point;
				backstep--;
			}
		}
		
		//INTRODUCING THE CORRECT PATH IN TO THE MAZE
		for(stepcounter = 0; stepcounter < steps; stepcounter++){
			for(int i = 0; i < n; i++){
				for(int j = 0; j < n; j++){
					if(thisIsTheWay[stepcounter].x == i && thisIsTheWay[stepcounter].y == j){
						maze[i][j] = '*';
					}else if((start.x == i && start.y == j) || (fin.x == i && fin.y == j)){
						maze[i][j] = '*';
					}
				}
			}
		}
		printf("========OutTheMaze========\n");
		for(int q = 0; q < n; q++){
			for(int p = 0; p < n; p++){
				printf("%c ", maze[q][p]);
			}
			printf("\n");
		}
		printf("\nShortest Path Lenght: %d\n", steps);
	}else{
		printf("No path found.\n");
	}
	
	
	
	
	return 0;

}


int ShortestPath(char maze[n][n], struct Node start, struct Node fin){
	
	
	int unvisited[n][n];
	
	//setting all cells as unvisited
	for(int q = 0; q < n; q++){
		for(int p = 0; p < n; p++){
			unvisited[q][p] = 1;
		}
	}
	
	//Starting distance set to 0
	struct queueNode s = {start, 0};
	//adds starting point to the queue
	addq(s);
	
	while(front != rear){
		struct queueNode curr = queue[front+1];
		struct Node point = curr.point;
		
		//if reached the end F, returns distance
		if(point.x == fin.x && point.y == fin.y){
			return curr.distance;
		}
		
		//SAVING THE PATH TAKEN
		pathtaken[moveNumber] = deleteq();
		moveNumber++;
		
		//MOVES IN ALL DIRECTIONS
		for(int i = 0; i < 4; i++){
			int row = point.x + rowMove[i];
			int col = point.y + colMove[i];
			
			if(row >= 0 && row < n && col >= 0 && col < n && unvisited[row][col]== 1 && maze[row][col] != 'X'){
				unvisited[row][col] = 0;
				struct queueNode AdjCell = {{row,col}, curr.distance+1};
				addq(AdjCell);
				
				};	
		};
			
	}
	
	return -1;
}

void addq(struct queueNode data){
	if(rear == MAX_QUEUE_SIZE -1){
		printf("Queue is full\n");
	}
	rear = rear + 1;
	queue[rear] = data;
}

struct queueNode deleteq(){
	struct queueNode item;
	if(rear == front){
		printf("Queue is empty\n");
	}
	front = front + 1;
	item = queue[front];
	return item;
}
