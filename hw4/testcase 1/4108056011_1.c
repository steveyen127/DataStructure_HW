#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct v{
	char var[4];
	char out[300];
	struct v *next;
};

struct f{
	char var[4];
	char fun[300];
	struct f *next;
};

struct v* newv(char arr[4]){
	struct v *n;
	n=(struct v*)malloc(sizeof(struct v));
	strcpy(n->var,arr);
	strcpy(n->out,arr);
	n->next=NULL;
}

struct f* newf(char arr[4]){
	struct f *n;
	n=(struct f*)malloc(sizeof(struct f));
	strcpy(n->var,arr);
	n->next=NULL;
}

char *strrpc(char *str,char *oldstr,char *newstr){
    char bstr[strlen(str)];//轉換緩衝區
    memset(bstr,0,sizeof(bstr));
 
    for(int i = 0;i < strlen(str);i++){
        if(!strncmp(str+i,oldstr,strlen(oldstr))){//查詢目標字串
            strcat(bstr,newstr);
            i += strlen(oldstr) - 1;
        }else{
        	strncat(bstr,str + i,1);//儲存一位元組進緩衝區
	    }
    }

    strcpy(str,bstr);
    return str;
} 

int main(){
	FILE *fp,*out;
	fp = fopen("test4.txt","r");              //檔名更改處 
	out = fopen("output.txt","w");
	if(fp == NULL||out == NULL){
		printf ("error\n");
		exit(1);
	}
	printf("程式開始!\n");
	
	int n,m,i,change=1,count=0;
	struct v *vroot,*vtemp;
	struct f *froot,*ftemp;
	char var[4],*p,fun[300],outc[300];
	fscanf(fp,"%d\n",&n);
	fscanf(fp,"%s",var);
	vroot=newv(var);
	vtemp=vroot;
	for(i=2;i<=n;i++){
		fscanf(fp,"%s",var);
		vtemp->next=newv(var);
		vtemp=vtemp->next;
		//printf("%s??\n",var);
	}
//	temp=vroot;
//	for(;temp;temp=temp->next){
//		printf("%s??\n",temp->var);
//	}
//	fscanf(fp,"\n");
    fscanf(fp,"%d\n",&m);
//  printf("%d",m);
    if(m==0){
    	vtemp=vroot;
    	for(;vtemp;vtemp=vtemp->next){
    		fprintf(out,"%s = %s\n",vtemp->var,vtemp->var);
		}
	}else{
		fscanf(fp,"%s",var);
		froot=newf(var);
		ftemp=froot;
		fscanf(fp," = ",var);
		fgets(fun,290,fp);
		if(fun[strlen(fun)-1]=='\n')
			fun[strlen(fun)-1]='\0';
//		printf("%sll",fun);
		strcpy(ftemp->fun,fun);
		for(i=2;i<=m;i++){
			fscanf(fp,"%s",var);
			ftemp->next=newf(var);
			fscanf(fp," = ",var);
			fgets(fun,99,fp);
			if(fun[strlen(fun)-1]=='\n')
				fun[strlen(fun)-1]='\0';
			ftemp=ftemp->next;
			strcpy(ftemp->fun,fun);
//			printf("%sll",fun);
		}
//		for(ftemp=froot;ftemp;ftemp=ftemp->next){
//			printf("%s = %s      ppppp\n",ftemp->var,ftemp->fun);
//		}
		for(vtemp=vroot;vtemp;vtemp=vtemp->next){
			count=0;
			do{
				change=0;
//				printf("%slll\n",vtemp->var);
				strcpy(outc,vtemp->out);
				p=strtok(outc," ");
				while(p){
					for(ftemp=froot;ftemp;ftemp=ftemp->next){
						printf("%s %s\n",p,vtemp->var);
						if(count!=0&&strcmp(p,vtemp->var)==0){
							fprintf(out,"No soiution.\n");
							fclose(fp);
							fclose(out);
							printf("程式結束!\n");
							exit(1);
						}
						if(strcmp(p,ftemp->var)==0){
							strrpc(vtemp->out,p,ftemp->fun);
							change=1;
						}	
					}
					p=strtok(NULL," ");
					count++;
				}
			}while(change!=0);
		}
		for(vtemp=vroot;vtemp;vtemp=vtemp->next){
			fprintf(out,"%s = %s\n",vtemp->var,vtemp->out);
		}
	}
	
	fclose(fp);
	fclose(out);
	printf("程式結束!\n");
	return 0;
}
