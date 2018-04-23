
/* ******************************************************************
 *								Martin Dardis				Padron:101608
 * *****************************************************************/

#include "tp0.h"
#include <stdbool.h>


void swap (int* x, int* y) {
	int aux=0;
	aux = *x;
	*x = *y;
	*y = aux;
	return;
}



int maximo(int vector[], int n) {
	if (n==0)
		return -1;
	int posc_max=0;
	for(int i=0;i<n;i++){
		if(vector[posc_max]<vector[i])
			posc_max=i;
	}
	return posc_max;
}




int comparar(int vector1[], int n1, int vector2[], int n2) {
	const int VECTOR1_MENOR=-1,VECTOR2_MENOR=1,VECTORES_IGUALES=0;
	int i=0;
	while(i<n1 && i<n2){//Mientras los 2 arreglos tengan elementos
		if (vector1[i]<vector2[i])
			return VECTOR1_MENOR;
		else if (vector1[i]>vector2[i])
			return VECTOR2_MENOR;
		i++;
	}
	if(n1<n2)
		return VECTOR1_MENOR;
	else if (n1>n2)
		return VECTOR2_MENOR;
	return VECTORES_IGUALES;
}




void seleccion(int vector[], int n) {
	for(int i=0;i<n;i++){
		int min=i;
		for(int j=i+1;j<n;j++){
			if(vector[j]<vector[i]){
				min=j;
				swap(&vector[i],&vector[min]);
			}
		}
	}
	return;
}
