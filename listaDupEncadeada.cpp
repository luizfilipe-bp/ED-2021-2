#include <iostream>

using namespace std;

class noh{
    friend class listaDup;
    private:
        noh* mAnterior;
        noh* mProximo;
        int mDado;
    public:
        noh(int valor);
};
noh::noh(int valor){
    mDado = valor;
    mAnterior = NULL;
    mProximo = NULL;
}
class listaDup{
    private:
        noh* mInicio;
        noh* mFim;
        int mTamanho;
        bool vazia();
    public:
        listaDup();
        ~listaDup();
        void removeTodos();
        void insereInicio(int valor);
        void insereFim(int valor);
        void insereEmPos(int valor, int pos);
        void imprime();
        void removeInicio();
        void removeFim();
        int procura(int valorProcurado);
};
listaDup::listaDup(){
    mInicio = NULL;
    mFim = NULL;
    mTamanho = 0;
}
void listaDup::removeTodos(){
    noh* aux = mInicio;
    noh* nohDeletado;
    while(aux != NULL){
        nohDeletado = aux;
        aux = aux->mProximo;
        delete nohDeletado;
    }
    mTamanho = 0;
    mInicio = NULL;
    mFim = NULL; 
}
listaDup::~listaDup(){
    removeTodos();
}
bool listaDup::vazia(){
    return (mTamanho == 0);
}
void listaDup::insereInicio(int valor){
    noh* novoNoh = new noh(valor);
    if(vazia()){
        mInicio = novoNoh;
        mFim = novoNoh;
    }else{
        mInicio->mAnterior = novoNoh;
        novoNoh->mProximo = mInicio;
        mInicio = novoNoh;
    }
    mTamanho++;
}
void listaDup::insereFim(int valor){
    noh* novoNoh = new noh(valor);
    if(vazia()){
        mInicio = novoNoh;
        mFim = novoNoh;
    }else{
        mFim->mProximo = novoNoh;
        novoNoh->mAnterior = mFim;
        mFim = novoNoh;
    }
    mTamanho++;
}
void listaDup::insereEmPos(int valor, int pos){
    noh* novoNoh = new noh(valor);
    if(vazia()){
        mInicio = novoNoh;
        mFim = novoNoh;
    }else if(pos == 0){
        mInicio->mAnterior = novoNoh;
        novoNoh->mProximo = mInicio;
        mInicio = novoNoh;
    }else if(pos == mTamanho){
        mFim->mProximo = novoNoh;
        novoNoh->mAnterior = mFim;
        mFim = novoNoh;
    }else{
        noh* aux = mInicio;
        int posAux = 0;
        while(posAux != (pos - 1)){
            aux = aux->mProximo;
            posAux++;
        }
        novoNoh->mProximo = aux->mProximo;
        aux->mProximo->mAnterior = novoNoh;
        aux->mProximo = novoNoh;
        novoNoh->mAnterior = aux;
    }
    mTamanho++;
}
void listaDup::imprime(){
    noh* aux = mInicio;
    while(aux != NULL){
        cout << aux->mDado << ' ';
        aux = aux->mProximo;
    }
    cout << endl;
    aux = mFim;
    while(aux != NULL){
        cout << aux->mDado << ' ';
        aux = aux->mAnterior;
    }
    cout << endl;
}
void listaDup::removeInicio(){
    if(vazia()){
        cout << "Lista vazia" << endl;
    }else{
        noh* nohRemovido = mInicio;
        mInicio = mInicio->mProximo;
        if(mInicio != NULL){
            mInicio->mAnterior = NULL;
        }
        delete nohRemovido;
        mTamanho--;
        if(vazia()){
            mFim = NULL;
        }
    }
}
void listaDup::removeFim(){
    if(vazia()){
        cout << "Lista vazia" << endl;
    }else{
        noh* nohRemovido = mFim;
        mFim = mFim->mAnterior;
        if(mFim != NULL){
            mFim->mProximo = NULL;
        }
        delete nohRemovido;
        mTamanho--;
        if(vazia()){
            mInicio = NULL;
        }
    }
}
int listaDup::procura(int valorProcurado){
    noh* aux = mInicio;
    int posProcurado = 0;
    while((aux->mDado != valorProcurado) and (aux != NULL)){
        aux = aux->mProximo;
        posProcurado++;
    }
    if(aux == NULL){
        posProcurado = -1;
    }
    return posProcurado;
}
int main(){
    listaDup lista;
    lista.insereInicio(25);
    lista.insereInicio(20);
    lista.insereFim(30);
    lista.insereInicio(14);
    lista.insereEmPos(99, 2);
    lista.insereFim(33);
    lista.imprime();
    cout << endl;

    lista.removeInicio();
    lista.imprime();
    lista.removeFim();
    lista.imprime();

    cout << "pos do 99: " << lista.procura(99) << endl;
    cout << "pos do 30: " << lista.procura(30) << endl;
    cout << "pos do 03: " << lista.procura(3) << endl;
    
}
