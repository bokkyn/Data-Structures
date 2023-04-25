// Definirati strukturu osoba (ime, prezime, godina rođenja) i napisati program koji:
// A. dinamički dodaje novi element na početak liste,
// B. ispisuje listu,
// C. dinamički dodaje novi element na kraj liste,
// D. pronalazi element u listi (po prezimenu),
// E. briše određeni element iz liste,
// U zadatku se ne smiju koristiti globalne varijable

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_NAME (25)
#define MALLOC_ERROR (-1)

typedef struct osoba* pozicija;   

typedef struct osoba{             //ovdi ga definiramo, struktura sa podacima i nextom
 char ime[MAX_NAME];
 char prezime[MAX_NAME];
 int godina_rodjenja;
 pozicija next;
}osoba;

void unosNaPocetakListe(pozicija);
void unosNaKrajListe(pozicija);
void ispisListe(pozicija);
pozicija pronalaziElement(char*, pozicija);
pozicija onajIza(char*, pozicija);
osoba* stvaranje(void);                 //ovo san doda funkcijica koja pravi onaj malloc i stvari koje se ponavljaju
int brisanjeElementa(pozicija);

int main()        //u mainu ih samo zovemo
{
    pozicija head = NULL;
    head=stvaranje();
    unosNaPocetakListe(head);
    unosNaPocetakListe(head);
    unosNaKrajListe(head);
    ispisListe(head->next);
    char str[25];
    printf("Unesite trazeno prezime:\n");
    scanf("%s",str);
    pozicija x=NULL;
    x=pronalaziElement(str, head->next);
    if(x!=NULL){
        printf("Trazena osoba:%s %s \n", x->ime,x->prezime);
    }
    brisanjeElementa(head);
    ispisListe(head->next);
return 1;
}

osoba* stvaranje()
{
    osoba* o = NULL;                                   
    o = (osoba*)malloc(sizeof(osoba));              //alociramo meoriju
    if (o==NULL){
        printf("malloc error");

    }

    o->next = NULL;                                 //njegov pointeric
    return o;
}

void ispisListe(pozicija o)
{
    if(o==NULL){                                   //provjeramo postoji li itko uopce
    printf("Lista je prazna\n");}

    printf("Lista:\n");
    while(o!=NULL)//idemo kroz listu sve dok ne dodemo do kraja
    {
        printf("Ime: %s %s\n", o->ime, o->prezime);
        printf("Godina rodjenja: %d\n", o->godina_rodjenja);
        o=o->next;//idemo na sljedeci element liste
    }
}

void unosNaPocetakListe(pozicija head)
{ 
    pozicija q=stvaranje();

    if(q==NULL){//provjeravamo je li malloc uspio naci prostora u memoriji
        printf("malloc error");
        }
    else //nastavljamo ako je malloc uspio
    {
        printf("Unesite ime\n");
        scanf(" %s",q->ime);                   //sve stvari unosimo sa scanf, i spremamo ih na mjesto u strukturi q tipa pozicija
        printf("Unesite prezime\n");
        scanf(" %s",q->prezime);
        printf("Unesite godinu rodjenja\n");
        scanf("%d",&q->godina_rodjenja);       // za godinu koja je int treba &
        q->next=head->next;
        head->next=q;
    }
}
void unosNaKrajListe(pozicija head)
{
pozicija q=head;                                       //stavljamo q na pocetak
    while(q->next != NULL)                              //vrtimo dok ne stignemo na kraj
    {
        q = q->next;                                   
    }
    unosNaPocetakListe(q);                          //i onda unesemo, kao da je pocetak, samo saljemo taj prevrceni q, a ne head
}


pozicija pronalaziElement(char* str, pozicija head)
{
    pozicija s= head;
    while(s!=NULL && strcmp(s->prezime, str)!=0){               //uspoređuje uneseni sa svakim i gleda dolazimo li do kraja
        s=s->next;                                              
    }
    if (s==NULL){
        printf("Osoba nije pronađena");
    }
    return s;
}

int brisanjeElementa(pozicija head)
{
    char str[20];
    printf("Unesi prezime osobe za brisanje:");
    scanf("%s", str);
    
    pozicija o = onajIza(str, head);                                 //na neku poziciju stavimo onaj koji je iza (zapravo ispred) (nisan uspia brisat bas taj)
    if(o == NULL)                                                   
    {
        printf("Ne postoji!");  
        return 0;
    }

    pozicija temp = o->next;                                       
    o->next = temp->next;
    free(temp);

    return 1;
}

pozicija onajIza(char* str, pozicija head)                     //ovo je zapravo onaj ISPRED
{
    pozicija s= head;                          //imamo prvog
    pozicija nova=head->next;                   //i onaj iza
    while(nova!=NULL && strcmp(nova->prezime, str)!=0){   //gledamo kakav je taj iza
        s=nova;                                           //ovde vrtimo oba napried, dok ne nađemo onaj koji nam treba  
        nova=nova->next;                                 
    }
    if (s==NULL){
        printf("Osoba nije pronađena");
    }
    return s;                                           //i na kraju vracamo onaj prethodni
}