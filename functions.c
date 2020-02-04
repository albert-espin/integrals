/* Arxiu que conté la definició de les funcions de la pràctica*/

#include <math.h>
#include "functions.h"



/* Aproxima la integral entre l'interval a,b particionant-lo en N subintervals iguals, i operant amb el mètode dels trapezis*/
double trapezis(int N, double a, double b){
	int i;
	double hN, result;

	hN = (b - a) / N;
	result = f(a) / 2.;

	for (i = 1; i < N; i++){
		result += f(a + i*hN);
	}

	result += f(b) / 2.;

	result *= hN;

	return result;
}


/* Rep un punter a un valor inicial de x, una tolerància, un nombre d'iteracions i una constant, i itera tot intentant convergir cap a un zero a partir del valor x de l'anterior iteració, la imatge i la derivada de la funció; retorna 0 si troba un zero, amb x apuntant al valor de x que l'aconsegueix; 1 altrament*/
int Newton(double * x, double tol, int itmax, double c){
	int i;
	double xPrevious;

	xPrevious = -1.;
	for (i = 0; i < itmax; i++){
		if (i > 0){
			xPrevious = *x;
		}
		*x = *x - ((F(*x) - c) / dF(*x));
		if ((fabs((*x) - xPrevious) <= tol) || (fabs(F(*x) - c) <= tol)){
			return 0;
		}
	}

	return 1;
}


