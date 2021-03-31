#include <stdio.h>
#include <stdlib.h>

	
struct view{
	int *count;
	int mirror;
};
	
struct node{
	char type;
	struct view pov[4];
};

void dfss(int);	
void print();

int **vision;
int move[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
int v,z,g,size,mark;
int flag;
struct node *manor;
int *vptr;

int main(){
	FILE *rf, *wf;
	
	rf = fopen("test1.txt", "r");
	wf = fopen("outputMine1.txt", "w");
	
	if(rf == NULL || wf == NULL){
		printf("Failed openning files\n");
		exit(1);
	}else{
		
		fscanf(rf, "%d %d %d\n%d", &v, &z, &g, &size);
		struct node mansion[size][size];
		int vission[4][size];
		
		for(int i = 0; i < 4; i++){
			for(int j = 0; j < size; j++){
				fscanf(rf,"%d ", &vission[i][j]);
			}
			fscanf(rf,"\n");
		}
		
		
		for(int i = 0; i < size; i++){
			for(int j = 0; j <size; j++){
				mansion[i][j].type = fgetc(rf);
				for(int k = 0; k < 4; k++){
					mansion[i][j].pov[k].count = NULL;
				}
				//printf("%c ", mansion[i][j].type);
			}
		//	printf("\n");
			fscanf(rf,"\n");
		}
		
		for(int i = 0 ; i < 4; i++){
			for(int j = 0; j < size; j++){
				int curr_dir = i;
				int x,y;
				int flagM=0;
				switch(i){
					case 0: x=0;   y=j;break;
					case 1: x=size-1; y=j;break;
					case 2: x=j;   y=0;break;
					case 3: x=j; y=size-1;break;
				}
				
				while(x>-1 && x<size && y>-1 && y<size){
					if(mansion[x][y].type == '\\'){
						switch(curr_dir){
							case 0: curr_dir = 2; break;
							case 1: curr_dir = 3; break;
							case 2: curr_dir = 0; break;
							case 3: curr_dir = 1; break;
						}
						flagM = 1;
					}
					else if(mansion[x][y].type == '/'){
						switch(curr_dir){
							case 0: curr_dir = 3;break;
							case 1: curr_dir = 2;break;
							case 2: curr_dir = 1;break;
							case 3: curr_dir = 0;break;
							
						}
						flagM=1;
					}else{
						mansion[x][y].pov[curr_dir].count = &vission[i][j];
						mansion[x][y].pov[curr_dir].mirror = flagM;
					}
					x = x+move[curr_dir][0];
					y = y+move[curr_dir][1];	
				}
				
			}
		}
		
		
		mark = 1;
		manor = mansion;
		vptr = vission;
		
		dfss(0);	
		
	}
	fclose(rf);
	fclose(wf);
}

void print(){
	for(int i = 0; i < size; i++){
			for(int j = 0; j < size; j++){
					printf("%c ", (manor+i*size+j)->type);
			}
			printf("\n");
		}
}

void dfs1(struct node **mansion,int x, int y, int v, int z, int g, int size){

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
			 			printf("%c ", mansion[i][j].type);
					 }
					 printf("\n");
				 }
			 }else{
			 	flag = 0;
			 }
			 return;
	 }
	 else if(mansion[x][y].type != '.'){
	 	if(x==size-1 && y==size-1){
	 		dfs1(mansion,x+1,y+1,v,z,g,size);
		 }
	 	else if(y==size-1){
	 		dfs1(mansion,x+1,0,v,z,g,size);
		 }else{
		 	dfs1(mansion,x,y+1,v,z,g,size);
		 }
	 }
	 else{
	 	if(z>0){
	 		mansion[x][y].type = 'Z';
	 		for(int i = 0; i < 4; i ++){
	 			if(mansion[x][y].pov[i].count){
	 				*mansion[x][y].pov[i].count = *mansion[x][y].pov[i].count - 1;	
	 				if(*mansion[x][y].pov[i].count<0)
	 					flag = 1;
				 }
			 }
			 if(x==size-1 && y==size-1){
	 			dfs1(mansion,x+1,y+1,v,z-1,g,size);
		 	}	
			else if(y==size-1){
	 			dfs1(mansion,x+1,0,v,z-1,g,size);
		 	}else{
		 		dfs1(mansion,x,y+1,v,z-1,g,size);
		 	}
		 	flag=0;
		 	for(int i = 0; i < 4; i ++){
		 		if(mansion[x][y].pov[i].count){
		 			*mansion[x][y].pov[i].count = *mansion[x][y].pov[i].count+1;	
				 }
	 		}
	 			
		 }
		 if(v>0){
	 		mansion[x][y].type = 'V';
	 		for(int i = 0; i < 4; i ++){
	 			if(mansion[x][y].pov[i].count && mansion[x][y].pov[i].mirror==0){
	 				*mansion[x][y].pov[i].count = *mansion[x][y].pov[i].count - 1;	
	 				if(*mansion[x][y].pov[i].count<0)
	 					flag = 1;
				 }
			 }
			 if(x==size-1 && y==size-1){
	 			dfs1(mansion,x+1,y+1,v-1,z,g,size);
		 	}
			 else if(y==size-1){
	 			dfs1(mansion,x+1,0,v-1,z,g,size);
		 	}else{
		 		dfs1(mansion,x,y+1,v-1,z,g,size);
		 	}
		 	flag=0;
		 	for(int i = 0; i < 4; i ++){
	 			if(mansion[x][y].pov[i].count && mansion[x][y].pov[i].mirror==0){
	 				*mansion[x][y].pov[i].count = *mansion[x][y].pov[i].count+1;	
				 }
			 }
			 
		 }
		 if(g>0){
	 		mansion[x][y].type = 'G';
	 		for(int i = 0; i < 4; i ++){
	 			if(mansion[x][y].pov[i].count && mansion[x][y].pov[i].mirror==1){
	 				*mansion[x][y].pov[i].count = *mansion[x][y].pov[i].count - 1;	
	 				if(*mansion[x][y].pov[i].count<0)
	 					flag = 1;
				 }
			 if(x==size-1 && y==size-1){
	 			dfs1(mansion,x+1,y+1,v,z,g-1,size);
		 	}
			 else if(y==size-1){
	 			dfs1(mansion,x+1,0,v,z,g-1,size);
		 	}else{
		 		dfs1(mansion,x,y+1,v,z,g-1,size);
		 	}
		 	flag=0;
		 	for(int i = 0; i < 4; i ++){
	 			if(mansion[x][y].pov[i].count && mansion[x][y].pov[i].mirror==1){
	 				*mansion[x][y].pov[i].count = *mansion[x][y].pov[i].count+1;	
				 }
			 }
		 	}
		}
		mansion[x][y].type = '.';
	 }
}

