#include <iostream>
using namespace std;

class noh{
    friend class pilha;
    private:
        int mValor;
        noh* mProximo;
    public:
        noh(int valor);
};
noh::noh(int valor){
    mValor = valor;
    mProximo = NULL;
}
class pilha{
    private:
        noh* mTopo;
        unsigned mTamanho;
    public:   
        pilha();
        ~pilha();
        unsigned tamanho();
        void empilha(int valor);
        int desempilha();
        void limpaPilha();
        bool vazia();
};
pilha::pilha(){
    mTopo = NULL;
    mTamanho = 0;
}
pilha::~pilha(){
    limpaPilha();
}
void pilha::limpaPilha(){
    while(mTamanho > 0){
        desempilha();
    }
}
unsigned pilha::tamanho(){
    return mTamanho;
}
bool pilha::vazia(){
    return(mTamanho == 0);
}
void pilha::empilha(int valor){
    //cout << "topo antes de empilhar: "<< mTopo << endl;

    noh* novo = new noh(valor);         //instancia um novo nó
    novo->mProximo = mTopo;             //o endereço do proximo do novo nó é apontado pro topo
    mTopo = novo;                       //topo aponta para o novo nó
    mTamanho++;                         //aumenta em um o tamanho da pilha

    //cout << "topo depois de empilhar: "<< mTopo << endl;
    //cout << "proximo noh do topo: "<< mTopo->mProximo << endl;
}
int pilha::desempilha(){
    int valor = mTopo->mValor;          //pega valor do topo
    noh* temp = mTopo;                  //noh temporario aponta para o topo
    mTopo = mTopo->mProximo;            //o topo vai apontar para o proximo nó
    delete temp;                        //deleta o nó temporario
    mTamanho--;                         //reduz o tamanho da pilha
    return valor;                       //retorna o valor inicial do topo
}
int main(){
    pilha p1;
    int qntElementos;
    cin >> qntElementos;
    int num;
    for(int i = 0; i < qntElementos; i++){
        cin >> num;
        p1.empilha(num);
    }

    cout << "tamanho pilha: " << p1.tamanho() << endl;
    cout << "elementos: ";
    while(not p1.vazia()){
        cout << p1.desempilha() << ' ';
    }
}