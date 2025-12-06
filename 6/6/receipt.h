#pragma once
#include "open.h"

int createItem(itemP head, char* itemName, int itemAmount, double itemPrice);		//stvara strukturu namirnica
int createReceipt(receiptP head, dateP receiptDate, itemP itemHead);		//stvara strukturu racuna
int addItem(itemP head, itemP newItem);		//sortirani unos namirnica
int addReceipt(receiptP head, receiptP newReceipt);		//sortirani unos racuna
int freeReceipt(receiptP head);		//oslobadanje memorije racuna
int freeItem(itemP head);		//oslobadanje memorije namirnica