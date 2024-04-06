//두 다항식을 곱하는 프로그램
#include <stdio.h>
#include <stdlib.h>

#define MAX_TERMS 101
struct term {
	float coef;
	int expon;
}terms[MAX_TERMS] = {
	{7.0, 6}, {5.0, 3}, {9.0, 2}, {1.0, 0},
	{5.0, 3}, {2.0, 2}, {1.0, 1}, {10.0, 0}
};
int avail = 8;

// 새로운 항을 다항식에 추가한다.
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
				if (terms[k].expon == tempExpon) { // 이미 같은 지수의 항이 있다면
					terms[k].coef += tempCoef; // 계수를 그 항에 더해준다.
					found = 1;
					break;
				}
			}
			if (!found) { // 없다면
				attach(tempCoef, tempExpon); // 새로운 항을 다항식에 추가한다.
			}
		}
	}
	*Ce = avail - 1;
}
int main(int argc, char* argv[]) {
	int As = 0, Ae = 3, Bs = 4, Be = 7, Cs, Ce;

	poly_multiply(As, Ae, Bs, Be, &Cs, &Ce);
	print_poly(As, Ae);
	print_poly(Bs, Be);
	printf("-----------------------------\n");
	print_poly(Cs, Ce);

	return 0;
}
