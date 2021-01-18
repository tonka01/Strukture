#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define VELICINA (11)
#define VEL_DAT (1024)

struct _stablo;
typedef struct _stablo *StabloPozicija;
typedef struct _stablo {
	char data[VELICINA];
	StabloPozicija lijevo;
	StabloPozicija desno;
}Stablo;

struct _lista;
typedef struct _lista *ListaPozicija;
typedef struct _lista {
	StabloPozicija stablo;
	ListaPozicija next;
}Lista;

StabloPozicija stvori(char *);
int pushFront(ListaPozicija, StabloPozicija);
int pushBack(ListaPozicija, StabloPozicija);
StabloPozicija popFront(ListaPozicija);
int jeLiBroj(char*);
StabloPozicija citanjeIzDatoteke(char*);
void ispisInOrder(ListaPozicija, StabloPozicija);

int main(void) {
	StabloPozicija cvor = NULL;
	ListaPozicija p = NULL;
	char imeDat[VEL_DAT] = { 0 };
	FILE* novaDat;
	novaDat = fopen("noviupis.txt", "w");
	Lista head;
	head.next = NULL;

	printf("Unesite ime datoteke!\n");
	scanf("%s", imeDat);

	cvor = citanjeIzDatoteke(imeDat);
	if (NULL == cvor) {
		return EXIT_FAILURE;
	}

	ispisInOrder(&head, cvor);

	for (p = head.next; p != NULL; p = p->next) {
		fprintf(novaDat, "%s", p->stablo->data);
	}
	fclose(novaDat);

	return EXIT_SUCCESS;
}

StabloPozicija stvori(char *data) {
	StabloPozicija cvor = NULL;
	cvor = (StabloPozicija)malloc(sizeof(Stablo));

	if (NULL == cvor) {
		printf("Pogresna alokacija memorije!\r\n");
		return NULL;
	}

	strcpy(cvor->data, data);
	cvor->lijevo = NULL;
	cvor->desno = NULL;

	return cvor;
}

int pushFront(ListaPozicija head, StabloPozicija cvorStablo) {
	ListaPozicija cvorLista = malloc(sizeof(Lista));

	if (NULL == cvorLista) {
		printf("Pogresna alokacija memorije!\r\n");
		return -1;
	}

	cvorLista->stablo = cvorStablo;
	cvorLista->next = head->next;
	head->next = cvorLista;

	return 0;
}

int pushBack(ListaPozicija head, StabloPozicija cvorStablo) {
	ListaPozicija p = head;//pitati

	while (p->next != NULL) p = p->next;//dolazak do kraja

	return pushFront(p, cvorStablo);
}

StabloPozicija popFront(ListaPozicija head) {
	ListaPozicija prvi = head->next;
	StabloPozicija temp = NULL;

	if (NULL == prvi) return NULL;

	head->next = prvi->next;
	temp = prvi->stablo;
	free(prvi);

	return temp;
}

int jeLiBroj(char *data) {

	int br = 0;

	if (sscanf(data, "%d", &br) == 1) return 1;

	return 0;
}

StabloPozicija citanjeIzDatoteke(char* imeDat) {

	FILE *dat=NULL;
	Lista head;
	StabloPozicija temp=NULL;
	char data[VELICINA] = { 0 };
	head.next = NULL;
	dat = fopen(imeDat, "r");

	if (NULL == dat) {
		printf("Datoteka %s ne postoji ili nemas ovlastenja.\r\n", imeDat);
		return NULL;
	}

	while (!feof(dat)) {
		StabloPozicija cvor = NULL;
		fscanf(dat, "%s", data);
		cvor = stvori(data);

		if (NULL==cvor) {
			fclose(dat);
			return NULL;
		}

		if (jeLiBroj(cvor->data)) {
			pushFront(&head, cvor);
		}

		else {
			cvor->desno = popFront(&head);

			if (NULL == cvor->desno) {
				printf("Nevaljan upis postfixa u datoteci %s!\r\n", imeDat);
			}

			cvor->lijevo = popFront(&head);

			 if (NULL == cvor->lijevo) {
				printf("Nevaljan upis postfixa u datoteci %s!\r\n", imeDat);
			}
			pushFront(&head, cvor);
		}
	}

	temp = popFront(&head);

	if (NULL == temp) {
		printf("Nevaljan upis postfixa u datoteci %s!\r\n", imeDat);
		return NULL;
	}

	if (popFront(&head) != NULL) {
		printf("Nevaljan upis postfixa u datoteci %s!\r\n", imeDat);
		return NULL;
	}

	return temp;

}

void ispisInOrder(ListaPozicija head, StabloPozicija trenutni) {
	if (NULL == trenutni) return;

	ispisInOrder(head, trenutni->lijevo);
	pushBack(head, trenutni);
	ispisInOrder(head, trenutni->desno);
}
