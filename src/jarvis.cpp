#include "jarvis.hpp"

Jarvis::Jarvis() {
  jasvisHull = new FechoConvexo(nullptr, 0);
}



Jarvis::~Jarvis() {
  delete jasvisHull;
}



void Jarvis::convexHull(Ponto points[], int tamanho) {
  // Verifica se há pelo menos 3 pontos
  if (tamanho < 3) {
    throw std::invalid_argument("Tamanho invalido!");
  }

  // Encontra o ponto mais à esquerda
  int pontoEsquerda = 0;
  for (int i = 1; i < tamanho; i++) {
    if (points[i].getX() < points[pontoEsquerda].getX()) {
      pontoEsquerda = i;
    }
  }

  // Inicializa a lista de pontos do casco convexo
  int pontoAtual = pontoEsquerda;
  int proximoPonto;

  do {
    jasvisHull->addPontoLista(points[pontoAtual]);
    proximoPonto = (pontoAtual + 1) % tamanho;

    for (int i = 0; i < tamanho; i++) {
      // Verifica se o ponto i é mais à esquerda do que o pontoAtual e proximoPonto
      if (points[pontoAtual].orientacao(points[i], points[proximoPonto]) == 2) {
        proximoPonto = i;
      }
    }

    pontoAtual = proximoPonto;

  } while (pontoAtual != pontoEsquerda);
}



FechoConvexo Jarvis::getHull() {
  return *jasvisHull;
}