#include <iostream>

using namespace std;

class noh{
    friend class avl;
    private:
        int mDado;
        int altura;
        noh* esq;
        noh* dir;
    public:
        noh(int valor);
};
noh::noh(int valor){
    mDado = valor;
    altura = 0;
    esq = NULL;
    dir = NULL;
}
class avl{
    private:
        noh* raiz;
        noh* inserirAux(noh* umNoh, int valor);
        noh* minimoAux(noh* raizSubArvore);
        noh* maximoAux(noh* raizSubArvore);
        noh* buscaAux(int valorBuscado);
        void percorreEmOrdemAux(noh* umNoh);
        void percorrePreOrdemAux(noh* umNoh);
        void percorrePosOrdemAux(noh* umNoh);
        void desalocaNoh(noh* umNoh);
        noh* removerAux(noh* umNoh, int umValor);
        noh* removeMenor(noh* raizSub);
        int informarAltura(noh* umNoh);
        void atualizaAltura(noh* umNoh);
        int fatorBalanceamento(noh* umNoh);
        noh* rotacaoEsq(noh* umNoh);
        noh* rotacaoDir(noh* umNoh);
        noh* rotacaoEsqDir(noh* umNoh);
        noh* rotacaoDirEsq(noh* umNoh);
        noh* arrumarBalanceamento(noh* umNoh);
    public:
        avl();
        ~avl();
        //Inserção recursiva
        void inserir(int valor);
        int minimo();
        int maximo();
        void busca(int valorBuscado);
        void percorreEmOrdem();
        void percorrePreOrdem();
        void percorrePosOrdem();
        void imprime();
        void removerRecursivamente(int umValor);
};
avl::avl(){
    raiz = NULL;
}
avl::~avl(){
    desalocaNoh(raiz);
}
void avl::desalocaNoh(noh* umNoh){
    if(umNoh != NULL){
        desalocaNoh(umNoh->esq);
        desalocaNoh(umNoh->dir);
        delete umNoh;
    } 
}
void avl::inserir(int valor){
    raiz = inserirAux(raiz, valor);
}
noh* avl::inserirAux(noh* umNoh, int valor){
    //Inserção em folha nula
    if(umNoh == NULL){
        noh* novoNoh = new noh(valor);
        return novoNoh;
    }else{
        //Inserção verificando as folhas
        if(valor < umNoh->mDado){
            umNoh->esq = inserirAux(umNoh->esq, valor);
        }else{
            umNoh->dir = inserirAux(umNoh->dir, valor);
        }
    }
    return arrumarBalanceamento(umNoh);
}
int avl::minimo(){
    if(raiz == NULL){
        cout << "Arvore vazia" << endl;
        return -1;
    }else{
        noh* nohMinimo = minimoAux(raiz);
        return nohMinimo->mDado;
    }
}
noh* avl::minimoAux(noh* raizSubArvore){
    while(raizSubArvore->esq != NULL){
        raizSubArvore = raizSubArvore->esq;
    }
    return raizSubArvore;
}
int avl::maximo(){
    if(raiz == NULL){
        cout << "Arvore vazia" << endl;
        return -1;
    }else{
        noh* nohMaximo = maximoAux(raiz);
        return nohMaximo->mDado;
    }
}
noh* avl::maximoAux(noh* raizSubArvore){
    while(raizSubArvore->dir != NULL){
        raizSubArvore = raizSubArvore->dir;
    }
    return raizSubArvore;
}
void avl::busca(int valorBuscado){
    noh* nohComValor = buscaAux(valorBuscado);
    if(nohComValor == NULL){
        cout << "Valor nao encontrado na arvore" << endl;
    }else{
        cout << "Valor encontrado: " << nohComValor->mDado << endl;
    }
}
noh* avl::buscaAux(int valorBuscado){
    noh* atual = raiz;
    while(atual != NULL){
        if(atual->mDado == valorBuscado){
            return atual;
        }else if(atual->mDado > valorBuscado){
            atual = atual->esq;
        }else{
            atual = atual->dir;
        }
    }
    return atual;
}
void avl::percorreEmOrdem(){
    percorreEmOrdemAux(raiz);
}
void avl::percorreEmOrdemAux(noh* umNoh){
    if(umNoh != NULL){
        percorreEmOrdemAux(umNoh->esq);
        cout << umNoh->mDado << ' ';
        percorreEmOrdemAux(umNoh->dir);
    }
}
void avl::percorrePreOrdem(){
    percorrePreOrdemAux(raiz);
}
void avl::percorrePreOrdemAux(noh* umNoh){
    if(umNoh != NULL){
        cout << umNoh->mDado << ' ';
        percorrePreOrdemAux(umNoh->esq);
        percorrePreOrdemAux(umNoh->dir);
    }
}
void avl::percorrePosOrdem(){
    percorrePosOrdemAux(raiz);
}
void avl::percorrePosOrdemAux(noh* umNoh){
    if(umNoh != NULL){
        percorrePosOrdemAux(umNoh->esq);
        percorrePosOrdemAux(umNoh->dir);
        cout << umNoh->mDado << ' ';
    }
}
noh* avl::removeMenor(noh* raizSub){
    if(raizSub->esq == NULL){
        return raizSub->dir;
    }else{
        raizSub->esq = removeMenor(raizSub->esq);
        return arrumarBalanceamento(raizSub);
    }
}
void avl::removerRecursivamente(int umValor){
    raiz = removerAux(raiz, umValor);
}
noh* avl::removerAux(noh* umNoh, int umValor){
    if(umNoh == NULL){
        cout << "Noh nao encontrado " << endl;
        return NULL;
    }
    noh* novaRaizSubArvore = umNoh;
    if(umValor < umNoh->mDado){
        umNoh->esq = removerAux(umNoh->esq, umValor);
    }else if(umValor > umNoh->mDado){
        umNoh->dir = removerAux(umNoh->dir, umValor);
    }else{
        if(umNoh->esq == NULL){
            novaRaizSubArvore = umNoh->dir;
        }else if(umNoh->dir == NULL){
            novaRaizSubArvore = umNoh->esq;
        }else{
            novaRaizSubArvore = minimoAux(umNoh->dir);
            novaRaizSubArvore->dir = removeMenor(umNoh->dir);
            novaRaizSubArvore->esq = umNoh->esq;
            delete umNoh;
        }
    }
    return arrumarBalanceamento(novaRaizSubArvore);
}

