#ifndef FECHO_CONVEXO_H
#define FECHO_CONVEXO_H

#include "ponto.hpp"
#include "lista_encadeada.hpp"

class FechoConvexo {
private:
  ListaEncadeada pontos;

  int _tamanho;

public:
  FechoConvexo();
  FechoConvexo(const Ponto* p, int tamanho);

  const ListaEncadeada& getLista() const;
  void addPontoLista(Ponto p);
  int getTamanho() const;
};

#endif