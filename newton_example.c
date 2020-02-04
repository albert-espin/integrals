/* Programa que cerca els zeros en un interval d'una funció mitjançant el mètode de Newton*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "functions.h"


/* funció principal del programa*/
int main(void){
	int i, n, m, foundSolutionsCount, itmax, NewtonResult, scanResult;
	double tol, a, b, c, aCurrent, aPrevious, currentG, previousG, x;
	double * solutions;
  
  printf("CÀLCUL DELS ZEROS D'UNA FUNCIÓ PEL MÈTODE DE NEWTON.\n\n");

  /* obtenció de la tolerància */
  printf("Introdueix la tolerància (per exemple 1e-3): ");
  scanResult = scanf("%le", &tol);

  /* obtenció de a */
  printf("Introdueix el punt d'inici de l'interval, a: ");
  scanResult = scanf("%le", &a);

  /* obtenció de a */
  printf("Introdueix el punt final de l'interval, b: ");
  scanResult = scanf("%le", &b);
  
  /* obtenció de a */
  printf("Introdueix la constant c: ");
  scanResult = scanf("%le", &c);

  /* obtenció del nombre de solucions que es volen trobar*/
  printf("Introdueix el nombre m de solucions que es volen trobar com a màxim: ");
  scanResult = scanf("%d", &m);
  
  /* obtenció del nombre de subintervals*/
  printf("Introdueix el nombre n de subintervals en què dividir l'interval: ");
  scanResult = scanf("%d", &n);

  /* obtenció del nombre de divisions*/
  printf("Introdueix el nombre d'iteracions màximes del mètode de Newton: ");
  scanResult = scanf("%d", &itmax);

  printf("\nF(x) =  x^3 -3x^2 + x\nc = %e\nG(x) = F(x) - c = x^3 -3x^2 + x - (%e)\n",c,c);
	printf("Buscarem un màxim de %d zeros de G(x) a [%e, %e].\n", m, a, b);


  /* reserva de memòria dinàmica per a la llista de solucions*/
  foundSolutionsCount = 0;
  solutions = (double *)malloc(sizeof(double) * m);

  aCurrent = 0.;
  aPrevious = 0.;
  currentG = 0.;
  previousG = 0.;
  i = 0;

  /* dividim l'interval en n subintervals, i anem analitzant el valor de la funció entre una iteració i la següent mentre quedin solucions per calcular*/
  while((i < n) && (foundSolutionsCount < m)){
	  aPrevious = aCurrent;
	  aCurrent = a + i*(b - a) / n;
	  previousG = currentG;
	  currentG = F(aCurrent) - c;

	  /* si la funció dóna 0 per a un cert valor de x, guardem aquest com a solució*/
	  if (currentG == 0){
		  solutions[foundSolutionsCount] = aCurrent;
		  foundSolutionsCount++;
	  }

	  /*altrament, si hi ha un canvi de signe d'un valor al següent, analitzem pel mètode de Newton si hi ha un zero, i en tal cas el guardem*/
	  else if (previousG*currentG < 0){
		  x = (aPrevious + aCurrent) / 2;
		  NewtonResult = Newton(&x, tol, itmax, c);
		  if (NewtonResult == 0){
			  solutions[foundSolutionsCount] = x;
			  foundSolutionsCount++;
		  }
	  }
	  i++;
  }

  /*mostrem les solucions trobades, si tenim alguna*/
  if (foundSolutionsCount == 0){
	  printf("\nNo s'ha trobat cap solució.\n");
  }

  else{
	  printf("\nEls següents valors fan que G(x) sigui 0:\n");
	  for (i = 0; i < foundSolutionsCount; i++){
		  printf("x = %e\n", solutions[i]);
	  }
  }

  /* alliberem la memòria dinàmica prèviament reservada*/
  free(solutions);
  
  return scanResult;
}


/* Funció pròpia de la part a de la pràctica (aquí buida) però que cal afegir aquí per evitar que a prac2funs, on es troba la funció del mètode dels trapezis, hi hagi una referència a una funció no implementada quan es munta prac2b i prac2funs*/
double f(double x){
	return -1;
}

/* Retona la imatge de la funció en el punt x donat (pels requeriments de la part b de la pràctica, la funció és x^3 -3x^2 + x)*/
double F(double x){
	return x*x*x - 3*x*x + x;
}

/* Retona la derivada de la funció en el punt x donat (pels requeriments de la part b de la pràctica, és la derivada de la funció és x^3 -3x^2 + x, és a dir, 3x^2 -6x + 1)*/
double dF(double x){
	return 3*x*x - 6*x + 1;
}
