//P.S. zadatak je dodan ranije, ali pod master, a ne u main. Možete pogledati.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct broj * Pozicija;

struct broj
{
	int koef;
	int eksp;
	Pozicija next;
};


void citanje(Pozicija, char *);
void ispis(Pozicija);
void zbrajanje(Pozicija, Pozicija, Pozicija);
void mnozenje(Pozicija, Pozicija, Pozicija);


int main()
{
	Pozicija prvi, drugi, zbroj, umnozak;
	prvi = (Pozicija)malloc(sizeof(struct broj));
	drugi = (Pozicija)malloc(sizeof(struct broj));
	zbroj = (Pozicija)malloc(sizeof(struct broj));
	umnozak = (Pozicija)malloc(sizeof(struct broj));
	prvi->next = NULL;
	drugi->next = NULL;
	zbroj->next = NULL;
	umnozak->next = NULL;
	citanje(prvi, "prviPolinomi.txt");
	ispis(prvi);

	citanje(drugi, "drugiPolinomi.txt");
	ispis(drugi);


	zbrajanje(prvi, drugi, zbroj);
	printf("\n Zbroj je:");
	ispis(zbroj);

	mnozenje(prvi, drugi, umnozak);
	printf("\n Umnozak je:");
	ispis(umnozak);

	printf("\n");

	return 0;
}


void citanje(Pozicija p, char *imeDat)
{
	FILE *dat;
	Pozicija q, temp, prije;

	dat = fopen(imeDat, "r");
	if (dat==NULL)
	{
		printf("Greska!");
		exit(-1);
	}
	else
	{
		while (1)
		{
			q = (Pozicija)malloc(sizeof(struct broj));

			fscanf(dat, "%d %d", &q->koef, &q->eksp);

			temp = p->next;
			prije = p;
			while (temp != NULL && temp->eksp > q->eksp)
			{
				prije = temp;
				temp = temp->next;
			}

			prije->next = q;

			if (temp != NULL)
				q->next = temp;
			else
				q->next = NULL;

			if (feof(dat))
				break;
		}
	}


}

void ispis(Pozicija p)
{
	p = p->next;

	printf("\n");
	while (p != NULL)
	{
		printf("%d*x^%d ", p->koef, p->eksp);
		p = p->next;

	}
}

void zbrajanje(Pozicija prvi, Pozicija drugi, Pozicija zbroj)
{
	Pozicija q, temp;

	while (prvi != NULL && drugi != NULL)
	{
		q = (Pozicija)malloc(sizeof(struct broj));
		q->next = NULL;


		if (prvi->eksp < drugi->eksp)
		{
			q->eksp = drugi->eksp;
			q->koef = drugi->koef;
			drugi = drugi->next;
		}
		
		else if (prvi->eksp > drugi->eksp)
		{
			q->eksp = prvi->eksp;
			q->koef = prvi->koef;
			prvi = prvi->next;
		}
		else 
		{
			q->eksp = prvi->eksp;
			q->koef = prvi->koef + drugi->koef;
			prvi = prvi->next;
			drugi = drugi->next;
		}
		zbroj->next = q;
		zbroj = q;
	}

	if (prvi != NULL)
		temp = prvi;
	else
		temp = drugi;

	while (temp != NULL)
	{
		q = (Pozicija)malloc(sizeof(struct broj));
		q->next = NULL;
		q->eksp = temp->eksp;
		q->koef = temp->koef;
		zbroj->next = q;
		zbroj = q;
		temp = temp->next;
	}

}


void mnozenje(Pozicija prvi, Pozicija drugi, Pozicija umnozak)
{
	Pozicija q, p1, p2, temp, prev;
	p1 = prvi;
	p2 = drugi;
	int n;

	while (p1 != NULL)
	{
		p2 = drugi;
		while (p2 != NULL)
		{
			temp = umnozak->next;
			prev = umnozak;

			n = p1->eksp + p2->eksp;

			while (temp != NULL && temp->eksp > n)
			{
				prev = temp;
				temp = temp->next;
			}

			if (temp != NULL && temp->eksp == n)
				temp->koef += p1->koef * p2->koef;
			else
			{
				q = (Pozicija)malloc(sizeof(struct broj));

				q->eksp = n;
				q->koef = p1->koef* p2->koef;

				prev->next = q;
				q->next = temp;
			}

			p2 = p2->next;
		}
		p1 = p1->next;
	}

	while (umnozak->next != NULL)
	{
		if (umnozak->next->koef == 0)
		{
			temp = umnozak->next;
			umnozak->next = umnozak->next->next;
			free(temp);
		}
		umnozak = umnozak->next;
	}

}
