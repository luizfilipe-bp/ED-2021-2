/* avl - Árvore Binária de Busca com Balanceamento AVL
 *
 * by Joukim, Outubro de 2020 - Estrutura de Dados (GCC216)
 * Caracteristicas de implementação outubro de 2020:
 * -> tratamento de exceção
 * -> usa dado na forma chave/valor
 * -> uso de métodos recursivos
 * -> sem duplo encadeamento
 * -> invés de transplanta, usa removeMenor
 */

#include <iostream>
#include <stdexcept>

using namespace std;
#include <stdexcept>

struct dado {
    unsigned chave;
    string ferramenta;
    string marca;
    short potencia;
};

ostream& operator<<(ostream& saida, const dado& e) {
    saida << "(" << e.chave << "," << e.ferramenta << "," << e.marca << "," << e.potencia << ")";
    return saida;
}

istream& operator>>(istream& entrada, dado& e) {
    entrada >> e.chave >> e.ferramenta >> e.marca >> e.potencia;
    return entrada;
}

typedef unsigned tipoChave; // tipo da chave usada na comparação

class noh {
    friend class avl;
    private:
        dado elemento;
        noh* esq;
        noh* dir;
        unsigned altura;
    public:
        noh(const dado& umDado):
            elemento(umDado),  esq(NULL), dir(NULL), altura(1) { }
        ~noh() { }
        int fatorBalanceamento();
};

int noh::fatorBalanceamento() {
    int alturaEsq;
    if(esq == NULL){
        alturaEsq = 0;
    }else{
        alturaEsq = esq->altura;
    }

    int alturaDir;
    if(dir == NULL){
        alturaDir = 0;
    }else{
        alturaDir = dir->altura;
    }
    //retorna o fator de Balanceamento
    return alturaEsq - alturaDir;
}

class avl {
    friend ostream& operator<<(ostream& output, avl& arvore);
    private:
        noh* raiz;
        // percorrimento em ordem da árvore
        void percorreEmOrdemAux(noh* atual, int nivel);
        // funções auxiliares para remoção
        noh* encontraMenor(noh* raizSub);
        noh* removeMenor(noh* raizSub);
        // funções auxiliares para inserção e remoção usando método recursivo
        // retorna o nó para ajustar o pai ou o raiz
        noh* insereAux(noh* umNoh, const dado& umDado);
        noh* removeAux(noh* umNoh, tipoChave chave);
        // métodos para manutenção do balanceamento
        noh* rotacaoEsquerda(noh* umNoh);
        noh* rotacaoDireita(noh* umNoh);
        noh* arrumaBalanceamento(noh* umNoh);
        // busca, método iterativo
        noh* buscaAux(tipoChave chave);
        // função auxiliar do destrutor, usa percorrimento pós-ordem
        void destruirRecursivamente(noh* umNoh);
        void imprimirDir(const std::string& prefixo, const noh* meuNoh);
        void imprimirEsq(const std::string& prefixo, const noh* meuNoh, bool temIrmao);
        void levantamentoAux(noh* umNoh, dado& ferramentaMaiorPotencia, string nomeFerramenta);
        //função auxiliar para atualizar os valores de altura
        void atualizaAltura(noh* umNoh);
        //função auxiliar para informar a altura do noh
        int informarAltura(noh* umNoh);
    public:
        avl() { raiz = NULL; }
        ~avl();
        void imprimir();
        // inserção e remoção são recursivos
        void insere(const dado& umDado);
        void remove(tipoChave chave);
        // inserção e remoção, métodos recursivos
        // busca retorna uma cópia do objeto armazenado
        dado busca(tipoChave chave);
        // efetua levantamento da marca da ferramenta com maior potência
        string levantamento(string nomeFerramenta);
};

// destrutor
avl::~avl() {
    destruirRecursivamente(raiz);
}

