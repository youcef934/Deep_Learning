#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define data_size 150
#define vector_size 4
#define taille 40

#ifndef DATA_H
#define DATA_H


struct data 
{
	double *v;
	double norme;
	char *label;
};
typedef struct data data_t;

data_t * recup();
void affichage(data_t *data);
double norme(double *v);
void normalisation(double *v, double norme);
int * shuffle(int tab_size);
double * vec_moyen(data_t * t);
double * vec_maximum(double *v);
double * vec_minimum(double *v);

#endif