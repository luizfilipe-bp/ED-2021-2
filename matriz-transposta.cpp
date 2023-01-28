#include <iostream>
using namespace std;

int main(){
	int l;
	cin >> l;
	int c;
	cin >> c;
	int matriz[l][c];
	
	int i, j;
	for(i = 0; i < l; i++){
		for(j = 0; j < c; j++){
			cin >> matriz[i][j];
		}
	}
	
	for(i = 0; i < c; i++){
		for(j = 0; j < l; j++){
			cout << matriz[j][i] << ' ';
		}
		cout << endl;
	}
	
	return 0;
}
