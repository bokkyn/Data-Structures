// Napisati program koji iz datoteke čita postfiks izraz i zatim korištenjem stoga računa
// rezultat. Stog je potrebno realizirati preko vezane liste.

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_LINE (256)
#define FILE_DIDNT_OPEN_ERROR (-1)
#define MALLOC_ERROR (-1)

typedef struct lista* pozicija;
typedef struct lista {
    float el; //element(broj)
    pozicija next;
}lista;

lista* stvaranje();
int push(float, pozicija);
int brisi(pozicija);
int brisiSve(pozicija);
int pop(pozicija);
int racunanje(char*, pozicija);

int main()
{
    lista* stog = NULL;
    stog = stvaranje();
    racunanje("filename.txt", stog);
    if (stog->next == NULL)
        printf("Greska u ucitavanju iz datoteke\n");
    else if (stog->next->next == NULL) //ako je na stogu samo jedan element, ispisujemo rezultat
        printf("Rezultat:%.1f\n", stog->next->el);
    else printf("Doslo je do greske u procesu racunanja, provjerite je li postfiks izraz pravilno napisan.\n");
    brisiSve(stog);
    return 0;

}

lista* stvaranje()
{
    lista* p = NULL;
    p = malloc(sizeof(lista));              //alociramo meoriju
    if (p == NULL) {
        printf("Greska u alokaciji memorije\n");
    }
    else
        p->next = NULL;                         //njegov pointeric stavljamo na onog sljedeceg
    return p;
}

int push(float n, pozicija p)            //temp je taj sta se dodaje, p je iza koga
{
    pozicija temp = stvaranje();                //sve treba prvo "stvorit"
    temp->el = n;
    temp->next = p->next;                     //taj koji stvorimo pokazuje na ono na sto je p pokazivao (stvaramo ize?u p i prvog)
    p->next = temp;                           //a p pokazuje na njega
    return 0;
}

int brisi(pozicija p)
{
    pozicija temp = NULL;
    temp = p->next;      //privremeni postane ono na sto p pokazuje (prvi pravi u nizu)                                    
    p->next = temp->next;    //a p umijesto na njega, pokazuje na ono sto pokazuje on (onaj iza, drugi u nizu)
    free(temp);             //tako smo izbacili taj temp(prvi u nizu), prespojili ga, i sad ga mozemo free-at              
    return 0;
}

int brisiSve(pozicija p)
{
    while (p->next != NULL)
    {
        brisi(p);
    }
    free(p);
    return 0;
}

int pop(pozicija p) {     //najnepotrebnija funkcija ikad, al aj
    brisi(p);
    brisi(p);
}

int racunanje(char* filename, pozicija stog)
{
    FILE* fp = NULL;
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Datoteka nije uspjesno otvorena!\n");
        return FILE_DIDNT_OPEN_ERROR;
    }
    char bufferr[MAX_LINE] = { 0 };
    char* buffer = bufferr;
    int offset = 0, check = 1;
    float n = 0, temp = 0;
    char znak = 0;

    fgets(buffer, MAX_LINE, fp);
    while (check == 1) //dok ne dodemo na kraj
    {
        if (check = sscanf(buffer, " %f%n", &n, &offset) == 1) //ako je prosa sscanf i imamo float, pushaj ga
        {
            push(n, stog);
            buffer += offset;        //i onaj buffer, koji se kreće po stringu, pomakni za taj %n (broj mista)
        }
        if (sscanf(buffer, " %f%n", &n, &offset) != 1) {     //ako nije = 1 imamo nesto sta nije float, neki char
            check = sscanf(buffer, " %c%n", &znak, &offset);  //sad ponavljamo sve, ali za char
            if (check != 1)
                break;
            switch (znak)
            {
            case '+':                                                  
                temp = ((stog->next->next->el) + (stog->next->el));   //ako je +, stvorimo privremeni koji je zbroj ta 2
                pop(stog);              //izbrisemo ta 2
                push(temp, stog);     //na stog stavimo taj novi
                buffer += offset;
                break;
            case '*':
                temp = ((stog->next->next->el) * (stog->next->el));
                pop(stog);
                push(temp, stog);
                buffer += offset;
                break;
            case '-':
                temp = ((stog->next->next->el) - (stog->next->el));
                pop(stog);
                push(temp, stog);
                buffer += offset;
                break;
            case '/':
                temp = (stog->next->next->el) / (stog->next->el);
                pop(stog);
                push(temp, stog);
                buffer += offset;
                break;
            default:
                printf("Error-greska u fileu, sadrzi nedozvoljen znak\n");
                check = 0;
                break;
            }
        }
    }
    return 0;
}