void dfss(int i){
	
	if(!mark){
		return;
	}
	else if(i == size*size){
		for(int j = 0; j < 4*size; j++){
			printf("%d ",*(vptr+j));
			if(*(vptr+j)!=0){
				mark = 0;
			}
		}
		printf("\n");
		if(mark){
			print();
		}
		else{
			mark=1;
		}
		return;
	}
	else if((manor+i)->type!='.'){
		dfss(i+1);
	}
	else{
		if(z>0){
			z--;
			(manor+i)->type = 'Z';
			for(int j = 0; j < 4; j++){
				if((manor+i)->pov[j].count){
					*(manor+i)->pov[j].count-=1;
					if(*(manor+i)->pov[j].count<0)
						mark=0;
				}
			}
			dfss(i+1);
			z++;
			mark=1;
			for(int j=0; j<4; j++){
				if((manor+i)->pov[j].count){
					*(manor+i)->pov[j].count +=1;
				}
			}
		}
		
		if(v>0){
			v--;
			(manor+i)->type = 'V';
			for(int j = 0; j < 4; j++){
				if((manor+i)->pov[j].count && !(manor+i)->pov[j].mirror){
					*(manor+i)->pov[j].count-=1;
					if(*(manor+i)->pov[j].count<0)
						mark=0;
				}
			}
			dfss(i+1);
			v++;
			mark=1;
			for(int j=0; j<4; j++){
				if((manor+i)->pov[j].count && !(manor+i)->pov[j].mirror){
					*(manor+i)->pov[j].count +=1;
				}
			}
		}
		
		if(g>0){
			g--;
			(manor+i)->type = 'G';
			for(int j = 0; j < 4; j++){
				if((manor+i)->pov[j].count && (manor+i)->pov[j].mirror){
					*(manor+i)->pov[j].count-=1;
					if(*(manor+i)->pov[j].count<0)
						mark=0;
				}
			}
			dfss(i+1);
			g++;
			mark=1;
			for(int j=0; j<4; j++){
				if((manor+i)->pov[j].count && (manor+i)->pov[j].mirror){
					*(manor+i)->pov[j].count +=1;
				}
			}
		}
		(manor+i)->type = '.';	
	}
		
}

	
