#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int lpsFinder(char *subpattern) {
	int len = strlen(subpattern);
	char *pre = (char*)malloc(sizeof(char)*(len + 1));
	char *suf = (char*)malloc(sizeof(char)*(len + 1));
	int b = 0;
	int e = len - 1;

	if (len == 1) {
		return 0;
	}
	for (b; b < len - 1; b++) {
		char placeholder;
		char *p;
		placeholder = subpattern[e];
		subpattern[e] = 0;
		strcpy(pre, subpattern);
		subpattern[e] = placeholder;
		p = &subpattern[b + 1];
		strcpy(suf, p);
		if (strcmp(pre, suf) == 0) {
			return e;
		}
		else {
			e = e - 1;
		}
	}
	return 0;
}

int main()
{
	char *text;
	char *pattern;
	int* lps;
	int tSize = 0;
	int pSize = 0;
	char input;
	int i = 0;
	int j = 0;
	char *locations[10];
	int pats = 0;

	//Get text&pattern
	printf("What is the length of the text: ");
	while ((input = getchar()) != '\n') {
		tSize = tSize * 10 + (input - '0');
	}
	text = (char*)malloc(sizeof(char)*(tSize+1));
	printf("Please input the text: ");
	while ((input = getchar()) != '\n') {
		text[i] = input;
		i++;
	}
	text[i] = 0;

	printf("What is the length of the pattern: ");
	while((input = getchar()) != '\n') {
		pSize = pSize * 10 + (input - '0');
	}
	pattern = (char*)malloc(sizeof(char)*(pSize + 1));
	printf("Please input the pattern: ");
	i = 0;
	while ((input = getchar()) != '\n') {
		pattern[i] = input;
		i++;
	}
	pattern[i] = 0;

	//Create LPS array
	lps = (int*)malloc(sizeof(int)*pSize);
	for (i = 0; i < pSize; i++) {
		char placeholder;
		placeholder = pattern[i + 1];
		pattern[i + 1] = 0;
		lps[i] = lpsFinder(pattern);
		pattern[i + 1] = placeholder;
	}

	//String Search
	i = 0;
	while (i < tSize) {
		if (pattern[j] == text[i]) {//Match
			i++, j++;
			if (j == pSize) {//Full match
				printf("Pattern found\n");
				locations[pats] = &text[i - (pSize)];
				pats++;
				j = lps[j - 1];
			}
		}
		else {//No match
			if (j == 0) {
				i++;
			}
			else {
				j = lps[j - 1];
			}
		}
	}

	//Verification
	for (i = 0; i < pats; i++) {
		char *p = locations[i];
		for (j = 0; j < pSize; j++) {
			printf("%c", p[j]);
		}
		printf("\n");
	}
}

