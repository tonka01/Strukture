#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_DULJINA 256

typedef struct direktorij* Pozicija;
typedef struct stog* stogPozicija;

typedef struct direktorij {
	char ime[MAX_DULJINA];
	Pozicija braca;
	Pozicija dijete;
}Direktorij;
typedef struct stog {
	stogPozicija sada;
	stogPozicija next;
}Stog;

Pozicija novi(char*);
stogPozicija noviStog(Pozicija);
void noviDirektorij(Pozicija, char*);
void ispis(Pozicija);
Pozicija ulaz(Pozicija, stogPozicija, char*);
Pozicija izlaz(stogPozicija);
void trenutni(stogPozicija, Pozicija);
void brisi(Pozicija);

int main() {
	Direktorij root;
	strcpy(root.ime, "C:");
	root.braca = NULL;
	root.dijete = NULL;
	Stog head;
	head.next = NULL;
	Pozicija sadasnji = &root;
	int x = 0;
	char ime[MAX_DULJINA];
	while (1) {
		trenutni(&head, sadasnji);
		printf("Za pravljenje novog direktorija (md) unesi 1.\t Za promjenu direktorija (cd dir) unesi 2.\t Za vracanje na prethodni direktorij (cd..) unesi 3.\t Za ispis pod-direktorija (dir) unesi 4.\t Za izlaz iz programa unesi 5.\t ");
		scanf("%d", &x);
		if (x == 1) {
			printf("\nUnesite ime direktorija: ");
			scanf(" %s", ime);
			noviDirektorij(sadasnji, ime);
		}
		else if (x == 2) {
			printf("\nIzaberite direktorij: ");
			scanf(" %s", ime);
			sadasnji = ulaz(sadasnji, &head, ime);
		}
		else if (x == 3) {
			sadasnji = izlaz(&head);
		}
		else if (x == 4) {
			ispis(sadasnji);
		}
		else if (x == 5) {
			brisi(root.dijete);
			return -1;
		}
		else {
			printf("\n Unesen je krivi broj! Unesi ponovno!\n");
		}
	}
	return 0;
}
Pozicija novi(char *ime) {
	Pozicija p = NULL;
	p = (Pozicija)malloc(sizeof(Direktorij));
	if (p == NULL) {
		printf("\nGreska pri alokaciji memorije\n");
		return NULL;
	}
	strcpy(p->ime, ime);
	p->braca = NULL;
	p->dijete = NULL;
	return p;
}
stogPozicija noviStog(Pozicija sadasnji) {
	stogPozicija p = NULL;
	p = (stogPozicija)malloc(sizeof(Stog));
	if (p == NULL) {
		printf("\nGreska pri alokaciji memorije\n");
		return NULL;
	}
	p->sada = sadasnji;
	p->next = NULL;
	return p;
}
void noviDirektorij(Pozicija sadasnji, char *ime) {
	Pozicija p = NULL;
	Pozicija q = NULL;
	p = novi(ime);
	if (sadasnji->dijete == NULL) {
		sadasnji->dijete = p;
	}
	else if (sadasnji->dijete != NULL) {
		q = sadasnji->dijete;
		while (q->braca != NULL) {
			q = q->braca;
		}
		q->braca = p;
	}
}
void ispis(Pozicija sadasnji) {
	Pozicija p = NULL;
	p = sadasnji->dijete;
	while (p != NULL) {
		printf("\n%s", p->ime);
		p = p->braca;
	}
	printf("\n");
}
Pozicija ulaz(Pozicija sadasnji, stogPozicija head, char *ime) {
	Pozicija p = sadasnji->dijete;
	stogPozicija stogPoz = NULL;
	if (p == NULL) {
		return sadasnji;
	}
	while (p != NULL) {
		if (strcmp(p->ime, ime) == 0) {
			break;
		}
		else {
			p = p->braca;
		}
	}
	if (p != NULL) {
		stogPoz = noviStog(sadasnji);
		stogPoz->next = head->next;
		head->next = stogPoz;
		return p;
	}
	else if (p == NULL) {
		printf("\nDirektorije ne postoji\n");
		return sadasnji;
	}
}
Pozicija izlaz(stogPozicija head) {
	Pozicija p = NULL;
	stogPozicija temp = head->next;
	p = temp->sada;
	head->next = temp->next;
	free(temp);
	return p;
}
void trenutni(stogPozicija head, Pozicija current) {
	stogPozicija p;
	p = head->next;
	int x = 0, i = 0;
	printf("\n");
	if (p != NULL) {
		while (p != NULL) {
			x++;
			p = p->next;
		}
		while (x != 0) {
			p = head;
			for (i = 0; i < x; i++) {
				p = p->next;
			}
			printf("%s/", p->sada->ime);
			x--;
		}
	}
	printf("%s/\n", current->ime);
}
void brisi(Pozicija sadasnji) {
	if (sadasnji == NULL) {
		return;
	}
	brisi(sadasnji->braca);
	brisi(sadasnji->dijete);
	free(sadasnji);
}
