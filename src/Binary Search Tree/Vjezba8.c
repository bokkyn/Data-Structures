// Napisati program koji omogućava rad s binarnim stablom pretraživanja. Treba
// omogućiti unošenje novog elementa u stablo, ispis elemenata (inorder, preorder, postorder i
// level order), brisanje i pronalaženje nekog elementa

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

typedef struct cvor* pozicija;
typedef struct cvor {
    int br;
    pozicija left;
    pozicija right;
}cvor;

static int brojac = 0;

cvor* stvaranje();
int Level(pozicija);
int PrintCurrentLevel(pozicija p, int level);
pozicija insert(pozicija, pozicija);
pozicija find(pozicija, int);
pozicija delete(pozicija, int);
pozicija findMax(pozicija);
pozicija findMin(pozicija);
pozicija printInorder(pozicija);
pozicija printPreorder(pozicija);
pozicija printPostorder(pozicija);
pozicija printLevelorder(pozicija);
int clear(pozicija);
int userInterface(pozicija, pozicija);

int main()
{
    pozicija root = NULL;
    root = stvaranje();
    userInterface(root, root);
    return 0;
}

int userInterface(pozicija p, pozicija root)
{
    int check = 1;
    int n;
    while (check == 1)
    {
        printf("\nOdaberite\n");
        printf("A-Unos\n");
        printf("B-Brisanje\n");
        printf("C-Pronalazenje elementa\n");
        printf("D-Ispis elemenata - inorder\n");
        printf("E-Ispis elemenata - preorder\n");
        printf("F-Ispis elemenata - postorder\n");
        printf("G-Ispis elemenata - level order\n");
        printf("X-Izlaz iz programa\n");
        
        char c = { 0 };
        scanf(" %c", &c); //korisnik unosi opciju koju zeli
        c = toupper(c); //u slucaju da je korisnik unio malo slovo, postavljamo ga na veliko slovo tako da switch case moze preopznati
        switch (c)
        {
        case 'A':
            printf("Unesite broj koji zelite unijeti\n");
            if (scanf("%d", &n) == 1)//ako je korisnik zapravo unio broj
            {
                if (brojac==0) {// ako je to prvi broj kojeg unosimo
                    p->br = n;
                    brojac++;   //dizemo brojac, vise nije prvi broj
                }
                else {
                    pozicija q = NULL;
                    q = stvaranje();
                    q->br = n;
                    p = insert(p, q);
                    brojac++;
                }
            }
            else printf("Unesite broj\n");
            break;
        case 'B':
            printf("Unesite broj koji zelite izbrisati\n");
            if (scanf("%d", &n) == 1) {//ako je korisnik zapravo unio broj
                p = delete(p, n);
                //brojac--;
            }
            else printf("Unesite broj\n");
            break;
        case 'C':
            printf("Unesite broj koji zelite naci\n");
            if (scanf("%d", &n) == 1)//ako je korisnik zapravo unio broj
            {
                if (!p->br) // ako root nema broj
                    printf("Taj broj ne postoji\n");
                else {
                    p = find(p, n);
                    if (p == NULL)
                        printf("Taj broj ne postoji\n");
                    else printf("Taj broj postoji\n");
                }
            }
            else
                printf("Unesite broj\n");
            p = root; //vracamo pokazivac na root
            break;
        case 'D':
            p = printInorder(p);
            break;
        case 'E':
            p = printPreorder(p);
            break;
        case 'F':
            p = printPostorder(p);
            break;
        case 'G':
            p = printLevelorder(p);
            break;
        case 'X':
            check = 0;
            clear(root);
            break;
        default: //ako se nije uneseno nijedno od ponudenih slova nego nesto drugo
            printf("Unesite jedno od ponudenih slova\n");
            break;
        }
    }
    return 0;
}

cvor* stvaranje()
{
    cvor* c = NULL;
    c = malloc(sizeof(cvor));
    if (NULL == c) {
        printf("Greska u alokaciji memorije\n");
    }
    else
    {
        c->left = NULL;
        c->right = NULL;
    }
    return c;
}

pozicija insert(pozicija p, pozicija q)
{
    if (p == NULL)
        return q;
    if (p->br < q->br)
        p->right = insert(p->right, q);  
    else if (p->br > q->br)
        p->left = insert(p->left, q);
    else
        free(q);
    return p;
}

pozicija find(pozicija p, int n)
{
    if (p == NULL)
        return NULL;
    else if (p->br > n)
        return find(p->left, n);
    else if (p->br < n)
        return find(p->right, n);
    else return p;
}

pozicija delete(pozicija p, int n)
{
    if (p == NULL)
        return NULL;
    if (p->br > n)
        p->left = delete(p->left, n);
    else if (p->br < n)
        p->right = delete(p->right, n);
    else {
        if (p->left) {
            pozicija temp = findMax(p->left);
            p->br = temp->br;
            p->left = delete(p->left, temp->br);
        }
        else if (p->right) {
            pozicija temp = findMin(p->right);
            p->br = temp->br;
            p->right = delete(p->right, temp->br);
        }
        else {
            free(p);
            return NULL;
        }
    }
    brojac--;
    return p;
}

pozicija findMax(pozicija p)
{
    while (p->right != NULL)
        p = p->right;
    return p;
}

pozicija findMin(pozicija p)
{
    while (p->left != NULL)
        p = p->left;
    return p;
}

pozicija printInorder(pozicija p)
{
    if (p == NULL) {                                //nije greška u rekurziji
        return NULL;
    }
    p->left=printInorder(p->left);
    printf("%d ", p->br);
    p->right=printInorder(p->right);

    return p;
}

pozicija printPostorder(pozicija p)
{
    if (p == NULL)
        return NULL;
    p->left = printPostorder(p->left);
    p->right=printPostorder(p->right);
    printf("%d ", p->br);
    return p;
}

pozicija printPreorder(pozicija p)
{
    if (p == NULL)
        return NULL;
    printf("%d ", p->br);
    p->left=printPreorder(p->left);
    p->right=printPreorder(p->right);
    return p;
}

pozicija printLevelorder(pozicija p)
{
    int h = Level(p);
    for (int i = 1; i <= h; i++)
        PrintCurrentLevel(p, i);
    return p;
}

int PrintCurrentLevel(pozicija p, int level)
{
    if (p == NULL)
        return 0;
    if (level == 1)
        printf("%d ", p->br);
    else if (level > 1) {
        PrintCurrentLevel(p->left, level - 1);
        PrintCurrentLevel(p->right, level - 1);
    }
    return 0;
}

int Level(pozicija p)
{
    int right = 0, left = 0;
    if (p == NULL)
        return 0;
    else {
        left = Level(p->left);
        right = Level(p->right);

        if (left > right)
            return (left + 1);
        else
            return (right + 1);
    }
}

int clear(pozicija p)
{
    if (p != NULL)
    {
        clear(p->left);
        clear(p->right);
        free(p);
    }
    return 0;

    // 2.Nacin:
    // while(p->left!=NULL || p->right!=NULL)
    //     delete(p,p->br);
    // free(p);
    // return 0;
}

