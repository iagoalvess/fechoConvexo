#include "ponto.hpp"

Ponto::Ponto() : _x(0), _y(0) {}



Ponto::Ponto(int x, int y) : _x(x), _y(y) {}



// Calcula a distância ao quadrado entre dois pontos.
int Ponto::distancia(const Ponto& p2) const {
  int dx = this->_x - p2._x;
  int dy = this->_y - p2._y;

  return (dx * dx) + (dy * dy);
}



// Troca as coordenadas de dois pontos.
void Ponto::troca(Ponto& p2) {
  int tempX = this->_x;
  int tempY = this->_y;

  this->_x = p2._x;
  this->_y = p2._y;

  p2._x = tempX;
  p2._y = tempY;
}



// Determina a orientação de três pontos em relação ao sentido horário ou anti-horário.
int Ponto::orientacao(const Ponto& q, const Ponto& r) const {
  int area = (q._y - this->_y) * (r._x - q._x) - (q._x - this->_x) * (r._y - q._y);

  if (area == 0) return 0; // Os pontos são colineares

  else if (area > 0) return 1; // Sentido horário (clockwise)

  else return 2; // Sentido anti-horário (counterclockwise)
}



// Compara dois pontos com base na sua orientação e distância em relação a um terceiro ponto.
int Ponto::comparar(const Ponto& p1, const Ponto& p2) const {
  int o = orientacao(p1, p2);

  if (o == 0) {
    // Os pontos são colineares. Compara as distâncias ao quadrado.
    if (distancia(p2) >= distancia(p1)) return -1;
    else return 1;
  }
  else {
    // Os pontos não são colineares. Compara a orientação.
    if (o == 2) return -1;
    else return 1;
  }
}



// Dada a operação Ponto = Ponto, compara os valores x e y
bool Ponto::operator==(const Ponto& other) const {
  return (_x == other._x) && (_y == other._y);
}



int Ponto::getX() const {
    return _x;
}



int Ponto::getY() const {
    return _y;
}
