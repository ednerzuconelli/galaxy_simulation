/* Nome: Willians Vieira Fujita        RA.: 51853
   Nome: Edner Zuconelli	       RA.: 54496
*/

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ncurses.h>
#include "mpi.h"


#define MAX 100;

double G = (pow(6.67,11));
typedef struct tipoPlaneta planeta;
double deltaT = 0;

struct tipoPlaneta{
	double x,y,massa,fx,fy,vx,vy;
	
};

int quantidade;
planeta lP[999];


void desenhaPlanetas(int n){
	int i;
	
	for(i=0;i<n;i++){
		move(lP[i].x,lP[i].y);
		printf("*");	
	}
}



//criar planetas.
void criaPlanetas(int n){

	srand(time(NULL));
	int i;
	for(i=0;i<n;i++){
			lP[i].x = rand() % 100;
			lP[i].y = rand() % 100;
			lP[i].massa = 1;
			lP[i].fx = 0;
			lP[i].fy = 0;
			lP[i].vx = 0;
			lP[i].vy = 0;	
	}
}

//listar planetas
void listarPlanetas(int n){
	int i;
	printf("\n\nListando Planetas: No tempo: %f \n",deltaT);
	for(i=0;i<n;i++){

			printf("Planeta: %d -> x = %f , y = %f , massa = %f , fx = %f , fy = %f , vx = %f, vy= %f \n", i,lP[i].x,lP[i].y,lP[i].massa,lP[i].fx,lP[i].fy,lP[i].vx,lP[i].vy);

	}
}


//tira o elemento da lista
void tiraElemento(int i){
	
	lP[i] = lP[quantidade-1];
	quantidade--;
}

//Verifica Colisões
void verificaColisoes(int n){
	int i,j;	

	for(i=0;i<n;i++){
		for(j=i+1;j<n-1;j++){
			if(ceil(lP[i].x) == ceil(lP[j].x) && ceil(lP[i].y) == ceil(lP[j].y)){
				lP[i].massa = lP[i].massa + lP[j].massa;
				tiraElemento(j);
			}
		}
	}
}


//Calcular força gravitacional
void calculaForca(int n){
	int i,j;	
	double distancia,forca,distanciaX,distanciaY;

	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			
			if(i!=j){	
					
				
				distanciaX = lP[j].x - lP[i].x;
				distanciaY = lP[j].y - lP[i].y;
				distancia = distanciaX*distanciaX + distanciaY*distanciaY;

				double aux = (G * lP[i].massa) * lP[j].massa;	
			
				forca = (aux/ distancia);
				//printf("força: %f", forca);
		
				lP[i].fx = lP[i].fx + forca * distanciaX;
				lP[i].fy = lP[i].fy + forca * distanciaY;
			}

		}
	}
}


//Calcular velocidade
void calculaVelocidade(int n){
	double dvx,dvy,dpx,dpy;	
	int i;
	for(i=0;i<n;i++){
		
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
	initscr();	
		

	quantidade = 2; 
	MPI_Status status;
	MPI_Init(&argc,&argv);	
	criaPlanetas(quantidade);
	listarPlanetas(quantidade);
	int i;
	for(i =0;i<10;i++){
		deltaT = time(NULL) - deltaT;
		deltaT = deltaT/1000000000000000;
		calculaForca(quantidade);
		calculaVelocidade(quantidade);
		//listarPlanetas(quantidade);
		verificaColisoes(quantidade);
		desenhaPlanetas(quantidade);
		getch();
	}
	
	
	endwin();	
return 0;}
