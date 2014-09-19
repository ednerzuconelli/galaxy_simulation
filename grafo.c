#include<stdio.h>

#include<stdlib.h>


/************************************************************/

typedef struct x{

	int num;

	struct x *prox;

}x;

typedef struct sentinela{

	struct pilha *inicio;

	struct pilha *fim;

}sentinela;

typedef struct pilha{

	int num;

	struct pilha *prox;

}pilha;

/************************************************************/

char erro[]={"Opcao Invalida!\n"};

/************************************************************/

void menu(x *grafo, int tam);

x *insere_aresta(x *grafo, int tam);

void imprime(x *grafo, int tam);

void busca_em_prof(x *grafo, int tam, int inicio);

pilha *desempilha(pilha *p);

pilha *empilha(pilha *p, int num);

sentinela *insere_fila(sentinela *filas, int num);

sentinela *desenfila(sentinela *filas);

void busca_largura(x *grafo, int tam, int inicio);

/************************************************************/

int main(){

	x *grafo=NULL;
	
	int tam;
	
	printf("Tamanho do vetor: ");
	
	scanf("%d",&tam);
	
	grafo=(x *)malloc(tam * sizeof(x));
	
	if(!grafo){
	
		puts("ERRO\n");
		//system("pause");
		exit(0);
	
	}
	
	//system("cls");

	menu(grafo,tam);

}

/************************************************************/

void menu(x *grafo, int tam){

	int op,i;
	
	for(i=0;i<tam;i++){
	
		grafo[i].num=i;
	
		grafo[i].prox=NULL;
	
	}
	
	//system("cls");
	
	do{
	
		printf("\t 1 - Inserir Arestas\n");
		
		printf("\t 2 - Imprimir\n");
		
		printf("\t 3 - Busca em Profundidade\n");
		
		printf("\t 4 - Busca em Largura\n");
		
		printf("\t 5 - Sair\n\n");
		
		printf("Opcao: ");
		
		scanf("%d",&op);
		
		switch(op){
		
			case 1: grafo=insere_aresta(grafo,tam);break;
			
			case 2: imprime(grafo,tam);break;
			
			case 3: busca_em_prof(grafo,tam,grafo[0].num);break;
			
			case 4: busca_largura(grafo,tam,grafo[0].num);break;
			
			case 5:exit(0);break;
			
			default: printf(erro);break;
			
		}
		
	//	system("pause");
		
	//	system("cls");
		
	}while(op!=5);

}

/************************************************************/

x *insere_aresta(x *grafo, int tam){

	int n1,n2,i;
	
	x *novo, *out;
	
	x *aux;
	
	printf("Insira a aresta\n");
	
	printf("1 Ponto: ");
	
	scanf("%d",&n1);
	
	printf("2 Ponto: ");
	
	scanf("%d",&n2);
	
	if(n1==n2){
	
		novo=(x *)malloc(sizeof(x));
		
		novo->num=n2;
		
		novo->prox=NULL;
		
		novo->prox=grafo[n1].prox;
		
		grafo[n1].prox=novo;
	
	}
	
	else{
	
		novo=(x *)malloc(sizeof(x));
		
		novo->prox=NULL;
		
		novo->num=n2;
		
		novo->prox=grafo[n1].prox;
		
		grafo[n1].prox=novo;
		
		out=(x *)malloc(sizeof(x));
		
		out->prox=NULL;
		
		out->num=n1;
		
		out->prox=grafo[n2].prox;
		
		grafo[n2].prox=out;
	
	}
	
	printf("\n\tOK\n\n");
	
	return grafo;

}

/************************************************************/

void imprime(x *grafo, int tam){

	x *aux;
	
	int i;
	
	for(i=0;i<tam;i++){
		
		printf("Lista do Numero: %d :",grafo[i].num);
		
		if(grafo[i].prox==NULL)
		
		continue;
		
		aux=grafo[i].prox;
		
		while(aux!=NULL){
		
			printf(" ->%d",aux->num);
		
			aux=aux->prox;
		
		}
	
		puts("\n\n");
	
	}

}

/************************************************************/

pilha *empilha(pilha *p, int num){

	pilha *aux=(pilha *)malloc(sizeof(pilha));
	
	aux->num=num;
	
	if(p!=NULL)
	
	aux->prox=p;
	
	else
	
	aux->prox=NULL;
	
	return aux;
	
}

/************************************************************/

pilha *desempilha(pilha *p){

	pilha *aux=p;
	
	p=p->prox;
	
	free(aux);
	
	return p;

}

/************************************************************/

void busca_em_prof(x *grafo, int tam, int inicio){

	int visitados[tam];
	
	pilha *p=NULL;
	
	int i,pos,y;
	
	x *aux;
	
	for(i=0;i<tam;i++){
	
		visitados[i]=0;
	
	}
	
	p=empilha(p,inicio);
	
	while(p!=NULL){
	
		pos=p->num;
		
		p=desempilha(p);
		
		if(visitados[pos]!=1){
		
			visitados[pos]=1;
		
			printf(" %d ",pos);
		
		}
		
		aux = grafo[pos].prox;
		
		while(aux!=NULL){
		
			if(visitados[aux->num]!=1){
		
				y=aux->num;
		
				p=empilha(p,y);
		
			}
		
			aux=aux->prox;
		
		}
	
	}

}

/************************************************************/

sentinela *insere_fila(sentinela *sent, int num){

	pilha *aux=(pilha *)malloc(sizeof(pilha));
	
	aux->num=num;
	
	aux->prox=NULL;
	
	if(sent->fim==NULL){
	
		sent->inicio=aux;
	
		sent->fim=aux;
	
	}else{
	
		sent->fim->prox=aux;
	
		sent->fim=aux;
	
	}
	
	return sent;

}

/************************************************************/

sentinela *desenfila(sentinela *fila){

	pilha *aux;
	
	if(fila->inicio == fila->fim){
	
		free(fila->inicio);
	
		fila->inicio=NULL;
	
		fila->fim=NULL;
	
	} else{
	
		aux=fila->inicio;
	
		fila->inicio=fila->inicio->prox;
	
		free(aux);
	
	}
	
	return fila;

}

/************************************************************/

void busca_largura(x *grafo, int tam, int inicio){

	int visitados[tam];
	
	sentinela *sent=(sentinela *)malloc(sizeof(sentinela));
	
	sent->inicio=NULL;
	
	sent->fim=NULL;
	
	int i,pos,y;
	
	x *aux;
	
	for(i=0;i<tam;i++){
	
		visitados[i]=0;
	
	}
	
	sent=insere_fila(sent,inicio);
	
	while(sent->fim!=NULL){
	
		pos=sent->inicio->num;
		
		sent=desenfila(sent);
		
		if(visitados[pos]!=1){
		
			visitados[pos]=1;
		
			printf(" %d ",pos);
		
		}
		
		aux = grafo[pos].prox;
		
		while(aux!=NULL){
		
			if(visitados[aux->num]!=1){
		
				y=aux->num;
		
				sent=insere_fila(sent,y);
		
			}
		
			aux=aux->prox;
		
		}
		
	}

}
