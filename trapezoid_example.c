/* Programa que calcula una aproximació de la integral en un interval pel mètode dels trapezis*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "functions.h"


/* funció principal del programa*/
int main(void){
	int n, nmax, reachedMax, scanResult;
  double a, b, tol, expMax, prevResult, result;
  
  printf("CÀLCUL DE LA INTEGRAL EN UN INTERVAL PEL MÈTODE DELS TRAPEZIS.\n\n");

  /* obtenció de la tolerància */
  printf("Introdueix la tolerància (per exemple 1e-3): ");
  scanResult = scanf("%le", &tol);
  
  /* obtenció de a */
  printf("Introdueix el punt d'inici de l'interval, a: ");
  scanResult = scanf("%le", &a);
  
   /* obtenció de b */
  printf("Introdueix el punt final de l'interval, b: ");
  scanResult = scanf("%le", &b);

  /* obtenció del nombre de divisions*/
  printf("Introdueix el màxim nombre de subdivisions (nmax): ");
  scanResult = scanf("%d", &nmax);

  printf("\nf(x) = sin(x)\nVolem trobar la integral de f(x) a l'interval [%e, %e].\n", a, b);

  reachedMax = 0;
  prevResult = -1.;
  result = 0.;
  n = 2;
  expMax = pow(2,nmax);

  /* s'opera amb el mètode dels trapezis duplicant el nombre de subintervals cada vegada fins el nombre de subintervals supera el resultat d'elevar el màxim a 2 o fins que la diferència en valor absolut d'una iteració a la següent és menor que la tolerància*/
  while ((!reachedMax) && (fabs(result - prevResult) >= tol)){
	  prevResult = result;
	  result = trapezis(n, a, b);
	  n *= 2;
	  reachedMax = (n >= expMax);
  }

  /* si s'han arribat a fer totes les iteracions permeses sense resultat vàlid, diem que el càlcul no s'ha resolt*/
  if (reachedMax && (fabs(result - prevResult) >= tol)){
	  printf("\nNo s'ha pogut calcular la integral amb la tolerància desitjada.");
  }

  else{
	  /* obtenció de la integral en l'interval a,b */
	  printf("\nLa integral a l'interval pel mètode dels trapezis s'aproxima com:\n%e\n", result);
  }

  return scanResult;
}

/* Retorna la imatge d'una funció per a un valor x passat per paràmetre (pels requeriments de la part a de la pràctica, f(x)=sin(x))*/
double f(double x){

	/*cas en què la funció és el sinus*/
	return sin(x);

	/* exemples d'altres possibilitats de funció:*/
	/* return cos(x);*/
	/* return pow(2,x);*/
}

/* Funció pròpia de la part b de la pràctica (aquí buida) però que cal afegir aquí per evitar que a prac2funs, on es troba la funció del mètode de Newton, hi hagi una referència a una funció no implementada (aquesta) quan es munta prac2a i prac2funs*/
double F(double x){
	return -1;
}

/* Funció pròpia de la part b de la pràctica (aquí buida) però que cal afegir aquí per evitar que a prac2funs, on es troba la funció del mètode de Newton, hi hagi una referència a una funció no implementada(aquesta) quan es munta prac2a i prac2funs*/
double dF(double x){
	return -1;
}
