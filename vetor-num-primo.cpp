#include <iostream>
using namespace std;

int main(){
	int vetorInt[9];
	int i;
	int j;
	int cont = 0;
	for(i = 0; i < 9; i++){
		cin >> vetorInt[i];
	}
	
	for(i = 0; i < 9; i++){
		for(j = 1; j <= vetorInt[i] and cont <= 2; j++){
			if(vetorInt[i] % j == 0){
				cont++;
			}
		}
		if(cont == 2){
			cout << vetorInt[i] << ' ' << i << endl;
		}
		cont = 0;
	}
	return 0;
}
