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

char* creatArr1D(int n);
char*** creatArr3D(int row, int col, int height);
int*** creatArr3Dint(int row, int col, int height);

int rowMove[4] = {-1,0,0,1};
int colMove[4] = {0,-1,1,0};
int levelMove[4] = {0,0,0,0};
int shortest= 9999999;
int pathCount=0;
int pcount=0;

void dfs(char*** maze3D, char*** visitedPath, struct Node point, int steps, int pcount, int inPpath);

	
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
			pathCount = 0;
			pcount = 0;
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
							if(maze3D[i][j][k] == 'P'){
								pcount++;
							}
							visitedPath[i][j][k] = maze3D[i][j][k];
						}
					}
					nextN = nextN -2; // when going up one floor n = n-2
				}
				fclose(rf);
				
					dfs(maze3D, visitedPath, start, 0, 0, 0);
					fprintf(wf, "Shortest path: %d, The number of different paths: %d\n\n", shortest, pathCount);
					printf("Shortest path: %d, The number of different paths: %d\n\n", shortest, pathCount);
				free(maze3D);
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

void dfs(char*** maze3D, char*** visitedPath, struct Node point, int steps, int ptaken, int inPpath){
	struct Node nextPoint;
	
	//when passing P +1 to passed through P
	if(maze3D[point.z][point.x][point.y] == 'P'){
		inPpath = 1;
		ptaken++;
	}
	//if passed P == amount of P in maze then already taken P path, so we leave the p path
	if(ptaken == pcount){
		inPpath = 0;
	}
	
	if(maze3D[point.z][point.x][point.y] == 'F' && ptaken == pcount){
		pathCount++;
		if(shortest> steps){
			shortest = steps;
		}
		return;
	}
	//set current posistion as visited so we do not come back
	visitedPath[point.z][point.x][point.y] = 'X';
	
	//moves up if encounter U or P
	if(maze3D[point.z][point.x][point.y] == 'U' || maze3D[point.z][point.x][point.y] == 'P'){
			nextPoint = point;
			nextPoint.x = point.x-1;
			nextPoint.y = point.y-1;
			nextPoint.z = nextPoint.z +1;
			
			//if we are still in P path when going up next position MUST be P 
			if(inPpath){
				if(visitedPath[nextPoint.z][nextPoint.x][nextPoint.y] != 'X' && maze3D[nextPoint.z][nextPoint.x][nextPoint.y] == 'P'){
					
					//set current posistion as visited so we do not come back
					visitedPath[nextPoint.z][nextPoint.x][nextPoint.y] = 'X';
					
					//enters recursion from the next point and return when all possible paths are taken
					dfs(maze3D, visitedPath, nextPoint, steps+1, ptaken, inPpath);
					
					//reset the next point as not visited when comming out the recursion
					visitedPath[nextPoint.z][nextPoint.x][nextPoint.y] = maze3D[nextPoint.z][nextPoint.x][nextPoint.y];
				}
				
			}else{
				//if not in P path we can go up normaly
				if(visitedPath[nextPoint.z][nextPoint.x][nextPoint.y]!= 'X'){
					
					//set current posistion as visited so we do not come back
					visitedPath[nextPoint.z][nextPoint.x][nextPoint.y] = 'X';
					
					//when encounter T trap adds 3 steps
					if(maze3D[nextPoint.z][nextPoint.x][nextPoint.y] == 'T'){
						
						//enters recursion from the next point and return when all possible paths are taken
						dfs(maze3D, visitedPath, nextPoint, steps+3, ptaken, inPpath);
						
						//reset the next point as not visited when comming out the recursion
						visitedPath[nextPoint.z][nextPoint.x][nextPoint.y] = maze3D[nextPoint.z][nextPoint.x][nextPoint.y];
					}else{
						//enters recursion from the next point and return when all possible paths are taken
						dfs(maze3D, visitedPath, nextPoint, steps+1, ptaken, inPpath);
						
						//reset the next point as not visited when comming out the recursion
						visitedPath[nextPoint.z][nextPoint.x][nextPoint.y] = maze3D[nextPoint.z][nextPoint.x][nextPoint.y];
	
					}
				}
			}
	}
	
	if((maze3D[point.z][point.x][point.y] == 'D' || maze3D[point.z][point.x][point.y] == 'P') && point.z > 0){
		nextPoint = point;
		nextPoint.x = point.x +1;
		nextPoint.y = point.y +1;
		nextPoint.z = nextPoint.z -1;
		
		if(inPpath){
			if(visitedPath[nextPoint.z][nextPoint.x][nextPoint.y] != 'X' && maze3D[nextPoint.z][nextPoint.x][nextPoint.y] == 'P'){
				//set current posistion as visited so we do not come back
				visitedPath[nextPoint.z][nextPoint.x][nextPoint.y] = 'X';
				
				//enters recursion from the next point and return when all possible paths are taken
				dfs(maze3D, visitedPath, nextPoint, steps+1, ptaken, inPpath);
				
				//reset the next point as not visited when comming out the recursion
				visitedPath[nextPoint.z][nextPoint.x][nextPoint.y] = maze3D[nextPoint.z][nextPoint.x][nextPoint.y];
			}	
		}else{
			if(visitedPath[nextPoint.z][nextPoint.x][nextPoint.y] != 'X'){
				//set current posistion as visited so we do not come back
				visitedPath[nextPoint.z][nextPoint.x][nextPoint.y] = 'X';
				
				if(maze3D[nextPoint.z][nextPoint.x][nextPoint.y] == 'T'){
					//when encounter T trap adds 3 steps
					//enters recursion from the next point and return when all possible paths are taken
					dfs(maze3D, visitedPath, nextPoint, steps+3, ptaken, inPpath);
					
					//reset the next point as not visited when comming out the recursion
					visitedPath[nextPoint.z][nextPoint.x][nextPoint.y] = maze3D[nextPoint.z][nextPoint.x][nextPoint.y];
				}else{
					//enters recursion from the next point and return when all possible paths are taken
					dfs(maze3D, visitedPath, nextPoint, steps+1, ptaken, inPpath);
					
					//reset the next point as not visited when comming out the recursion
					visitedPath[nextPoint.z][nextPoint.x][nextPoint.y] = maze3D[nextPoint.z][nextPoint.x][nextPoint.y];

				}
			}
		}
	}
	
	//try to move in all 4 directions 
	for(int i = 0; i < 4; i++){
		nextPoint.x = point.x + rowMove[i];
		nextPoint.y = point.y + colMove[i];
		nextPoint.z = point.z + levelMove[i];
		
		if(inPpath){
			if(visitedPath[nextPoint.z][nextPoint.x][nextPoint.y] != 'X' && maze3D[nextPoint.z][nextPoint.x][nextPoint.y] == 'P'){
				//set current posistion as visited so we do not come back
				visitedPath[nextPoint.z][nextPoint.x][nextPoint.y] = 'X';
				
				//enters recursion from the next point and return when all possible paths are taken
				dfs(maze3D, visitedPath, nextPoint, steps+1, ptaken, inPpath);
				
				//reset the next point as not visited when comming out the recursion
				visitedPath[nextPoint.z][nextPoint.x][nextPoint.y] = maze3D[nextPoint.z][nextPoint.x][nextPoint.y];
			}
		}else{
			if(visitedPath[nextPoint.z][nextPoint.x][nextPoint.y] != 'X'){
				//set current posistion as visited so we do not come back
				visitedPath[nextPoint.z][nextPoint.x][nextPoint.y] = 'X';
				
				if(maze3D[nextPoint.z][nextPoint.x][nextPoint.y] == 'T'){
					//when encounter T trap adds 3 steps
					//enters recursion from the next point and return when all possible paths are taken
					dfs(maze3D, visitedPath, nextPoint, steps+3, ptaken, inPpath);
					
					//reset the next point as not visited when comming out the recursion
					visitedPath[nextPoint.z][nextPoint.x][nextPoint.y] = maze3D[nextPoint.z][nextPoint.x][nextPoint.y];	
				}else{
					//enters recursion from the next point and return when all possible paths are taken
					dfs(maze3D, visitedPath, nextPoint, steps+1, ptaken, inPpath);
					
					//reset the next point as not visited when comming out the recursion
					visitedPath[nextPoint.z][nextPoint.x][nextPoint.y] = maze3D[nextPoint.z][nextPoint.x][nextPoint.y];

					}	
			}
			
		}
	}
}


