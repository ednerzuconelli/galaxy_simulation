/* Nome: Willians Vieira Fujita        RA.: 51853
   Nome: Edner Zuconelli	       RA.: 54496
   
   gcc modelo_paralelo.c -lm -pthread -o executavel
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

typedef struct{
	int i;
	int tamanho;
}threads_arg, *pth_pthread_arg;


int quantidade;
planeta lP[999];





//criar planetas.
void *criaPlanetas(void *args){

	pth_pthread_arg targ = (pth_pthread_arg)args;

	srand(time(NULL));
	int i;
	for(i=targ->i;i<(targ->tamanho+targ->i);i++){
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
void *listarPlanetas(void *args){
	
	pth_pthread_arg targ = (pth_pthread_arg)args;
	
	int i;
	printf("\n\nListando Planetas: No tempo: %f \n",deltaT);
	for(i=targ->i;i<(targ->tamanho+targ->i);i++){

			printf("Planeta: %d -> x = %f , y = %f , massa = %f , fx = %f , fy = %f , vx = %f, vy= %f \n", i,lP[j].x,lP[j].y,lP[j].massa,lP[j].fx,lP[j].fy,lP[j].vx,lP[j].vy);

	}
}


//tira o elemento da lista
void tiraElemento(int i){
	
	lP[i] = lP[quantidade-1];
	quantidade--;
}

//Verifica Colisões
void verificaColisoes(void *args){
	
	pth_pthread_arg targ = (pth_pthread_arg)args;
	
	int i,j;	

	for(i=targ->i;i<(targ->tamanho+targ->i);i++){
		for(j=i+1;j<(targ->tamanho+targ->i);j++){
			if(ceil(lP[i].x) == ceil(lP[j].x) && ceil(lP[i].y) == ceil(lP[j].y)){
				lP[i].massa = lP[i].massa + lP[j].massa;
				tiraElemento(j);
			}
		}
	}
}


//Calcular força gravitacional
void calculaForca(void *args){
	
	pth_pthread_arg targ = (pth_pthread_arg)args;
	int i,j;	
	double distancia,forca,distanciaX,distanciaY;

	for(i=targ->i;i<(targ->tamanho+targ->i);i++){
		for(j=i+1;j<(targ->tamanho+targ->i);j++){
			
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
void calculaVelocidade(void *args){
	
	pth_pthread_arg targ = (pth_pthread_arg)args;
	double dvx,dvy,dpx,dpy;	
	int i;
	for(i=targ->i;i<(targ->tamanho+targ->i);i++){
		
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
	int parc = quantidade/10;
	pthread_t threads[10];	
	
	threads_arg argumentos[10];

	for(int i=0;i<10;i++){
			argumento[i].i = i*10;
			argumento[i].tamanho = parc;
			pthread_create(&(threads[i]),NULL,criaPlanetas,&(argumentos[i]));
	}
	
	for(int i=0;i<10;i++){
		pthread_join(threads[i],NULL);
		
	}
	
return 0;}
