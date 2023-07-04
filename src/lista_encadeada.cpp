#include "lista_encadeada.hpp"

ListaEncadeada::ListaEncadeada() : head(nullptr), size(0) {
  // Construtor padrão
}



ListaEncadeada::~ListaEncadeada() {
  clear();
  // Destrutor
}



ListaEncadeada::ListaEncadeada(const ListaEncadeada &other) : head(nullptr), size(0) {
  Node *current = other.head;

  while (current != nullptr) {
    push_back(current->data);
    current = current->next;
  }
  // Construtor de cópia
}



ListaEncadeada &ListaEncadeada::operator=(const ListaEncadeada &other) {
  if (this != &other) {
    clear();
    Node *current = other.head;

    while (current != nullptr) {
      push_back(current->data);
      current = current->next;
    }
  }

  return *this;
  // Operador de atribuição
}



void ListaEncadeada::push_front(const Ponto &value) {
  Node *newNode = new Node(value);

  newNode->next = head;
  head = newNode;

  size++;
  // Insere um elemento no início da lista
}



void ListaEncadeada::push_back(const Ponto &value) {
  Node *newNode = new Node(value);

  if (head == nullptr) {
    head = newNode;
  }
  else {
    Node *current = head;

    while (current->next != nullptr) {
      current = current->next;
    }
    current->next = newNode;
  }

  size++;
  // Insere um elemento no final da lista
}



void ListaEncadeada::remove(const Ponto &value) {
  if (head == nullptr) {
    return;
  }

  if (head->data == value) {
    Node *temp = head;
    head = head->next;
    delete temp;
    size--;
    return;
  }

  Node *current = head;
  while (current->next != nullptr) {
    if (current->next->data == value) {
      Node *temp = current->next;
      current->next = current->next->next;
      delete temp;
      size--;
      return;
    }
    current = current->next;
  }
  // Remove um elemento da lista
}



void ListaEncadeada::clear() {
  Node *current = head;

  while (current != nullptr) {
    Node *temp = current;
    current = current->next;
    delete temp;
  }

  head = nullptr;
  size = 0;
  // Remove todos os elementos da lista
}



void ListaEncadeada::set(int index, const Ponto& value) {
  if (index < 0 || index >= size) {
    throw std::out_of_range("Índice inválido");
  }

  Node *current = head;
  int count = 0;

  while (current != nullptr && count < index) {
    current = current->next;
    count++;
  }

  if (current != nullptr) {
    current->data = value;
  }
  // Define o valor de um elemento em um índice específico
}



int ListaEncadeada::getSize() const {
  return size;
  // Obtém o tamanho da lista
}



Ponto ListaEncadeada::getData(int index) const {
  if (index < 0 || index >= size) {
    throw std::out_of_range("Indice fora de alcance");
  }

  Node *current = head;
  for (int i = 0; i < index; i++) {
    current = current->next;
  }

  return current->data;
  // Obtém o dado armazenado em um determinado índice da lista
}
