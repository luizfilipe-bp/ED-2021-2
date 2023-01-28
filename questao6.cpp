#include <iostream>

using namespace std;

class filaCircular{
    private:
        int mInicio;
        int mFim;
        int* mDados;
        unsigned mCapacidade;       //Capacidade do vetor
        unsigned mTamanho;          //Quantidade de dados armazenados
    public:   
        filaCircular(unsigned capacidade);
        ~filaCircular();
        unsigned tamanho();
        unsigned capacidade();
        unsigned inicio();
        unsigned fim();
        void enfileira(int dado);
        int desenfileira();
        int* copiaDados();
};
filaCircular::filaCircular(unsigned capacidade){
    mCapacidade = capacidade;
    mDados = new int[mCapacidade];
    mTamanho = 0;
}
filaCircular::~filaCircular(){
    delete[] mDados;
}

unsigned filaCircular::tamanho(){
    return mTamanho;
}
unsigned filaCircular::capacidade(){
    return mCapacidade;
}
unsigned filaCircular::inicio(){
    return mInicio;
}
unsigned filaCircular::fim(){
    return mFim;
}

void filaCircular::enfileira(int valor){
    if(mTamanho == 0){
        mInicio = -1;
        mFim = -1;
    }
    if(mTamanho <= mCapacidade){
        mFim++;
        mFim = mFim % mCapacidade;
        mDados[mFim] = valor;
        if(mTamanho == 0){
            mInicio++;
        }
        mTamanho++;
    }
}
int filaCircular::desenfileira(){
    if(mTamanho > 0){
        int valor = mDados[mInicio];
        mTamanho--;
        if(mTamanho > 0){
            mInicio++;
            mInicio = mInicio % mCapacidade;
        }else{
            mInicio = -1;
            mFim = -1;
        }
        return valor;
    }else{
		return -1;
	}
}
int* filaCircular::copiaDados(){
    return mDados;
}
int main(){
    unsigned capacidade;
    cin >> capacidade;
    filaCircular f1(capacidade);

    char opcao;
    cin >> opcao;
    while(opcao != 't'){
        switch(opcao){
            case 'e':
                int dado;
                cin >> dado; 
                f1.enfileira(dado);
                break;
            case 'd':
                cout << f1.desenfileira() << endl;
                break;
            case 'i':
                int tamanho = f1.tamanho();
                int inicio = f1.inicio();
                int fim = f1.fim();

                unsigned capacidade = f1.capacidade();
                cout << "tamanho=" << tamanho
                     << " capacidade=" << capacidade
                     << " inicio=" << inicio
                     << " fim=" << fim << endl;
                    
                    filaCircular filaAux(capacidade);

                    int *dadosFila = f1.copiaDados();      //Apenas para a depuração e fins didáticos
                    for(int i = 0; i < tamanho; i++){
						cout << dadosFila[i] << ' ';
                    }                    
                    cout << endl;
                break;
        }
        cin >> opcao;
    }

}
