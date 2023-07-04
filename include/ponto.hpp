#ifndef PONTO_H
#define PONTO_H

class Ponto {
private:
  int _x;
  int _y;

public:
  Ponto();
  Ponto(int x, int y);

  int distancia(const Ponto& p2) const;

  void troca(Ponto& p2);

  int comparar(const Ponto& p1, const Ponto& p2) const;
  int orientacao(const Ponto& q, const Ponto& r) const;

  bool operator==(const Ponto& other) const;

  int getX() const;
  int getY() const;
};

#endif