// destrutor é recursivo, fazendo percorrimento pós-ordem
void avl::destruirRecursivamente(noh* umNoh) {
    if(umNoh != NULL){
        destruirRecursivamente(umNoh->esq);
        destruirRecursivamente(umNoh->dir);
        delete umNoh;
    }
}

void avl::insere(const dado& umDado) {
    raiz = insereAux(raiz, umDado);
}

// inserção recursiva, devolve nó para atribuição de pai ou raiz
noh* avl::insereAux(noh* umNoh, const dado& umDado) {
    //Inserção em folha nula
    if(umNoh == NULL){
        noh* novoNoh = new noh(umDado);
        return novoNoh;
    }else{
        //Inserção verificando as folhas
        if(umDado.chave < umNoh->elemento.chave){
            umNoh->esq = insereAux(umNoh->esq, umDado);
        }else{
            umNoh->dir = insereAux(umNoh->dir, umDado);
        }
    }
    return arrumaBalanceamento(umNoh);
}

// checa e arruma, se necessário, o balanceamento em umNoh,
// fazendo as rotações e ajustes necessários
noh* avl::arrumaBalanceamento(noh* umNoh) {
    if(umNoh == NULL){
        return umNoh;
    }
    //Atualiza a altura e calcula o fator de balanceamento
    atualizaAltura(umNoh);
    int fatorBal = umNoh->fatorBalanceamento();
    //Se estiver balanceado, retorna o noh 
    if((fatorBal >= -1) and (fatorBal <= 1)){
        return umNoh;
    }
    //Rotação para a direita
    if((fatorBal > 1) and (umNoh->esq->fatorBalanceamento() >= 0)){
        return rotacaoDireita(umNoh);
    //Rotação esquerda-direita
    }else if((fatorBal > 1) and (umNoh->esq->fatorBalanceamento() <= 0)){
        umNoh->esq = rotacaoEsquerda(umNoh->esq);
        return rotacaoDireita(umNoh);
    //Rotação esquerda
    }else if((fatorBal < -1) and (umNoh->dir->fatorBalanceamento() <= 0)){
        return rotacaoEsquerda(umNoh);
    //Rotação direita-esquerda
    }else{
        umNoh->dir = rotacaoDireita(umNoh->dir);
        return rotacaoEsquerda(umNoh);
    }
}
//Função para retornar a altura de um noh verificando se o noh é uma folha nula
int avl::informarAltura(noh* umNoh){
    if(umNoh == NULL){
        return 0;
    }else{
        return umNoh->altura;
    }
}
//Função auxiliar para atualizar o valor da altura
void avl::atualizaAltura(noh* umNoh){
    int alturaEsq = informarAltura(umNoh->esq);
    int altArvDir = informarAltura(umNoh->dir);
    int maximo;
    if(altArvDir >= alturaEsq){
        maximo = altArvDir;
    }else{
        maximo = alturaEsq;
    }
    umNoh->altura = 1 + maximo;
}

// rotação à esquerda na subárvore com raiz em umNoh
// retorna o novo pai da subárvore
noh* avl::rotacaoEsquerda(noh* umNoh) {
    noh* nohAux = umNoh->dir;
    umNoh->dir = nohAux->esq;
    nohAux->esq = umNoh;
//Atualização das alturas após a rotação
    atualizaAltura(umNoh);
    atualizaAltura(nohAux);
    return nohAux;
}

// rotação à direita na subárvore com raiz em umNoh
// retorna o novo pai da subárvore
noh* avl::rotacaoDireita(noh* umNoh) {
    noh* nohAux = umNoh->esq;
    umNoh->esq = nohAux->dir;
    nohAux->dir = umNoh;
//Atualização das alturas após a rotação
    atualizaAltura(umNoh);
    atualizaAltura(nohAux);
    return nohAux;
}


// método de busca auxiliar (retorna o nó), iterativo
noh* avl::buscaAux(tipoChave chave) {
    noh* atual = raiz;
    while(atual != NULL){
        if(atual->elemento.chave == chave){
            return atual;
        }else if(atual->elemento.chave > chave){
            atual = atual->esq;
        }else{
            atual = atual->dir;
        }
    }
    return atual;
}

