#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max_bodovi 50

typedef struct student {
	char ime[20];
	char prezime[20];
	int bodovi;
}stud;

stud* upis(stud* s, FILE* f, int br) {
	for (int i = 0;i < br;i++) {
		fscanf(f, "%s %s %d\n", s[i].ime, s[i].prezime, &s[i].bodovi);
	}
	return s;
}

void ispis(stud* s, int br) {
	for (int i = 0;i < br;i++) {
		float rel_bodovi = (float)s[i].bodovi / (float)max_bodovi * 100;
		printf("%s %s %d %.2f\n", s[i].ime, s[i].prezime, s[i].bodovi, rel_bodovi);
	}
}

void main() {
	int br = 0;

	FILE* f = fopen("studenti.txt", "r");
	
	while (!feof(f))
		if (fgetc(f) == '\n')
			br++;

	stud* s;
	s = malloc(br * sizeof(stud));

	rewind(f);
	s = upis(s, f, br);
	ispis(s, br);

	fclose(f);
}