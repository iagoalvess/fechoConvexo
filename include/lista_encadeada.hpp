#ifndef LISTA_ENCADEADA_H
#define LISTA_ENCADEADA_H

#include "ponto.hpp"

#include <iostream>

class ListaEncadeada {
private:
  struct Node {
    Ponto data; // Dado armazenado no node
    Node *next;

    Node(const Ponto &value) : data(value), next(nullptr) {} // Construtor do node
  };

  Node *head;
  int size;

public:
  ListaEncadeada();
  ~ListaEncadeada();

  ListaEncadeada(const ListaEncadeada &other); // Construtor de cópia
  ListaEncadeada &operator=(const ListaEncadeada &other); // Operador de atribuição 

  void push_front(const Ponto &value);
  void push_back(const Ponto &value);
  void remove(const Ponto &value);
  void clear();
  void set(int index, const Ponto& value);

  int getSize() const;
  Ponto getData(int index) const;
};

#endif
