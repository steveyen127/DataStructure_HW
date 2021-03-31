#include <stdio.h>
#include <stdlib.h>
#define MALLOC(p,s)\
	if(!((p)=malloc(s))){\
	fprintf(stderr,"Insufficient memory\n");\
	exit(EXIT_FAILURE);\
	}

struct pview{
	int *count;
	int mirror;
};

struct mnode{
	struct pview pov[4];
	char mons;
};

void dfs1(FILE *wf,struct mnode **mainsion,int x, int y, int v, int z, int g, int size);

int flag;
int **vision;
int moveX[4]= {1,-1,0,0};
int moveY[4]= {0,0,1,-1};
int main(){
	FILE *rf, *wf;
	rf = fopen("test1.txt", "r");////////////////////cahnge file names here;
	wf = fopen("output.txt", "w");//////////////
	
	if(rf == NULL || wf == NULL){
		printf("File openning error\n");
		exit(1);
	}
	printf("Program started.\n");
	
	int v,z,g,size;
	struct mnode **mansion;
	fscanf(rf,"%d %d %d\n%d", &v, &z, &g, &size);
	
	mansion = malloc(size * sizeof *mansion);
	for(int i = 0; i < size; i ++){
		mansion[i] = malloc(size * sizeof *mansion[i]);
	}
	
	vision= malloc(4 * sizeof *vision);
	for(int i = 0; i < 4; i++){
		vision[i] = malloc(size * sizeof *vision[i]);
	}
	
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < size; j++){
			fscanf(rf,"%d ", &vision[i][j]);
		}
	}
	
	
	for(int i = 0; i < size; i++){
		for(int j = 0; j <size; j++){
			mansion[i][j].mons = fgetc(rf);
			for(int k = 0; k < 4; k++){
				mansion[i][j].pov[k].count = NULL;
			}
		}
		fgetc(rf);
	}
	
	for(int i = 0; i < 4; i++){
		for(int j = 0; j <size; j++){
			int current = i;
			int x,y;
			int flagM=0;
			switch(i){
				case 0: x=0; y=j; break;
				case 1: x=size-1; y=j; break;
				case 2: x=j; y=0; break;
				case 3: x=j; y=size-1; break;
			}
			while(x >-1 && x < size && y > -1 && y < size){
				if(mansion[x][y].mons == '/'){
					switch(current){
						case 0: current = 3;break;
						case 1: current = 2;break;
						case 2: current = 1;break;
						case 3: current = 0;break;
					}
					flagM=1;
				}
				else if(mansion[x][y].mons =='\\'){
					switch(current){
						case 0: current = 2;break;
						case 1: current = 3;break;
						case 2: current = 0;break;
						case 3: current = 1;break;
					}
					flagM=1;
				}
				else{
					mansion[x][y].pov[current].count = &vision[i][j];
					mansion[x][y].pov[current].mirror = flagM;
				}
				x = x + moveX[current];
				y = y + moveY[current];
			}
		}
	}

	
	flag = 0;
	dfs1(wf,mansion,0,0,v,z,g,size);
	free(vision);
	free(mansion);
	fclose(rf);
	fclose(wf);
	printf("Program completed.\n");
	return 0;
}


void dfs1(FILE* wf,struct mnode **mansion,int x, int y, int v, int z, int g, int size){

	 if(flag == 1){
	 	return;
	 }
	 else if(x==size && y==size){
	 	for(int i = 0; i < 4; i++){
	 		for(int j = 0; j < size; j++){
	 			if(vision[i][j]!=0){
	 				flag = 1;
				 }
			 }
		}
			 if(flag == 0){
			 	for(int i = 0; i < size; i++){
			 		for(int j = 0; j < size; j ++){
			 			fprintf(wf,"%c", mansion[i][j].mons);
					 }
					 fprintf(wf,"\n");
				 }
			 }else{
			 	flag = 0;
			 }
			 return;
	 }
	 else if(mansion[x][y].mons != '.'){
	 	if(x==size-1 && y==size-1){
	 		dfs1(wf,mansion,x+1,y+1,v,z,g,size);
		 }
	 	else if(y==size-1){
	 		dfs1(wf,mansion,x+1,0,v,z,g,size);
		 }else{
		 	dfs1(wf,mansion,x,y+1,v,z,g,size);
		 }
	 }
	 else{
	 	if(z>0){
	 		mansion[x][y].mons = 'Z';
	 		for(int i = 0; i < 4; i ++){
	 			if(mansion[x][y].pov[i].count){
	 				*mansion[x][y].pov[i].count = *mansion[x][y].pov[i].count - 1;	
	 				if(*mansion[x][y].pov[i].count<0)
	 					flag = 1;
				 }
			 }
			 if(x==size-1 && y==size-1){
	 			dfs1(wf,mansion,x+1,y+1,v,z-1,g,size);
		 	}	
			else if(y==size-1){
	 			dfs1(wf,mansion,x+1,0,v,z-1,g,size);
		 	}else{
		 		dfs1(wf,mansion,x,y+1,v,z-1,g,size);
		 	}
		 	flag=0;
		 	for(int i = 0; i < 4; i ++){
		 		if(mansion[x][y].pov[i].count){
		 			*mansion[x][y].pov[i].count = *mansion[x][y].pov[i].count+1;	
				 }
	 		}
	 			
		 }
		 if(v>0){
	 		mansion[x][y].mons = 'V';
	 		for(int i = 0; i < 4; i ++){
	 			if(mansion[x][y].pov[i].count && mansion[x][y].pov[i].mirror==0){
	 				*mansion[x][y].pov[i].count = *mansion[x][y].pov[i].count - 1;	
	 				if(*mansion[x][y].pov[i].count<0)
	 					flag = 1;
				 }
			 }
			 if(x==size-1 && y==size-1){
	 			dfs1(wf,mansion,x+1,y+1,v-1,z,g,size);
		 	}
			 else if(y==size-1){
	 			dfs1(wf,mansion,x+1,0,v-1,z,g,size);
		 	}else{
		 		dfs1(wf,mansion,x,y+1,v-1,z,g,size);
		 	}
		 	flag=0;
		 	for(int i = 0; i < 4; i ++){
	 			if(mansion[x][y].pov[i].count && mansion[x][y].pov[i].mirror==0){
	 				*mansion[x][y].pov[i].count = *mansion[x][y].pov[i].count+1;	
				 }
			 }
			 
		 }
		 if(g>0){
	 		mansion[x][y].mons = 'G';
	 		for(int i = 0; i < 4; i ++){
	 			if(mansion[x][y].pov[i].count && mansion[x][y].pov[i].mirror==1){
	 				*mansion[x][y].pov[i].count = *mansion[x][y].pov[i].count - 1;	
	 				if(*mansion[x][y].pov[i].count<0)
	 					flag = 1;
				 }	 
			}
			 if(x==size-1 && y==size-1){
	 			dfs1(wf,mansion,x+1,y+1,v,z,g-1,size);
		 	}
			 else if(y==size-1){
	 			dfs1(wf,mansion,x+1,0,v,z,g-1,size);
		 	}else{
		 		dfs1(wf,mansion,x,y+1,v,z,g-1,size);
		 	}
		 	flag=0;
		 	for(int i = 0; i < 4; i ++){
	 			if(mansion[x][y].pov[i].count && mansion[x][y].pov[i].mirror==1){
	 				*mansion[x][y].pov[i].count = *mansion[x][y].pov[i].count+1;	
				 }
			 }	
		}
		mansion[x][y].mons = '.';
	 }
}

