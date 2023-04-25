#define _CRT_SECURE_NO_WARNINGS
#define MAX (50)
#include <stdio.h>
#include <stdlib.h>

typedef struct lista* pozicija;
typedef struct lista {
	char ime[MAX];
	int br;
	pozicija next;
}lista;

pozicija stvaranje();
int dodaj(pozicija head);
int ispis(pozicija head);
int dodajIza(pozicija head);
int clearLista(pozicija head);
pozicija onajIza(pozicija, char[]);
int brisanjePoImenu(head);
int brisanjeElementa(pozicija head);
int trazi(pozicija head);
int dodajIzaTrazenog(pozicija head);
int dodajIspredTrazenog(pozicija head);
int unosIzDatoteke(pozicija head);
int ispisUDatoteku(pozicija head);
int sortiraniUnos(pozicija head);

int main() {
	pozicija head = NULL;
	head = stvaranje();
	//dodaj(head);
	//dodaj(head);
	// dodajIza(head);
	//dodajIzaTrazenog(head);
	// brisanjeElementa(head);
	// dodajIspredTrazenog(head);
	//unosIzDatoteke(head);
	sortiraniUnos(head);
	sortiraniUnos(head);
	sortiraniUnos(head);
	sortiraniUnos(head);
	ispis(head->next);
	ispisUDatoteku(head);
	//trazi(head);
	clearLista(head);
	return 0;
}

pozicija stvaranje() {                    //stvaranje
	pozicija p=NULL;                      //inicijaliziramo poziciju
	p = malloc(sizeof(lista));             //malloc
	if (p == NULL) {                      //sta ako ne uspije
		printf("Malloc error");
		return -1;
	}
	p->next = NULL;                     //njegov next je jednak NULL
	return p;                          //vratimo poziciju
}

int dodaj(pozicija head) {  //u dodaj upisujemo imena
	pozicija p = NULL;
	p = stvaranje();
	printf("unesite ime\n");
	scanf("%s", p->ime);
	printf("unesite broj\n");
	scanf("%d", &p->br);
	p->next = head->next;      //ovo je najveca baza dodavanja
	head->next = p;
}

int dodajIza(pozicija head) {  //odvrtis na kraj pa dodas
	while (head->next != NULL) {
		head = head->next;
	}
	dodaj(head);
}

int ispis(pozicija head) {
	if (head == NULL) {
		printf("prazno");
	}
	while (head != NULL) {
		printf("%s", head->ime);
		printf(" %d\n", head->br);
		head = head->next;
	}
}


int brisanjeElementa(pozicija head) //iz nekog razloga, ovo brisanje radi
{
	char str[20];
	printf("Unesi prezime osobe za brisanje:");
	scanf("%s", str);

	pozicija o = onajIza(head, str);                                 //na neku poziciju stavimo onaj koji je iza (zapravo ispred) (nisan uspia brisat bas taj)
	if (o == NULL)
	{
		printf("Ne postoji!");
		return 0;
	}

	pozicija temp = o->next;   //kako brisati
	o->next = temp->next;
	free(temp);

	return 1;
}


pozicija onajIza(pozicija head, char ime[]) {
	pozicija nova = head->next;
	while (strcmp(ime, nova->ime) != 0 && nova!=NULL) {
		
		head = nova;
		nova = nova->next;
	}
	if (head == NULL) {
		printf("error");
		return NULL;
	}
	return head;
	
	
}
int trazi(pozicija head) {
	char ime[50];
	printf("Unesi trazeno ime:\n");
	scanf("%s", ime);
	while (strcmp(ime, head->ime) != 0 && head->next != NULL) {
		head = head->next;
	}
	if (head->next == NULL && strcmp(ime, head->ime) != 0) {
		printf("error");
		return 1;
	}
	else {
		printf("broj trazenog je: %d", head->br);
	}
	return 0;
}


int dodajIzaTrazenog(pozicija head) {
	char ime[50];
	printf("Unesi trazeno ime:\n");
	scanf("%s", ime);
	while (strcmp(ime, head->ime) != 0 && head != NULL) {
		head = head->next;
	}
	if (head->next == NULL) {
		printf("trazeni ne postoji\n");
		return 1;
	}
	else {
		dodaj(head);
		return 0;
	}

}

int dodajIspredTrazenog(pozicija head) {
	char ime[50];
	printf("Unesi trazeno ime:\n");
	scanf("%s", ime);
	pozicija temp = onajIza(head, ime);
	dodaj(temp);
	return 0;

}

int clearLista(pozicija head) {
	pozicija temp = NULL;           //moramo stvorit neki temp
	temp = stvaranje();
	while (head->next!= NULL) {   //dok ne dodjemo do predzadnjeg
		temp = head->next;         //temp je onaj ispred heada               //ovako iz liste izvadimo temp, i mozemo ga brisat PRESPOJIMO
		head->next = temp->next;   //a sljedeci postaje onaj nakon tempa
		free(temp);
	}
	free(head);
	return 0;
}

int unosIzDatoteke(pozicija head) {
	FILE* fp = fopen("drzave.txt", "r");            //ona standardna porcedura za otvaranje datoteke
	if (fp == NULL) {
		printf("Trazena datoteka ne postoji\n");
		return -1;
	}
	pozicija o = NULL;
	while (!feof(fp))       //sad vrtimo do tog broja
	{
		o = stvaranje();              //svako stvaramo i dajemo mu podatke iz filea
		fscanf(fp, "%s %d", o->ime, &o->br);
		o->next = head->next;              //ovo koristimo za unos, dio koda koji se vec gore pojavljuje od unosa
		head->next = o;
	}
	fclose(fp);
}

int ispisUDatoteku(pozicija head) {
	FILE* fp = fopen("ispis.txt", "w");   //ne zaboravi FILE*
	if (fp == NULL) {
		printf("Trazena datoteka ne postoji\n");
		return -1;
	}
	head = head->next;
	while (head != NULL) {
		fprintf(fp,"%s %d\n", head->ime, head->br);
		head = head->next;
	}
	fclose(fp);
}

int sortiraniUnos(pozicija head) {
	pozicija o = stvaranje();
	printf("Unesi ime:\n");
	scanf("%s", o->ime);
	printf("\nUnesi broj:\n");
	scanf("%d", &o->br);
	if (head->next==NULL) {
		head->next= o;
	}
	else {
		while (strcmp(o->ime, head->ime) >= 0) {
			head = head->next;
		}
		o->next = head->next;
		head->next = o;
	}

	return 0;
}