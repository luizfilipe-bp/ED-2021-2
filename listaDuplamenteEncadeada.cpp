#include <iostream>

using namespace std;
class noh{
    friend class listaDup;
    private:
        int mDado;
        noh* mProximo;
        noh* mAnterior;
    public:
        noh(int valor);
};
noh::noh(int valor){
    mDado = valor;
    mProximo = NULL;
    mAnterior = NULL;
}
class listaDup{
    private:
        noh* mInicio;       //Primeiro elemento
        noh* mFim;          //último elemento
        int mTamanho;
        void removeTodos();
    public:
        listaDup();
        //construtor de cópia
        listaDup(const listaDup& umaLista);
        ~listaDup();
        listaDup& operator=(const listaDup& umaLista);
        void insere(int valor);
        void inserirInicio(int valor);
        void inserirFim(int valor);
        void inserirEmUmaPos(int valor, int pos);
        void imprime();
        bool vazia();
        int procura(int valorProcurado);
        void removeNoFim();
        void removeNoInicio();
        void removeValor(int valor);
}; 
listaDup::listaDup(){
    mInicio = NULL;
    mFim = NULL;
    mTamanho = 0;
}
listaDup::listaDup(const listaDup& umaLista){
    mTamanho = 0;
    mFim = NULL;
    mInicio = NULL;

    noh* aux = umaLista.mInicio;
    while(aux != NULL){
        inserirFim(aux->mDado);
        aux = aux->mProximo;
    }
}
listaDup::~listaDup(){
    removeTodos();
}
void listaDup::removeTodos(){
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
listaDup& listaDup::operator=(const listaDup& umaLista){
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
//insere por padrao no final da lista
void listaDup::insere(int valor){
    inserirFim(valor);
}
bool listaDup::vazia(){
    return (mTamanho == 0);
}
void listaDup::inserirInicio(int valor){
    noh* novoNoh = new noh(valor);
    if(vazia()){
        mInicio = novoNoh;
        mFim = novoNoh;
    }else{
        novoNoh->mProximo = mInicio;
        mInicio->mAnterior = novoNoh;
        mInicio = novoNoh;
    }
    mTamanho++;
}
void listaDup::inserirFim(int valor){
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
void listaDup::inserirEmUmaPos(int valor, int pos){
    noh* novoNoh = new noh(valor);
    if((pos <= mTamanho) and (pos >= 0)){
        if(vazia()){
            mInicio = novoNoh;
            mFim = novoNoh;
        }else if(pos == 0){
            novoNoh->mProximo = mInicio;
            mInicio->mAnterior = novoNoh;
            mInicio = novoNoh;
        }else if(pos == mTamanho ){
            mFim->mProximo = novoNoh;
            novoNoh->mAnterior = mFim;
            mFim = novoNoh;
        }else{
            noh* aux = mInicio;
            int posAux = 0;                 //Pos do aux
            while(posAux < (pos - 1)){
                aux = aux->mProximo;
                posAux++;
            }
            novoNoh->mProximo = aux->mProximo;
            aux->mProximo->mAnterior = novoNoh;
            aux->mProximo = novoNoh;
            novoNoh->mAnterior = aux;
        }
        mTamanho++;
    }else{
        cout << "Posicao invalida" << endl;
    }
}
int listaDup::procura(int valorProcurado){
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

void listaDup::removeNoFim(){
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
void listaDup::removeNoInicio(){
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
void listaDup::removeValor(int valor){
    noh* aux = mInicio;
    while((aux != NULL) and (aux->mDado != valor)){
        aux = aux->mProximo;
    }
    if(aux == NULL){
        cout << "Valor nao encontrado" << endl;
    }else{
        noh* anterior = aux->mAnterior;
        noh* proximo = aux->mProximo;
        if(anterior != NULL){
            anterior->mProximo = proximo;
        }else{
            mInicio = aux->mProximo;
        }
        if(proximo != NULL){
            proximo->mAnterior = anterior;
        }else{
            mFim = aux->mAnterior;
        }
        delete aux;
        mTamanho--;
        if(vazia()){
            mFim = NULL;
            mInicio = NULL;
        }
    } 
}
int main(){
    listaDup minhaLista;
    cout << "Teste de lista" << endl;

    minhaLista.insere(5);
    minhaLista.insere(3);
    minhaLista.insere(1);
    minhaLista.insere(0);
    minhaLista.insere(6);
    minhaLista.inserirInicio(18);
    minhaLista.inserirEmUmaPos(25,3);
    minhaLista.imprime();

    cout << "pos do num procurado: " << minhaLista.procura(3) << endl;
    cout << "pos do num procurado: " << minhaLista.procura(50) << endl;
    cout << "pos do num procurado: " << minhaLista.procura(6) << endl;

    //utilização do construtor de cópia
    cout << "Sobrecarga do construtor de copia" << endl;
    listaDup outraLista(minhaLista);
    outraLista.inserirInicio(99);
    outraLista.inserirFim(10);
    outraLista.imprime();

    //sobrecarga do operador de atribuição
    cout << "Sobrecarga do operador de atribuicao" << endl;
    listaDup maisUmaLista;
    maisUmaLista = outraLista;
    maisUmaLista.inserirInicio(31);
    maisUmaLista.inserirFim(13);    
    maisUmaLista.imprime();
    cout << endl;
    minhaLista.imprime();
    outraLista.imprime();
    maisUmaLista.imprime();

    cout << "Remocao no inicio e fim do objeto minhaLista" << endl;
    minhaLista.removeNoFim();
    minhaLista.removeNoInicio();
    minhaLista.imprime();
    minhaLista.removeNoFim();
    minhaLista.removeNoInicio();
    minhaLista.imprime();
    minhaLista.removeNoFim();
    minhaLista.removeNoInicio();
    minhaLista.imprime();
    minhaLista.removeValor(25);
    minhaLista.imprime();

    cout << "Remocao do valor 10 do objeto outraLista" << endl;
    outraLista.imprime();
    outraLista.removeValor(10);
    outraLista.removeValor(99);
    outraLista.removeValor(18);
    outraLista.removeValor(6);
    outraLista.imprime();

    cout << "Remocao dos valores 31 e 25 do objeto maisUmaLista" << endl;
    maisUmaLista.imprime();
    maisUmaLista.removeValor(31);
    maisUmaLista.imprime();
    maisUmaLista.removeValor(25);
    maisUmaLista.imprime();

    cout << "Insercao dos valores 0 e 11 no minhaLista que estava vazia" << endl;
    minhaLista.insere(0);
    minhaLista.insere(11);
    minhaLista.imprime();
}
