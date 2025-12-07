#pragma once
#include "open.h"

int showReceipt(receiptP head);		//pregled svih racuna
int printReceipt(receiptP head);		//ispis racuna
int showItem(receiptP head);		//trazi odredenu namirnicu i njenu potraznju u odredenom vremenskom razdoblju
int highestValue(receiptP head);		//trazi racun s najvecom potrosnjom
int lowestValue(receiptP head);		//trazi racun s najmanjom potrosnjom
int itemSearch(receiptP head);		//prikazuje sve racune s odredenom namirnicom