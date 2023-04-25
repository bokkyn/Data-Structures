// Zadan je niz brojeva 2, 5, 7, 8, 11, 1, 4, 2, 3, 7 koji su spremljeni u čvorove binarnog stabla.
// a) Napisati funkciju insert koja dodaje element u stablo tako da se pozivima te funkcije za
// sve element zadanog niza brojeva stvori stablo kao na slici Slika 1. Funkcije vraća
// pokazivač na korijen stabla.
// b) Napisati funkciju replace koja će svaki element stabla zamijeniti sumom elemenata u
// njegovom lijevom i desnom podstablu (tj. sumom svih potomaka prije zamjene
// vrijednosti u tim potomcima). Npr. stablo sa slike Slika 1 transformirat će se u stablo na
// slici Slika 2.
// c) Prepraviti program na način da umjesto predefiniranog cjelobrojnog polja korištenjem
// funkcije rand() generira slučajne brojeve u rasponu <10, 90>. Također, potrebno je
// upisati u datoteku sve brojeve u inorder prolasku nakon korištenja funkcije iz a), zatim b)
// dijela zadatka.

#define _CRT_SECURE_NO_WARNINGS
#define FILE_ERROR (-1)

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

typedef struct stablo* pozStablo;
typedef struct stablo {
    int br;
    pozStablo left;
    pozStablo right;
}stablo;

typedef struct lista* pozLista;
typedef struct lista {
    int br;
    pozLista next;
}lista;

stablo* stvaranjeStablo();
lista* stvaranjeLista();
pozStablo insert(pozStablo, pozStablo);
int replace(pozStablo);
pozStablo inorderLista(pozStablo, pozLista);
int clearStablo(pozStablo);
int clearLista(pozLista);
int RandomBroj(int min, int max);
int writeToFile(char* ime, pozLista root);

int main()
{
    srand(time(NULL));
    int niz[10] = { 2,5,7,8,11,1,4,2,3,7 };
    for (int i = 0;i < 10;i++) { 
        niz[i] = RandomBroj(10, 90);
    }
    pozStablo root = NULL;
    root = stvaranjeStablo();
    //unosimo brojeve u stablo:
    for (int i = 0;i < 10;i++)
        if (!root->br) // ako root nema broj
            root->br = niz[i];
        else {
            pozStablo q = NULL;
            q = stvaranjeStablo();
            q->br = niz[i];
            root = insert(root, q);
        }

    pozLista head = NULL;
    head = stvaranjeLista();
    root = inorderLista(root, head); //elemente stabla stavljamo u listu
    writeToFile("stari.txt", head->next);
    //mijenjamo stablo iz slike 1 tako da bude kao na slici 2:
    int temp = root->br;
    root->br = replace(root);
    root->br -= temp;
    pozLista head2 = NULL;
    head2 = stvaranjeLista();
    root = inorderLista(root, head2); //elemente stabla stavljamo u listu
    writeToFile("novi.txt", head2->next);
    clearStablo(root);
    clearLista(head);
    clearLista(head2);
    return 0;
}

stablo* stvaranjeStablo()
{
    stablo* s = NULL;
    s = malloc(sizeof(stablo));
    if (NULL == s) {
        printf("Greska u alokaciji memorije\n");
    }
    else
    {
        s->left = NULL;
        s->right = NULL;
    }
    return s;
}

lista* stvaranjeLista()
{
    lista* l = NULL;
    l = malloc(sizeof(lista));
    if (l == NULL) {
        printf("Greska u alokaciji memorije\n");
    }
    else
        l->next = NULL;
    return l;
}

pozStablo insert(pozStablo p, pozStablo q)
{
    if (p == NULL)
        return q;
    if (p->br < q->br)
        p->left = insert(p->left, q);
    else if (p->br > q->br)
        p->right = insert(p->right, q);
    else { //ako su jednaki idemo na lijevu stranu jer je tako na slici
        p->left = insert(p->left, q);
    }
    return p;
}

int replace(pozStablo p)
{
    if (p == NULL)
        return 0;
    int sumLeft = replace(p->left);
    int sumRight = replace(p->right);
    int sum = p->br + sumLeft + sumRight;
    p->br = sumLeft + sumRight;
    return sum;
}

pozStablo inorderLista(pozStablo ps, pozLista pl)
{
    if (ps == NULL)
        return NULL;
    inorderLista(ps->right, pl);
    pozLista q = NULL;
    q = stvaranjeLista();
    q->br = ps->br;
    q->next = pl->next; //dodajemo na pocetak liste, al zato smo obrnili pozive na lijevu i desnu stranu (inace se prvo zove ps->left pa poslije ps->right) tako da dobijemo inorder
    pl->next = q;
    inorderLista(ps->left, pl);
    return ps;
}

int clearStablo(pozStablo p)
{
    if (p != NULL)
    {
        clearStablo(p->left);
        clearStablo(p->right);
        free(p);
    }
    return 0;
}

int clearLista(pozLista head)
{
    pozLista temp = NULL;
    while (head->next != NULL)
    {
        temp = head->next;
        head->next = temp->next;
        free(temp);
    }
    free(head);
    return 0;
}

int RandomBroj(int min, int max)
{
    int num = (rand() % (max - min + 1)) + min;

    return num;

}

int writeToFile(char* ime, pozLista head)
{
    FILE* fptr;
    fptr = fopen(ime, "w");

    if (fptr == NULL)
    {
        printf("Error\n");
        return FILE_ERROR;
    }

    else
    {
        while (head != NULL)
        {
            fprintf(fptr, "%d\n", head->br);
            head = head->next;
        }
        return 0;
    }

    fclose(fptr);
}