int avl::informarAltura(noh* umNoh){
    if(umNoh == NULL){
        return 0;
    }else{
        return umNoh->altura;
    }
}

void avl::atualizaAltura(noh* umNoh){
    int altArvEsq = informarAltura(umNoh->esq);
    int altArvDir = informarAltura(umNoh->dir);
    int maximo;
    if(altArvDir >= altArvEsq){
        maximo = altArvDir;
    }else{
        maximo = altArvEsq;
    }
    umNoh->altura = 1 + maximo;
}

int avl::fatorBalanceamento(noh* umNoh){
    int altArvEsq = informarAltura(umNoh->esq);
    int altArvDir = informarAltura(umNoh->dir);
    //retorna o fator de Balanceamento
    return altArvEsq - altArvDir;
}

noh* avl::rotacaoEsq(noh* umNoh){
    noh* nohAux = umNoh->dir;
    umNoh->dir = nohAux->esq;
    nohAux->esq = umNoh;

    atualizaAltura(umNoh);
    atualizaAltura(nohAux);
    return nohAux;
}

noh* avl::rotacaoDir(noh* umNoh){
    noh* nohAux = umNoh->esq;
    umNoh->esq = nohAux->dir;
    nohAux->dir = umNoh;

    atualizaAltura(umNoh);
    atualizaAltura(nohAux);
    return nohAux;
}

noh* avl::rotacaoEsqDir(noh* umNoh){
    umNoh->esq = rotacaoEsq(umNoh->esq);
    return rotacaoDir(umNoh);
}
noh* avl::rotacaoDirEsq(noh* umNoh){
    umNoh->dir = rotacaoDir(umNoh->dir);
    return rotacaoEsq(umNoh);
}

noh* avl::arrumarBalanceamento(noh* umNoh){
    if(umNoh == NULL){
        return umNoh;
    }
    atualizaAltura(umNoh);
    int fatorBal = fatorBalanceamento(umNoh);
    if((fatorBal >= -1) and (fatorBal <= 1)){
        return umNoh;
    }
    if((fatorBal > 1) and (fatorBalanceamento(umNoh->esq) >= 0)){
        return rotacaoDir(umNoh);
    }else if((fatorBal > 1) and (fatorBalanceamento(umNoh->esq) <= 0)){
        return rotacaoEsqDir(umNoh);
    }else if((fatorBal < -1) and (fatorBalanceamento(umNoh->dir) <= 0)){
        return rotacaoEsq(umNoh);
    }else{
        return rotacaoDirEsq(umNoh);
    }
}
void avl::imprime(){
    cout << "Percorre Pre ordem" << endl;
	percorrePreOrdem();
	cout << endl << "Percorre Em ordem" << endl;
	percorreEmOrdem();
	cout << endl << "Percorre Pos ordem" << endl;
	percorrePosOrdem();
	cout << endl;
}
int main(){
    avl arvoreAvl;
    arvoreAvl.inserir(11);
    arvoreAvl.inserir(10);
    arvoreAvl.inserir(9);
    arvoreAvl.inserir(14);
    arvoreAvl.inserir(12);
    arvoreAvl.inserir(15);
    arvoreAvl.inserir(13);
    arvoreAvl.inserir(18);
    cout << "minimo: " << arvoreAvl.minimo() << endl;
    cout << "maximo: " << arvoreAvl.maximo() << endl;
    arvoreAvl.busca(14);
    arvoreAvl.busca(99);
    
    arvoreAvl.imprime();
    arvoreAvl.removerRecursivamente(14);
    arvoreAvl.removerRecursivamente(14);
}
