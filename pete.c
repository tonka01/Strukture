#include<stdio.h>
#include <string.h>
#include<stdlib.h>

typedef struct lista* Pozicija;
struct lista
{
	int el;
	Pozicija next;
};

void citanje(Pozicija, char *);
void unos(Pozicija);
void ispis(Pozicija);
void unija(Pozicija, Pozicija, Pozicija);
void presjek(Pozicija, Pozicija, Pozicija);

int main()
{
	struct lista a, b, u, p;
	char z;

	a.next = NULL;
	b.next = NULL;
	u.next = NULL;
	p.next = NULL;

	
	
	while (1) {
		printf("Za citanje iz liste unesite 'L', a za unos liste unesite 'U'. Za izlaz iz programa unesite 'K'. \n");
		scanf("%c", &z);
		

		if ((z == 'L') || (z == 'l')) {
			getchar();
			citanje(&a, "PrvaLista.txt");
			printf("Prva lista je: \n");
			ispis(&a);

			citanje(&b, "DrugaLista.txt");
			printf("Druga lista je: \n");
			ispis(&b);

		}

		else if ((z == 'U') || (z == 'u')) {
			printf("Unos u prvu listu.\n");
			unos(&a);
			printf("Prva lista je: \n");
			ispis(&a);

			printf("Unos u drugu listu.\n");
			unos(&b);
			printf("Druga lista je: \n");
			ispis(&b);
			
		}
		else if (z == 'K' || z == 'k') {
			printf("Izlaz iz programa.\n");
			exit(1);
		}
		else {
			printf("Unijeli ste pogresno slovo!");
		}

	printf("Unija je: \n");
	unija(a.next, b.next, &u);
	ispis(&u);

	printf("Presjek je: \n");
	presjek(a.next, b.next, &p);
	ispis(&p);
	}

	return 0;
}


void citanje(Pozicija p, char *imeDat) {
	FILE *dat;
	Pozicija temp, prev, q;

	dat = fopen(imeDat, "r");
	if (dat==NULL)
	{
		printf("Datoteka nije pronadjena!");
		exit(1);
	}
	else
	{
		while (!feof(dat))
		{
			q = (Pozicija)malloc(sizeof(struct lista));

			fscanf(dat, " %d", &q->el);

			temp = p->next;
			prev = p;

			while (temp != NULL && temp->el < q->el)
			{
				prev = temp;
				temp = temp->next;
			}

			prev->next = q;

			if (temp != NULL)
				q->next = temp;
			else
				q->next = NULL;
		}
	}

}

void unos(Pozicija p) {
	int x;
	Pozicija q;
	q = (Pozicija)malloc(sizeof(struct lista));

	printf("Unesite clan kojeg zelite unijeti.\n");
	printf("Molim te unesi od najmanjeg do najveceg. :)\n");
	scanf("%d", &x);
	getchar();

	q->el = x;
	q->next = p->next;
	p->next = q;

}

void ispis(Pozicija p) {

	printf("\n");

	p = p->next;

	while (p != NULL)
	{
		printf("%d\t", p->el);
		p = p->next;
	}

	printf("\n");

}

void unija(Pozicija a, Pozicija b, Pozicija u)
{
	Pozicija q, p;

	while (a && b)
	{
		q = (Pozicija)malloc(sizeof(struct lista));
		u->next = q;
		q->next = NULL;

		if (a->el < b->el)
		{
			q->el = a->el;
			a = a->next;
		}
		else if (b->el < a->el)
		{
			q->el = b->el;
			b = b->next;
		}

		else 
		{
			q->el = a->el;
			a = a->next;
			b = b->next;
		}

		u = u->next;
	}

	if (a)
		p = a;
	else
		p = b;

	while (p)
	{
		q = (Pozicija)malloc(sizeof(struct lista));
		u->next = q;
		q->next = NULL;
		q->el = p->el;
		u = u->next;
		p = p->next;
	}

}


void presjek(Pozicija a, Pozicija b, Pozicija p)
{
	Pozicija q;

	while (a && b)
	{
		if (a->el < b->el)
			a = a->next;
		else if (b->el < a->el)
			b = b->next;
		else
		{
			q = (Pozicija)malloc(sizeof(struct lista));
			p->next = q;
			q->next = NULL;

			q->el = a->el;
			a = a->next;
			b = b->next;

			p= p->next;
		}
	}
}