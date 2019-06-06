#include <iostream>
#include <assert.h>
#include <stdio.h> 
#include <stdlib.h>
#include <conio.h>

using namespace std;

#define fmt "%d ";
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

Arv busca_No(Item x, Arv A){
    if( A == NULL ) 
		return NULL;
   	if( x == A->item ) 
	   	return A;
   	if( x <= A->item ) 
	   	return busca_No(x,A->esq);
   	else 
	   	return busca_No(x,A->dir);
}

Cor b_cor(Arv A){
	if(A == NULL)
		return Black;
	else
		return A->cor;
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

void destroi(Arv *A) {
   if( *A == NULL ) return;
   destroi(&(*A)->esq);
   destroi(&(*A)->dir);
   free(*A);
   *A = NULL;
}

void rotacionar_esquerda(struct arv *n);
void rotacionar_direita(struct arv *n);
void insercao_caso1(struct arv *n);
void insercao_caso3(struct arv *n);
void insercao_caso4(struct arv *n);
void insercao_caso5(struct arv *n);
void remocao_caso1(struct arv *n);
void remocao_caso2(struct arv *n);
void remocao_caso3(struct arv *n);
void remocao_caso4(struct arv *n);
void remocao_caso5(struct arv *n);
void remocao_caso6(struct arv *n);
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

Arv bIrmao(struct arv *n){
	if(n == n->pai->esq)
		return n->pai->dir;
	else
		return n->pai->esq;
}

void trocarNos(Arv oldn, Arv newn) {
    if (oldn->pai != NULL){
        if (oldn == oldn->pai->esq)
            oldn->pai->esq = newn;
        else
            oldn->pai->dir = newn;
    }
    if (newn != NULL) {
        newn->pai = oldn->pai;
    }
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
	Arv r = n->dir;

    trocarNos(n,r);
    n->dir = r->esq;
    if (r->esq != NULL) {
        r->esq->pai = n;
    }
    r->esq = n;
    n->pai = r;
	
}
//Rotação a direita
void rotacionar_direita(struct arv *n){
    Arv r = n->esq;

    trocarNos(n,r);
    n->esq = r->dir;
    if (r->dir != NULL) {
        r->dir->pai = n;
    }
    r->dir = n;
    n->pai = r;
}

//Usado para encontrar a nova raiz
Arv retornaRaiz(struct arv *n){
	if(n->pai == NULL)
		return n;
	else
		return retornaRaiz(n->pai);
}

Arv max_no(Arv A) {
   	if( A == NULL ) 
   		abort();
   	while( A->dir != NULL ){
	   	A = A->dir;
	}
    return A;
}

void rem(Item x, Arv *A) {
    
    Arv n = busca_No(x, *A), filho;
    if (n == NULL) return; 
    if (n->esq != NULL && n->dir != NULL) {
        Arv sucessor = max_no(n->esq);
        n->item   = sucessor->item;
        n = sucessor;
    }

    if(n->esq == NULL)
        filho = n->dir;		
    else if ( n->dir == NULL ) 
        filho = n->esq;
    
    if (n->cor == Black) {
        n->cor = b_cor(filho);
        remocao_caso1(n);
    }
    trocarNos(n, filho);
    if (n->pai == NULL && filho != NULL)
        filho->cor = Black;
    free(n);

    //verify_properties(t);
}
void remocao_caso1(struct arv *n){
	//O primeiro caso verifica se o pai do nó não é nulo, se for vai para o segundo caso.
	if(n->pai != NULL)
		remocao_caso2(n);
}
void remocao_caso2(struct arv *n){
	//No segundo caso, 
	//se o nó e seu pai forem pretos e seu irmão for vermelho o pai deve ser pintado de vermelho e o irmão de preto e 
	//então se o nó for filho esquerdo, faz a rotação à esquerda de seu pai e vai pro próximo caso, 
	//se for filho direito, rotaciona o pai à direita e vai pro próximo caso.
	struct arv *pai = n->pai, *irmao = bIrmao(n);
	if(n->cor == Black && pai->cor == Black && b_cor(irmao) == Red){
		pai->cor = Red;
		irmao->cor = Black;
		if(n == pai->esq)
			rotacionar_esquerda(pai);
		else
			rotacionar_direita(pai);
	}
	remocao_caso3(n);
}
void remocao_caso3(struct arv *n){
	//Nesse caso, 
	//se o pai do nó, o irmão, o filho esquerdo e direito do irmão forem todos pretos, 
	//pinta o irmão de vermelho e volte para o primeiro caso com o pai do nó, 
	//se não forem vai pro próximo caso.
	struct arv *pai = n->pai, *irmao = bIrmao(n);
	if(pai->cor == Black && b_cor(irmao) == Black && b_cor(irmao->esq) == Black && b_cor(irmao->dir) == Black){
		irmao->cor = Red;
		remocao_caso1(pai);
	}
	else{
		remocao_caso4(n);
	}	
}
void remocao_caso4(struct arv *n){
	//No quarto caso, 
	//se o irmão e o filho esquerdo e direito do irmão forem pretos e o pai do nó for vermelho, 
	//deve pintar o irmão de vermelho e o pai do nó de preto, 
	//se não deve prosseguir para o próximo caso.
	struct arv *pai = n->pai, *irmao = bIrmao(n);
	if(pai->cor == Red && b_cor(irmao) == Black && b_cor(irmao->esq) == Black && b_cor(irmao->dir) == Black){
		irmao->cor = Red;
		pai->cor = Black;
	}else{
		remocao_caso5(n);
	}
	
}
void remocao_caso5(struct arv *n){
	//No quinto caso, se o nó for filho esquerdo e o filho direito do irmão for preto 
	//deverá pintar o irmão de vermelho e o filho esquerdo do irmão de preto e aí sim rotacionar à direita o irmão, 
	//mas se o nó for filho direito deverá pintar o irmão de vermelho e o filho direito do irmão de preto e então rotacionar para esquerda o irmão, 
	//indo para o último caso.
	struct arv *pai = n->pai, *irmao = bIrmao(n);
    if(b_cor(irmao) == Black && b_cor(irmao->esq) == Red && b_cor(irmao->dir) == Black){
        irmao->cor = Red;
        if(n == pai->esq){
            irmao->esq->cor = Black;
            rotacionar_direita(irmao);    
        }else{
            irmao->dir->cor = Black;
            rotacionar_esquerda(irmao);
        }
    }
	remocao_caso6(n);
}
void remocao_caso6(struct arv *n){
	//Ao chegar no último caso deverá pintar o pai do nó de preto, 
	//caso o nó seja filho esquerdo, pinta o filho direito do irmão do nó de preto e rotaciona o pai do nó para a esquerda, 
	//se o nó for filho direito, 
	//pinta o filho esquerdo do irmão de preto e rotaciona o pai para direita.
	struct arv *pai = n->pai, *irmao = bIrmao(n);
	pai->cor = Black;
	if(n == pai->esq){
		assert (b_cor(irmao->dir) == Red);
		irmao->dir->cor = Black;
		rotacionar_esquerda(pai);
	}else{
		assert (b_cor(irmao->esq) == Red);
		irmao->esq->cor = Black;
		rotacionar_direita(pai);
	}
}


int main(int argc, char** argv) {

	int opcao, num;
	Arv I;
	do{
		system("cls");
		cout << "|-------Arvore Rubro Negra-------|\n";
		cout << "|--------------------------------|\n";
		cout << "|Escolha uma opcao e aperte ENTER|\n";
		cout << "|    1 - Inserir Elemento        |\n";
		cout << "|    2 - Remover Elemento        |\n";
		cout << "|    3 - Exibir arvore           |\n";
		cout << "|    4 - Buscar Elemento         |\n";
		cout << "|    5 - Destruir arvore         |\n";
		cout << "|    0 - Sair                    |\n";
		cout << "|--------------------------------|\n";
		cin >> opcao;
		system("cls");
		switch(opcao){
			case 1:
				cout << "Digite o numero que deseja inserir: ";
				cin >> num;
				ins(num, &I);
				I = retornaRaiz(I);//Necessario pois a raiz pode mudar
				break;
			case 2:
				cout << "Digite o numero que deseja remover: ";
				cin >> num;
				rem(num, &I);
				I = retornaRaiz(I);
				break;
			case 3:
				cout << "\n\n";
				if(I != NULL)
					exibe(I);
				else
					cout << "Arvore Vazia";
				getch();
				break;
			case 4:
				cout << "Digite o numero que deseja buscar: ";
				cin >> num;
				if(busca(num, I))
					cout << num << " foi encontrado na arvore.";
				else
					cout << num << " nao esta na arvore.";
				getch();
				break;
			case 5:
				destroi(&I);
				cout << "Arvore foi destruida.";
				break;
			case 0:
				break;
			default:
				cout << "Opcao Invalida.";
				getch();
				break;
		}
		
	}while(opcao != 0);
	
	system("exit");
}
