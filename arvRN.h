#include <stdio.h> 
#include <stdlib.h>
#include <iostream>

using namespace std;

#define fmt "%d "
#define Red 0
#define Black 1

typedef int Item;
typedef int Cor;

typedef struct arv {
   struct arv *esq;
   Item item;          
   struct arv *dir;
   struct arv *pai;
   Cor cor;
} *Arv;

Arv arv(Arv e, Item x, Arv d, Arv p, Cor c) {
   Arv n = (Arv) malloc(sizeof(struct arv));
   n->esq  = e;
   n->item = x;
   n->dir  = d;
   n->cor = c;
   n->pai = p;
   return n;
}

Arv arv(Item x, Cor c, Arv p = NULL) {
   Arv n = (Arv) malloc(sizeof(struct arv));
   n->esq  = NULL;
   n->item = x;
   n->dir  = NULL;
   n->cor = c;
   n->pai = p;
   return n;
} 

//Desconhecido
Item remmax(Arv *A) {
   	if( *A == NULL ) 
   		abort();
   	while( (*A)->dir != NULL ){
	   	A = &(*A)->dir;
	}
   	Arv n = *A;
   	Item x = n->item;
   	*A = n->esq;
   	free(n);
   	return x;
}

//Alterar
void rem(Item x, Arv *A) {
   	if( *A == NULL ) 
	   	return;
   	if(x == (*A)->item ) {
      	Arv n = *A;
      	if( n->esq == NULL ) 
		  	*A = n->dir;
      	else if ( n->dir == NULL ) 
		  	*A = n->esq;
		else 
			n->item = remmax(&n->esq);
      	if( n != *A ) 
		  	free(n);
   	}
   	else if( x <= (*A)->item ) 
	   	rem(x,&(*A)->esq);
   	else 
	   	rem(x,&(*A)->dir);
}

bool busca(Item x, Arv A) {
   	if( A == NULL ) 
		return false;
   	if( x == A->item ) 
	   	return true;
   	if( x <= A->item ) 
	   	return busca(x,A->esq);
   	else 
	   	return busca(x,A->dir);
}

void exibe(Arv A, int n = 0){
	if( A==NULL ) 
		return; 
	exibe(A->dir,n+1);
	if(A->cor == Red) 
		printf("%*s%d R\n",3*n,"",A->item);
	else
		printf("%*s%d B\n",3*n,"",A->item);
	exibe(A->esq,n+1);
}

void rotacionar_esquerda(struct arv *n);
void rotacionar_direita(struct arv *n);
void insercao_caso1(struct arv *n);
void insercao_caso3(struct arv *n);
void insercao_caso4(struct arv *n);
void insercao_caso5(struct arv *n);
Arv retornaRaiz(Arv *n);

//Encontrar Avo
Arv bAvo(struct arv *n){
	if ((n != NULL) && (n->pai != NULL))
		return n->pai->pai;
	else
		return NULL;
}

//Encontrar Tio
Arv bTio(struct arv *n){
	struct arv *avo = bAvo(n);
	if (avo == NULL)
		return NULL; // Não ter avô significa não ter tio
	if (n->pai == avo->esq)
		return avo->dir;
	else
		return avo->esq;
}

//Inicio Inserção
void ins(Item x, Arv *A, Arv *Pai = NULL) {
   	if( *A == NULL ){
   		if(Pai != NULL)
   			*A = arv(x, Red, *Pai);
   		else
   			*A = arv(x, Red);
		insercao_caso1(*A);
	}
   	else if( x >= (*A)->item ) 
   		ins(x,&(*A)->dir, A);
   	else 
   		ins(x,&(*A)->esq, A);
}

void insercao_caso1(struct arv *n){
	if (n->pai == NULL){
		n->cor = Black;
	}
	else if (n->pai->cor == Black)
		return;
	else
		insercao_caso3(n);
}

void insercao_caso3(struct arv *n){
	struct arv *tio = bTio(n), *avo;

	if ((tio != NULL) && (tio->cor == Red)) {
		n->pai->cor = Black;
		tio->cor = Black;
		avo = bAvo(n);
		avo->cor = Red;
		insercao_caso1(avo);
	} else {
		insercao_caso4(n);
	}
}

void insercao_caso4(struct arv *n){
	struct arv *avo = bAvo(n);

	if ((n == n->pai->dir) && (n->pai == avo->esq)) {
		rotacionar_esquerda(n->pai);
		n = n->esq;
	} else if ((n == n->pai->esq) && (n->pai == avo->dir)) {
		rotacionar_direita(n->pai);
		n = n->dir;
	}
	insercao_caso5(n);
}

void insercao_caso5(struct arv *n){
	struct arv *avo = bAvo(n);

	n->pai->cor = Black;
	avo->cor = Red;
	if ((n == n->pai->esq) && (n->pai == avo->esq)) {
		rotacionar_direita(avo);
	} else {
		rotacionar_esquerda(avo);
	}
}
//Fim Inserção

//Rotação a esquerda
void rotacionar_esquerda(struct arv *n){
	struct arv *fd  = n->dir;
	struct arv *aux = fd->esq;
	struct arv *pai = n->pai;
	
	fd->esq = n;
	n->pai  = fd;
	
	n->dir  = aux;
	if(aux != NULL)
		aux->pai = n;
	
	if(pai != NULL)
		pai->esq = fd;
	fd->pai = pai;
}
//Rotação a direita
void rotacionar_direita(struct arv *n){
	struct arv *fe  = n->esq;
	struct arv *aux = fe->dir;
	struct arv *pai = n->pai;
	
	fe->dir = n;
	n->pai  = fe;
	
	n->esq  = aux;
	if(aux != NULL)
		aux->pai = n;
	
	if(pai != NULL)
		pai->dir = fe;
	fe->pai = pai;
}

//Usado para encontrar a nova raiz
Arv retornaRaiz(struct arv *n){
	if(n->pai == NULL)
		return n;
	else
		return retornaRaiz(n->pai);
}

void destroi(Arv *A) {
   if( *A == NULL ) return;
   destroi(&(*A)->esq);
   destroi(&(*A)->dir);
   free(*A);
   *A = NULL;
}