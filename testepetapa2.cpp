#include <iostream>
#include <string>

using namespace std;

class especie{
    private:
        string nomeEspecie;
        string periodoPlantio;
        string tempoProducao;

    public:                    //especie (*vec[]) --> está errado ? 
        void registraEspecies(especie vec[], int qntEspecies);
        void mostraObj(especie vec[]);

};

void especie:: mostraObj(especie vec[]){
    cout << vec[0].nomeEspecie << '\t' << vec[0].periodoPlantio << '\t' << vec[0].tempoProducao;
}
void especie::registraEspecies(especie *vec, int qntEspecies){
        for(int i = 0; i < qntEspecies; i++){
            cout << "Especie de planta " << i + 1 << endl; 
            cout << "Digite o nome da especie: ";
            cin >> vec[i].nomeEspecie;
            cout << "Digite o periodo de plantio: ";
            cin >> vec[i].periodoPlantio;
            cout << "Digite o tempo de producao: ";
            cin >> vec[i].tempoProducao;
        }
        
        for(int i = 0; i < qntEspecies; i++){
            cout << vec[i].nomeEspecie << "\t";
            cout << vec[i].periodoPlantio << "\t";
            cout << vec[i].tempoProducao << endl;
        
        }
}

int main(){
    int qntEspecies;
    cout << "Digite a quantidade de especies a serem cadastradas: ";
    cin >> qntEspecies;
    
    especie *plantas = new especie[qntEspecies];
    plantas->registraEspecies(plantas, qntEspecies);
                             // (&plantas, qntEspecies) --> está errado ? 
    delete[] plantas;
  //  plantas = NULL;
    
    //Continua o pragrama mesmo depois de desalocar plantas, isso deveria acontecer?
   // plantas->registraEspecies(plantas, qntEspecies);
    plantas->mostraObj(plantas);

    cout << endl << endl;
    int *vet = new int[10];
    for(int i = 0; i < 10; i++){
        cin >> vet[i];
    }
    for(int i = 0; i < 10; i++){
        cout << vet[i];
    }
    cout << endl;
    delete[] vet;

    for(int i = 0; i < 10; i++){
        cout << vet[i] << ' ';
    }
}