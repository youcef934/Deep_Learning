#include "data.h"
#include "init.h"
#include<time.h>

int main(){
	srand(time(NULL));
	data_t *data;
  	network_t * mynet;

 	data = recup();
	mynet=init_network(data);
	learning(data, mynet,0.9,3,500);
//	learning(data, mynet,0.07,1,2500);
	etiquette(data,mynet);
	affichenet(mynet);
}
