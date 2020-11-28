#include"data.h"
#include"init.h"

//initialisation du réseau avec des valeurs aléatoires entre le vecteur max et le vecteur min du vecteur moyenne
network_t * init_network(data_t* data){
	network_t *net;
	net = malloc (sizeof(* net));
	net->l=12;
	net->c=5;
	//calcul du vecteur min et max pour remplir les vec du neuronne avec une val alétoire entre le max et le min
	double * vec_moy = vec_moyen(data);
	double * vec_max =vec_maximum(vec_moy);
	double * vec_min =vec_minimum(vec_moy);
	net->node= malloc(net->l * sizeof(*net->node));
	for(int i = 0; i<net->l; ++i){
		net->node[i]= malloc(net->c * sizeof(*net->node[i]));
		for (int j= 0; j< net->c; ++j){
			net->node[i][j].l = i;
			net->node[i][j].c = j;
			net->node[i][j].v = malloc(vector_size * sizeof(* net->node[i][j].v));
			net->node[i][j].labelnode = NULL;
			for (int k = 0; k <vector_size; ++k)
			{
				double val=(vec_max[k] - vec_min[k]) * ( (double)rand() / (double)RAND_MAX ) +vec_min[k];

				net->node[i][j].v[k] = val;
			}
		}
	}
   return net;
}

double disteuc(double *v1, double *v2){
	double res = 0.0;
	for (int i = 0; i <vector_size; ++i)
	{
		res += pow((v1[i] - v2[i]) ,2);
	}
	return sqrt(res);
}

int * bmu(network_t * net,double * vec){
	int * coordbmu;
	double bmu,bmucalcule;
	coordbmu=calloc(2,sizeof(*coordbmu));
	bmu=disteuc(vec, net->node[0][0].v);
	for (int l= 0; l <net->l; ++l){
		for(int c=0; c < net->c; ++c){
			bmucalcule = disteuc(vec,net->node[l][c].v);
		 	if(bmucalcule< bmu){
				bmu = bmucalcule;
				coordbmu[0]= l;
				coordbmu[1]= c;
			}

		}
	}
	return coordbmu;
}
void getvoisinage(int tab[], int r, network_t * net,voisinage_t *voisinage){
	voisinage->l_plus = tab[0] + r;
	voisinage->l_moins = tab[0]-r;
	voisinage->c_plus = tab[1]+r;
	voisinage->c_moins = tab[1]-r;
	if(voisinage->l_plus > net->l-1){
		voisinage->l_plus=net-> l-1;
	}
	if(voisinage->l_moins < 0)
		voisinage->l_moins= 0;
	if(voisinage->c_plus > net-> c-1)
		voisinage->c_plus = net-> c-1;
	if(voisinage->c_moins < 0)
		voisinage->c_moins = 0;

}

void learning(data_t *data, network_t *net, double alphainit,int r,int nb_ittiration){
	double alpha ;
	int *tab_melange;
	int * coordonne_bmu;
	voisinage_t *voisinage;
    int tmp = nb_ittiration/r;
	voisinage=calloc(1,sizeof(*voisinage));
	for (int it = 1; it < nb_ittiration; ++it){
		alpha = alphainit *(1.0 -((double)it/(double)nb_ittiration));
		tab_melange=shuffle(data_size);

		for (int i = 0; i < data_size; ++i){//pour tout vecteur de la base de donnée
				voisinage->l_plus=0;
	voisinage->l_moins=0;
	voisinage->c_plus=0;
	voisinage->c_moins=0;
			double *v = data[tab_melange[i]].v;
			coordonne_bmu=bmu(net,v);
			if(it%tmp == 0)
			  	r--;

			getvoisinage(coordonne_bmu,r,net,voisinage);
			for (int l=voisinage->l_moins; l <= voisinage->l_plus ; l++){
				for (int c =voisinage->c_moins ; c <= voisinage->c_plus; c++){
					double *w = net->node[l][c].v;
					for (int p=0; p<vector_size; ++p){
						w[p] += alpha *(v[p] - w[p]);

					}
				}
			}

		}
		free(tab_melange);
		r=(r>0)? r:1;

    }
}
void etiquette(data_t *data, network_t *net){
	double bmu;
	double bmuinit;
	int lbmu;
	lbmu=0;

	for (int l = 0; l < net->l; ++l){
		for(int c=0;c< net->c;++c){
			bmu=disteuc(data[0].v, net->node[l][c].v);
	        for (int i= 1; i<data_size ; ++i){
	        	double * w = data[i].v;
		        bmuinit = disteuc(w,net->node[l][c].v);
				if(bmuinit < bmu){
					bmu = bmuinit;
					lbmu = i;
				}

		    }
		    net->node[l][c].labelnode =data[lbmu].label;


	    }
	}
}
void affichenet(network_t *net){
	for (int i = 0; i < net->l; ++i){
			for (int j= 0; j< net->c; ++j){
				if((strcmp(net->node[i][j].labelnode,"Iris-virginica"))==0)
					printf("\033[31mC ");
				if((strcmp(net->node[i][j].labelnode,"Iris-versicolor"))==0)
					printf("\033[32mB ");
				if((strcmp(net->node[i][j].labelnode,"Iris-setosa"))==0)
					printf("\033[34mA ");
				if((strcmp(net->node[i][j].labelnode,"NULL"))==0)
				    printf("%d",0);
			}
		printf("\n");
	}

	printf("\033[34mIris-setosa--> A\n");
	printf("\033[32mIris-versicolor--> B \n");
	printf("\033[31mIris-virginica--> C \n");
}
