#include <iostream>

using namespace std;

// função de hash utilizada para cálculo da posição
const int UMPRIMO = 83;
int funcaoHash(string s, int M) {
    long h = 0;
    for (unsigned i = 0; i < s.length(); i++) {
        h = (UMPRIMO * h + s[i]) % M;  
    }
    return h;
}

// classe noh armazena um par chave/valor em uma tabela hash
// com tratamento de colisão por encadeamento
class noh {
    friend class tabelaHash;
    private:
        string chave;
        string valor;
        noh* proximo;
    public:
        noh(){
            chave = "";
            valor = "";
            proximo = NULL;
        }
};

// tabela hash com colisão por encadeamento (usando lista implícita)
class tabelaHash {
    private:
        // vetor de ponteiros de nós (lista implícita para tratar colisões)
        noh** elementos;
        int capacidade;
    public:
        // construtor padrão
        tabelaHash(int cap = 100);
        // destrutor
        ~tabelaHash();
        // insere um valor v com chave c
        void insere(string c, string v);
        // recupera um valor associado a uma dada chave
        string recupera(string c);
        // percorrendo a tabela hash (para fins de depuração)
        void percorre();
};

// construtor padrão
tabelaHash::tabelaHash(int cap) {
    elementos = new noh*[cap];
    capacidade = cap;

    for (int i = 0; i < cap; i++) {
        elementos[i] = NULL;
    }
}

// destrutor
tabelaHash::~tabelaHash() {
    for (int i=0; i < capacidade; i++) {
        noh* atual = elementos[i];

        // percorre a lista removendo todos os nós
        while (atual != NULL) {
            noh* aux = atual;
            atual = atual-> proximo;
            delete aux;
        }
    }
    delete[] elementos;
}

// insere um valor v com chave c
void tabelaHash::insere(string c, string v){
    unsigned pos = funcaoHash(c, capacidade);
//Inserção da chave e valor no primeiro elemento da lista

    if(elementos[pos] == NULL){
        elementos[pos] = new noh;
        elementos[pos]->chave = c;
        elementos[pos]->valor = v;
//Inserção no final da lista
    }else{
        noh* novoNoh = new noh;
        novoNoh->chave = c;
        novoNoh->valor = v;
//Percorre a lista até seu último elemento
        noh* lista = elementos[pos];
        while(lista->proximo != NULL){
            lista = lista->proximo;
        }
//Insere o novo noh ao final da lista
        lista->proximo = novoNoh;
    }
}

// recupera um valor associado a uma dada chave
string tabelaHash::recupera(string c) {
    unsigned pos = funcaoHash(c, capacidade);
    noh* lista = elementos[pos];
//String para armazenar os valores associados a uma chave
    string valores;
//Percorrendo a lista e concatenando os valores 
    while((lista != NULL)){
        if(lista->chave == c){
            valores = valores + lista->valor;
        }
        lista = lista->proximo;
    }
//Verifica se valores armazenou algum dado
    if(valores.length()){
        return valores;
    }else{
        return "";
    }
}

// percorrendo a tabela hash (para fins de depuração)
void tabelaHash::percorre() {
    noh* atual;
    for (int i = 0; i < capacidade; i++) {
        cout << i << ":";
        atual = elementos[i];
        while (atual != NULL) {
            cout << "[" << atual->chave << "/"
                 << atual->valor << "]->";
            atual = atual->proximo;

        }
        cout << "NULL  ";
    }
    cout << endl;
}

int main(){
    int capacidade;
    cin >> capacidade;

    tabelaHash hash(capacidade);
    string chave;
    string valor;

    char opcao;
    cin >> opcao;
    while (opcao != 'Q') {
        switch(opcao) {
            case 'I':
                cin >> chave;
                cin >> valor;
                hash.insere(chave,valor);
                break;
            case 'R':
                cin >> chave;
                cout << hash.recupera(chave) << endl;
                break;
            case 'P':
                hash.percorre();
                break;
        }
        cin >> opcao;
    }

    return 0;
}
