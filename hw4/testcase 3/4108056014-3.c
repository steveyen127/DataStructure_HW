#include<stdio.h>
#include<stdlib.h>

typedef struct vision vis;
struct vision {
	int* count;
	int mirror;
};

typedef struct block node;
struct block {
	vis path[4];
	char type;
};

void dfs(int);
void printmans();

int v,z,g,n,mark;
int dir[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
node* mans;
int* viss;
int main() {
	
	FILE *input_file ,*output_file;
	
	/////////////////change the file name here////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if((input_file=fopen("test2.txt","r"))==NULL) {
	////////////////////^^^^^^^^^^^^^^^^//////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		puts("open file error");
		exit(1);
	}
	
	fscanf(input_file,"%d %d %d\n%d\n",&v,&z,&g,&n);
	int vision[4][n];
	for(int i=0;i<4;i++) {
		for(int j=0;j<n;j++) {
			fscanf(input_file,"%d ",&vision[i][j]);
		}
	}

	node mansion[n][n];
	for(int i=0;i<n;i++) {
		for(int j=0;j<n;j++) {
			mansion[i][j].type = getc(input_file);
			for(int k=0;k<4;k++) {
				mansion[i][j].path[k].count = NULL;
			}
		}
		getc(input_file);
	}
	for(int i=0;i<4;i++) {
		for(int j=0;j<n;j++) {
			int cur_dir = i;
			int flag = 0;
			int x,y;
			switch(i) {
				case 0: x=0;y=j;break;
				case 1: x=n-1;y=j;break;
				case 2: x=j;y=0;break;
				case 3: x=j;y=n-1;break;
			}
			while(x>-1&&x<n&&y>-1&&y<n) {
				if(mansion[x][y].type == '\\') {
					switch(cur_dir) {
						case 0: cur_dir = 2; break;
						case 1: cur_dir = 3; break;
						case 2: cur_dir = 0; break;
						case 3: cur_dir = 1; break;
					}
					flag = 1;
				}
				else if(mansion[x][y].type == '/') {
					switch(cur_dir) {
						case 0: cur_dir = 3; break;
						case 1: cur_dir = 2; break;
						case 2: cur_dir = 1; break;
						case 3: cur_dir = 0; break;
					}
					flag = 1;
				}
				else {
					mansion[x][y].path[cur_dir].count = &vision[i][j];
					mansion[x][y].path[cur_dir].mirror = flag;
				}
				x += dir[cur_dir][0];
				y += dir[cur_dir][1]; 
			}
		}
	}
	
	mark = 1;
	mans = mansion;
	viss = vision;
	dfs(0);
	
}

void dfs(int i) {
	
	if(!mark) {
		return;
	}
	else if(i==n*n) {
//		if (z==0 && v==0 && g==0) {
			for(int j=0;j<4*n;j++) {	//head要全部減為零 
				if(*(viss+j)!=0)	//若有非零，mark=0 
					mark = 0;
			}
			if(mark) {
				printmans();
			}
			else mark = 1;	///
			return;
//		}
	}
	else if((mans+i)->type !='.') {
		dfs(i+1);
	}
	else {
		if(z>0) {
			z--;
			(mans+i)->type = 'Z';
			for(int j=0;j<4;j++) {
				if((mans+i)->path[j].count) {
					*(mans+i)->path[j].count -=1;
					if(*(mans+i)->path[j].count<0)
						mark=0;		///
				}
			}
			dfs(i+1);
			z++;
			mark=1;
			for(int j=0;j<4;j++) {
				if((mans+i)->path[j].count) {
					*(mans+i)->path[j].count +=1;
				}
			}
		}
		if(v>0) {
			v--;
			(mans+i)->type = 'V';
			for(int j=0;j<4;j++) {
				if((mans+i)->path[j].count && !(mans+i)->path[j].mirror) {
					*(mans+i)->path[j].count -=1;
					if(*(mans+i)->path[j].count<0)
						mark=0;
				}
			}
			dfs(i+1);
			v++;
			mark=1;
			for(int j=0;j<4;j++) {
				if((mans+i)->path[j].count && !(mans+i)->path[j].mirror) {
					*(mans+i)->path[j].count +=1;
				}
			}
		}
		if(g>0) {
			g--;
			(mans+i)->type = 'G';
			for(int j=0;j<4;j++) {
				if((mans+i)->path[j].count && (mans+i)->path[j].mirror) {
					*(mans+i)->path[j].count -=1;
					if(*(mans+i)->path[j].count<0)
						mark=0;
				}
			}
			dfs(i+1);
			g++;
			mark=1;
			for(int j=0;j<4;j++) {
				if((mans+i)->path[j].count && (mans+i)->path[j].mirror) {
					*(mans+i)->path[j].count +=1;
				}
			}
			
		}
		(mans+i)->type = '.';
	}
}

void printmans() {
	for(int i=0;i<n;i++) {
		for(int j=0;j<n;j++) {
			printf("%c ",(mans+i*n+j)->type);
		}
		puts("");
	}
}
