#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50

typedef struct _poly* Position;
typedef struct _poly {
	int coeff;
	int pow;
	Position next;
}poly;

int openFile(char*, char*);
int createPoly(Position, char*);
int addPoly(Position, int, int);
int sumPoly(Position, Position, Position);
int multPoly(Position, Position, Position);
int printPoly(Position);

int main() {
	poly sumhead = { .coeff = 0, .pow = 0, .next = NULL};		//head liste za rezultat zbrajanja
	poly multhead = sumhead;									//head liste za rezultat mnozenja
	poly first = sumhead;										//head liste prvog polinoma
	poly second = sumhead;										//head liste drugog polinoma

	char* fp = malloc(MAX * sizeof(char));						//alokacija buffera za prvi polinom
	if (fp == NULL) {
		printf("Error pri alociranju memorije\n");
		return -1;
	}

	char* sp = malloc(MAX * sizeof(char));						//alokacija buffera za drugi polinom
	if (sp == NULL) {
		printf("Error pri alociranju memorije\n");
		return -1;
	}

	openFile(fp, sp);
	createPoly(&first, fp);
	createPoly(&second, sp);
	
	printPoly(&first);
	printPoly(&second);

	sumPoly(&sumhead, &first, &second);
	printPoly(&sumhead);

	multPoly(&multhead, &first, &second);
	printPoly(&multhead);

	Position q;										//oslobadanje memorije
	while (sumhead.next != NULL) {
		q = sumhead.next;
		sumhead.next = q->next;
		free(q);
	}

	while (multhead.next != NULL) {
		q = multhead.next;
		multhead.next = q->next;
		free(q);
	}

	while (first.next != NULL) {
		q = first.next;
		first.next = q->next;
		free(q);
	}

	while (second.next != NULL) {
		q = second.next;
		second.next = q->next;
		free(q);
	}

	free(fp);
	free(sp);

	return 0;
}

int openFile(char* fp, char* sp) {
	FILE* file = fopen("poly.txt", "r");				//otvaranje datoteke
	if (!file) {
		printf("Error pri otvaranju datoteke\n");
		return -1;
	}

	char c = fgetc(file);
	int i = 0;

	while (c != '\n' && !feof(file)) {					//punjenje stringa prvog polinoma
		if (feof(file)) {
			printf("Neispravan format datoteke\n");
			return -1;
		}
		fp[i++] = c;
		c = fgetc(file);
	}

	fp[i] = '\0';
	c = fgetc(file);
	i = 0;

	while (c != '\n' && !feof(file)) {					//punjenje stringa drugog polinoma
		sp[i++] = c;
		c = fgetc(file);
	}

	sp[i] = '\0';
	fclose(file);										//zatvaranje datoteke

	return 0;
}

int createPoly(Position head, char* buffer) {
	int i,c,p;

	while (sscanf(buffer, "%d %d%n", &c, &p, &i) == 2) {	//odvajanje vrijednosti iz stringa
		addPoly(head, c, p);
		buffer += i+1;										//pozicioniranje na iduci par
	}

	return 0;
}

int addPoly(Position head, int pc, int pp) {
	Position newpoly = malloc(sizeof(poly));				//alokacija novog elementa liste
	if (newpoly == NULL) {
		printf("Error pri alociranju memorije\n");
		return -1;
	}
	newpoly->coeff = pc;
	newpoly->pow = pp;

	Position p = head;
	Position q = p->next;

	int added = 1;											//provjera je li dodan element

	while (added) {
		if (q == NULL) {
			newpoly->next = q;
			p->next = newpoly;
			added = 0;
		}
		else if (q->pow == pp) {
			q->coeff += pc;
			if (q->coeff == 0) {
				p->next = q->next;
				q->next = NULL;
				free(q);
			}
			free(newpoly);
			added = 0;
		}
		else if (q->pow > pp) {
			q = q->next;
			p = p->next;
		}
		else if (q->pow < pp) {
			newpoly->next = q;
			p->next = newpoly;
			added = 0;
		}
	}

	return 0;
}

int sumPoly(Position head, Position first, Position second) {
	Position f = first->next;
	Position s = second->next;

	while (f != NULL) {
		addPoly(head, f->coeff, f->pow);
		f = f->next;
	}

	while (s != NULL) {
		addPoly(head, s->coeff, s->pow);
		s = s->next;
	}

	return 0;
}

int multPoly(Position head, Position first, Position second) {
	Position f = first->next;
	Position s = second->next;

	while (f != NULL) {												//mnozenje svag elementa sa svakim
		while (s != NULL) {
			addPoly(head, f->coeff * s->coeff, f->pow + s->pow);
			s = s->next;
		}
		f = f->next;
		s = second->next;
	}

	return 0;
}

int printPoly(Position head) {
	Position q = head->next;

	while (q != NULL) {												//printanje liste
		printf("%d %d ", q->coeff, q->pow);
		q = q->next;
	}

	printf("\n");

	return 0;
}