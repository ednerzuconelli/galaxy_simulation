/* Nome: Willians Vieira Fujita        RA.: 51853
   Nome: Edner Zuconelli	       RA.: 54496
*/

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>



#define MAX 100;

double G = -(pow(6.67,11));
typedef struct tipoPlaneta planeta;
double deltaT = 0;

struct tipoPlaneta{
	double x,y,massa,fx,fy,vx,vy;
	
};

planeta lP[10];


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



//Calcular força gravitacional
void calculaForca(int n){
	int i,j;	
	double distancia,forca,direcaoX,direcaoY,x2,y2,direcaoX2,direcaoY2;

	for(i=0;i<n-1;i++){
		for(j=i+1;j<n;j++){
			x2 = pow(lP[i].x - lP[j].x,2);
			y2 = pow(lP[i].y - lP[j].y,2);
			double aux = x2 + y2;
			distancia = sqrt(aux);
			aux = (G * lP[i].massa) * lP[j].massa;	
			
			forca = (aux/ pow(distancia,2));
			direcaoX = lP[j].x - lP[i].x; 
			direcaoY = lP[j].y - lP[i].y;
			direcaoX2 = lP[i].x - lP[j].x;
			direcaoY2 = lP[i].y - lP[j].y;

			if(lP[i].x<lP[j].x){
				lP[i].fx = lP[i].fx + (cos (tan(direcaoY/direcaoX)));//(forca * direcaoX)/distancia; 
				lP[j].fx = lP[j].fx - (cos (tan(direcaoY/direcaoX)));//(forca * direcaoX)/distancia;
			}else{
				lP[i].fx = lP[i].fx - (cos (tan(direcaoY/direcaoX)));//(forca * direcaoX)/distancia; 
				lP[j].fx = lP[j].fx + (cos (tan(direcaoY/direcaoX)));//(forca * direcaoX)/distancia
			
			}

			if(lP[i].y<lP[j].y){
				lP[i].fy = lP[i].fy + (sin (tan(direcaoY/direcaoX)));//(forca * direcaoY)/distancia;
				lP[j].fy = lP[j].fy - (sin (tan(direcaoY/direcaoX)));//(forca * direcaoY)/distancia;
			}else{
				lP[i].fy = lP[i].fy - (sin (tan(direcaoY/direcaoX)));//(forca * direcaoY)/distancia;
				lP[j].fy = lP[j].fy + (sin (tan(direcaoY/direcaoX)));//(forca * direcaoY)/distanci
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

			lP[i].fx =0;
			lP[i].fy =0;
		
	}
}


int main(int argc, char** argv){
	criaPlanetas(2);
	listarPlanetas(2);
	int i;
	for(i =0;i<2;i++){
		deltaT = time(NULL) - deltaT;
		deltaT = deltaT/1000000000;
		calculaForca(2);
		
		
		calculaVelocidade(2);
		listarPlanetas(2);
	}
return 0;}
