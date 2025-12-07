#include "functions.h"
#include "date.h"
#include "ui.h"

int showReceipt(receiptP head) {
	int run = 1;
	int n = 1;
	int userInput, i;
	date dateMin = { .year = 0, .month = 0, .day = 0 };
	date dateMax = { .year = MAX * MAX, .month = MAX, .day = MAX };
	receiptP p;

	inputDate(&dateMin, &dateMax);

	while (run) {		//omogucava laksi pregled racuna jer se ne vraca na glavni meni
		p = head->receiptNext;

		while (p != NULL) {
			if (compareDate(p->date, &dateMin) == 1 && compareDate(&dateMax, p->date) == 1)
				printf("[%d] - %d-%d-%d\n", n++, p->date->year, p->date->month, p->date->day);
			p = p->receiptNext;
		}

		printf("[0] - Povratak\n\n");

		while (scanf(" %d", &userInput) != 1 || userInput < 0 || userInput > n - 1) {
			printf("\nNeispravan unos. Pokusajte ponovo:\n");
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

int showItem(receiptP head) {
	int found = 0;
	char itemName[MAX];
	int itemAmount = 0;
	double itemPrice = 0;
	date dateMin = {.year = 0, .month = 0, .day = 0};
	date dateMax = {.year = MAX*MAX, .month = MAX, .day = MAX};
	receiptP p = head->receiptNext;
	itemP ip;

	printf("Upisite ime namirnice:\n");

	while (scanf(" %s", itemName) != 1) {
		printf("\nNeispravan unos namirnice. Pokusajte ponovo:\n");
		while (getchar() != '\n');		//ciscenje buffera
	}

	printf("\n");

	inputDate(&dateMin, &dateMax);

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
		printf("\nNamirnica nije pronadena\n\n");

	separatorUI();

	return 0;
}

int highestValue(receiptP head) {
	double PriceMax = 0;
	double Price = 0;
	date dateMin = { .year = 0, .month = 0, .day = 0 };
	date dateMax = { .year = MAX * MAX, .month = MAX, .day = MAX };
	receiptP p = head->receiptNext;
	receiptP q = p;
	itemP ip;

	inputDate(&dateMin, &dateMax);

	separatorUI();

	while (p != NULL) {
		ip = p->item->itemNext;
		if (compareDate(p->date, &dateMin) == 1 && compareDate(&dateMax, p->date) == 1) {
			while (ip != NULL) {
				Price += ip->price * ip->amount;
				ip = ip->itemNext;
			}
		}
		if (Price > PriceMax) {
			PriceMax = Price;
			q = p;
		}
		Price = 0;
		p = p->receiptNext;
	}
	
	printf("Racun s najvecom potrosnjom je:\n");

	printReceipt(q);

	return 0;
}

int lowestValue(receiptP head) {
	double PriceMin = MAX*MAX;
	double Price = 0;
	date dateMin = { .year = 0, .month = 0, .day = 0 };
	date dateMax = { .year = MAX * MAX, .month = MAX, .day = MAX };
	receiptP p = head->receiptNext;
	receiptP q = p;
	itemP ip;

	inputDate(&dateMin, &dateMax);

	separatorUI();

	while (p != NULL) {
		ip = p->item->itemNext;
		if (compareDate(p->date, &dateMin) == 1 && compareDate(&dateMax, p->date) == 1) {
			while (ip != NULL) {
				Price += ip->price * ip->amount;
				ip = ip->itemNext;
			}
		}
		if (Price < PriceMin) {
			PriceMin = Price;
			q = p;
		}
		Price = 0;
		p = p->receiptNext;
	}

	printf("Racun s najmanjom potrosnjom je:\n");

	printReceipt(q);

	return 0;
}

int itemSearch(receiptP head) {
	int found = 0;
	char itemName[MAX];
	date dateMin = { .year = 0, .month = 0, .day = 0 };
	date dateMax = { .year = MAX * MAX, .month = MAX, .day = MAX };
	receiptP p = head->receiptNext;
	itemP ip;

	printf("Upisite ime namirnice:\n");

	while (scanf(" %s", itemName) != 1) {
		printf("\nNeispravan unos namirnice. Pokusajte ponovo:\n");
		while (getchar() != '\n');		//ciscenje buffera
	}

	printf("\n");

	inputDate(&dateMin, &dateMax);

	separatorUI();

	while (p != NULL) {
		ip = p->item->itemNext;
		found = 0;
		if (compareDate(p->date, &dateMin) == 1 && compareDate(&dateMax, p->date) == 1) {
			while (ip != NULL && !found) {
				if (strcmp(itemName, ip->name) == 0) {
					found = 1;
					printReceipt(p);
				}
				ip = ip->itemNext;
			}
		}
		p = p->receiptNext;
	}

	if (!found)
		printf("\nNamirnica nije pronadena\n\n");

	return 0;
}