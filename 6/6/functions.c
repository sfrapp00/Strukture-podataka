#include "functions.h"
#include "date.h"
#include "ui.h"

int showReceipt(receiptP head) {
	int run = 1;
	int n = 1;
	int userInput, i;
	receiptP p;

	while (run) {		//omogucava laksi pregled racuna jer se ne vraca na glavni meni
		p = head->receiptNext;

		while (p != NULL) {
			printf("[%d] - %d-%d-%d\n", n++, p->date->year, p->date->month, p->date->day);
			p = p->receiptNext;
		}

		printf("[0] - Povratak\n");

		while (scanf(" %d", &userInput) != 1 || userInput < 0 || userInput > n - 1) {
			printf("Neispravan unos. Pokusajte ponovo:\n");
			while (getchar() != '\n');		//ciscenje buffera
		}

		separatorUI();

		p = head;

		if (userInput == 0)
			return 0;

		for (i = 0; i < userInput;i++) {
			p = p->receiptNext;
		}

		printReceipt(p);

		n = 1;		//resetiranje countera
	}

	return 0;
}

int printReceipt(receiptP p) {
	itemP ip = p->item->itemNext;

	printf("%d-%d-%d\n\n", p->date->year, p->date->month, p->date->day);

	while (ip != NULL) {
		printf("%-16s\t%d\t%.2f\n", ip->name, ip->amount, ip->price);		//formatiranje ispisa kako bi i namirnice s duzim imenom bile u ravnini s ostalima
		ip = ip->itemNext;
	}

	separatorUI();

	return 0;
}

int itemSearch(receiptP head) {
	int found = 0;
	int userInput;
	char itemName[MAX];
	int itemAmount = 0;
	double itemPrice = 0;
	date dateMin = {.year = 0, .month = 0, .day = 0};
	date dateMax = {.year = MAX*MAX, .month = MAX, .day = MAX};
	receiptP p = head->receiptNext;
	itemP ip;

	printf("Upisite ime namirnice:\n");

	while (scanf(" %s", itemName) != 1) {
		printf("Neispravan unos namirnice. Pokusajte ponovo:\n");
		while (getchar() != '\n');		//ciscenje buffera
	}

	printf("Zelite li ograniciti pretragu na odredeni vremenski period\n"
		"[1] - Da\n"
		"[0] - Ne\n"
	);

	while (scanf(" %d", &userInput) != 1 || userInput < 0 || userInput > 1) {
		printf("Neispravan unos. Pokusajte ponovo:\n");
		while (getchar() != '\n');		//ciscenje buffera
	}

	if (userInput) {
		printf("Upisite od kojeg datuma zelite uvid (YYYY-MM-DD):\n");

		while (scanf(" %4d-%2d-%2d", &dateMin.year, &dateMin.month, &dateMin.day) != 3 || !(validDate(&dateMin))) {
			printf("Neispravan unos datuma. Pokusajte ponovo:\n");
			while (getchar() != '\n');		//ciscenje buffera
		}

		printf("Upisite do kojeg datuma zelite uvid (YYYY-MM-DD):\n");

		while (scanf(" %4d-%2d-%2d", &dateMax.year, &dateMax.month, &dateMax.day) != 3 || !(validDate(&dateMax))) {
			printf("Neispravan unos datuma. Pokusajte ponovo:\n");
			while (getchar() != '\n');		//ciscenje buffera
		}
	}

	separatorUI();

	while (p != NULL) {		//prolazak kroz sve racune i usporedivanje datuma i imena namirnica
		ip = p->item->itemNext;
		if (compareDate(p->date, &dateMin) == 1 && compareDate(&dateMax, p->date) == 1) {
			while (ip != NULL) {
				if (strcmp(itemName, ip->name) == 0) {
					found = 1;
					itemAmount += ip->amount;
					itemPrice += ip->price * ip->amount;
				}
				ip = ip->itemNext;
			}
		}
		p = p->receiptNext;
	}
	if (found)
		printf("%-16s\t%d\t%.2f\n", itemName, itemAmount, itemPrice);		//foramtirani ispis
	else
		printf("Namirnica nije pronadena\n");

	separatorUI();

	return 0;
}