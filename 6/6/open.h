#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 64

typedef struct _date* dateP;
typedef struct _date {
	int year;
	int month;
	int day;
}date;

typedef struct _item* itemP;
typedef struct _item {
	char* name;
	int amount;
	double price;
	itemP itemNext;
}item;

typedef struct _receipt* receiptP;
typedef struct _receipt {
	dateP date;
	itemP item;
	receiptP receiptNext;
}receipt;

int openFile(receiptP head);		//otvara racuni.txt
int openReceipt(receiptP head, char* txtPath);		//otvara zasebne racune