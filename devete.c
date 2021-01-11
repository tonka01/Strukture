#include <stdio.h>
#include <stdlib.h>

struct _cvorStabla;
typedef struct _cvorStabla *Stablo;
typedef struct _cvorStabla {
	int br;
	Stablo lijevo;
	Stablo desno;
} Cvor;

Stablo unos(Stablo, Stablo);
Stablo trazi(Stablo, int);
void ispisInOrder(Stablo);
Stablo brisi(Stablo, int);
Stablo traziMax(Stablo);
Stablo traziMin(Stablo);


int main(void) {

	Stablo root = NULL;
	Stablo temp = NULL;
	Stablo tmp;

	int x, d;

	while (1) {
		printf("Za unos novog broja u stablu unesite 1.\t Za trazenje elementa u stablu unesite 2.\t Za brisanje elementa iz stabla unesite 3.\t Za ispis stabla unesite 4.\t Izlaz iz programa - 0.\n");
		scanf("%d", &x);
		if (x == 1) {
			printf("Unesite broj kojeg zelite unijeti u stablo!\t");
			scanf("%d", &d);
			temp = (Stablo)malloc(sizeof(Cvor));
			temp->br = d;
			temp->lijevo = NULL;
			temp->desno = NULL;
			root = unos(root, temp);
			ispisInOrder(root);

		}

		else  if (x == 2) {
			printf("Unesite broj koji zelite pronaci!\t");
			scanf("%d", &d);
			tmp = trazi(root, d);
			if (tmp != NULL)
				printf("Broj %d je pronadjen!\n", tmp->br);
			else
				printf("Uneseni broj nije pronadjen.");
		}
		else if (x == 3) {
			printf("Unesite broj koji zelize izbrisati!\t");
			scanf("%d", &d);
			root = brisi(root, d);
		}
		else if (x == 4) {
			ispisInOrder(root);
		}

		else if (x == 0) {
			printf("Izlaz!\n");
			return 1;
		}
		else {
			printf("Unijeli ste pogresan znak!");
		}
	}

	return EXIT_SUCCESS;
}

Stablo unos(Stablo trenutni, Stablo el) {

	if (NULL == trenutni)
	{
		trenutni = el;
		return el;
	}

	if (trenutni->br > el->br) {
		trenutni->lijevo = unos(trenutni->lijevo, el);
	}
	else if (trenutni->br < el->br) {
		trenutni->desno = unos(trenutni->desno, el);
	}
	else {
		free(el);
		return trenutni;
	}

	return trenutni;
}
Stablo trazi(Stablo trenutni, int broj) {
	if (NULL == trenutni)
		return NULL;

	if (trenutni->br > broj) {
		return trazi(trenutni->lijevo, broj);
	}
	else if (trenutni->br < broj) {
		return trazi(trenutni->desno, broj);
	}
	else {
		return trenutni;
	}
}

void ispisInOrder(Stablo trenutni) {
	if (NULL == trenutni)
		return;

	ispisInOrder(trenutni->lijevo);
	printf("%d\t", trenutni->br);
	ispisInOrder(trenutni->desno);

}

Stablo brisi(Stablo trenutni, int broj) {
	if (NULL == trenutni)
		return NULL; //NULL ili trenutni, isto nam je

	if (trenutni->br == broj) {

		if (trenutni->lijevo != NULL) {
			Stablo temp = traziMax(trenutni->lijevo);
			trenutni->br = temp->br;
			trenutni->lijevo = brisi(trenutni->lijevo, temp->br);
		}
		else if (trenutni->desno != NULL) {
			Stablo temp = traziMin(trenutni->desno);
			trenutni->br = temp->br;
			trenutni->desno = brisi(trenutni->desno, temp->br);
		}
		else {
			free(trenutni);
			return NULL;
		}

	}
	else if (trenutni->br > broj) {
		trenutni->lijevo = brisi(trenutni->lijevo, broj);
	}
	else {
		trenutni->desno = brisi(trenutni->desno, broj);
	}

	return trenutni;
}

Stablo traziMax(Stablo trenutni) {
	if (NULL == trenutni)
		return NULL;

	while (trenutni->desno != NULL)
		trenutni = trenutni->desno;

	return trenutni;
}

Stablo traziMin(Stablo trenutni) {
	if (NULL == trenutni)
		return NULL;

	while (trenutni->lijevo != NULL)
		trenutni = trenutni->lijevo;

	return trenutni;
}
