//napisati program koji generira 15 sluc br izmedu 100 i 120 i sprema ih u vezanu listu(ne sortirano), u listi ne smije biti duplih vrijednosti
//a) potrebno je pronaci min i max te iz njih izracunati srednju vrijednost (min+max)/2 i nakon toga sve vrijednosti veće od srednje prebacit na kraj liste. ispisati min,max,srednju vr i listu
//b)pronaci vrijednot u listi koja je najbliza srednjoj vr i nju postavit kao root. Nakon toga sve elemente iz liste prebacit u stablo i stablo ispisat na level order nacin

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

typedef struct stablo* pozStablo;
typedef struct stablo{
    int n;
    pozStablo left;
    pozStablo right;
}stablo;

typedef struct lista* pozLista;
typedef struct lista{
    int n;
    pozLista next;
}lista;

pozLista stvaranjeListe();
pozStablo stvaranjeStabla();
int clearListu(pozLista);
int clearStablo(pozStablo);
int insertInList(pozLista,pozLista);
int insertAtEndOfList(pozLista,pozLista);
pozStablo insertInTree(pozStablo,pozStablo);
int listMin(pozLista);
int listMax(pozLista);
int shiftAboveAverageToEnd(pozLista, double);
pozLista findMedium(pozLista,double);
int makeTree(pozLista, pozStablo);

int main()
{
    srand(time(NULL));
    pozLista head=stvaranjeListe();
    for(int i=0;i<15;i++){
        pozLista newL=stvaranjeListe();
        newL->n=rand()%21 +100;
        insertAtEndOfList(head,newL);
    }
    int min=listMin(head->next);
    int max=listMax(head->next);
    double avg=(double)(min+max)/2;
    shiftAboveAverageToEnd(head,avg);
    pozLista medium=findMedium(head->next,avg);
    pozStablo root=stvaranjeStabla();
    root->n=medium->n;
    makeTree(head->next,root);
    clearListu(head);
    return 0;
}

pozLista stvaranjeListe(){
    pozLista p=NULL;
    p=malloc(sizeof(lista));
    if(p==NULL){
        printf("malloc error");
    }
    else{
        p->next=NULL;
    }
    return p;
}

pozStablo stvaranjeStabla(){
    pozStablo p=NULL;
    p=malloc(sizeof(stablo));
    if(p==NULL){
        printf("malloc error");
    }
    else{
        p->right=NULL;
        p->left=NULL;
    }
    return p;
}

int clearListu(pozLista p){
    while(p->next!=NULL){
        pozLista temp=p->next;
        p->next=temp->next;
        free(temp);
    }
    return 0;
}

int clearStablo(pozStablo p){
    if(p!=NULL){
        clearStablo(p->left);
        clearStablo(p->right);
        free(p);
    }
    return 0;
}

int insertInList(pozLista p,pozLista q){
    q->next=p->next;
    p->next=q;
    return 0;
}

int insertAtEndOfList(pozLista p,pozLista q){
    while(p->next!=NULL){
        p=p->next;
    }
    q->next=p->next;
    p->next=q;
    return 0;
}

pozStablo insertInTree(pozStablo p,pozStablo q){
    if(p==NULL){
        return q;
    }
    if(q->n < p->n){
        p->left=insertInTree(p->left,q);
    }
    else{
        p->right=insertInTree(p->right,q);
    }
    return p;
}

int listMin(pozLista p){
    int min=p->n;
    while(p!=NULL){
        if(p->n < min){
            min=p->n;
        }
        p=p->next;
    }
    return min;
}

int listMax(pozLista p){
    int max=p->n;
    while(p!=NULL){
        if(p->n > max){
            max=p->n;
        }
        p=p->next;
    }
    return max;
}

int shiftAboveAverageToEnd(pozLista p, double avg){
    pozLista end=p;
    while(end->next!=NULL){
        end=end->next;
    }
    while(p!=end){
        if(p->next->n > avg){
            pozLista temp=p->next;
            p->next=temp->next;
            insertAtEndOfList(p,temp);
        }
        else p=p->next;
    }
    return 0;
}

pozLista findMedium(pozLista p,double avg){
    int distance=abs(p->n - avg);
    pozLista med=p;
    while(p!=NULL){
        if(abs(p->n - avg) < distance){
            distance=abs(p->n - avg);
            med=p;
        }
        p=p->next;
    }
    return med;
}

int makeTreeFromList(pozLista l, pozStablo s){
    while(l!=NULL){
        pozStablo newS=stvaranjeStabla();
        newS->n=l->n;
        s=insertInTree(s,newS);
        l=l->next;
    }
    return 0;
}