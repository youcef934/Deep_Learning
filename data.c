
#include "data.h"
//récupération des données et sauvegarde dans la structure data
data_t* recup(){
  data_t *data = malloc(data_size * sizeof(*data));
  FILE *fp;
  int i=0;
  char str[taille];
  char *token;
  fp = fopen("iris.data" , "r");
  if(fp == NULL) {
    perror("Error opening file");
  }

  while((fgets(str,taille,fp) != NULL)){
    data[i].v=malloc(vector_size* sizeof(*data[i].v));
    token = strtok(str,",");
    for(int j=0;j<vector_size;j++){
      if(token){
        data[i].v[j]=strtod(token,NULL);
        token = strtok(NULL,",");
      }
    }
    data[i].norme = norme(data[i].v);
    normalisation(data[i].v,data[i].norme);
    token=strtok(token,"\n");
    data[i].label=strdup(token);
    i++;
  }
  return data;
}
//calcule de la norme d'un vecteur
double norme(double *v){
  double norm=0;
  for (int i = 0; i <vector_size; ++i)
  {
    norm = norm+v[i] * v[i];

  }
  return sqrt(norm);
}
//normalistaion d'un vecteur
void normalisation(double *v, double norme){
  for (int i = 0; i < vector_size; ++i)
  {
      v[i]=v[i]/norme;
  }
}
//affichage de la structure data
void affichage(data_t *data){
  for (int i = 0; i < data_size; ++i){
    printf("%d\n",i);
    for (int j= 0; j<vector_size; ++j)
    {
      printf("%f\n",data[i].v[j]);
    }
    printf("%f\n%s\n\n",data[i].norme,data[i].label);

  }
}
//la fonction shuffle renvoie un vecteur de 150 case contenant des valeur entre 0 et 149 mélangée
int * shuffle(int tab_size){
  int * tab_shuffle;
  int j;
  int tmp;
tab_shuffle=malloc(tab_size* sizeof(*tab_shuffle));
for (int i = 0; i < tab_size; ++i){
    tab_shuffle[i]=i;
  }
  for (int i = 0; i <tab_size; ++i){
    j=rand()%(tab_size  - i) + i;

    tmp=tab_shuffle[i];
    tab_shuffle[i]=tab_shuffle[j];
    tab_shuffle[j]=tmp;

  }
  return tab_shuffle;
}
//le calcul de la moyenne de tout les vecteur permets la centralisation des données
double * vec_moyen(data_t * t){
  double * vec;

  vec = calloc(vector_size ,sizeof(*vec));
  for (int i = 0; i <data_size; i++){
    for (int j= 0; j<vector_size; j++){
      vec[j]+= t[i].v[j];
    }
  }
  for (int i = 0; i <vector_size; ++i)
  {
    vec[i]/=data_size;
  }
  return vec;
}
//le vecteur maximun est égale au vecteur de la moyenne plus une valeur
double * vec_maximum(double *v){
  double *vec_max;
  double plus=0.03;
  vec_max=calloc(vector_size,sizeof(*vec_max));
  for (int i = 0; i <vector_size; ++i)
  {
    vec_max[i]=v[i]+plus;
  }
  return vec_max;
}
//le vecteur maximun est égale au vecteur de la moyenne moins une valeur
double * vec_minimum(double *v){
  double *vec_min;
  double moins=0.05;
  vec_min=calloc(vector_size,sizeof(*vec_min));
  for (int i = 0; i <vector_size; ++i)
  {
    vec_min[i]=v[i]-moins;
  }
  return vec_min;
}
