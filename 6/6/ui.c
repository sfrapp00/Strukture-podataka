#include "ui.h"
#include "receipt.h"
#include "functions.h"

int UI(receiptP head) {
	int run = 1;
	int userInput;

	while (run) {
		printf("Naredbe:\n"
			"[1] - Prikaz racuna\n"
			"[2] - Prikaz trazene namirnice\n"
			"[3] - Racun s najvecom potrosnjom\n"
			"[4] - Racun s najmanjom potrosnjom\n"
			"[5] - Prikaz svih racuna s trazenom namirnicom\n"
			"[0] - Ugasi program\n"
			"\n"
		);

		while (scanf(" %d", &userInput) != 1) {
			printf("\nNeispravan unos. Pokusajte ponovo:\n");
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
			showItem(head);
			break;
		case 3:
			highestValue(head);
			break;
		case 4:
			lowestValue(head);
			break;
		case 5:
			itemSearch(head);
			break;
		default:
			printf("Neispravan unos. Pokusajte ponovo\n\n");
			break;
		}
	}

	return 0;
}

int separatorUI() {
	int i;
		
	printf("\n");

	for (i = 0;i < MAX;i++) {
		printf("=");
	}
	printf("\n\n");

	return 0;
}