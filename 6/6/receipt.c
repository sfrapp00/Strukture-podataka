#include "receipt.h"
#include "date.h"

int createItem(itemP head, char* itemName, int itemAmount, double itemPrice) {
	itemP newItem = malloc(sizeof(item));
	if (newItem == NULL) {
		printf("Error pri alokaciji memorije");
		return -1;
	}

	newItem->name = malloc(strlen(itemName) + 1);		//alokacija imena nove namirnice
	if (newItem->name == NULL) {
		printf("Error pri alokaciji memorije");
		return -1;
	}
	strcpy(newItem->name, itemName);		//pridruzivanje vrijednosti stringa
	newItem->amount = itemAmount;
	newItem->price = itemPrice;
	newItem->itemNext = NULL;

	addItem(head, newItem);

	return 0;
}

int createReceipt(receiptP head, dateP receiptDate, itemP itemHead) {
	receiptP newReceipt = malloc(sizeof(receipt));
	if (newReceipt == NULL) {
		printf("Error pri alokaciji memorije");
		return -1;
	}

	newReceipt->date = receiptDate;
	newReceipt->item = itemHead;
	newReceipt->receiptNext = NULL;

	addReceipt(head, newReceipt);

	return 0;
}

int addItem(itemP head, itemP newItem) {
	itemP p = head;
	itemP q = p->itemNext;

	int added = 0;		//provjerava je li element dodan

	while (!added) {
		if (q == NULL) {
			newItem->itemNext = p->itemNext;
			p->itemNext = newItem;
			added = 1;
		}
		else if (strcmp(q->name, newItem->name) == 0) {		//ako su imena jednaka dodaje se nakon postojeceg
			newItem->itemNext = q->itemNext;
			q->itemNext = newItem;
			added = 1;
		}
		else if (strcmp(q->name, newItem->name) > 0) {
			newItem->itemNext = p->itemNext;
			p->itemNext = newItem;
			added = 1;
		}
		else if (strcmp(q->name, newItem->name) < 0) {
			q = q->itemNext;
			p = p->itemNext;
		}
	}

	return 0;
}

int addReceipt(receiptP head, receiptP newReceipt) {
	receiptP p = head;
	receiptP q = p->receiptNext;

	int added = 0;

	while (!added) {
		if (q == NULL) {
			newReceipt->receiptNext = p->receiptNext;
			p->receiptNext = newReceipt;
			added = 1;
		}
		else if (compareDate(q->date, newReceipt->date) == 0) {		//ako su datumi isti dodaje se nakon postojeceg
			newReceipt->receiptNext = q->receiptNext;
			q->receiptNext = newReceipt;
			added = 1;
		}
		else if (compareDate(q->date, newReceipt->date) == 1) {
			newReceipt->receiptNext = p->receiptNext;
			p->receiptNext = newReceipt;
			added = 1;
		}
		else if (compareDate(q->date, newReceipt->date) == -1) {
			q = q->receiptNext;
			p = p->receiptNext;
		}
	}

	return 0;
}

int freeReceipt(receiptP head) {
	receiptP p;
	while (head->receiptNext != NULL) {
		p = head->receiptNext;
		head->receiptNext = p->receiptNext;
		freeItem(p->item);
		free(p->date);		//datum se posebno oslobada
		free(p);
	}

	return 0;
}

int freeItem(itemP head) {
	itemP p;
	while (head->itemNext != NULL) {
		p = head->itemNext;
		head->itemNext = p->itemNext;
		free(p->name);		//ime se posebno oslobada
		free(p);
	}
	free(head);		//posto je head dio strukture racun i njega oslobadamo

	return 0;
}