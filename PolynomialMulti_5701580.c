#include <stdio.h>
#include <stdlib.h>

#define MAX_TERMS 101
struct term {
	float coef;
	int expon;
}terms[MAX_TERMS] = {
	{4.0, 3}, {3.0, 2}, {2.0, 1}, {1.0, 0},
	{3.0, 2}, {2.0, 1}, {8.0, 0}
};
int avail = 7;

void attach(float coef, int expon) {
	if (avail >= MAX_TERMS) {
		fprintf(stderr, "항의 개수가 너무 많음\n");
		exit(1);
	}
	terms[avail].coef = coef;
	terms[avail].expon = expon;
	avail++;
}

void print_poly(int s, int e) {
	for (int i = s; i < e; i++)
		printf("%3.1fx^%d + ", terms[i].coef, terms[i].expon);
	printf("%3.1fx^%d + \n", terms[e].coef, terms[e].expon);
}

void poly_multiply(int As, int Ae, int Bs, int Be, int* Cs, int* Ce) {
	float tempCoef;
	int tempExpon;
	int i, j;
	*Cs = avail;
	for (i = As; i <= Ae; i++) {
		for (j = Bs; j <= Be; j++) {
			tempCoef = terms[i].coef * terms[j].coef;
			tempExpon = terms[i].expon + terms[j].expon;
			int found = 0;
			for (int k = *Cs; k < avail; k++) {
				if (terms[k].expon == tempExpon) {
					terms[k].coef += tempCoef;
					found = 1;
					break;
				}
			}
			if (!found) {
				attach(tempCoef, tempExpon);
			}
		}
	}
	*Ce = avail - 1;
}
int main(int argc, char* argv[]) {
	int As = 0, Ae = 3, Bs = 4, Be = 6, Cs, Ce;

	poly_multiply(As, Ae, Bs, Be, &Cs, &Ce);
	print_poly(As, Ae);
	print_poly(Bs, Be);
	printf("-----------------------------\n");
	print_poly(Cs, Ce);

	return 0;
}
