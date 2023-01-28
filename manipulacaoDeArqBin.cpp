#include <iostream>
#include <fstream>
using namespace std;

class athlete{
    friend athlete* pegaAtleta();
    friend void visualizaIntervalo(const int posI, const int posF);
	friend void imprimeTodos();
    private:
        int id;
        char name[60];
        char city[30];
        char sport[30];
        char event[60];
        char noc[3];
};
void visualizaIntervalo(const int posI, const int posF){
	ifstream entradaBin("arquivoBin.dat", ios::binary);
	athlete atleta;
	for(int i = posI; i <= posF; i++){
		entradaBin.seekg(i * sizeof(athlete));
		entradaBin.read(reinterpret_cast<char*>(&atleta), sizeof(athlete));
		cout << atleta.id << ',';
		cout << atleta.name << ',';
		cout << atleta.city << ',';
		cout << atleta.sport << ',';
		cout << atleta.event << ',';
		cout << atleta.noc << endl;
	}
	cout << endl;
	entradaBin.close();
}

void alteraDados(const int pos, athlete* atleta){
	ofstream saidaBin("arquivoBin.dat", ios::binary | ios::in);
	saidaBin.seekp(pos * sizeof(athlete));
	saidaBin.write(reinterpret_cast<char*>(atleta), sizeof(athlete));	
	saidaBin.close();
}

athlete* pegaAtleta(){
	athlete* atleta = new athlete;
	cout << "Digite o ID: ";
	cin >> atleta->id;
	cout << "Digite o nome: ";
	cin.ignore();
	cin.getline(atleta->name, 60);
	cout << "Digite a cidade: ";
	cin.getline(atleta->city, 30); 
	cout << "Digite o esporte: ";
	cin.getline(atleta->sport, 30);
	cout << "Digite o evento: ";
	cin.getline(atleta->event, 60);
	cout << "Digite o NOC: ";
	cin.getline(atleta->noc, 4);

	return atleta;
}
void adicionaNovoAtleta(const int pos, athlete* atleta){
	ifstream entradaBin("arquivoBin.dat", ios::binary);
	entradaBin.seekg(0, entradaBin.end);
	int tamFinal = int(entradaBin.tellg());
	entradaBin.seekg(pos * sizeof(athlete));
	int tamPos = int(entradaBin.tellg());
//Determinação do tamanho do bloco que será alocado dinamicamente
	char* blocoAtleta = new char[(tamFinal-tamPos)];
	entradaBin.read(blocoAtleta, (tamFinal-tamPos));
//Leitura de todo o bloco de dados
	entradaBin.close();

	ofstream saidaBin("arquivoBin.dat", ios::binary | ios::in);
	saidaBin.seekp(pos * sizeof(athlete));
	saidaBin.write(reinterpret_cast<char*>(atleta), sizeof(athlete));
	saidaBin.write(blocoAtleta, (tamFinal-tamPos));
//Escreve todo o bloco de dados uma posicao depois do atleta inserido
	delete[] blocoAtleta;
	saidaBin.close();
}

void imprimeTodos(){
	ifstream entradaBin("arquivoBin.dat", ios::binary);
	athlete atleta;
	int i = 0;
	entradaBin.seekg(i * sizeof(athlete));
	while(entradaBin.read(reinterpret_cast<char*>(&atleta), sizeof(athlete))){
		cout << atleta.id << ',';
		cout << atleta.name << ',';
		cout << atleta.city << ',';
		cout << atleta.sport << ',';
		cout << atleta.event << ',';
		cout << atleta.noc << endl;
		i++;
		entradaBin.seekg(i * sizeof(athlete));
	}
	cout << endl;
	entradaBin.close();
}

