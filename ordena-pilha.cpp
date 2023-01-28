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
        void ordenaPilha(unsigned qntElementos);
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

void pilha::ordenaPilha(unsigned qntElementos){
    pilha pilhaAux;
    for(unsigned ordenados = 0; ordenados < qntElementos; ordenados++){
        int maior;
        bool primeiroDesempilhamento = 1;
        while(this->mTamanho > ordenados){
            int valorDesempilhado = this->desempilha();
            if(primeiroDesempilhamento){
                primeiroDesempilhamento = 0;
                maior = valorDesempilhado;
            }
            pilhaAux.empilha(valorDesempilhado);
            if(valorDesempilhado > maior){
                maior = valorDesempilhado;
            }
        }
        this->empilha(maior);
        while(pilhaAux.mTamanho > 0){
            int valorDesempilhado = pilhaAux.desempilha();
            if(valorDesempilhado != maior){
                this->empilha(valorDesempilhado);
            }
        }
    }
}
int main(){
    pilha pilhaOriginal;
    int qntElementos;
    cin >> qntElementos;

    int valor;
    for(int i = 0; i < qntElementos; i++){
        cin >> valor;
        pilhaOriginal.empilha(valor);
    }
    pilhaOriginal.ordenaPilha(qntElementos);
    for(int i = 0; i < qntElementos; i++){
        cout << pilhaOriginal.desempilha() << ' ';
    }
}
