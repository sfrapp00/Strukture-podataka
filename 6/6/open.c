#include "open.h"
#include "receipt.h"
#include "date.h"

int openFile(receiptP head) {
	FILE* file = fopen("racuni.txt", "r");
	if (!file) {
		printf("Error pri otvaranju datoteke racuni.txt\n");
		return -1;
	}

	char txtPath[MAX];

	while (fscanf(file, "%s\n", txtPath) == 1) {
		if (openReceipt(head, txtPath) == -1)
			return -1;
	}

	return 0;
}

int openReceipt(receiptP head, char* txtPath) {
	FILE* file = fopen(txtPath, "r");
	if (!file) {
		printf("Error pri otvaranju datoteke %s\n", txtPath);
		return -1;
	}

	int y, m, d, a;
	float p;
	char n[MAX];

	itemP itemHead = malloc(sizeof(item));		//alokacija heada za namirnice
	if (itemHead == NULL) {
		printf("Error pri alokaciji memorije");
		return -1;
	}
	itemHead->name = "";
	itemHead->amount = 0;
	itemHead->price = 0;
	itemHead->itemNext = NULL;

	if (fscanf(file, "%4d-%2d-%2d\n", &y, &m, &d) != 3) {
		printf("Neispravan datum racuna\n");
		return -1;
	}

	dateP receiptDate = malloc(sizeof(date));		//alokacija datuma
	if (receiptDate == NULL) {
		printf("Error pri alokaciji memorije");
		return -1;
	}
	receiptDate->year = y;
	receiptDate->month = m;
	receiptDate->day = d;

	if (!validDate(receiptDate)) {
		printf("Neispravan datum racuna\n");
		return -1;
	}

	createReceipt(head, receiptDate, itemHead);

	while (!feof(file)) {
		if (fscanf(file, "%s %d %f", n, &a, &p) != 3) {
			printf("Neispravan format artikla %s\n", n);
			return -1;
		}
		createItem(itemHead, n, a, p);
	}

	fclose(file);

	return 0;
}