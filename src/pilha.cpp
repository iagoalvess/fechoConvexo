#include "pilha.hpp"

Pilha::Pilha() {
  topo = nullptr;
  tam = 0;
}

Pilha::~Pilha() {
  limpar();
}

bool Pilha::vazia() {
  return topo == nullptr;
}

// Adiciona um elemento no topo da pilha
void Pilha::empilhar(Ponto elemento) {
  Nodo *novoNodo = new Nodo;
  novoNodo->dado = elemento;
  novoNodo->proximo = topo;
  topo = novoNodo;
  tam++;
}

// Remove todos os elementos da pilha e libera a memória alocada
void Pilha::limpar() {
  while (!vazia()) {
    desempilhar();
  }
}

// Retorna o valor do elemento no topo da pilha
Ponto Pilha::valorTopo() {
  if (vazia()) {
    throw "ERRO: PILHA VAZIA!";
  }

  return topo->dado;
}

// Remove e retorna o elemento no topo da pilha
Ponto Pilha::desempilhar() {
  if (vazia()) {
    throw "ERRO: PILHA VAZIA!";
  }

  Ponto valor = topo->dado;
  Nodo *temp = topo;
  topo = topo->proximo;
  delete temp;
  tam--;

  return valor;
}

int Pilha::tamanho() {
  return tam;
}
