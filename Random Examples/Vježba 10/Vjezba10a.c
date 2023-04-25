// 10. Napisati program koji čita datoteku drzave.txt u kojoj su zapisani nazivi pojedinih država. Uz
// ime države u datoteci se nalazi i ime dodatne datoteke u kojoj se nalaze gradovi pojedine
// države. Svaka datoteka koja predstavlja državu sadrži popis gradova u formatu naziv_grada,
// broj_stanovnika.
// a) Potrebno je formirati sortiranu vezanu listu država po nazivu. Svaki čvor vezane liste
// sadrži stablo gradova sortirano po broju stanovnika, zatim po nazivu grada.
// b) Potrebno je formirati stablo država sortirano po nazivu. Svaki čvor stabla sadrži vezanu
// listu gradova sortiranu po broju stanovnika, zatim po nazivu grada.
// Nakon formiranja podataka potrebno je ispisati države i gradove te omogućiti korisniku putem
// tastature pretragu gradova određene države koji imaju broj stanovnika veći od unosa na
// tastaturi.

#define _CRT_SECURE_NO_WARNINGS

#define FILE_DIDNT_OPEN_ERROR (-1)
#define MAX_LINE (256)
#define EMPTY_LIST (-1)

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

typedef struct stablo* pozStablo;
typedef struct stablo {
    char grad[MAX_LINE];
    int stanovnistvo;
    pozStablo left;
    pozStablo right;
}stablo;

typedef struct lista* pozLista;
typedef struct lista {
    char drzava[MAX_LINE];
    pozLista next;
    pozStablo root;
}lista;

lista* stvaranjeLista();
stablo* stvaranjeStablo();
int unosIza(pozLista, pozLista);
int sortiraniUnos(pozLista, pozLista);
int sortiraniUnosIzDatoteke(char*, pozLista);
int unosGradovaIzDatoteke(char*, pozLista);
pozStablo insert(pozStablo, pozStablo);
int cityCompare(pozStablo, pozStablo);
int ispisSvihDrzava(pozLista);
int ispisSvihDrzavaIGradova(pozLista);
int ispisSvihGradovaDrzave(pozLista);
pozStablo ispisVecihGradovaOdN(pozStablo, int);
pozStablo ispisInorder(pozStablo);
pozLista pronadiDrzavu(char*, pozLista);
int countryNameFormat(char*);
int userInterface(pozLista);
int clearStablo(pozStablo);
int clearLista(pozLista);

int main() {
    pozLista head = NULL;
    head = stvaranjeLista();
    sortiraniUnosIzDatoteke("drzave.txt", head);
    userInterface(head);
    clearLista(head);
	return 0;
}

lista* stvaranjeLista()
{
    lista* l = NULL;
    l = malloc(sizeof(lista));
    if (l == NULL) {
        printf("Greska u alokaciji memorije\n");
    }
    else {
        l->next = NULL;
        l->root = NULL;
    }

    return l;
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

int unosIza(pozLista temp, pozLista p)  //temp je taj sta se dodaje, p je iza koga
{
    temp->next = p->next;                     //taj koji stvorimo pokazuje na ono na sto je p pokazivao (stvaramo izeđu p i prvog)
    p->next = temp;                           //a p pokazuje na njega
    return 0;
}

int sortiraniUnos(pozLista temp, pozLista p)
{
    while (p->next != NULL && strcmp(temp->drzava, p->next->drzava)>0)
    {
        p = p->next;
    }
    unosIza(temp, p);
    return 0;
}

int sortiraniUnosIzDatoteke(char* filename, pozLista head)
{
    FILE* fp = NULL;                                    
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Datoteka nije uspjesno otvorena!\n");
        return FILE_DIDNT_OPEN_ERROR;
    }
    char buffer[MAX_LINE] = { 0 };
    while (!feof(fp))
    {
        fgets(buffer, MAX_LINE, fp); 
        pozLista l = NULL; //l je drzava koju citamo iz datoteke
        l = stvaranjeLista();
        char citiesFilename[MAX_LINE]; //ime datoteke koja sadrzava podatke o gradovima iz pojedine države
        sscanf(buffer, " %s %s", l->drzava, citiesFilename);
        for(int i=0;i<strlen(l->drzava);i++) //idemo kroz ime drzave
            if(l->drzava[i]=='_') //ako naidemo na _ pretvaramo ga u space
                l->drzava[i]=' ';
        unosGradovaIzDatoteke(citiesFilename, l); //drzavi pridruzujemo gradove
        sortiraniUnos(l, head); //unosimo drzavu, zajedno sa pripadajucim stablom gradova, u listu
    }
    fclose(fp);
    return 0;
}

