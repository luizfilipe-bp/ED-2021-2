#include <iostream>

using namespace std;

class noh{
    friend class fila;
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
class fila{
    private:
        noh* mInicio;
        noh* mFim;
        unsigned mTamanho;
    public:   
        fila();
        ~fila();
        unsigned tamanho();
        void enfileira(int valor);
        int desenfileira();
        void limpaPilha();
        bool vazia();
};
fila::fila(){
    mInicio = NULL;
    mFim = NULL;
    mTamanho = 0;
}
fila::~fila(){
    limpaPilha();
}
void fila::limpaPilha(){
    while(mTamanho > 0){
        desenfileira();
    }
}
unsigned fila::tamanho(){
    return mTamanho;
}
bool fila::vazia(){
    return(mTamanho == 0);
}
void fila::enfileira(int valor){
    noh* novo = new noh(valor);         //instancia novo nó
    if(mTamanho == 0){                  //se a fila estiver vazia o inicio será o nó
        mInicio = novo;
    }else{                              //caso contrario o nó será será apontado como próximo do topo atual
        mFim->mProximo = novo;
    }
    mFim = novo;                        //novo nó se torna o topo/fim
    mTamanho++;
}
int fila::desenfileira(){
    int valor = mInicio->mValor;        //copia o valor do noh
    noh* temp = mInicio;                //cria um aux
    mInicio = mInicio->mProximo;        //aponta o inicio para o proximo no
    delete temp;                        //apaga o nó retirado
    mTamanho--;                         //decrementa o tamanho
    if(mTamanho == 0){                  //se a pilha acabar o fim deve apontar para NULL
        mFim = NULL;
    }
    return valor;
}
int main(){
    fila f1;
    int num;
    cin >> num;

    while(num >= 0){
        f1.enfileira(num);
        cin >> num;
    }

    cout << "tamanho pilha: " << f1.tamanho() << endl;

    cout << "elementos: ";
    while(not f1.vazia()){
        cout << f1.desenfileira() << ' ';
    }
}