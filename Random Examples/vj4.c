#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

typedef struct list* pozList;
typedef struct list{
    int n;
    pozList next;
}list;

typedef struct tree* pozTree;
typedef struct tree{
    int n;
    pozTree left;
    pozTree right;
}tree;

pozList createListNode();
pozTree createTreeNode();
int insertIntoList(pozList,pozList);
pozTree insertIntoTree(pozTree,pozTree);
pozTree deleteFromTree(pozTree,int);
pozTree findMax(pozTree);
pozTree findMin(pozTree);
int preorder(pozTree);
int readData(char*, pozList, pozTree);

int main()
{
    pozList head=createListNode();
    pozTree root=createTreeNode();
    srand(time(NULL));
    for(int i=0;i<100;i++){
        if(!root->n){
            root->n=rand()%401+300;;
        }
        else{
            pozTree new=createTreeNode();
            new->n=rand()%401+300;
            root=insertIntoTree(root,new);
        }
    }
    preorder(root);
    readData("vj4.txt",head,root);
    preorder(root);
    return 0;
}

pozList createListNode(){
    pozList p=NULL;
    p=malloc(sizeof(list));
    if(p==NULL){
        printf("malloc error");
    }
    else p->next=NULL;
    return p;
}

pozTree createTreeNode(){
    pozTree p=NULL;
    p=malloc(sizeof(tree));
    if(p==NULL){
        printf("malloc error");
    }
    else{
        p->left=NULL;
        p->right=NULL;
    }
    return p;
}

int insertIntoList(pozList p,pozList q){
    q->next=p->next;
    p->next=q;
    return 0;
}

pozTree insertIntoTree(pozTree p, pozTree q){
    if(p==NULL){
        return q;
    }
    if(p->n > q->n){
        p->left=insertIntoTree(p->left,q);
    }
    else if(p->n < q->n){
        p->right=insertIntoTree(p->right,q);
    }
    else{
        free(q);
    }
    return p;
}

pozTree deleteFromTree(pozTree p,int n){
    if(p==NULL){
        return NULL;
    }
    if(p->n > n){
        p->left=deleteFromTree(p->left,n);
    }
    else if(p->n < n){
        p->right=deleteFromTree(p->right,n);
    }
    else{
        if(p->left){
            pozTree temp=findMax(p->left);
            p->n=temp->n;
            p->left=deleteFromTree(p->left,temp->n);
        }
        else if(p->right){
            pozTree temp=findMin(p->right);
            p->n=temp->n;
            p->right=deleteFromTree(p->right,temp->n);
        }
        else{
            free(p);
            return NULL;
        }
    }
    return p;
}

pozTree findMax(pozTree p){
    while(p->right!=NULL){
        p=p->right;
    }
    return p;
}

pozTree findMin(pozTree p){
    while(p->left!=NULL){
        p=p->left;
    }
    return p;
}

int preorder(pozTree p){
    if(p==NULL){
        return 0;
    }
    printf("%d ", p->n);
    preorder(p->left);
    preorder(p->right);
    return 0;
}

int readData(char* filename, pozList p, pozTree root){
    FILE*fp=NULL;
    fp=fopen(filename,"r");
    while(!feof(fp)){
        int n;
        fscanf(fp,"%d",&n);
        root=deleteFromTree(root,n);
    }
    fclose(fp);
    return 0;
}