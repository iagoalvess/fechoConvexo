#include "fecho_convexo.hpp"

FechoConvexo::FechoConvexo() : _tamanho(0) {
  // Construtor padrão que inicializa o tamanho como 0.
}



FechoConvexo::FechoConvexo(const Ponto* p, int tamanho) : _tamanho(tamanho) {
  if (tamanho < 0) {
    throw std::invalid_argument("Tamanho inválido.");
  }

  // Construtor que recebe um array de pontos e seu tamanho.
  for (int i = 0; i < tamanho; i++) {
    pontos.push_back(p[i]);
  }
  // Adiciona cada ponto do array à lista de pontos.
}



const ListaEncadeada& FechoConvexo::getLista() const {
  return pontos;
  // Retorna a lista de pontos.
}



void FechoConvexo::addPontoLista(Ponto p) {
  pontos.push_back(p);
  _tamanho++;
  // Adiciona um ponto à lista de pontos e incrementa o tamanho.
}



int FechoConvexo::getTamanho() const {
  return _tamanho;
  // Retorna o tamanho da lista de pontos.
}
