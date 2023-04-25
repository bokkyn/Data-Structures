//1. Napisati program koji prvo pročita koliko redaka ima datoteka, tj. koliko ima studenata
//zapisanih u datoteci. Nakon toga potrebno je dinamički alocirati prostor za niz struktura
//studenata (ime, prezime, bodovi) i učitati iz datoteke sve zapise. Na ekran ispisati ime,
//prezime, apsolutni i relativni broj bodova.
//Napomena: Svaki redak datoteke sadrži ime i prezime studenta, te broj bodova na kolokviju.
//relatvan_br_bodova = br_bodova/max_br_bodova*100

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include<string.h>

#define FILE_DIDNT_OPEN_ERROR (-1) //-1 magicni broj mrale
#define FILE_OPENED (0)
#define MAX_LINE (1024)
#define MAX_FILE_NAME (256)
#define MAX_NAME (747)

typedef struct {
 char ime[MAX_NAME];
 char prezime[MAX_NAME];
 int br_bodova;
}_Student;

int fileCheck(char* filename) //provjera može li se uopće datoteka otvoriti
{
    FILE* fp=NULL;
    fp=fopen(filename,"r");
    if (fp==NULL){ 
        printf("Datoteka %s se nije otvorila!", filename);
        return FILE_DIDNT_OPEN_ERROR;
    }
    else return FILE_OPENED;
}

int countStudentsFromFile(char* filename){ //šalješ pointer, ne datoteku
    FILE* fp=fopen(filename,"r");;
    int count =0;
    char buffer[MAX_LINE]={0};
    
    //brojanje-dok nije kraj filea, uspoređujemo s \n, da ne brojimo prazne
    while (!feof(fp)){
        fgets(buffer,MAX_LINE,fp);
        if (strcmp("\n", buffer)!=0){
            count++;
        }
    }
    fclose(fp);  //svaku datoteku je lijepo zatvoriti
    return count;
}

void saveStudentsFromFile(_Student* studenti, char* filename, int count)
{
    FILE*fp=fopen(filename,"r");
    for(int i=0;i<count;i++)
    {
        fscanf(fp," %s %s %d", (studenti+i)->ime, (studenti+i)->prezime, &(studenti+i)->br_bodova);
    }
    fclose(fp);
}

float relativan_br_bodova(int bodovi, int max_bodovi){
    return (float)bodovi/max_bodovi*100;
}

void ispisStudenata(_Student* studenti, int count)
{
    for (int i=0;i<count;i++)
    {
        printf("%s %s\t%d\t%.2f percent\n", (studenti+i)->ime, (studenti+i)->prezime, (studenti+i)->br_bodova, relativan_br_bodova((studenti+i)->br_bodova,50));
    }
    
}

int main(void){
    _Student* studenti=NULL;
    char filename[MAX_FILE_NAME]={0};
    int count=0;
    int check=0;
    printf("Unesi ime datoteke:\n");
    scanf(" %s", filename);
    check=fileCheck(filename);
    if(check!=FILE_DIDNT_OPEN_ERROR)//ostatak programa pokrećemo samo ako je datoteka uspješno otvorena
    {   
        count=countStudentsFromFile(filename);
        printf("Broj studenata je %d\n", count);
        studenti=malloc(count*sizeof(_Student));
        saveStudentsFromFile(studenti, filename, count);
        ispisStudenata(studenti, count);
        free(studenti);
    }
    return 0;
}