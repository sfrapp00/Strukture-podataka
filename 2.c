#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20

typedef struct Person* Position;
typedef struct Person {
	char name[MAX];
	char surname[MAX];
	int year;

	Position Next;
}P;

void createP(Position);				//funkcija za stvaranje elementa liste
void addPE(Position, Position);		//funkcija za dodavanje elementa liste na kraj
void addPS(Position, Position);		//funkcija za dodavanje elemenata liste na pocetak
void printP(Position);				//funkcija za ispisivanje svih elemenata liste
void findP(Position);				//funkcija za pronalazenje elementa liste po prezimenu
void removeP(Position);				//funkcija za brisanje elementa liste po prezimenu

int main() {
	P Head = {"", "", 0, NULL};

	int i = 1;
	char o;

	while (i) {
		printf("Sto zelite?\nd - Dodati osobu\ni - Ispisati listu\np - Pretraziti osobu\nb - Izbrisati osobu\nx - Ugasiti program\n");
		scanf(" %c", &o);

		switch (o) {			//switch case za odabir funkcije
			case 'd':
				createP(&Head);
				break;
			case 'i':
				printP(&Head);
				break;
			case 'p':
				findP(&Head);
				break;
			case 'b':
				removeP(&Head);
				break;
			case 'x':
				i = 0;
				break;
			default:
				printf("Neispravan unos\n");
		}
		printf("\n");
	}
	
	return 0;
}

void createP(Position Head) {
	Position newP = malloc(sizeof(P));			//alokacija memorije za novu osobu

	newP->name[0] = '\0';
	newP->surname[0] = '\0';
	newP->year = 0;
	newP->Next = NULL;

	char se;
	printf("Zelite li dodati osobu na pocetak ili kraj liste?\np - pocetak\nk - kraj\n");
	scanf(" %c", &se);

	if (se == 'p' || Head->Next == NULL)		//odabir dodavanja elementa na pocetak ili kraj liste
		addPS(Head, newP);
	else if (se == 'k')
		addPE(Head, newP);
	else
		printf("Greska neispravan unos\n");
}

void addPS(Position Head, Position newP) {
	printf("Upisite ime prezime i godinu rodenja (ime prezime godina rodenja)\n");
	scanf("%s %s %d", newP->name, newP->surname, &newP->year);

	newP->Next = Head->Next;				//povezivanje elemenata
	Head->Next = newP;
}

void addPE(Position Head, Position newP) {
	printf("Upisite ime prezime i godinu rodenja (ime prezime godina rodenja)\n");
	scanf("%s %s %d", newP->name, newP->surname, &newP->year);

	Position pointer;
	for (pointer = Head->Next; pointer->Next != NULL; pointer = pointer->Next){}	//navigacija do zadnjeg elementa liste

	newP->Next = pointer->Next;				//povezivanje elemenata
	pointer->Next = newP;
}

void printP(Position Head) {
	int counter = 1;
	for (Position pointer = Head->Next; pointer != NULL; pointer = pointer->Next) {	//ispisivanje svih elemenata liste
		printf("%d. %s %s %d\n", counter, pointer->name, pointer->surname, pointer->year);
		counter++;
	}
}

void findP(Position Head) {
	int counter = 1;
	char s[MAX];
	printf("Upisite prezime: ");
	scanf(" %s", s);

	Position pointer;
	for (pointer = Head->Next; pointer != NULL; pointer = pointer->Next) {
		if (strcmp(pointer->surname, s) == 0)				//usporedivanje stringova
			printf("%d. %s %s %d\n", counter, pointer->name, pointer->surname, pointer->year);		//ispis elementa
		counter++;
	}
}

void removeP(Position Head) {
	int i = 1;
	char s[MAX];
	printf("Upisite prezime: ");
	scanf(" %s", s);

	Position pointer = Head;
	Position temp;

	while (i) {		
		if (strcmp(pointer->Next->surname, s) == 0)			//usporedivanje stringova
			i = 0;										//izlazenje iz while petlje
		else
			pointer = pointer->Next;
	}

	temp = pointer->Next;
	pointer->Next = pointer->Next->Next;
	temp->Next = NULL;
	free(temp);
}