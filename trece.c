/*pitati za ispis*/
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
void unosIza(Pozicija);
void unosIspred(Pozicija);
void sortiranje(Pozicija);
void unosDat(Pozicija);
void ispisDat(Pozicija);

int main()
{
	struct Osoba head;
	head.sljed= NULL;
	Pozicija l, t;
	char c;
	char ime[100], prezime[100], traziPrezime[100], brisiPrezime[100], novoPrezime[100];
	int god;

	while (1) {
		printf("Unesi 1 za upis na pocetak liste.\n Unesi  2 za upis na kraj liste.\n Unesi 3 za trazenje u listi.\n Unesi slovo 4 za brisanje iz liste.\n Unesi 5 za unos iza odredjenog studenta. \n Unesi 6 za unos ispred odredjenog studenta.\n Unesi 7 za sortiranje studenata!\n Unesi 8 za unos u datoteku.\n Unesi 9 za ispis iz datoteke.\n Za izlaz iz programa unesi 0.\n");
		scanf("%c", &c);
		getchar();
		if (c == '1') {

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
		else if (c == '2') {
			printf("Unesite ime.\n");
			scanf("%s", ime);
			printf("Unesite prezime.\n");
			scanf("%s", prezime);
			printf("Unesite godinu rodjenja.\n");
			scanf("%d", &god);
			getchar();
			l = novi(ime, prezime, god);
			unosK(&head, l);
			ispis(&head);
		}
		else if (c == '3') {
			printf("Unesite prezime koje zelite pronaci.\n");
			scanf("%s", traziPrezime);
			getchar();

			t = trazi(&head, traziPrezime);
			printf("%s %s %d\n", t->strIme, t->strPrezime, t->strGodina);
		}

		else if (c == '4') {

			printf("Unesite prezime koje zelite izbrisati.\n");
			scanf("%s", brisiPrezime);
			getchar();

			obrisi(&head, brisiPrezime);
			ispis(&head);

		}

		else if (c == '5') {
			printf("Unesite prezime iza kojega zelite unijeti novoga studenta.\n");
			scanf("%s", novoPrezime);
			getchar();
			t = trazi(&head, novoPrezime);
			unosIza(t);
			ispis(&head);
		}

		else if (c == '6') {
			printf("Unesite prezime iza kojega zelite unijeti novoga studenta.\n");
			scanf("%s", novoPrezime);
			getchar();
			t = traziPrije(&head, novoPrezime);
			unosIspred(t);
			ispis(&head);
		}

		else if (c == '7') {
			sortiranje(&head);
			ispis(head.sljed);
		}

		else if (c == '8') {
			unosDat(&head);
		}

		else if (c == '9') {
			ispisDat(&head);
		}

		else if (c == '0') {
			printf("Izlaz iz programa.\n");
			exit(1);
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

void unosIza(Pozicija p) {
	Pozicija q;
	q = (Pozicija)malloc(sizeof(struct Osoba));
	
	printf("Unesite novoga studenta!\n");
	printf("Unesite ime.\n");
	scanf("%s", q->strIme);
	printf("Unesite prezime.\n");
	scanf("%s", q->strPrezime);
	printf("Unesite godinu rodjenja.\n");
	scanf("%d", &q->strGodina);
	getchar();
	q->sljed = p->sljed;
	p->sljed = q;
}

void unosIspred(Pozicija p) {
	Pozicija q;
	q = (Pozicija)malloc(sizeof(struct Osoba));

	printf("Unesite novoga studenta!\n");
	printf("Unesite ime.\n");
	scanf("%s", q->strIme);
	printf("Unesite prezime.\n");
	scanf("%s", q->strPrezime);
	printf("Unesite godinu rodjenja.\n");
	scanf("%d", &q->strGodina);
	getchar();
	q->sljed = p->sljed;
	p->sljed = q;
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

void sortiranje(Pozicija p) {
	Pozicija q;
	Pozicija temp;
	Pozicija kraj;
	Pozicija pom;
	kraj = NULL;
	int usp;

	while (p->sljed != NULL) {
		q = p;
		temp = p->sljed;

		while (temp->sljed != NULL) {
			usp = strcmp(temp->strPrezime, temp->sljed->strPrezime);

			if (usp > 0) {
				pom = temp->sljed;
				q->sljed = pom;
				temp->sljed = pom->sljed;
				pom->sljed = temp;
				temp = pom;

			}

			q = temp;
			temp = temp->sljed;
		}

		kraj = temp;
	}
}



void unosDat(Pozicija p) {
	
	FILE *dat;
	dat = fopen("Studenti.txt", "w");

	if (dat==NULL) {
		printf("Greska! Datoteka nije pronadjena.\n");
	}

	else {
		while (p != NULL) {
			fprintf(dat, "%s\t%s\t%d\n", p->strIme, p->strPrezime, p->strGodina);
			p = p->sljed;
		}
	}

	fclose(dat);

}

void ispisDat(Pozicija p) {
	FILE *dat;
	dat = fopen("Studenti.txt", "r");
	Pozicija q;


	if (dat == NULL) {
		printf("Greska! Datoteka nije pronadjena.\n");
	}

	else {
		while (feof(dat) == 0) {
			q = (Pozicija)malloc(sizeof(struct Osoba));
			fscanf(dat, "%s %s %d", q->strIme, q->strPrezime, &q->strGodina);
			printf("%s\t%s\t%d\n", q->strIme, q->strPrezime, q->strGodina);
			q->sljed = p->sljed;
			p->sljed = q;
			p = q;
		}
	}
	fclose(dat);
}