void trocaPos(int const posicaoI, int const posicaoF){
	ifstream entradaBin("arquivoBin.dat", ios::binary);
	int tamAthlete = sizeof(athlete);
	entradaBin.seekg(posicaoI * tamAthlete);
	char* atleta1 = new char[tamAthlete];
	entradaBin.read(atleta1, tamAthlete);

	entradaBin.seekg(posicaoF * tamAthlete);
	char* atleta2 = new char[tamAthlete];
	entradaBin.read(atleta2, tamAthlete);
	entradaBin.close();
//Alocação dinamica e leitura dos dados que terão suas posições invertidas

	ofstream saidaBin("arquivoBin.dat", ios::binary | ios::in);
	saidaBin.seekp(posicaoI * tamAthlete);
	saidaBin.write(atleta2, tamAthlete);
	delete[] atleta2;
	saidaBin.seekp(posicaoF * tamAthlete);
	saidaBin.write(atleta1, tamAthlete);
	delete[] atleta1;
//Escrita dos dados nas posições invertidas
	saidaBin.close();
}
int main(){
    ifstream entradaBin("arquivoBin.dat", ios::binary);
	if(entradaBin){
		cout << "Data Athlete Event" << endl << "* Menu de Acoes - Escolha uma opcao *" << endl << endl;
		cout << "1 - Inserir dados de um atleta em uma posicao especifica" << endl
			 << "2 - Visualizar dados de atletas" << endl
			 << "3 - Alterar os dados de um atleta" << endl
			 << "4 - Trocar a posicao de dois atletas" << endl
			 << "5 - Imprimir os dados de todos dos atletas" << endl
			 << "6 - Sair do programa" << endl;
		unsigned opcao;
		cin >> opcao;
		cout << endl;
		while(opcao != 6){
			if(opcao == 1){
				cout << "Digite a posicao em que o atleta sera inserido: ";
				int pos;
				cin >> pos;
				cout << "Digite os dados do atleta que sera inserido" << endl;
				athlete* novoAtleta = pegaAtleta();
				adicionaNovoAtleta(pos, novoAtleta);
				cout << "Informacoes do atleta inseridas com sucesso." << endl << endl;
				
			}else if(opcao == 2){
				cout << "Digite a posicao inicial de visualizacao: ";
				int posI;
				cin >> posI;
				while(posI < 0){
					cout << "A posicao nao pode ser negativa. Digite um outro valor: ";
					cin >> posI;
				}
				cout << "Digite a posicao final: ";
				int posF;
				cin >> posF;
				while(posI < 0 or posF < posI){
					cout << "A posicao final nao pode ser negativa ou menor que a inicial. Digite um outro valor: ";
					cin >> posF;
				}
				cout << "* Dados dos atletas entre as posicoes " << posI << " e " << posF << endl;
				visualizaIntervalo(posI, posF);

			}else if(opcao == 3){
				cout << "* Digite a posicao do atleta que tera seus dados alterados: ";
				int pos;
				cin >> pos;
				while(pos < 0){
					cout << "A posicao do atleta deve positiva. Digite um outro valor: ";
					cin >> pos;
				}
				cout << "* Alteracao de dados de um atleta" << endl
					 << "Digite os novos dados" << endl;
				athlete* atletaAlteracao = pegaAtleta();
				alteraDados(pos, atletaAlteracao);
				cout << "Dados alterados com sucesso." << endl << endl;

			}else if(opcao == 4){
				cout << "* Digite a primeira posicao: ";
				int posicaoI;
				cin >> posicaoI;
				while(posicaoI < 0){
					cout << "A posicao do atleta deve positiva. Digite um outro valor: ";
					cin >> posicaoI;
				}
				cout << "* Digite a segunda posicao: ";
				int posicaoF;
				cin >> posicaoF;
				while(posicaoF < 0){
					cout << "A posicao do atleta deve positiva. Digite um outro valor: ";
					cin >> posicaoF;
				}
				trocaPos(posicaoI, posicaoF);
				cout << "A troca de posicao foi realizada com sucesso." << endl << endl;
			}else if(opcao == 5){
				cout << "Impressao de todos os registros" << endl;
				imprimeTodos();
			}else{
				cout << "A opcao invalida" << endl;
			}
			cout << "Data Athlete Event" << endl << "* Menu de Acoes - Escolha uma opcao *" << endl << endl;
			cout << "1 - Inserir dados de um atleta em uma posicao especifica" << endl
				 << "2 - Visualizar dados de atletas" << endl
				 << "3 - Alterar os dados de um atleta" << endl
				 << "4 - Trocar a posicao de dois atletas" << endl
				 << "5 - Imprimir os dados de todos os atletas" << endl
				 << "6 - Sair do programa" << endl;
			cin >> opcao;
			cout << endl;
		}
		entradaBin.close();	 
    }else{
        cout << "ERRO. O arquivo binario nao pode ser aberto." << endl;
    }
    return 0;
}
