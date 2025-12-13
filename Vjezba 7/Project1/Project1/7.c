#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 64

typedef struct _directory* dirPosition;
typedef struct _directory {
	char name[MAX];
	dirPosition next;
	dirPosition subDirPos;
}directory;

typedef struct _stack* stackPosition;
typedef struct _stack {
	stackPosition next;
	dirPosition dirLevel;
}stack;

int ui(stackPosition headStack);
int printPath(stackPosition headStack);
int md(stackPosition headStack, char* dirName);
int cd(stackPosition headStack, char* dirName);
int cdreturn(stackPosition headStack);
int dir(dirPosition current, int count);
int freeDir(dirPosition rootDir);
int freeStack(stackPosition rootStack);

int main() {
	directory headDir = { .name = "", .next = NULL, .subDirPos = NULL };
	stack headStack = { .dirLevel = NULL, .next = NULL };
	directory rootDir = { .name = "C:", .next = NULL, .subDirPos = NULL };
	stack rootStack = { .dirLevel = NULL, .next = NULL };

	headDir.next = &rootDir;
	headStack.next = &rootStack;
	rootStack.dirLevel = &rootDir;

	ui(&headStack);
	freeDir(&rootDir);
	freeStack(&rootStack);

	return 0;
}

int ui(stackPosition headStack) {
	int i;
	char input[MAX];
	char input1[MAX];
	char input2[MAX];
	char input3[MAX];

	printf("Microsoft Windows [Version 10.0.78525.5893]\n"
		"(c)Microsoft Corporation.All rights reserved.\n\n");
	printPath(headStack->next);
	printf(">");

	while (1) {
		fgets(input, MAX, stdin);

		if (strcmp(input, "\n")) {
			i = sscanf(input, "%s %s %s", input1, input2, input3);

			if (i > 2)
				printf("Syntax error.\n");

			else if (strcmp(input1, "md") == 0) {
				if (i == 2)
					md(headStack, input2);
				else
					printf("The syntax of the command is incorrect.\n");
			}

			else if (strcmp(input1, "cd") == 0) {
				if (strcmp(input2, "..") == 0)
					cdreturn(headStack);
				else if (i == 2)
					cd(headStack, input2);
				else {
					printPath(headStack->next);
					printf("\n");
				}
			}

			else if (strcmp(input1, "cd..") == 0)
				if (i == 1)
					cdreturn(headStack);
				else
					printf("The syntax of the command is incorrect.\n");

			else if (strcmp(input1, "dir") == 0) {
				if (i == 1) {
					printf("\n");
					dir(headStack->next->dirLevel, 0);
				}
				else
					printf("The syntax of the command is incorrect.\n");
			}
			else if (strcmp(input1, "exit") == 0)
				return 0;

			else
				printf("'%s' is not recognized as an internal or external command,\n"
					"operable program or batch file.\n", input1);

			printf("\n");
		}
		printPath(headStack->next);
		printf(">");
	}
}

int printPath(stackPosition temp) {
	if (temp->next == NULL) {
		printf("%s/", temp->dirLevel->name);
		return 0;
	}
	else {
		printPath(temp->next);
		printf("%s/", temp->dirLevel->name);
	}
	
	return 0;
}

int md(stackPosition headStack, char* dirName) {
	dirPosition newDir = malloc(sizeof(directory));
	if (newDir == NULL) {
		printf("Memory allocation error\n");
		return -1;
	}
	strcpy(newDir->name, dirName);
	newDir->subDirPos = NULL;

	dirPosition parentDir = headStack->next->dirLevel;
	newDir->next = parentDir->subDirPos;
	parentDir->subDirPos = newDir;

	return 0;
}

int cd(stackPosition headStack, char* dirName) {
	int found = 1;
	dirPosition temp = headStack->next->dirLevel->subDirPos;
	stackPosition newStack = malloc(sizeof(stack));
	if (newStack == NULL) {
		printf("Memory allocation error\n");
		return -1;
	}

	while (temp != NULL && found) {
		if (strcmp(temp->name, dirName) == 0) {
			newStack->next = headStack->next;
			headStack->next = newStack;
			newStack->dirLevel = temp;
			found = 0;
		}
		temp = temp->next;
	}

	if (found)
		printf("The system cannot find the path specified.\n");

	return 0;
}

int cdreturn(stackPosition headStack) {
	stackPosition temp = headStack->next;
	headStack->next = temp->next;
	temp->next = NULL;
	free(temp);

	return 0;
}

int dir(dirPosition current, int count) {
	int i;
	count++;

	dirPosition currentSubDir = NULL;
	if (current->subDirPos != NULL) {
		currentSubDir = current->subDirPos;
		while (currentSubDir != NULL) {
			for (i = 0;i < count;i++)
				printf("\t");
			printf("<DIR>\t%s\n", currentSubDir->name);
			dir(currentSubDir, count);
			currentSubDir = currentSubDir->next;
			i = 0;
		}
	}
}

int freeDir(dirPosition rootDir) {
	dirPosition temp;

	if (rootDir->subDirPos != NULL) {
		freeDir(rootDir->subDirPos);
		rootDir->subDirPos = NULL;
	}

	while (rootDir->next != NULL) {
		temp = rootDir->next;
		if (temp->subDirPos != NULL)
			freeDir(temp->subDirPos);
		rootDir->next = temp->next;
		free(temp);
	}
	return 0;
}

int freeStack(stackPosition rootStack) {
	stackPosition temp;
	while (rootStack->next != NULL) {
		temp = rootStack->next;
		rootStack->next = temp->next;
		free(temp);
	}

	return 0;
}