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
void addPBP(Position, Position);	//funkcija za dodavanje elemenata liste iza trazene osobe
void addPIP(Position, Position);	//funkcija za dodavanje elemenata liste isprid trazene osobe
void printP(Position);				//funkcija za ispisivanje svih elemenata liste
Position findP(Position);			//funkcija za pronalazenje elementa liste po prezimenu
void removeP(Position);				//funkcija za brisanje elementa liste po prezimenu
void uploadP(Position);				//funkcija za spremanje liste u datoteku
void downloadP(Position);			//funkcija za citanje liste iz datoteke
void sort(Position);				//funkcija za sortiranje elemenata liste

int main() {
	P Head = { "", "", 0, NULL };

	int i = 1;
	char o;

	while (i) {
		printf("Sto zelite?\nd - Dodati osobu\ni - Ispisati listu\nb - Izbrisati osobu\nu - Upisati listu u datoteku\nc - Iscitati listu iz datoteke\ns - Sortirati listu\nx - Ugasiti program\n");
		scanf(" %c", &o);

		switch (o) {			//switch case za odabir funkcije
		case 'd':
			createP(&Head);
			break;
		case 'i':
			printP(&Head);
			break;
		case 'b':
			removeP(&Head);
			break;
		case 'u':
			uploadP(&Head);
			break;
		case 'c':
			if (Head.Next == NULL)
				downloadP(&Head);
			else
				printf("Vec postoje elementi u listi");
			break;
		case 's':
			sort(&Head);
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
	printf("Gdje zelite dodati osobu?\np - Na pocetak\nk - Na kraj\nz - Iza trazene osobe\ns - Ispred trazene osobe\n");
	scanf(" %c", &se);

	switch (se) {				//odabir nacina dodavanja elementa
	case 'p':
		addPS(Head, newP);
		break;
	case 'k':
		if (Head->Next == NULL)
			addPS(Head, newP);
		else
			addPE(Head, newP);
		break;
	case 'z':
		addPBP(Head, newP);
		break;
	case 's':
		addPIP(Head, newP);
		break;
	default:
		printf("Neispravan unos\n");
	}
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
	for (pointer = Head->Next; pointer->Next != NULL; pointer = pointer->Next) {}	//navigacija do zadnjeg elementa liste

	newP->Next = pointer->Next;				//povezivanje elemenata
	pointer->Next = newP;
}

void addPBP(Position Head, Position newP) {
	printf("Upisite ime prezime i godinu rodenja (ime prezime godina rodenja)\n");
	scanf("%s %s %d", newP->name, newP->surname, &newP->year);

	Position pointer = findP(Head);
	pointer = pointer->Next;

	newP->Next = pointer->Next;				//povezivanje elemenata
	pointer->Next = newP;
}

void addPIP(Position Head, Position newP) {
	printf("Upisite ime prezime i godinu rodenja (ime prezime godina rodenja)\n");
	scanf("%s %s %d", newP->name, newP->surname, &newP->year);

	Position pointer = findP(Head);

	newP->Next = pointer->Next;				//povezivanje elemenata
	pointer->Next = newP;
}

void printP(Position Head) {
	int counter = 1;
	for (Position pointer = Head->Next; pointer != NULL; pointer = pointer->Next) {			//ispisivanje svih elemenata liste
		printf("%d. %s %s %d\n", counter, pointer->name, pointer->surname, pointer->year);
		counter++;
	}
}

Position findP(Position Head) {
	char s[MAX];
	printf("Upisite prezime: ");
	scanf(" %s", s);

	Position pointer;
	for (pointer = Head; pointer->Next != NULL; pointer = pointer->Next) {
		if (strcmp(pointer->Next->surname, s) == 0)			//usporedivanje stringova
			return pointer;									//vracanje pozicije elementa ispred trazene osobe
	}

	return NULL;
}

void removeP(Position Head) {
	Position pointer = findP(Head);							//pozicioniranje ispred elementa koji zelimo izbrisati
	Position temp;

	temp = pointer->Next;
	pointer->Next = pointer->Next->Next;
	temp->Next = NULL;
	free(temp);
}

void uploadP(Position Head) {
	FILE* f = fopen("osobe.txt", "w");						//otvaranje datoteke
	int counter = 1;

	for (Position pointer = Head->Next; pointer != NULL; pointer = pointer->Next) {			//ispisivanje svih elemenata liste
		fprintf(f, "%d. %s %s %d\n", counter, pointer->name, pointer->surname, pointer->year);
		counter++;
	}

	fclose(f);
}

void downloadP(Position Head) {
	FILE* f = fopen("osobe.txt", "r");						//otvaranje datoteke
	int counter;
	Position pointer = Head;

	while (!feof(f)) {
		Position newP = malloc(sizeof(P));					//alokacija memorije
		newP->Next = NULL;

		fscanf(f, "%d. %s %s %d\n", &counter, newP->name, newP->surname, &newP->year);		//dohvacanje podataka iz datoteke

		newP->Next = pointer->Next;				//povezivanje elemenata
		pointer->Next = newP;
		pointer = pointer->Next;				//postavljanje pointera na iduci element
	}

	fclose(f);
}

void sort(Position Head) {
	Position temp;
	Position p = Head->Next;					//definiranje elemenata za usporedivanje
	Position q = Head;
	int sorted = 1;								//int varijabla za provjeravanje je li lista sortirana

	while (sorted) {
		sorted = 0;
		p = Head->Next;							//postavljanje p i q na pocetak liste
		q = Head;

		while (p != NULL && p->Next != NULL) {
			if (strcmp(p->surname, p->Next->surname) > 0) {
				temp = p->Next;
				p->Next = temp->Next;
				temp->Next = p;
				q->Next = temp;

				sorted = 1;
			}
			q = p;
			p = p->Next;
		}
	}
}