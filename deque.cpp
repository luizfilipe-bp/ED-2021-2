#include <iostream>

using namespace std;
class noh{
    friend class Deque;
    private:
        noh* mProximo;
        noh* mAnterior;
        int mDado;
    public:
        noh(int valor);
};
noh::noh(int valor){
    mProximo = NULL;
    mAnterior = NULL;
    mDado = valor;
}
class Deque{
    private:
        noh* esq;
        noh* dir;
        int mTamanho;
    public:
        Deque();
        bool vazia();
        void insereDir(int valor);
        void insereEsq(int valor);
        void removeDir();
        void removeEsq();
        void imprime();
};
Deque::Deque(){
    esq = NULL;
    dir = NULL;
    mTamanho = NULL;
}
bool Deque::vazia(){
    return (mTamanho == 0);
}
void Deque::insereDir(int valor){
    noh* novoNoh = new noh(valor);
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
void Deque::insereEsq(int valor){
    noh* novoNoh = new noh(valor);
    if(vazia()){
        esq = novoNoh;
        dir = novoNoh;
    }else{
        novoNoh->mProximo = esq;
        esq->mAnterior = novoNoh;
        esq = novoNoh;
    }
    mTamanho++;
}
void Deque::removeDir(){
    if(vazia()){
        cout << "Lista vazia" << endl;
    }else{
        noh* aux = dir;
        dir = dir->mAnterior;
        if(dir != NULL){
            dir->mProximo = NULL;
        }
        delete aux;
        mTamanho--;
        if(vazia()){
            esq = NULL;
        }
        
    }
}
void Deque::removeEsq(){
    if(vazia()){
        cout << "Lista vazia" << endl;
    }else{
        noh* aux = esq;
        esq = esq->mProximo;
        if(esq != NULL){
            esq->mAnterior = NULL;
        }
        delete aux;
        mTamanho--;
        if(vazia()){
            dir = NULL;
        }
    }
}
void Deque::imprime(){
    noh* aux = esq;
    while(aux != NULL){
        cout << aux->mDado << ' ';
        aux = aux->mProximo;
    }
    cout << endl;
    aux = dir;
    while(aux != NULL){
        cout << aux->mDado << ' ';
        aux = aux->mAnterior;
    }
    cout << endl;
}
int main(){
    Deque deque;
    deque.insereDir(1);
    deque.insereDir(2);
    deque.insereEsq(3);
    deque.insereEsq(4);
    deque.insereDir(5);
    deque.imprime();

    deque.removeDir();
    deque.imprime();
    deque.removeDir();
    deque.imprime();
    
    deque.removeEsq();
    deque.imprime();
    deque.removeEsq();
    deque.imprime();
    deque.removeEsq();
    deque.imprime();
}