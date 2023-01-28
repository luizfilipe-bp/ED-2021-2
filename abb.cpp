#include <iostream>

using namespace std;

class noh{
    friend class abb;
    private:
        int mDado;
        noh* esq;
        noh* dir;
    public:
        noh(int valor);
};
noh::noh(int valor){
    mDado = valor;
    esq = NULL;
    dir = NULL;
}
class abb{
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
    public:
        abb();
        ~abb();
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
abb::abb(){
    raiz = NULL;
}
abb::~abb(){
    desalocaNoh(raiz);
}
void abb::desalocaNoh(noh* umNoh){
    if(umNoh != NULL){
        desalocaNoh(umNoh->esq);
        desalocaNoh(umNoh->dir);
        delete umNoh;
    } 
}
void abb::inserir(int valor){
    raiz = inserirAux(raiz, valor);
}
noh* abb::inserirAux(noh* umNoh, int valor){
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
    return umNoh;
}
int abb::minimo(){
    if(raiz == NULL){
        cout << "Arvore vazia" << endl;
        return -1;
    }else{
        noh* nohMinimo = minimoAux(raiz);
        return nohMinimo->mDado;
    }
}
noh* abb::minimoAux(noh* raizSubArvore){
    while(raizSubArvore->esq != NULL){
        raizSubArvore = raizSubArvore->esq;
    }
    return raizSubArvore;
}
int abb::maximo(){
    if(raiz == NULL){
        cout << "Arvore vazia" << endl;
        return -1;
    }else{
        noh* nohMaximo = maximoAux(raiz);
        return nohMaximo->mDado;
    }
}
noh* abb::maximoAux(noh* raizSubArvore){
    while(raizSubArvore->dir != NULL){
        raizSubArvore = raizSubArvore->dir;
    }
    return raizSubArvore;
}
void abb::busca(int valorBuscado){
    noh* nohComValor = buscaAux(valorBuscado);
    if(nohComValor == NULL){
        cout << "Valor nao encontrado na arvore" << endl;
    }else{
        cout << "Valor encontrado: " << nohComValor->mDado << endl;
    }
}
noh* abb::buscaAux(int valorBuscado){
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
void abb::percorreEmOrdem(){
    percorreEmOrdemAux(raiz);
}
void abb::percorreEmOrdemAux(noh* umNoh){
    if(umNoh != NULL){
        percorreEmOrdemAux(umNoh->esq);
        cout << umNoh->mDado << ' ';
        percorreEmOrdemAux(umNoh->dir);
    }
}
void abb::percorrePreOrdem(){
    percorrePreOrdemAux(raiz);
}
void abb::percorrePreOrdemAux(noh* umNoh){
    if(umNoh != NULL){
        cout << umNoh->mDado << ' ';
        percorrePreOrdemAux(umNoh->esq);
        percorrePreOrdemAux(umNoh->dir);
    }
}
void abb::percorrePosOrdem(){
    percorrePosOrdemAux(raiz);
}
void abb::percorrePosOrdemAux(noh* umNoh){
    if(umNoh != NULL){
        percorrePosOrdemAux(umNoh->esq);
        percorrePosOrdemAux(umNoh->dir);
        cout << umNoh->mDado << ' ';
    }
}
noh* abb::removeMenor(noh* raizSub){
    if(raizSub->esq == NULL){
        return raizSub->dir;
    }else{
        raizSub->esq = removeMenor(raizSub->esq);
        return raizSub;
    }
}
void abb::removerRecursivamente(int umValor){
    raiz = removerAux(raiz, umValor);
}
noh* abb::removerAux(noh* umNoh, int umValor){
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
    return novaRaizSubArvore;
}
void abb::imprime(){
    cout << "Percorre Pre ordem" << endl;
	percorrePreOrdem();
	cout << endl << "Percorre Em ordem" << endl;
	percorreEmOrdem();
	cout << endl << "Percorre Pos ordem" << endl;
	percorrePosOrdem();
	cout << endl;
}
int main(){
    abb arvoreABB;
    arvoreABB.inserir(11);
    arvoreABB.inserir(10);
    arvoreABB.inserir(9);
    arvoreABB.inserir(14);
    arvoreABB.inserir(12);
    arvoreABB.inserir(15);
    arvoreABB.inserir(13);
    arvoreABB.inserir(18);
    cout << "minimo: " << arvoreABB.minimo() << endl;
    cout << "maximo: " << arvoreABB.maximo() << endl;
    arvoreABB.busca(14);
    arvoreABB.busca(99);
    
    arvoreABB.imprime();
    arvoreABB.removerRecursivamente(14);
    arvoreABB.removerRecursivamente(14);
}
