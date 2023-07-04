#ifndef PILHA_H
#define PILHA_H

#include "ponto.hpp"

class Pilha {
public:
    Pilha();        // Construtor padrão
    ~Pilha();       // Destrutor

    bool vazia();

    void empilhar(Ponto elemento);
    void limpar();

    Ponto valorTopo();
    Ponto desempilhar();

    int tamanho();
private:
    struct Nodo {
        Ponto dado;
        Nodo *proximo;
    };
    Nodo *topo;
    int tam;
};

#endif