// busca elemento com uma dada chave na árvore e retorna o registro completo
dado avl::busca(tipoChave chave) {
    noh* resultado = buscaAux(chave);
    if (resultado != NULL)
        return resultado->elemento;
    else
        throw runtime_error("Erro na busca: elemento não encontrado!");
}

// nó mínimo (sucessor) de subárvore com raiz em raizSub (folha mais à esquerda)
noh* avl::encontraMenor(noh* raizSub) {
    while(raizSub->esq != NULL){
        raizSub = raizSub->esq;
    }
    return raizSub;
}

// procedimento auxiliar para remover o sucessor substituíndo-o pelo
// seu filho à direita
noh* avl::removeMenor(noh* raizSub) {
    if(raizSub->esq == NULL){
        return raizSub->dir;
    }else{
        raizSub->esq = removeMenor(raizSub->esq);
        return arrumaBalanceamento(raizSub);
    }
}

// remoção recursiva
void avl::remove(tipoChave chave) {
    raiz = removeAux(raiz, chave);
}
//Função auxiliar de remove
noh* avl::removeAux(noh* umNoh, tipoChave chave) {
    if(umNoh == NULL){
        throw runtime_error("Nó não encontrado"); 
    }
    noh* novaRaizSubArvore = umNoh;
    //Busca pelo valor que será removido
    if(chave < umNoh->elemento.chave){
        umNoh->esq = removeAux(umNoh->esq, chave);
    }else if(chave > umNoh->elemento.chave){
        umNoh->dir = removeAux(umNoh->dir, chave);
    }else{
        //Remoção do elemento
        if(umNoh->esq == NULL){
            novaRaizSubArvore = umNoh->dir;
        }else if(umNoh->dir == NULL){
            novaRaizSubArvore = umNoh->esq;
        }else{
            novaRaizSubArvore = encontraMenor(umNoh->dir);
            novaRaizSubArvore->dir = removeMenor(umNoh->dir);
            novaRaizSubArvore->esq = umNoh->esq;
        }
        delete umNoh;
    }
    return arrumaBalanceamento(novaRaizSubArvore);
}


// utiliza o nó atual e seu nível na árvore (para facilitar visualização)
void avl::percorreEmOrdemAux(noh* atual, int nivel) {
    if(atual != NULL){
        percorreEmOrdemAux(atual->esq, nivel + 1);
        cout << atual->elemento;
        percorreEmOrdemAux(atual->dir, nivel + 1);
    }
}

ostream& operator<<(ostream& output, avl& arvore) {
    // arvore.percorreEmOrdemAux(arvore.raiz,0);
    arvore.imprimir();
    return output;
}

// imprime formatado seguindo o padrao tree as subarvores direitas de uma avl
void avl::imprimirDir(const std::string& prefixo, const noh* meuNoh)
{
    if( meuNoh != nullptr )
    {
        std::cout << prefixo
                  << "└d─"
                  << "(" << meuNoh->elemento.chave << "," << meuNoh->elemento.ferramenta << ")"
                  << std::endl;

        // Repassa o prefixo para manter o historico de como deve ser a formatacao e chama no filho direito e esquerdo
        imprimirEsq( prefixo + "    " , meuNoh->esq , meuNoh->dir==nullptr );
        imprimirDir( prefixo + "    " , meuNoh->dir );
    }
}

