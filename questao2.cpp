#include <iostream>

using namespace std;
//Classe de nós de string
class nohStr{
    friend class Deque;
    private:
        nohStr* mProximo;
        nohStr* mAnterior;
        string mComando;
    public:
        nohStr(string comando);
};
nohStr::nohStr(string comando){
    mProximo = NULL;
    mAnterior = NULL;
    mComando = comando;
}
//Deque com capacidade definida pelo usuário
class Deque{
    private:
        nohStr* esq;
        nohStr* dir;
        int mTamanho;
        int mCapacidade;
    public:
        Deque(int capacidade);
        ~Deque();
        bool vazia();
        void insere(string comando);
        void undo();
        void removeEsq();
};
//Construtor da Deque
Deque::Deque(int capacidade){
    esq = NULL;
    dir = NULL;
    mTamanho = 0;
    mCapacidade = capacidade;
}
//Destrutor da Deque
Deque::~Deque(){
    nohStr* aux = esq;
//Percorre o deque removendo os nós
    while(aux != NULL){
        nohStr* removido = aux;
        aux = aux->mProximo;
        delete removido;
    }
    esq = NULL;
    dir = NULL;
    mTamanho = 0;
    mCapacidade = 0;
}
//Verificação de se a Deque está vazia
bool Deque::vazia(){
    return (mTamanho == 0);
}
//Armazenamento do comando inserido 
void Deque::insere(string comando){
    nohStr* novoNoh = new nohStr(comando);
    //Verifica se a capacidade máxima foi atingida
    if(mTamanho == mCapacidade){
        removeEsq();
    }
    if(vazia()){
        esq = novoNoh;
        dir = novoNoh;
    }else{
        novoNoh->mAnterior = dir;
        dir->mProximo = novoNoh;
        dir = novoNoh;
    }
    mTamanho++;
}
//Função que remove o último elemento, elemento a direita. (comando que é desfeito)
//Se a Deque está vazia imprime um erro
void Deque::undo(){
    if(vazia()){
        cout << "ERRO" << endl;
    }else{
        nohStr* aux = dir;
        string cmdDesfeito = aux->mComando;
        dir = dir->mAnterior;
        if(dir != NULL){
            dir->mProximo = NULL;
        }
        delete aux;
        mTamanho--;
        if(vazia()){
            esq = NULL;
        }
        cout << "desfazer: " << cmdDesfeito << endl;
    }
}
//Função para remover o elemento da esquerda do Deque (elemento que é esquecido)
void Deque::removeEsq(){
    nohStr* aux = esq;
    string cmdEsquecido = aux->mComando;
    esq = esq->mProximo;
    if(esq != NULL){
        esq->mAnterior = NULL;
    }
    delete aux;
    mTamanho--;
    if(vazia()){
        dir = NULL;
    }
    cout << "esqueci: " << cmdEsquecido << endl;
}
int main(){
    int capacidade;
    cin >> capacidade;
    Deque dequeUndo(capacidade);

    string comando;
    cin.ignore();
    do{
        getline(cin, comando); 
        if(comando == "undo"){
            dequeUndo.undo();
        }else{
            dequeUndo.insere(comando);
        }
    }while(comando != "sair");
}