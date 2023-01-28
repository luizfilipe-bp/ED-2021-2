/*
    MaxHeap, para alteração de prioridade
    by joukim & bruno, 2019
    
    Resolução da atividade by Luiz Filipe Bartelega Penha
*/

#include <iostream>
#include <utility> // para usar swap

using namespace std;

struct dado {
    int prioridade;
    int valor;
};

bool operator>(dado d1, dado d2) {
    return d1.prioridade > d2.prioridade;
}

bool operator<(dado d1, dado d2) {
    return d1.prioridade < d2.prioridade;
}

ostream& operator<<(ostream& output,const dado& d) {
    output << "[" << d.valor << "/" << d.prioridade << "]"; 
    return output;
}

class MaxHeap {
private:
    dado* heap;
    int capacidade;
    int tamanho;
    inline int pai(int i);
    inline int esquerdo(int i);
    inline int direito(int i); 
    inline void arruma();
    void corrigeDescendo(int i); 
    void corrigeSubindo(int i);
public:
    MaxHeap(int cap);
    ~MaxHeap();
    void imprime();
    dado retiraRaiz();
    void insere(dado d);
    void alteraPrioridade(int umValor, int novaPrioridade);
};

MaxHeap::MaxHeap(int cap) {
    tamanho = 0;
    capacidade = cap;
    heap = new dado[capacidade];
}

void MaxHeap::arruma() {
    for(int i = ((tamanho / 2) - 1); i >= 0; i--){
        corrigeDescendo(i);
    }
}
MaxHeap::~MaxHeap() {
	capacidade = 0;
    delete[] heap;
}

int MaxHeap::pai(int i) {
    return (i - 1) / 2;
}
    
int MaxHeap::esquerdo(int i) {
    return (i * 2) + 1;
}
    
int MaxHeap::direito(int i) {
    return (i * 2) + 2;
}
    
void MaxHeap::corrigeDescendo(int i) {
    int esq = esquerdo(i);
    int dir = direito(i);
    int maior = i;
    
    if((esq < tamanho) and (heap[esq] > heap[maior])){
        maior = esq;
    }
    if((dir < tamanho) and (heap[dir] > heap[maior])){
        maior = dir;
    }
    if(maior != i){
        swap(heap[i], heap[maior]);
        corrigeDescendo(maior);
    }
}

void MaxHeap::corrigeSubindo(int i) {
    int paiAux = pai(i);
    if(heap[i] > heap[paiAux]){
        swap(heap[i], heap[paiAux]);
        corrigeSubindo(paiAux);
    }
}
        
void MaxHeap::imprime() {
    for(int i = 0; i < tamanho; i++){
        cout << heap[i] << ' ';
    }
    cout << endl;
}

dado MaxHeap::retiraRaiz() {
    dado aux = heap[0];
    tamanho--;
    swap(heap[0], heap[tamanho]);
    corrigeDescendo(0);
    return aux;
}

void MaxHeap::insere(dado d){
    heap[tamanho] = d;
    corrigeSubindo(tamanho);
    tamanho++;
}

void MaxHeap::alteraPrioridade(int umValor, int novaPrioridade) {
    int i = 0;
    while(heap[i].valor != umValor){
        i++;
    }
    int antigaPrioridade = heap[i].prioridade;
    heap[i].prioridade = novaPrioridade;
   
    if(novaPrioridade > antigaPrioridade){
        corrigeSubindo(i);
    }else{
        corrigeDescendo(i);
    }
}

int main () {
    int capacidade;
    cin >> capacidade;
    MaxHeap meuHeap(capacidade);
   
    char opcao;
    cin >> opcao;
    
    dado umDado;
    int valor, novaPrioridade;

    while (opcao != 'Q') {
        switch(opcao) {
            case 'I':
                cin >> umDado.valor;
                cin >> umDado.prioridade;
                meuHeap.insere(umDado);
                break;
            case 'R':
                cout << meuHeap.retiraRaiz().valor << endl;
                break;
            case 'A':
                cin >> valor >> novaPrioridade;
                meuHeap.alteraPrioridade(valor,novaPrioridade); 
                break;               
            case 'P':
                meuHeap.imprime();
                break;
            default:
                cout << "Opção inválida!" << endl;
        }
        cin >> opcao;
    }
    return 0;
}
