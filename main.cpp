#include <iostream>
#include <arvRN.h>
#include <stdio.h> 
#include <stdlib.h>
#include <conio.h>

using namespace std;

int main(int argc, char** argv) {
	/*
	Arv I = arv(NULL, 7, NULL, NULL, Black);
	ins(4, &I);
	ins(9, &I);
	ins(5, &I);
	exibe(I,0);//Exibir
	cout << "---------------------------------------------------------------------\n";
	ins(6, &I);
	exibe(I,0);//Exibir
	cout << "---------------------------------------------------------------------\n";
	ins(8, &I);
	ins(7, &I);
	ins(7, &I);
	exibe(I,0);
	*/
	int opcao, num;
	Arv I;
	do{
		system("cls");
		cout << "|-------Arvore Rubro Negra-------|\n";
		cout << "|--------------------------------|\n";
		cout << "|Escolha uma opcao e aperte ENTER|\n";
		cout << "|    1 - Inserir Elemento        |\n";
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
			case 3:
				cout << "\n\n";
				exibe(I);
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
