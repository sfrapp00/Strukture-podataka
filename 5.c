#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50

typedef struct _postfix* Position;
typedef struct _postfix {               //struktura za element liste
	double number;
	Position next;
}postfix;

int readFile(char*);
int pushEl(Position, double);
int popEl(Position, char);


int main() {
	postfix head = { .next = NULL, .number = 0 };

	char* buffer = malloc(MAX * sizeof(char));          //alokacija memorije za string buffer
    if (buffer == NULL) {                               //provjera alokacije
        printf("Error pri alociranju memorije\n");
        return -1;
    }

    int i = 0;
    int temp = 1;
    double x = 0;
    int num = 0;

	readFile(buffer);

    while (buffer[i] != '\0' && temp) {                                                     //petlja koja prolazi kroz buffer
        if (buffer[i] == '+' || buffer[i] == '-' || buffer[i] == '*' || buffer[i] == '/')
            popEl(&head, buffer[i]);                                                        //poziv funkcije za operatore

        else if (buffer[i] >= '0' && buffer[i] <= '9') {                                    //poziv funkcije za brojeve                                                            
            x = x * 10 + (double)(buffer[i] - '0');                                         //u slucaju vise znamenkastih brojeva
            num = 1;                                                                        //provjera kada zavrsava broj
        }

        else if (buffer[i] == ' ') {
            if (num == 1) {
                pushEl(&head, x);
                x = 0;
                num = 0;
            }
        }

        else {
            temp = 0;
            printf("Invalidna sintaksa u datoteci\n");                                      //provjera za neocekivane simbole
        }
        i++;
    }

    printf("%s = %.2f\n", buffer, head.next->number);

    free(buffer);                                       //oslobadanje memorije buffera

    Position q;
    while (head.next != NULL) {                         //oslobadanje memorije stoga
        q = head.next;
        head.next = q->next;
        free(q);
    }

	return 0;
}

int readFile(char* buffer) {
    FILE* file = fopen("postfix.txt", "r");             
    if (!file) {
        printf("Error pri otvaranju datoteke\n");
        return -1;
    }

    int i = 0;

    while (!feof(file)) {                       //punjenje buffera
        char c = fgetc(file);
        if(!feof(file))
            buffer[i++] = c;
    }

    buffer[i] = '\0';
    fclose(file);

    return 0;
}

int pushEl(Position head, double x) {               //dodavanje elemenata stoga
    Position newEl = malloc(sizeof(postfix));
    newEl->number = x;
    newEl->next = NULL;

    newEl->next = head->next;
    head->next = newEl;

    return 0;
}

int popEl(Position head, char operation) {
    Position first = head->next;
    Position second = first->next;

    double result;

    switch (operation) {
        case '+':
            result = second->number + first->number;
            break;
        case '-':
            result = second->number - first->number;
            break;
        case '*':
            result = second->number * first->number;
            break;
        case '/':
            result = second->number / first->number;
            break;
    }

    head->next = second->next;          //brisanje elemenata
    first->next = NULL;
    second->next = NULL;
    free(first);
    free(second);

    pushEl(head, result);

    return 0;
}