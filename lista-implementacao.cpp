#include <iostream>

using namespace std;
class noh{
    friend class lista;
    private:
        int mDado;
        noh* mProximo;
    public:
        noh(int valor);
};
noh::noh(int valor){
    mDado = valor;
    mProximo = NULL;
}
class lista{
    private:
        noh* mInicio;       //Primeiro elemento
        noh* mFim;          //último elemento
        int mTamanho;
        void removeTodos();
        void imprimeReversoAux(noh* umNoh);
    public:
        lista();
        //construtor de cópia
        lista(const lista& umaLista);
        //destrutor
        ~lista();
        //sobrecarga do operador = 
        lista& operator=(const lista& umaLista);
        void insere(int valor);
        void inserirInicio(int valor);
        void inserirFim(int valor);
        void inserirEmUmaPos(int valor, int pos);
        void imprime();
        void imprimeReverso();
        bool vazia();
        int procura(int valorProcurado);
        void removeNoFim();
        void removeNoInicio();
}; 
lista::lista(){
    mInicio = NULL;
    mFim = NULL;
    mTamanho = 0;
}
lista::lista(const lista& umaLista){
    mTamanho = 0;
    mFim = NULL;
    mInicio = NULL;

    noh* aux = umaLista.mInicio;
    while(aux != NULL){
        inserirFim(aux->mDado);
        aux = aux->mProximo;
    }
}
lista::~lista(){
    removeTodos();
}
void lista::removeTodos(){
    noh* aux = mInicio;
    noh* temp;
    while(aux != NULL){
        temp = aux;
        aux = aux->mProximo;
        delete temp;
    }
    mTamanho = 0;
    mFim = NULL;
    mInicio = NULL;
}
//sobrecarga do operador de atribuição
lista& lista::operator=(const lista& umaLista){
    //limpa a lista atual
    removeTodos();
    //percorre a lista recebida como parâmetro, copiando os dados
    noh* aux = umaLista.mInicio;
    while(aux != NULL){
        inserirFim(aux->mDado);
        aux = aux->mProximo;
    }
    return *this;
}
//insere por pad~rao no final da lista
void lista::insere(int valor){
    inserirFim(valor);
}
bool lista::vazia(){
    return (mTamanho == 0);
}
void lista::inserirInicio(int valor){
    noh* novoNoh = new noh(valor);
    if(vazia()){
        mInicio = novoNoh;
        mFim = novoNoh;
    }else{
        novoNoh->mProximo = mInicio;
        mInicio = novoNoh;
    }
    mTamanho++;
}
void lista::inserirFim(int valor){
    noh* novoNoh = new noh(valor);
    if(vazia()){
        mInicio = novoNoh;
        mFim = novoNoh;
    }else{
        mFim->mProximo = novoNoh;
        mFim = novoNoh;
    }
    mTamanho++;
}
void lista::inserirEmUmaPos(int valor, int pos){
    noh* novoNoh = new noh(valor);
    if((pos <= mTamanho) and (pos >= 0)){
        if(vazia()){
            mInicio = novoNoh;
            mFim = novoNoh;
        }else if(pos == 0){
            novoNoh->mProximo = mInicio;
            mInicio = novoNoh;
        }else if(pos == mTamanho){
            mFim->mProximo = novoNoh;
            mFim = novoNoh;
        }else{
            noh* aux = mInicio;
            int posAux = 0;
            while(posAux < (pos - 1)){            //Verifica a posição iniciando em zero | avança os nós até chegar na posição anterior a desejada
                aux = aux->mProximo;
                posAux++;
            }
            novoNoh->mProximo = aux->mProximo;
            aux->mProximo = novoNoh;
        }
    }else{
        cout << "Posicao invalida" << endl;
    }
}
int lista::procura(int valorProcurado){
    noh* aux = mInicio;
    int posAux = 0;
    while((aux != NULL) and (aux->mDado != valorProcurado)){
        posAux++;
        aux = aux->mProximo;
    }
    if(aux == NULL){
        posAux = -1;
    }
    return posAux;
}
void lista::imprime(){
    noh* aux = mInicio;
    while(aux != NULL){
        cout << aux->mDado << ' ';
        aux = aux->mProximo;
    }
    cout << endl;
}

//usamos recursão (pilha de recursão) para imprimir reverso
void lista::imprimeReverso(){
    imprimeReversoAux(mInicio);
    cout << endl;
}
void lista::imprimeReversoAux(noh* umNoh){
    if(umNoh != NULL){
        imprimeReversoAux(umNoh->mProximo);
        cout << umNoh->mDado << " ";
    }
}
void lista::removeNoFim(){
    if(vazia()){
        cout << "Lista vazia" << endl;
    }else{
        noh* aux = mInicio;
        noh* anterior = NULL;
        while(aux->mProximo != NULL){
            anterior = aux;
            aux = aux->mProximo;
        }
        delete mFim;
        anterior->mProximo = NULL;
        mFim = anterior;
        mTamanho--;
        if(vazia()){
            mInicio = NULL;
        }
    }
}
void lista::removeNoInicio(){
    if(vazia()){
        cout << "Lista vazia" << endl;
    }else{
        noh* nohRemovido = mInicio;
        mInicio = mInicio->mProximo;
        delete nohRemovido;
        mTamanho--;
        if(vazia()){
            mFim = NULL;
        }
    }
}
int main(){
    lista minhaLista;
    cout << "Teste de lista" << endl;
    int valor;
    int num;
    cin >> num;

    for(int i = 0; i < num; i++){
        cin >> valor;
        minhaLista.insere(valor);
    }
    minhaLista.imprime();

    minhaLista.inserirInicio(18);
    minhaLista.inserirEmUmaPos(25,3);
    minhaLista.imprime();
    minhaLista.imprimeReverso();

    cout << "pos do num procurado: " << minhaLista.procura(0) << endl;
    cout << "pos do num procurado: " << minhaLista.procura(50) << endl;
    cout << "pos do num procurado: " << minhaLista.procura(12) << endl;

    //utilização do construtor de cópia
    cout << "Sobrecarga do construtor de copia" << endl;
    lista outraLista(minhaLista);
    outraLista.imprime();
    outraLista.imprimeReverso();

    //sobrecarga do operador de atribuição
    cout << "Sobrecarga do operador de atribuicao" << endl;
    lista maisUmaLista;
    maisUmaLista = outraLista;

    maisUmaLista.imprime();
    maisUmaLista.imprimeReverso();
    //remoção
    maisUmaLista.removeNoFim();
    maisUmaLista.removeNoFim();
    maisUmaLista.imprime();
    maisUmaLista.imprimeReverso();

    maisUmaLista.removeNoInicio();
    maisUmaLista.removeNoInicio();
    maisUmaLista.imprime();
    maisUmaLista.imprimeReverso();
}