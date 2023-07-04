#ifndef JARVIS_H
#define JARVIS_H

#include "ponto.hpp"
#include "fecho_convexo.hpp"

class Jarvis {
private:
  FechoConvexo* jasvisHull; // Fecho convexo resultante

public:
  Jarvis();
  ~Jarvis();
  
  void convexHull(Ponto points[], int tamanho);

  FechoConvexo getHull();
};

#endif
