/*
        *Estruturas de Dados - REO01 - Tarefa 1 Etapa 2*
Aluno: Luiz Filipe Bartelega Penha
Matricula: 202111082
Turma: 10A

    Todas as entradas devem ser realizadas pelo usuário. As quantidades de especies e fornecedores a serem
cadastrados são definidas pelo usuário. A busca por um fornecedor ocorre uma única vez.
*/
#include <iostream>

using namespace std;

class especie{
    friend class agricultor;
    private:
        string nome;
        string periodoPlantio;
        string tempoProducao;
};

class fornecedor{
    friend class agricultor;
    private:
        string nome;
        string produtoInteresse;
        string telefoneContato;
};

class agricultor{
    private:
        especie *listaDeEspecies;
        fornecedor *listaDeFornecedores;
        int mQntFornecedores;
        int mQntEspecies;
    public:
        agricultor(int qntEspecies, int qntFornecedores);
        ~agricultor();
        void registaEspecies();
        void registraFornecedores();
        void buscaFornecedores(string nomeProduto);
};

agricultor::agricultor(int qntEspecies, int qntFornecedores){
    mQntEspecies = qntEspecies;
    mQntFornecedores = qntFornecedores;
    listaDeEspecies = new especie[mQntEspecies];
    listaDeFornecedores = new fornecedor[mQntFornecedores];
}

agricultor::~agricultor(){
    mQntEspecies = 0;
    mQntFornecedores = 0;
    delete[] listaDeEspecies;
    delete[] listaDeFornecedores;
    listaDeEspecies = NULL;
    listaDeFornecedores = NULL;
}

void agricultor::registaEspecies(){
    if(listaDeEspecies){
        cin.ignore();
        cout << endl << "Registro de especies" << endl;
        for(int i = 0; i < mQntEspecies; i++){
            cout << '\t' << "Especie " << i + 1 << endl;
            cout << "Digite o nome da especie: ";
            getline(cin, listaDeEspecies[i].nome);
            cout << "Digite o periodo de plantio dessa especie: ";
            getline(cin, listaDeEspecies[i].periodoPlantio);
            cout << "Digite o tempo de producao dessa especie: ";
            getline(cin, listaDeEspecies[i].tempoProducao);
        }
        
    }
}

void agricultor::registraFornecedores(){
    if(listaDeFornecedores){
		cout << endl << "Registro de Fornecedores" << endl;
        for(int i = 0; i < mQntFornecedores; i++){
            cout << '\t' << "Fornecedor " << i + 1 << endl;
            cout << "Digite o nome do fornecedor: ";
            getline(cin, listaDeFornecedores[i].nome);
            cout << "Digite o produto de seu interesse: ";
            getline(cin, listaDeFornecedores[i].produtoInteresse);
            cout << "Digite o telefone para contato: ";
            getline(cin, listaDeFornecedores[i].telefoneContato);
        }
    }
}

void agricultor::buscaFornecedores(string nomeProduto){
    if(listaDeFornecedores){    
        bool encontrado = 0;
        cout << endl << "Resultado da busca de fornecedores" << endl;
        for(int i = 0; i < mQntFornecedores; i++){
            if(nomeProduto == listaDeFornecedores[i].produtoInteresse){
                cout << "Nome: " << listaDeFornecedores[i].nome << '\t';
                cout << "Telefone: " << listaDeFornecedores[i].telefoneContato << endl;
                encontrado = 1;
            }
        }
        if(!encontrado){
            cout << "Nao ha fornecedores que possuem esse produto para venda!!!" << endl;
        }
    }
}

int main(){
    int qntEspecies;
    cout << "Digite a quantidade de especies que serao cadastradas: ";
    cin >> qntEspecies;

    int qntFornecedores;
    cout << "Digite a quantidade de fornecedores que serao cadastrados: ";
    cin >> qntFornecedores;

    agricultor *ptrMorgana = new agricultor(qntEspecies, qntFornecedores);
    ptrMorgana->registaEspecies();
    ptrMorgana->registraFornecedores();

    string nomeProduto;
    cout << endl << "Digite o nome do produto de seu interesse para buscar os fornecedores: ";
    getline(cin, nomeProduto);
    ptrMorgana->buscaFornecedores(nomeProduto);

    ptrMorgana->~agricultor();
}
