#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stog* pozicija;

struct stog {
	int el;
	char sl;
	pozicija next;
};

void push(int, pozicija);
int pop(pozicija);
void ispis(pozicija);
int citanje(pozicija);
void racunanje(char*, pozicija);

int main() {

	struct stog head;
	head.next = NULL;

	citanje(&head);
	printf("Rezultat je:");
	ispis(&head);

	return 0;
}

int citanje(pozicija p) {
	
	char* str=NULL;

	str = (char*)malloc(1000*sizeof(char));

	if (str == NULL) {
		printf("Neuspjesna alokacija memorije!\n");
		return -1;
	}

	FILE *dat;
	dat = fopen("postfix.txt", "r");

	if (dat == NULL) {
		printf("Greska! Datoteka ne postoji!\n");
		return -1;
	}
	else {
		printf("Datoteka je pronadjena!\n\n");

		fgets(str, 1000, dat);
		racunanje(str, p);
	}
	fclose(dat);
	return 0;
}

void push(int x, pozicija p) {
	pozicija q;
	q = (pozicija)malloc(sizeof(struct stog));

	q->el = x;
	q->next = p->next;
	p->next = q;
}

int pop(pozicija p) {
	int x = -1;
	pozicija temp;

	if (p->next != NULL) {
		x = p->next->el;
		temp = p->next;
		p->next = temp->next;
		//printf("Vracam: %d\n", x);
		free(temp);
	}

	return x;

}

void ispis(pozicija p) {
	p = p->next;

	if (p == NULL) {
		printf("Prazan stog!\n");
	}

	else {
		while (p != NULL) {
			printf("%d\t", p->el);
			p = p->next;
		}
		printf("\n");
	}
}

void racunanje(char* str, pozicija p) {
	int br, n, prvi, drugi, rezultat;
	char c;

	while (*str != '\0') {

		if (sscanf(str, "%d %n", &br, &n) > 0) {
			str += n;
			push(br, p);
		}

		else {
			sscanf(str, "%c %n", &c, &n);
			str += n;
			drugi = pop(p);
			prvi = pop(p);

			if (c == '+') {
				rezultat = drugi + prvi;
				push(rezultat, p);
			}

			else if (c == '-') {
				rezultat = drugi - prvi;
				push(rezultat, p);
			}

			else if (c == '*') {
				rezultat = drugi * prvi;
				push(rezultat, p);
			}

			else if (c == '/') {
				rezultat = drugi / prvi;
				push(rezultat, p);
			}
		}
		
	}

}