// imprime formatado seguindo o padrao tree as subarvores direitas de uma avl
void avl::imprimirEsq(const std::string& prefixo, const noh* meuNoh, bool temIrmao)
{
    if( meuNoh != nullptr )
    {
        std::cout << prefixo ;

        // A impressao da arvore esquerda depende da indicacao se existe o irmao a direita
        if (temIrmao)
            std::cout << "└e─" ;
        else
            std::cout << "├e─";

        std::cout << "(" << meuNoh->elemento.chave << "," << meuNoh->elemento.ferramenta << ")"
                  << std::endl;

        // Repassa o prefixo para manter o historico de como deve ser a formatacao e chama no filho direito e esquerdo
        imprimirEsq( prefixo + "│   " , meuNoh->esq, meuNoh->dir==nullptr );
        imprimirDir( prefixo + "│   " , meuNoh->dir );
    }
}
//Função para fazer o levantamento da ferramenta de maior potência
string avl::levantamento(string nomeFerramenta){
    //Dado que será passado por referência
	dado ferramentaMaiorPotencia;
    ferramentaMaiorPotencia.potencia = 0;
	levantamentoAux(raiz, ferramentaMaiorPotencia, nomeFerramenta);
	return ferramentaMaiorPotencia.marca;
}
void avl::levantamentoAux(noh* umNoh, dado& ferramentaMaiorPotencia, string nomeFerramenta){
    //Percorrimento Pos Ordem
    if(umNoh != NULL){
		levantamentoAux(umNoh->esq, ferramentaMaiorPotencia, nomeFerramenta);
		levantamentoAux(umNoh->dir, ferramentaMaiorPotencia, nomeFerramenta);
        //Se o nome do elemento é igual ao nome procurado, compara as potencias
        if(umNoh->elemento.ferramenta == nomeFerramenta){
			if(umNoh->elemento.potencia > ferramentaMaiorPotencia.potencia){
                ferramentaMaiorPotencia = umNoh->elemento;
            //Se as potencias são iguais, compara as chaves procurando o elemento de menor chave
            }else if(umNoh->elemento.potencia == ferramentaMaiorPotencia.potencia){
                if(umNoh->elemento.chave < ferramentaMaiorPotencia.chave){
                    ferramentaMaiorPotencia = umNoh->elemento;
                }
            }
		}
    }
}
// imprime formatado seguindo o padrao tree uma avl
void avl::imprimir()
{
    if( this->raiz != nullptr )
    {
        std::cout << "(" << this->raiz->elemento.chave << "," << this->raiz->elemento.ferramenta << ")" << std::endl;
        // apos imprimir a raiz, chama os respectivos metodos de impressao nas subarvore esquerda e direita
        // a chamada para a impressao da subarvore esquerda depende da existencia da subarvore direita
        imprimirEsq( " " , this->raiz->esq, this->raiz->dir==nullptr );
        imprimirDir( " " , this->raiz->dir );
    } else
        std::cout << "*arvore vazia*" << std::endl;
}

int main() {
    avl arvore;
    tipoChave chave;
    dado umDado;
    string ferramenta;
    string marca;

    char operacao;

    do {
        try {
            cin >> operacao;
            switch (operacao) {
                case 'i': // Inserir recursivamente
                    // objeto recebe chave, nome do ferramenta, marca e potência
                    cin >> umDado;
                    arvore.insere(umDado);
                    break;
                case 'r': // Remover recursivamente
                    cin >> chave;
                    arvore.remove(chave);
                    break;
                case 'b': // Buscar
                    cin >> chave; // ler a chave
                    umDado = arvore.busca(chave); // escrever os dados da ferramenta
                    cout << "Elemento buscado: " << umDado << endl;
                    break;
                case 'l': // Levantamento por ferramenta
                    cin >> ferramenta; // ler os dados para levantamento
                    marca = arvore.levantamento(ferramenta);
                    cout << "Levantamento do ferramenta " << ferramenta << ": " << marca << endl;
                    break;
                case 'e': // Escrever tudo (em ordem)
                    cout << arvore;
                    break;
                case 'f': // Finalizar execução
                    break;
                default:
                    cout << "Comando invalido!\n";
            }
        } catch (runtime_error& e) {
            cout << e.what() << endl;
        }
    } while (operacao != 'f');

    return 0;
}