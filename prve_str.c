#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
	char ime[50];
	char prezime[50];
	int bodovi;
	float relativni;
}student;

int brojiStud(FILE *dat) {
	char c;
	int brst = 0;
	if (dat == NULL) {
		printf("Nije pronadjena datotetka toga naziva.\n");
		return 0;
	}
	while (fgetc(dat) != '\n') {};
	for (c = getc(dat); c != EOF; c = getc(dat)) {
		if (c == '\n')
			brst += 1;
	}
	printf("Upisano je %d studenata.\n", brst);
	return brst;
};

int unosStud(int brSt, student *stud, int max)
{
	FILE *pf;
	int i;
	pf = fopen("studenti.txt", "r");
	while (fgetc(pf) != '\n') {};
	for (i = 0; i < brSt; i++)
	{
		fscanf(pf, "%s %s %d", &stud[i].ime, &stud[i].prezime, &stud[i].bodovi);
		stud[i].relativni = (float)stud[i].bodovi / max * 100;
	}
	fclose(pf);
	return 0;
}

int ispisStud(int n, student *st, int max) {

	int i;
	
	for (i = 0; i < n; i++) {
		printf("%s\t%s\t%d\t%f\n", st[i].ime, st[i].prezime, st[i].bodovi, st[i].relativni);
		
	}

	return 0;
};


int main()
{
	FILE *dat;
	dat = fopen("studenti.txt", "r");
	int uk = 0;
	int max;
	student *st;

	uk = brojiStud(dat);
	st = (student*)malloc(uk * sizeof(student));
	printf("Unesite maksimalan broj bodova.\n");
	scanf("%d", &max);
	unosStud(uk, st, max);
	
	ispisStud(uk, st, max);

	fclose(dat);
	return 0;
}