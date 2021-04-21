#include <stdlib.h>
#include "Structs.h"


struct b B;
struct slovo *reference[256];

int Len_q(struct node *q) {
	int length = 0;
	struct node *first;
	first = q;
	while (first != NULL) {
		first = first->next;
		length++;
	}
	return length;
}

int Empty_q(struct node *q) {
	return q == NULL;
}

void Insert(struct node **q, struct note p) {
	struct node *new;
	new = malloc(sizeof(struct node));
	new->info = p;
	new->next = NULL;
	if (Empty_q(*q)) {
		*q = new;
	}
	else {
		struct node *current;
		current = *q;
		while (current->next != NULL) {
			current = current->next;
		}
		current->next = new;
	}
}

void Delete(struct node **q) {
	if (!Empty_q(*q)) {
		struct node *temp;
		temp = *q;
		*q = (*q)->next;
		free(temp);
	}
}

int Len_b(struct b *qu) {
	return ((qu->rear < qu->front) ? SECOND : 0) + qu->rear - qu->front;
}

int Empty_b(struct b *qu) {
	return qu->front == qu->rear;
}

int Full_b(struct b *qu) {
	return (qu->rear + 1) % SECOND == qu->front;
}

void Insert_b(struct b *qu, long long int p) {
	if (!Full_b(qu)) {
		qu->notes[qu->rear] = p;
		qu->rear = (qu->rear + 1) % SECOND;
	}
}

long long int Delete_b(struct b *qu) {
	if (!Empty_b(qu)) {
		int temp = qu->front;
		qu->front = (qu->front + 1) % SECOND;
		return qu->notes[temp];
	}
}

void InitReference() {
	for (int j = 0; j < 256; j++) {
		reference[j] = 0;
	}
	reference['0'] = (struct slovo *)malloc(sizeof(struct slovo));
	reference['0']->bitmap = 0xe667;
	reference['1'] = (struct slovo *)malloc(sizeof(struct slovo));
	reference['1']->bitmap = 0x2040;
	reference['2'] = (struct slovo *)malloc(sizeof(struct slovo));
	reference['2']->bitmap = 0xc3c3;
	reference['3'] = (struct slovo *)malloc(sizeof(struct slovo));
	reference['3']->bitmap = 0xe1c3;
	reference['4'] = (struct slovo *)malloc(sizeof(struct slovo));
	reference['4']->bitmap = 0x21c4;
	reference['5'] = (struct slovo *)malloc(sizeof(struct slovo));
	reference['5']->bitmap = 0xd087;
	reference['6'] = (struct slovo *)malloc(sizeof(struct slovo));
	reference['6']->bitmap = 0xe387;
	reference['7'] = (struct slovo *)malloc(sizeof(struct slovo));
	reference['7']->bitmap = 0x2043;
	reference['8'] = (struct slovo *)malloc(sizeof(struct slovo));
	reference['8']->bitmap = 0xe3c7;
	reference['9'] = (struct slovo *)malloc(sizeof(struct slovo));
	reference['9']->bitmap = 0xe1c7;
	reference['A'] = (struct slovo *)malloc(sizeof(struct slovo));
	reference['A']->bitmap = 0x23c7;
	reference['B'] = (struct slovo *)malloc(sizeof(struct slovo));
	reference['B']->bitmap = 0xe953;
	reference['C'] = (struct slovo *)malloc(sizeof(struct slovo));
	reference['C']->bitmap = 0xc207;
	reference['D'] = (struct slovo *)malloc(sizeof(struct slovo));
	reference['D']->bitmap = 0xe853;
	reference['E'] = (struct slovo *)malloc(sizeof(struct slovo));
	reference['E']->bitmap = 0xc387;
	reference['F'] = (struct slovo *)malloc(sizeof(struct slovo));
	reference['F']->bitmap = 0x0387;
	reference['G'] = (struct slovo *)malloc(sizeof(struct slovo));
	reference['G']->bitmap = 0xe307;
	reference['H'] = (struct slovo *)malloc(sizeof(struct slovo));
	reference['H']->bitmap = 0x23c4;
	reference['I'] = (struct slovo *)malloc(sizeof(struct slovo));
	reference['I']->bitmap = 0xc813;
	reference['J'] = (struct slovo *)malloc(sizeof(struct slovo));
	reference['J']->bitmap = 0xe240;
	reference['K'] = (struct slovo *)malloc(sizeof(struct slovo));
	reference['K']->bitmap = 0x12a4;
	reference['L'] = (struct slovo *)malloc(sizeof(struct slovo));
	reference['L']->bitmap = 0xc204;
	reference['M'] = (struct slovo *)malloc(sizeof(struct slovo));
	reference['M']->bitmap = 0x226c;
	reference['N'] = (struct slovo *)malloc(sizeof(struct slovo));
	reference['N']->bitmap = 0x324c;
	reference['O'] = (struct slovo *)malloc(sizeof(struct slovo));
	reference['O']->bitmap = 0xe247;
	reference['P'] = (struct slovo *)malloc(sizeof(struct slovo));
	reference['P']->bitmap = 0x03c7;
	reference['Q'] = (struct slovo *)malloc(sizeof(struct slovo));
	reference['Q']->bitmap = 0xf247;
	reference['R'] = (struct slovo *)malloc(sizeof(struct slovo));
	reference['R']->bitmap = 0x13c7;
	reference['S'] = (struct slovo *)malloc(sizeof(struct slovo));
	reference['S']->bitmap = 0xe187;
	reference['T'] = (struct slovo *)malloc(sizeof(struct slovo));
	reference['T']->bitmap = 0x0813;
	reference['U'] = (struct slovo *)malloc(sizeof(struct slovo));
	reference['U']->bitmap = 0xe244;
	reference['V'] = (struct slovo *)malloc(sizeof(struct slovo));
	reference['V']->bitmap = 0x0624;
	reference['W'] = (struct slovo *)malloc(sizeof(struct slovo));
	reference['W']->bitmap = 0x3644;
	reference['X'] = (struct slovo *)malloc(sizeof(struct slovo));
	reference['X']->bitmap = 0x1428;
	reference['Y'] = (struct slovo *)malloc(sizeof(struct slovo));
	reference['Y']->bitmap = 0x0828;
	reference['Z'] = (struct slovo *)malloc(sizeof(struct slovo));
	reference['Z']->bitmap = 0xc423;
	reference[' '] = (struct slovo *)malloc(sizeof(struct slovo));
	reference[' ']->bitmap = 0x0000;
	reference['-'] = (struct slovo *)malloc(sizeof(struct slovo));
	reference['-']->bitmap = 0x0180;

}