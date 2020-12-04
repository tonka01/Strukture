//stog
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct broj* stog;
struct broj {
	int el;
	stog next;
};

void push(int, stog);
int pop(stog);
void ispis(stog);

int main() {

	struct broj head;
	head.next = NULL;
	srand(time(NULL));
	char c;

	while (1) {

		printf("Za unos u stog unesi 'U'. Za vadjenje broja sa stoga unesi 'V'. Za kraj programa unesi 'K'.\n");
		scanf("%c", &c);
		getchar();

		if (c == 'U' || c == 'u') {
			push(rand() % (100 - 10 + 1) + 10, &head);
			ispis(&head);
		}

		else if (c == 'V' || c == 'v') {
			pop(&head);
			printf("Novi stog:");
			ispis(&head);
		}

		else if (c == 'K' || c == 'k') {
			printf("Izlaz iz programa!\n");
			exit(1);
		}
		else
			printf("Unijeli ste krivo slovo.\n");

	}

	return 0;
}

void ispis(stog s) {

	s = s->next;

	if (s == NULL) {
		printf("Prazan stog!\n");
	}

	while (s != NULL) {
		printf("%d\t", s->el);
		s = s->next;
	}
	printf("\n");
}

void push(int x, stog s) {
	stog q;
	q = (stog)malloc(sizeof(struct broj));
	q->el = x;
	q->next = s->next;
	s->next = q;
}

int pop(stog s) {
	int x = -1;
	stog temp;
	if (s->next != NULL) {
		x = s->next->el;
		temp = s->next;
		s->next = temp->next;
		printf("Brisem %d\n", x);
		free(temp);
	}
	return x;
}