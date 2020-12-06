//red
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct broj* red;
struct broj {
	int el;
	red next;
};

void push(int, red);
void pop(red);
void ispis(red);

int main() {

	struct broj head;
	//struct broj last;
	head.next = NULL;
	//last.next = NULL;
	srand(time(NULL));
	char c;

	while (1) {

		printf("Za unos u red unesi 'U'. Za vadjenje broja iz reda unesi 'V'. Za kraj programa unesi 'K'.\n");
		scanf("%c", &c);
		getchar();

		if (c == 'U' || c == 'u') {
			push(rand() % (100 - 10 + 1) + 10, &head);
			ispis(&head);
		}

		else if (c == 'V' || c == 'v') {
			pop(&head);
			printf("Novi red:");
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

void ispis(red r) {

	r = r->next;

	if (r == NULL) {
		printf("Prazan stog!\n");
	}

	while (r != NULL) {
		printf("%d\t", r->el);
		r = r->next;
	}
	printf("\n");
}

void push(int x, red r) {
	red temp;
	static red last=NULL;

	if (r->next == NULL) {
		last = r;
	}
	temp = (red)malloc(sizeof(struct broj));
	temp->el = x;
	temp->next = NULL;
	last->next = temp;
	last = temp;
}

void pop( red r) {
	red temp;
	int x = -1;
	
	if (r->next == NULL )
		printf("Red je prazan!\n");

	else {
		x = r->next->el;
		temp = r->next;
		r->next = temp->next;
		printf("Brisem:\t %d\n", x);
		free(temp);
	}
}