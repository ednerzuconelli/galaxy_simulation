/* Nome: Willians Vieira Fujita        RA.: 51853
   Nome: Edner Zuconelli	       RA.: 54496
*/

#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>



#define MAX 100;
#define N_THREADS 10;

double G = (pow(6.67,11));
typedef struct tipoPlaneta planeta;
double deltaT = 0;

struct tipoPlaneta{
	double x,y,massa,fx,fy,vx,vy;
	
};

int quantidade;
planeta lP[999];





//criar planetas.
void criaPlanetas(int i,int f){

	srand(time(NULL));
	int j;
	for(j=i;i<f;j++){
			lP[j].x = rand() % 100;
			lP[j].y = rand() % 100;
			lP[j].massa = 1;
			lP[j].fx = 0;
			lP[j].fy = 0;
			lP[j].vx = 0;
			lP[j].vy = 0;	
	}
}

//listar planetas
void listarPlanetas(int i,int f){
	int j;
	printf("\n\nListando Planetas: No tempo: %f \n",deltaT);
	for(j=i;i<f;j++){

			printf("Planeta: %d -> x = %f , y = %f , massa = %f , fx = %f , fy = %f , vx = %f, vy= %f \n", i,lP[j].x,lP[j].y,lP[j].massa,lP[j].fx,lP[j].fy,lP[j].vx,lP[j].vy);

	}
}


//tira o elemento da lista
void tiraElemento(int i){
	
	lP[i] = lP[quantidade-1];
	quantidade--;
}

//Verifica Colisões
void verificaColisoes(int i,int f){
	int j,k,x;	

	for(j=i;j<f;j++){
		for(x=j+1;k<f-1;k++){
			if(ceil(lP[j].x) == ceil(lP[k].x) && ceil(lP[j].y) == ceil(lP[k].y)){
				lP[j].massa = lP[j].massa + lP[k].massa;
				tiraElemento(k);
			}
		}
	}
}


//Calcular força gravitacional
void calculaForca(int n,int f){
	int i,j;	
	double distancia,forca,distanciaX,distanciaY;

	for(i=n;i<f;i++){
		for(j=n;j<f;j++){
			
			if(i!=j){	
					
				
				distanciaX = lP[j].x - lP[i].x;
				distanciaY = lP[j].y - lP[i].y;
				distancia = distanciaX*distanciaX + distanciaY*distanciaY;

				double aux = (G * lP[i].massa) * lP[j].massa;	
			
				forca = (aux/ distancia);
				printf("força: %f", forca);
		
				lP[i].fx = lP[i].fx + forca * distanciaX;
				lP[i].fy = lP[i].fy + forca * distanciaY;
			}

		}
	}
}


//Calcular velocidade
void calculaVelocidade(int n,int f){
	double dvx,dvy,dpx,dpy;	
	int i;
	for(i=n;i<f;i++){
		
			dvx = (lP[i].fx/lP[i].massa)*deltaT;
			dvy = (lP[i].fy/lP[i].massa)*deltaT;

		

			dpx = (lP[i].vx + dvx/2)*deltaT;
			dpy = (lP[i].vy + dvy/2)*deltaT;			

			lP[i].vx = lP[i].vx + dvx; 
			lP[i].vy = lP[i].vy + dvy;

			lP[i].x = lP[i].x + dpx;
			lP[i].y = lP[i].y + dpy;

		
	}
}


int main(int argc, char** argv){
	
	pthread_t threads[10];	
	
return 0;}
