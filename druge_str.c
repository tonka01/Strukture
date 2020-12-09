#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Osoba* Pozicija;
struct Osoba {
	char strIme[100];
	char strPrezime[100];
	int strGodina;
	Pozicija sljed;
};

void ispis(Pozicija p);
Pozicija novi(char*, char*, int);
void unosP(Pozicija, Pozicija);
void unosK(Pozicija, Pozicija);
Pozicija trazi(Pozicija, char*);
Pozicija traziPrije(Pozicija, char*);
void obrisi(Pozicija, char*);


int main()
{
	struct Osoba head;
	head.next=NULL;
	Pozicija l, t;
	char c;
	char ime[100], prezime[100], traziPrezime[100], brisiPrezime[100];
	int god;

	while (1) {
		printf("Unesi slovo 'p' za upis na pocetak liste.\n Unesi slovo 'k' za upis na kraj liste.\n Unesi slovo 't' za trazenje u listi.\n Unesi slovo 'o' za brisanje iz liste.\n Za izlaz iz programa unesi 'e'.\n");
		scanf("%c", &c);
		if ((c == 'p') || (c == 'P')) {
			
			printf("Unesite ime.\n");
			scanf("%s", ime);
			printf("Unesite prezime.\n");
			scanf("%s", prezime);
			printf("Unesite godinu rodjenja.\n");
			scanf("%d", &god);
			getchar();
			l = novi(ime, prezime, god);
			unosP(&head, l);
			ispis(&head);
		}
		else if ((c == 'k') || (c == 'K')) {
			printf("Unesite ime.\n");
			scanf("%s", ime);
			printf("Unesite prezime.\n");
			scanf("%s", prezime);
			printf("Unesite godinu rodjenja.\n");
			scanf("%d", &god);
			getchar();
			l = novi(ime, prezime, god);
			unosK(&head,l);
			ispis(&head);
		}
		else if ((c == 't') || (c == 'T')) {
			printf("Unesite prezime koje zelite pronaci.\n");
			scanf("%s", traziPrezime);
			getchar();

			t = trazi(&head, traziPrezime);
			printf("%s %s %d\n", t->strIme, t->strPrezime, t->strGodina);
		}

		else if ((c == 'o') || (c == 'O')) {

			printf("Unesite prezime koje zelite izbrisati.\n");
			scanf("%s", brisiPrezime);
			getchar();

			obrisi(&head, brisiPrezime);
			ispis(&head);

		}

		else if ((c == 'e') || (c == 'E')) {
			printf("Izlaz iz programa.\n");
		}
		else
		{
			printf("Unijeli ste pogresno slovo.\n");
			return 0;
		}
	}

	return 0;
}

void ispis(Pozicija p) {
	while (p != NULL) {
		printf("%s %s %d\n", p->strIme, p->strPrezime, p->strGodina);
		p = p->sljed;
	}
}

Pozicija novi(char* ime, char* prezime, int godina) {
	Pozicija p;
		p = (Pozicija)malloc(sizeof(struct Osoba));

		strcpy(p->strIme, ime);
		strcpy(p->strPrezime, prezime);
		p->strGodina = godina;
		p->sljed = NULL;

		return p;
}

void unosP(Pozicija head, Pozicija p) {

	p->sljed = head->sljed;
	head->sljed = p;
}

void unosK(Pozicija q, Pozicija p) {
	while (q->sljed != NULL) {
		q = q->sljed;
	}
	unosP(q, p);
}

Pozicija trazi(Pozicija q, char* prezime) {
	while (q->sljed != NULL && strcmp(q->strPrezime, prezime))
	q = q->sljed;
	return q;
}

Pozicija traziPrije(Pozicija p, char* prezime) {
	Pozicija prije;
	prije = p;
	p = p->sljed;

	while (p->sljed != NULL && strcmp(p->strPrezime, prezime)) {
		prije = p;
		p = p->sljed;
	}

	return prije;
}

void obrisi(Pozicija p, char* prezime) {
	Pozicija prije;
	prije = traziPrije(p, prezime);

	if (prije != NULL) {
		p = prije->sljed;
		prije->sljed = p->sljed;
		free(p);
	}
}
