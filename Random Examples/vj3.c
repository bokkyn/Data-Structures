//red s prioritetom

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct red* poz;
typedef struct red{
    int n;
    int priority;
    poz next;
}red;

red* stvaranje();
int readData(char*,poz);
poz insert(poz,poz);

int main()
{
    poz r=stvaranje();
    readData("vj3.txt",r);
    return 0;
}

red* stvaranje(){
    poz r=NULL;
    r=malloc(sizeof(red));
    if(r==NULL){
        printf("malloc error");
    }
    else{
        r->next=NULL;
    }
    return r;
}

int readData(char* filename,poz p){
    FILE* fp=NULL;
    fp=fopen(filename,"r");
    while(!feof(fp)){
        poz new=stvaranje();
        fscanf(fp," %d %d", &new->n, &new->priority);
        p=insert(p,new);
    }
    fclose(fp);
    return 0;
}

poz insert(poz p,poz q){
    if(p==NULL){
        return q;
    }
    if(p->next!=NULL){
        if(p->next->priority < q->priority){
            p->next=insert(p->next,q);
        }
        else if(p->next->priority > q->priority){
            q->next=p->next;
            p->next=q;
        }
        else{
            if(p->next->n < q->n){
                p->next=insert(p->next,q);
            }
            else if(p->next->n > q->n){
                q->next=p->next;
                p->next=q;
            }
            else{
                free(q);
            }
        }
    }
    else p->next=insert(p->next,q);
    return p;
}