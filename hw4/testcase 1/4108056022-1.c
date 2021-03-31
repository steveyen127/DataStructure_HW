#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MALLOC(p,s)\
	if(!((p)=malloc(s))){\
	fprintf(stderr,"Insifficient memory\n");\
	exit(EXIT_FAILURE);\
	}


struct node{
	char var[3];
	char f[300];
	struct node *next;
	
};

struct node *newNodeV(char var[3]){
	struct node *temp;
	MALLOC(temp, sizeof(struct node*));
	strcpy(temp->var, var);
	strcpy(temp->f, var);
	temp->next = NULL;
	return temp;
}

struct node *newNodeF(char f[300]){
	struct node *temp;
	MALLOC(temp, sizeof(struct node*));
	strcpy(temp->f, f);
	temp->next = NULL;
	return temp;
}

char *strrpc(char *str, char *oldstr, char *newstr){
	char bstr[strlen(str)];
	memset(bstr,0,sizeof(bstr));
	
	for(int i = 0; i < strlen(str);i++){
		if(!strncmp(str+i, oldstr, strlen(oldstr))){
			strcat(bstr, newstr);
			i+=strlen(oldstr) -1;
		}else{
			strncat(bstr, str + i, 1);
		}
	}
	strcpy(str,bstr);
	return str;
}

int main(){
	FILE *rf, *wf;
	
	rf = fopen("test4.txt", "r");
	wf = fopen("outputME1.txt", "w");
	
	if(rf == NULL || wf==NULL){
		printf("File opening error\n");
		exit(1);
	}else{
		printf("Program Started\n");
		int N, M;
		char var[3];
		char bad[2];
		char f[300];
		struct node *varNode = NULL, *varTemp = NULL;
		struct node *funNode = NULL, *funTemp = NULL;
		fscanf(rf, "%d\n", &N);
		
		for(int i = 0; i < N; i++){
			fscanf(rf,"%s", var);
			if(varNode==NULL){
				varNode = newNodeV(var);
				varTemp = varNode;
			}else{
				varTemp->next = newNodeV(var);
				varTemp = varTemp->next;
			}
		}
//		for(varTemp = varNode; varTemp; varTemp = varTemp->next){
//			printf("%s %s, ", varTemp->var, varTemp->f);
//		}
//		printf("\n");
		fscanf(rf,"%d\n",&M);
		if(M==0){
			for(varTemp = varNode; varTemp; varTemp = varTemp->next){
				fprintf(wf,"%s -> %s\n", varTemp->var, varTemp->var);
			}
		}else{
			for(int i = 0; i < M; i++){
				fscanf(rf, "%s", var);
				if(funNode == NULL){
					funNode = newNodeV(var);
					funTemp = funNode;	
				}else{
					funTemp->next = newNodeV(var);
					funTemp=funTemp->next;
				}
				fscanf(rf, " = ", var);
				fgets(f, 300, rf);
				if(f[strlen(f)-1] == '\n')
					f[strlen(f)-1] = '\0';
				strcpy(funTemp->f, f);	
			}
//			for(funTemp = funNode; funTemp; funTemp = funTemp->next){
//				printf("%s  %s,", funTemp->var, funTemp->f);
//			}
//			printf("\n");
			char string[300];
			int counter, flag;
			char *token;
			for(varTemp = varNode; varTemp; varTemp = varTemp->next){
				counter = 0;
				do{
					flag = 0;
					strcpy(string,varTemp->f);
					token = strtok(string, " ");
					while(token){
						for(funTemp = funNode; funTemp; funTemp= funTemp->next){
							if(counter!=0 && strcmp(token,varTemp->var)==0){
								fprintf(wf, "No Solution.\n");
								fclose(rf);
								fclose(wf);
								printf("Program Completed.\n");
								exit(1);
							}
							if(strcmp(token, funTemp->var)==0){
								strrpc(varTemp->f,token,funTemp->f);
								flag=1;
							}
						}
						token = strtok(NULL," ");
						counter++;
					}
					
				}while(flag!=0);
			}
			for(varTemp = varNode; varTemp; varTemp= varTemp->next){
				fprintf(wf, "%s -> %s\n", varTemp->var, varTemp->f);
			}
			
			
		}
		
	}
	fclose(rf);
	fclose(wf);
	printf("ProgramCompleted\n");
	return 0;
}
