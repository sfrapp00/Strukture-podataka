#include "ui.h"
#include "receipt.h"
#include "functions.h"

int UI(receiptP head) {
	int run = 1;
	int userInput;

	while (run) {
		printf("Naredbe:\n"
			"[1] - Prikaz racuna\n"
			"[2] - Prikaz namirnica\n"
			"[0] - Ugasi program\n"
			"\n"
		);

		while (scanf(" %d", &userInput) != 1) {
			printf("Neispravan unos. Pokusajte ponovo:\n");
			while (getchar() != '\n');		//ciscenje buffera
		}

		separatorUI();

		switch (userInput) {
		case 0:
			freeReceipt(head);
			run = 0;
			break;
		case 1:
			showReceipt(head);
			break;
		case 2:
			itemSearch(head);
			break;
		default:
			printf("Neispravan unos. Pokusajte ponovo:\n");
			break;
		}
	}

	return 0;
}

int separatorUI() {
	int i;

	for (i = 0;i < MAX;i++) {
		printf("=");
	}
	printf("\n");

	return 0;
}