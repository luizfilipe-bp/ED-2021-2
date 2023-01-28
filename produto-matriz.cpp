#include <iostream>
using namespace std;

int main(){
	int matriz1[4][5];
	int matriz2[5][2];
	
	int l, c;
	for(l = 0; l < 4; l++){
		for(c = 0; c < 5; c++){
			cin >> matriz1[l][c];
		}
	}
	for(l = 0; l < 5; l++){
		for(c = 0; c < 2; c++){
			cin >> matriz2[l][c];
		}
	}
	int produto = 0;
	int soma = 0;
	for(l = 0; l < 4; l++){
		for(c = 0; c < 5; c++){
			produto = matriz1[l][c] * matriz2[c][0];
			soma += produto;
		}
		cout << soma << ' ';
		soma = 0;
		for(c = 0; c < 5; c++){
			produto = matriz1[l][c] * matriz2[c][1];
			soma += produto;
		}
		cout << soma << endl;
		soma = 0;
	}	
	
	return 0;
}
