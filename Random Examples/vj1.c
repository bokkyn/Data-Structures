#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

typedef struct cvor* poz;
typedef struct cvor{
    int n;
    poz next;
}cvor;

int randomNToFile(char*);
int readFile(char*,poz);
poz stvaranje();
int insert(poz,poz);
int insertSorted(poz,poz);
int insertSortedWithRepeating(poz,poz);
int clear(poz);
int presjekParnih(poz,poz,poz);
int unijaNeparnih(poz,poz,poz);

int main(){
    srand(time(NULL));
    randomNToFile("vj1.txt");
    randomNToFile("vj12.txt");
    poz head1=stvaranje();
    poz head2=stvaranje();
    readFile("vj1.txt",head1);
    readFile("vj12.txt",head2);
    poz head3=stvaranje();
    poz head4=stvaranje();
    unijaNeparnih(head1,head2,head4);
    presjekParnih(head1,head2,head3);
    clear(head1);
    clear(head2);
    clear(head3);
    clear(head4);
    return 0;
}

int randomNToFile(char* filename){
    FILE* fp=NULL;
    fp=fopen(filename,"w");
    if(fp==NULL){
        printf("fileopen error");
        return -1;
    }
    for(int i=0;i<10;i++){
        fprintf(fp,"%d ",rand()%16+20);
    }
    fclose(fp);
    return 0;
}

int readFile(char* filename,poz p){
    FILE* fp=NULL;
    fp=fopen(filename,"r");
    if(fp==NULL){
        printf("fileopen error");
        return -1;
    }
    for(int i=0;i<10;i++){
        poz new=stvaranje();
        fscanf(fp,"%d",&new->n);
        insertSortedWithRepeating(p,new);
    }
    fclose(fp);
    return 0;
}

poz stvaranje(){
    poz p=NULL;
    p=malloc(sizeof(cvor));
    if(p==NULL){
        printf("malloc error");
    }
    else{
        p->next=NULL;
    }
    return p;
}

int insert(poz p,poz q){
    q->next=p->next;
    p->next=q;
    return 0;
}

int insertSorted(poz p,poz q){
    while(p->next!=NULL && p->next->n<q->n){
        p=p->next;
    }
    if(p->next!=NULL && p->next->n==q->n){
        free(q);
    }
    else {
        q->next=p->next;
        p->next=q;
    }
    return 0;
}

int insertSortedWithRepeating(poz p,poz q){
    while(p->next!=NULL && p->next->n<q->n){
        p=p->next;
    }
    q->next=p->next;
    p->next=q;
    return 0;
}

int clear(poz p){
    while(p->next!=NULL){
        poz temp=p->next;
        p->next=temp->next;
        free(temp);
    }
    free(p);
    return 0;
}

int unijaNeparnih(poz p1,poz p2,poz p){
    while(p1!=NULL){
        if(p1->next!=NULL && p1->next->n%2!=0){
            poz temp=p1->next;
            p1->next=p1->next->next;
            insertSorted(p,temp);
        }
        else p1=p1->next;
    }
    while(p2!=NULL){
        if(p2->next!=NULL && p2->next->n%2!=0){
            poz temp=p2->next;
            p2->next=p2->next->next;
            insertSorted(p,temp);
        }
        else p2=p2->next;
    }
    return 0;
}

int presjekParnih(poz p1,poz p2,poz p){
    while(p1!=NULL && p2!=NULL){
        if(p1->next!=NULL && p2->next!=NULL && p1->next->n==p2->next->n){
            poz temp1=p1->next;
            poz temp2=p2->next;
            p1->next=p1->next->next;
            p2->next=p2->next->next;
            insertSorted(p,temp1);
            free(temp2);
        }
        else if(p1->next!=NULL && p2->next!=NULL && p1->next->n > p2->next->n){
            p2=p2->next;
        }
        else if(p1->next!=NULL && p2->next!=NULL && p1->next->n < p2->next->n){
            p1=p1->next;
        }
        else if(p1->next==NULL){
            p1=p1->next;
        }
         else if(p2->next==NULL){
            p2=p2->next;
        }
    }
    return 0;
}