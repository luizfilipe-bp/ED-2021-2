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
        void empilha(int valor);
        int desempilha();
        void ordenaPilha();
};
pilha::pilha(){
    mTopo = NULL;
    mTamanho = 0;
}
void pilha::empilha(int valor){
    noh* novo = new noh(valor);         
    novo->mProximo = mTopo;             
    mTopo = novo;                       
    mTamanho++;                         
}
int pilha::desempilha(){
    int valor = mTopo->mValor;          
    noh* temp = mTopo;                  
    mTopo = mTopo->mProximo;            
    delete temp;                        
    mTamanho--;                         
    return valor;                       
}

void pilha::ordenaPilha(){
    pilha pilhaAux;
    while(this->mTamanho > 0){
        int menor;
        bool primeiroDesempilhamento = 1;
        while(this->mTamanho > 0){
            int valorDesempilhado = this->desempilha();
            if(primeiroDesempilhamento){
                primeiroDesempilhamento = 0;
                menor = valorDesempilhado;
            }
            pilhaAux.empilha(valorDesempilhado);
            if(valorDesempilhado < menor){
                menor = valorDesempilhado;
            }
        }
        while(pilhaAux.mTamanho > 0){
            int valorDesempilhado = pilhaAux.desempilha();
            if(valorDesempilhado == menor){
                cout << menor << ' ';
            }else{
                this->empilha(valorDesempilhado);
            }
        }
    }

}
int main(){
    pilha pilhaOriginal;
    int capacidade;
    cin >> capacidade;

    int valor;
    for(int i = 0; i < capacidade; i++){
        cin >> valor;
        pilhaOriginal.empilha(valor);
    }
    pilhaOriginal.ordenaPilha();
}