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
        filaCircular(int capacidade);
        ~filaCircular();
        unsigned tamanho();
        void enfileira(int valor);
        int desenfileira();
        bool vazia();
};
filaCircular::filaCircular(int capacidade){
    mInicio = -1;
    mFim = -1;
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
bool filaCircular::vazia(){
    return(mTamanho == 0);              //Return 1 se está vazia
}
void filaCircular::enfileira(int valor){
    if(mTamanho <= mCapacidade){
        mFim++;
        mFim = mFim % mCapacidade;
        mDados[mFim] = valor;
        if(mTamanho == 0){
            mInicio++;
        }
        mTamanho++;
    }else{
        cout << "Fila cheia" << endl;
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
        cout << "Fila vazia" << endl;
        return -1;
    }
}
int main(){
    int capacidade;
    cin >> capacidade;
    filaCircular f1(capacidade);
    
    int num;
    cout << "Enfileira 8 elementos: " << endl;
    for(int i = 0; i < 8; i++){
        cin >> num;
        f1.enfileira(num);
    }
	cout << "Tamanho: " << f1.tamanho() << endl;
	
    cout << "Desenfileira 5 elementos" << endl;
    for(int i = 0; i < 5; i++){
        cout << f1.desenfileira() << " ";
    }
    cout << "Tamanho: " << f1.tamanho() << endl;

    cout << "Enfileira 8 elementos" << endl;
    for(int i = 0; i < 8; i++){
        cin >> num;
        f1.enfileira(num);
    }
    cout << "Tamanho: " << f1.tamanho() << endl;

    cout << "Desenfileira 5 elementos" << endl;
    for(int i = 0; i < 5; i++){
        cout << f1.desenfileira() << " ";
    }
    cout << "Tamanho: " << f1.tamanho() << endl;

}
