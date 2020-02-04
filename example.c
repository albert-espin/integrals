/* Programa que resol una equació que iguala a una constant c > 0 la integral de d'una funció f(y) a l'interval [-x, x]*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "functions.h"



/* funció principal del programa*/
int main(void){
	int i, n, nmax, itmax, found, scanResult;
	double a, b, c, tol, x, previousX, integral, previousIntegral, var;
  
  printf("Càlcul de x > 0 tal que la integral de (sin(y))^2 a l'interval [-x, x] és igual a c > 0.\n\n");

  /* obtenció de la constant c*/
  printf("Dóna la constant c > 0:\n");
  scanResult = scanf("%le", &c);
  if (c <= 0){
	  printf("No heu donat un valor c real positiu. Finalitzem l'execució.\n");
	  exit(1);
  }

	/* com x > 0, partim com a mínim de 0 en la cerca del valor de x, i com treballem amb la integral de (sin(x))^2 a l'interval [-x, x], que igualem a c, volem fixar com a b, punt final de l'interval de treball, un nombre que x no pugui superar: la integral a l'interval és x - sin(x)*cos(x); sabent que tenim x - sin(x)*cos(x) = c, aïllem la x que està sola i prenem el valor més gran possible de sin(x)*cos(x), és a dir 1, veiem que és impossible que x sigui major que c + 1, per tant fixem que b sigui això; per una argumentació similar, prenent el mínim valor possible de sin(x)*cos(x), és a dir -1, sabem que x no podrà ser menor que c -1, i donem aquest valor a a, a menys que sigui menor que 0, en tal cas deixem a = 0.*/
	a = (c >= 1) ? c - 1: 0;
	b = c + 1;

  /* fixació de la resta de dades d'acord amb l'enunciat*/
  n = 1000;
  tol = 1e-8;
  nmax = 30;
  itmax = 100;

  i = 0;
  found = 0;
  previousX = 0;
  x = 0;
  var = 0;
  integral = 0;
  previousIntegral = 0;

  /* dividim n vegades l'interval [a, b] per cercar un punt x que compleixi l'equació. Si veiem que entre el valor x d'una iteració i l'anterior hi ha un canvi de signe en la integral entre [-x, x] de f(x), passem tals valors de x al mètode de Newton perquè intenti trobar una aproximació precissa del valor de x que fa verifica l'equació de l'exercici; un cop trobada, parem les iteracions i mostrem la solució.*/
  while ((!found) && (x < b)){
	  previousX = x;
	  x = a + i * (b - a) / n;
	  previousIntegral = integral;
	  integral = trapezis(nmax, -x, x) - c;

	  if (integral == 0){
		  var = x;
		  found = 0;
	  }

	  else{
		  if (previousIntegral*integral < 0){
			  var = (x + previousX) / 2;
			  found = Newton(&var, tol, itmax, c);
		  }
	  }

	  i++;
  }

  if (found == 0){
	  printf("\nLa solució és x = %e\n", var);
  }
  else{
	  printf("\nNo s'ha trobat cap solució a l'equació.\n");
  }

  return scanResult;
}


/* Retorna la imatge f(x) per a un valor passat de x (pels requisits de l'apartat c de la pràctica, és (sin(x))^2)*/
double f(double x){
	return sin(x)*sin(x);
}

/* Retorna el valor de la funció F(x), que és la integral de la funció f a l'interval[-x, x] (pels requisits de l'apartat c de la pràctica, és la integral de (sin(x))^2 a [-x, x])*/
double F(double x){
	return x - sin(x)*cos(x);
}

/* Retorna la derivada de la funció F(x)*/
double dF(double x){
	return f(x) + f(-x);
}


