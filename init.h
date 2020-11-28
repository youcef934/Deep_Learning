#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct node{
    int l;
    int c;
    double * v;
    char * labelnode;
};
typedef struct node node_t;

struct network{
    int l;
    int c;
    node_t ** node;//matrice

};
typedef struct network network_t;

struct voisinage{
    int l_moins;
    int l_plus;
    int c_moins;
    int c_plus;

};
typedef struct voisinage voisinage_t;

network_t* init_network(data_t *data);
void learning(data_t * data, network_t* net, double alphainit,int r,int nb_ittiration);
void etiquette(data_t *data, network_t *net);
void affichenet(network_t *net);
int * bmu(network_t * net,double *vec);
void getvoisinage(int * tab,int r,network_t * net,voisinage_t *voisinage);
