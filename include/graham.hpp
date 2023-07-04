#ifndef GRAHAM_H
#define GRAHAM_H

#include "ponto.hpp"
#include "fecho_convexo.hpp"
#include "pilha.hpp"

#include <iostream>

class Graham {
private:
  Ponto p0; // Ponto de referência

  int tipoOrdenacao; // Armazena qual ordenação será usada em Graham

  FechoConvexo* grahamHull; // Fecho convexo resultante

public:
  Graham();
  Graham(int tipoOrd);
  ~Graham();
  
  Ponto proxAoTopo(Pilha &S);

  int encontrarMenorPonto(Ponto points[], int tamanho);

  void sort(Ponto points[], int tamanho);
  void insertionSort(Ponto points[], int tamanho);
  void mergeSort(Ponto* points, int esq, int dir);
  void merge(Ponto* points, int esq, int meio, int dir);
  //void bucketSort(Ponto pontos[], int tamanho);
  void convexHull(Ponto points[], int tamanho);

  FechoConvexo getHull();
};

#endif