int unosGradovaIzDatoteke(char* filename, pozLista l)
{
    FILE* fp = NULL;                                    
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Datoteka nije uspjesno otvorena!\n");
        return FILE_DIDNT_OPEN_ERROR;
    }
    char buffer[MAX_LINE] = { 0 };
    pozStablo root = NULL; //root stabla u koje cemo spremit gradove
    root = stvaranjeStablo();
    while (!feof(fp))
    {
        fgets(buffer, MAX_LINE, fp); 
        pozStablo s = NULL; //s je grad kojeg citamo iz datoteke
        s = stvaranjeStablo();
        sscanf(buffer, " %s %d", s->grad, &s->stanovnistvo);
        for(int i=0;i<strlen(s->grad);i++) //idemo kroz ime grada
            if(s->grad[i]=='_') //ako naidemo na _ pretvaramo ga u space
                s->grad[i]=' ';
        if (!root->stanovnistvo) // ako root nije popunjen
        {
            strcpy(root->grad,s->grad);
            root->stanovnistvo=s->stanovnistvo;
            free(s);
        }
        else root=insert(root,s);//dodajemo grad u stablo
    }
    l->root=root; //cvor liste nam sad pokazuje na stvoreno stablo
    fclose(fp);
    return 0;
}

pozStablo insert(pozStablo p, pozStablo q)
{
    if (p == NULL)
        return q;
    if(cityCompare(p,q)>0)
        p->left = insert(p->left, q);
    else p->right = insert(p->right, q);
    return p;
}

int cityCompare(pozStablo p, pozStablo q)
{
    int rezultat=p->stanovnistvo-q->stanovnistvo;
    if(rezultat==0)
    {
        if (strcmp(p->grad,q->grad)>0)
            rezultat=1;
        else rezultat=-1;
    }
    return rezultat;
}

int ispisSvihDrzava(pozLista p)
{
    if (p == NULL) {                                  
        printf("Prazno\n");
        return EMPTY_LIST;
    }

    while (p != NULL)
    {
        printf("%s\n", p->drzava);
        p = p->next;
    }
    return 0;
}

int ispisSvihDrzavaIGradova(pozLista p)
{
    if (p == NULL) {                                  
        printf("Prazno\n");
        return EMPTY_LIST;
    }

    while (p != NULL)
    {
        printf("%s\n", p->drzava);
        p->root=ispisInorder(p->root);
        p = p->next;
    }
    return 0;
}

int ispisSvihGradovaDrzave(pozLista p)
{
    p->root=ispisInorder(p->root);
    return 0;
}

pozStablo ispisVecihGradovaOdN(pozStablo p, int n)
{
    if(p == NULL){
        return NULL;
    }
    p->right=ispisVecihGradovaOdN(p->right, n);
    if(p->stanovnistvo > n)
    {
        printf("\t%s - %d\n", p->grad, p->stanovnistvo);
        p->left=ispisVecihGradovaOdN(p->left, n);
    }
    return p;
}

pozStablo ispisInorder(pozStablo p)
{
    if (p == NULL) {                                
        return NULL;
    }
    p->left=ispisInorder(p->left);
    printf("\t%s - %d\n", p->grad, p->stanovnistvo);
    p->right=ispisInorder(p->right);

    return p;
}

pozLista pronadiDrzavu(char* name, pozLista p)
{
    while(p!=NULL && strcmp(p->drzava,name)!=0)
    {
        p=p->next;
    }
    return p;
}

int countryNameFormat(char* s)
{
    for(int i=0;i<strlen(s);i++)
        if(i==0 || s[i-1]==' ')
            s[i]=toupper(s[i]);
        else s[i]=tolower(s[i]);
    return 0;
}

int userInterface(pozLista p)
{
    int check = 1;
    while(check==1)
    {
        printf("\nOdaberite\n");
        printf("A-Ispis svih drzava\n");
        printf("B-Ispis svih drzava i gradova\n");
        printf("C-Ispis svih gradova jedne drzave\n");
        printf("D-Ispis svih gradova jedne drzave iznad odredenog broja stanovnika\n");
        printf("X-Izlaz iz programa\n");
        
        char c = { 0 };
        scanf(" %c", &c); //korisnik unosi opciju koju zeli
        c = toupper(c); //u slucaju da je korisnik unio malo slovo, postavljamo ga na veliko slovo tako da switch case moze preopznati
        char drzava[MAX_LINE] = { 0 }; //ime drzave koju unese korisnik
        pozLista d=NULL; //pointer na tu drzavu
        switch (c)
        {
            case 'A':
                ispisSvihDrzava(p->next);
                break;
            case 'B':
                ispisSvihDrzavaIGradova(p->next);
                break;
            case 'C':
                printf("Unesite ime drzave\n");
                scanf(" %[^\n]", drzava);
                countryNameFormat(drzava);//tako da korisnik moze unijeti i samo mala slova npr
                d=pronadiDrzavu(drzava, p);
                if(d==NULL)
                    printf("Drzava nije pronadena\n");
                else ispisSvihGradovaDrzave(d);
                break;
            case 'D':
                printf("Unesite ime drzave\n");
                scanf(" %[^\n]", drzava);
                countryNameFormat(drzava);//tako da korisnik moze unijeti i samo mala slova npr
                d=pronadiDrzavu(drzava, p);
                if(d==NULL)
                    printf("Drzava nije pronadena\n");
                else
                {
                    int n;
                    printf("Unesite broj stanovnika\n");
                    scanf("%d", &n);
                    d->root=ispisVecihGradovaOdN(d->root,n);
                }
                break;
            case 'X':
                check = 0;
                break;
            default: //ako se nije uneseno nijedno od ponudenih slova nego nesto drugo
                printf("Unesite jedno od ponudenih slova\n");
                break;
        }
    }
    return 0;
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
        clearStablo(temp->root);
        free(temp);
    }
    free(head);
    return 0;
}