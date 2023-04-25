#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE (256)

typedef struct cvorl* pozl;
typedef struct cvorl{
	char rijec[MAX_LINE];
	pozl next;
}cvorl;

typedef struct cvors* pozs;
typedef struct cvors{
	char rijec[MAX_LINE];
	pozs left;
	pozs right;
	pozl next;
}cvors;

pozl stvaranjel();
pozs stvaranjes();
int readData(char*, pozs);
pozs inserts(pozs, char*,pozs);
int insertl(pozs, pozl);
int clear(pozs);
pozs inorder(pozs);

int main()
{
	pozs root=stvaranjes();
	readData("vj0.txt",root);
	root=inorder(root);
	clear(root);
	return 0;
}

pozl stvaranjel(){
	pozl p=NULL;
	p=malloc(sizeof(cvorl));
	if(p==NULL){
		printf("malloc error");
	}
	else{
		p->next=NULL;
	}
	return p;
}

pozs stvaranjes(){
	pozs p=NULL;
	p=malloc(sizeof(cvors));
	if(p==NULL){
		printf("malloc error");
	}
	else{
		p->left=NULL;
		p->right=NULL;
		p->next=NULL;
	}
	return p;
}

int readData(char* filename, pozs s){
	FILE* fp=NULL;
	fp=fopen(filename,"r");
	if(fp==NULL){
		printf("file not opened");
		return -1;
	}
	while(!feof(fp)){
		char newWord[MAX_LINE]={0};
		fscanf(fp," %s",newWord);
		s=inserts(s,newWord,s);
	}
	fclose(fp);
	return 0;
}

pozs inserts(pozs s, char* newWord,pozs root){
	if(root->rijec[0]==0){
		strcpy(root->rijec,newWord);
		return root;
	}
	if(s==NULL){
		pozs newS=stvaranjes();
		strcpy(newS->rijec,newWord);
		return newS;
	}
	if(strcmp(s->rijec,newWord)>0){
		s->left=inserts(s->left,newWord,root);
	}
	else if(strcmp(s->rijec,newWord)<0){
		s->right=inserts(s->right,newWord,root);
	}
	else{
		pozl newL=stvaranjel();
		strcpy(newL->rijec,newWord);
		insertl(s,newL);
	}
	return s;
}

int insertl(pozs s, pozl l){
	l->next=s->next;
	s->next=l;
	return 0;
}

int clear(pozs s){
	if(s!=NULL){
		clear(s->left);
		clear(s->right);
		while(s->next!=NULL){
			pozl temp=s->next;
			s->next=temp->next;
			free(temp);
		}
		free(s);
	}
	return 0;
}

pozs inorder(pozs s){
	if(s==NULL){
		return NULL;
	}
	s->left=inorder(s->left);
	printf("%s ",s->rijec);
	int br=1;
	pozl l=s->next;
	while(l!=NULL){
		br++;
		l=l->next;
	}
	printf("%d\n", br);
	s->right=inorder(s->right);
	return s;
}