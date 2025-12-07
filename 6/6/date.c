#include "date.h"

int compareDate(dateP date1, dateP date2) {
	if (date1->year > date2->year) {
		return 1;
	}
	else if (date1->year < date2->year) {
		return -1;
	}
	else {
		if (date1->month > date2->month) {
			return 1;
		}
		else if (date1->month < date2->month) {
			return -1;
		}
		else {
			if (date1->day > date2->day) {
				return 1;
			}
			else if (date1->day < date2->day) {
				return -1;
			}
			else
				return 0;
		}
	}
}

int validDate(dateP d) {
	if (d->year > 0 && d->year < 2026) {
		switch (d->month) {
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			if (d->day > 0 && d->day < 32)
				return 1;
			break;
		case 4:
		case 6:
		case 9:
		case 11:
			if (d->day > 0 && d->day < 31)
				return 1;
			break;
		case 2:
			if (d->day > 0 && d->day < 29)
				return 1;
			else if (d->day == 29 && d->year % 4 == 0)		//provjera za prijestupnu godinu (neukljucuje preciznost za vise od 400 godina)
				return 1;
			break;
		default:
			return 0;
			break;
		}
		return 0;
	}
	return 0;
}

int inputDate(dateP dateMin, dateP dateMax) {
	int userInput;

	printf("Zelite li ograniciti pretragu na odredeni vremenski period\n"
		"[1] - Da\n"
		"[0] - Ne\n"
		"\n"
	);

	while (scanf(" %d", &userInput) != 1 || userInput < 0 || userInput > 1) {
		printf("\nNeispravan unos. Pokusajte ponovo:\n");
		while (getchar() != '\n');		//ciscenje buffera
	}

	if (!userInput)
		return 0;

	printf("\nUpisite od kojeg datuma zelite uvid (YYYY-MM-DD):\n");

	while (scanf(" %4d-%2d-%2d", &dateMin->year, &dateMin->month, &dateMin->day) != 3 || !(validDate(dateMin))) {
		printf("\nNeispravan unos datuma. Pokusajte ponovo:\n");
		while (getchar() != '\n');		//ciscenje buffera
	}


	printf("\nUpisite do kojeg datuma zelite uvid (YYYY-MM-DD):\n");

	while (scanf(" %4d-%2d-%2d", &dateMax->year, &dateMax->month, &dateMax->day) != 3 || !(validDate(dateMax))) {
		printf("\nNeispravan unos datuma. Pokusajte ponovo:\n");
		while (getchar() != '\n');		//ciscenje buffera
	}

	return 0;
}