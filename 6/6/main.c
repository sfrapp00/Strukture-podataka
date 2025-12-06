#include "open.h"
#include "ui.h"

int main() {
	receipt receiptHead = { .date = NULL, .item = NULL, .receiptNext = NULL };

	openFile(&receiptHead);
	UI(&receiptHead);
	
	return 0;
}