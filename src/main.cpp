#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <cstring>

#include "graham.hpp"
#include "jarvis.hpp"

const int MAX_PONTOS = 1000;

// Função para ler uma linha de entrada e converter em um objeto Ponto
int lerPontos(const std::string& arquivo, Ponto* pontos) {
  std::ifstream arquivoEntrada(arquivo);
  if (!arquivoEntrada) {
    throw std::invalid_argument("Erro: não foi possível abrir o arquivo.");
  }

  std::string linha;
  int tamanho = 0;

  try {
    while (std::getline(arquivoEntrada, linha) && tamanho < MAX_PONTOS) {
      std::istringstream iss(linha);
      int x, y;
      if (iss >> x >> y) {
        pontos[tamanho] = Ponto(x, y);
        tamanho++;
      } else {
        throw std::invalid_argument("Valores invalidos encontrados no arquivo de entrada.");
      }
    }
  } catch (const std::invalid_argument& e) {
    arquivoEntrada.close();
    throw e;
  }

  arquivoEntrada.close();
  return tamanho;
}



// Função para imprimir um array de pontos
void printPoints(Ponto* pontos, int tamanho) {
  std::cout << "FECHO CONVEXO:" << std::endl;
  for (int i = 0; i < tamanho; i++) {
    std::cout << pontos[i].getX() << " " << pontos[i].getY() << std::endl;
  }
}



void calcularTempoGrahamInsert(Ponto* pontos, int tamanho) {
  Ponto* pontosCopia = new Ponto[tamanho];
  memcpy(pontosCopia, pontos, tamanho * sizeof(Ponto));

  Graham insertionHull(0);
  clock_t inicio = clock();
  insertionHull.convexHull(pontosCopia, tamanho);
  clock_t fim = clock();
  double tempoInsertion = static_cast<double>(fim - inicio) / CLOCKS_PER_SEC; 

  std::cout << "GRAHAM+INSERTIONSORT: " << std::fixed << std::setprecision(3) << tempoInsertion << "s\n";

  delete[] pontosCopia;
}



void calcularTempoGrahamMerge(Ponto* pontos, int tamanho) {
  Ponto* pontosCopia = new Ponto[tamanho];
  memcpy(pontosCopia, pontos, tamanho * sizeof(Ponto));

  Graham mergeHull(1);
  clock_t inicio = clock();
  mergeHull.convexHull(pontosCopia, tamanho);
  clock_t fim = clock();
  double tempoMerge = static_cast<double>(fim - inicio) / CLOCKS_PER_SEC;

  std::cout << "GRAHAM+MERGESORT: " << std::fixed << std::setprecision(3) << tempoMerge << "s\n";

  delete[] pontosCopia;
}



/* void calcularTempoGrahamBucket(Ponto* pontos, int tamanho) {
  Ponto* pontosCopia = new Ponto[tamanho];
  memcpy(pontosCopia, pontos, tamanho * sizeof(Ponto));

  Graham bucketHull(2);
  clock_t inicio = clock();
  bucketHull.convexHull(pontosCopia, tamanho);
  clock_t fim = clock();
  double tempoBucket = static_cast<double>(fim - inicio) / CLOCKS_PER_SEC;

  std::cout << "GRAHAM+BUCKETSORT: " << std::fixed << std::setprecision(3) << tempoBucket << "s\n";

  delete[] pontosCopia;
} */



void calcularTempoJarvis(Ponto* pontos, int tamanho) {
  Ponto* pontosCopia = new Ponto[tamanho];
  memcpy(pontosCopia, pontos, tamanho * sizeof(Ponto));

  Jarvis jHull;
  clock_t inicio = clock();
  jHull.convexHull(pontosCopia, tamanho);
  clock_t fim = clock();
  double tempoJarvis = static_cast<double>(fim - inicio) / CLOCKS_PER_SEC;

  std::cout << "JARVIS: " << std::fixed << std::setprecision(3) << tempoJarvis << "s\n";

  delete[] pontosCopia;
}



void imprimirFechoConvexo(Ponto* pontos, int tamanho) {
  Ponto* pontosCopia = new Ponto[tamanho];
  memcpy(pontosCopia, pontos, tamanho * sizeof(Ponto));

  try {
    Jarvis jHull;
    jHull.convexHull(pontosCopia, tamanho);

    std::cout << "FECHO CONVEXO:" << std::endl;
    for (int i = 0; i < jHull.getHull().getTamanho(); i++) {
      int x = jHull.getHull().getLista().getData(i).getX();
      int y = jHull.getHull().getLista().getData(i).getY();

      std::cout << x << ", " << y << std::endl;
    }
    std::cout << std::endl;
  } catch (const std::invalid_argument& e) {
    delete[] pontosCopia;
    throw e;
  }

  delete[] pontosCopia;
}



void testesTempos(Ponto* pontos, int tamanho) {
  Ponto* pontosCopia = new Ponto[tamanho]; // Cria uma cópia do vetor de pontos

  // Copia o vetor de pontos para a cópia
  memcpy(pontosCopia, pontos, tamanho * sizeof(Ponto));

  try {
    calcularTempoGrahamInsert(pontosCopia, tamanho);

    memcpy(pontosCopia, pontos, tamanho * sizeof(Ponto));

    calcularTempoGrahamMerge(pontosCopia, tamanho);

    memcpy(pontosCopia, pontos, tamanho * sizeof(Ponto));

    // calcularTempoGrahamBucket(pontosCopia, tamanho);

    // memcpy(pontosCopia, pontos, tamanho * sizeof(Ponto));

    calcularTempoJarvis(pontosCopia, tamanho);
  } catch (const std::invalid_argument& e) {
    delete[] pontosCopia;
    throw e;
  }

  delete[] pontosCopia;
}



int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cout << "Erro: Inclua o arquivo na linha de comando." << std::endl;
    return 1;
  }
  std::string arquivo = argv[1];

  std::ifstream arquivoEntrada(arquivo);
  if (!arquivoEntrada) {
    std::cout << "Erro: não foi possível abrir o arquivo." << std::endl;
    return 1;
  }

  Ponto pontos[MAX_PONTOS];
  int tamanho = 0;

  try {
    tamanho = lerPontos(arquivo, pontos);
  } catch (const std::invalid_argument& e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }

  if (tamanho == 0) {
    std::cout << "Nenhum ponto válido foi encontrado no arquivo de entrada." << std::endl;
    return 1;
  }

  try {
  imprimirFechoConvexo(pontos, tamanho);

  testesTempos(pontos, tamanho);
  } catch (const std::invalid_argument &e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }

  return 0;
}

