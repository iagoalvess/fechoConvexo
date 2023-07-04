#include "graham.hpp"

Graham::Graham() : tipoOrdenacao(0) {
  grahamHull = new FechoConvexo(nullptr, 0);
}



Graham::Graham(int tipoOrd) : tipoOrdenacao(tipoOrd) {
  grahamHull = new FechoConvexo(nullptr, 0);
}



Graham::~Graham() {
  delete grahamHull;
}



// Retorna o próximo elemento abaixo do topo da pilha
Ponto Graham::proxAoTopo(Pilha &pilha) {
  // Armazena o valor do topo atual
  Ponto topoAtual = pilha.valorTopo();

  // Desempilha o elemento do topo
  pilha.desempilhar();

  // Armazena o próximo elemento após desempilhar o topo atual
  Ponto proximoElemento = pilha.valorTopo();

  // Empilha novamente o elemento do topo inicial
  pilha.empilhar(topoAtual);

  // Retorna o próximo elemento abaixo do topo
  return proximoElemento;
}



// Encontra o índice do ponto com a menor coordenada y
int Graham::encontrarMenorPonto(Ponto pontos[], int tamanho) {
  int indiceMenor = 0;

  for (int i = 1; i < tamanho; i++) {
    // Verifica se o ponto atual possui uma coordenada y menor
    if (pontos[i].getY() < pontos[indiceMenor].getY() ||
        (pontos[i].getY() == pontos[indiceMenor].getY() && pontos[i].getX() < pontos[indiceMenor].getX())) {
      indiceMenor = i;
    }
  }

  // Retorna o índice do ponto com a menor coordenada y (e menor coordenada x em caso de empate)
  return indiceMenor;
}



// Trata a variavel tipoOrdenacao para saber qual metodo ordenatorio executar
void Graham::sort(Ponto pontos[], int tamanho) {
  if (tipoOrdenacao == 0) {
    insertionSort(pontos, tamanho);
  }
  else if (tipoOrdenacao == 1) {
    mergeSort(pontos, 0, tamanho - 1);
  }
  /* else if (tipoOrdenacao == 2) {
    bucketSort(pontos, tamanho);
  } */
  // Lança uma exceção para algum valor invalido
  else {
    throw std::invalid_argument("Tipo de ordenacao invalido");
  }
}



void Graham::insertionSort(Ponto pontos[], int tamanho) {
  // Aplica o algoritmo de ordenação por inserção nos pontos
  for (int i = 1; i < tamanho; i++) {
    Ponto chave = pontos[i];
    int j = i - 1;

    // Move os elementos maiores que a chave para a direita
    while (j >= 0 && p0.comparar(pontos[j], chave) > 0) {
      pontos[j + 1] = pontos[j];
      j = j - 1;
    }
    pontos[j + 1] = chave;
  }
}



void Graham::merge(Ponto* pontos, int esq, int meio, int dir) {
  // Determina o tamanho dos subarrays L e R
  int i, j, k;
  int n1 = meio - esq + 1;
  int n2 = dir - meio;

  // Cria os subarrays L e R
  Ponto L[n1], R[n2];

  // Copia os elementos dos subarrays originais para L e R
  for (i = 0; i < n1; i++) {
    L[i] = pontos[esq + i];
  }
  for (j = 0; j < n2; j++) {
    R[j] = pontos[meio + 1 + j];
  }

  i = 0;
  j = 0;
  k = esq;
  while (i < n1 && j < n2) {
    // Compara os elementos de L e R e os insere no array
    if (p0.comparar(L[i], R[j]) <= 0) {
      pontos[k] = L[i];
      i++;
    } else {
      pontos[k] = R[j];
      j++;
    }
    k++;
  }

  // Copia os elementos restantes de L (se houver) para pontos
  while (i < n1) {
    pontos[k] = L[i];
    i++;
    k++;
  }

  // Copia os elementos restantes de R (se houver) para pontos  
  while (j < n2) {
    pontos[k] = R[j];
    j++;
    k++;
  }
}



void Graham::mergeSort(Ponto* pontos, int esq, int dir) {
  // Verifica se ainda há elementos para ordenar
  if (esq < dir) {
    int meio = esq + (dir - esq) / 2; // Calcula o ponto médio do array

    // Divide o array em subarrays menores e ordena recursivamente
    mergeSort(pontos, esq, meio);
    mergeSort(pontos, meio + 1, dir);

    // Combina os subarrays ordenados em um único array ordenado
    merge(pontos, esq, meio, dir);
  }
}



/* void Graham::bucketSort(Ponto pontos[], int n) {
  // Encontra o valor máximo e mínimo do critério de comparação nos pontos
  int valorMaximo = p0.comparar(pontos[0], pontos[0]);
  int valorMinimo = p0.comparar(pontos[0], pontos[0]);
  for (int i = 1; i < n; i++) {
    int valor = p0.comparar(pontos[i], pontos[i]);
    if (valor > valorMaximo) {
      valorMaximo = valor;
    }
    if (valor < valorMinimo) {
      valorMinimo = valor;
    }
  }

  // Calcula o número de baldes com base no valor máximo e mínimo
  const int numBaldes = valorMaximo - valorMinimo + 1;
  ListaEncadeada baldes[numBaldes];

  // Coloca os elementos nos baldes de acordo com o critério de comparação
  for (int i = 0; i < n; i++) {
    int indiceBalde = p0.comparar(pontos[i], pontos[i]) - valorMinimo;
    baldes[indiceBalde].push_back(pontos[i]);
  }

  // Atualiza diretamente os elementos dos baldes no array original
  int indice = 0;
  for (int i = 0; i < numBaldes; i++) {
    int tamanhoBalde = baldes[i].getSize();
    
    for (int j = 0; j < tamanhoBalde; j++) {
      pontos[indice++] = baldes[i].getData(j);
    }

    // Ordena os pontos dentro do balde usando o insertion sort
    insertionSort(pontos + indice - tamanhoBalde, tamanhoBalde);
  }
} */



void Graham::convexHull(Ponto pontos[], int tamanho) {
  if (tamanho < 3) {
    throw std::invalid_argument("Tamanho invalido");
  }

  // Encontra o índice do ponto com a menor coordenada y
  int menorIndice = encontrarMenorPonto(pontos, tamanho);

  // Move o ponto de menor índice para a primeira posição
  pontos[0].troca(pontos[menorIndice]);

  // Define p0 como o ponto de referência para o cálculo das orientações
  p0 = pontos[0];

  // Ordena os pontos
  sort(pontos, tamanho);

  int m = 1; // Inicializa o tamanho do array modificado

  // Remove pontos colineares mantendo apenas o mais distante
  for (int i = 1; i < tamanho; i++) { 
    // Enquanto os pontos são colineares, avança para o próximo ponto
    while ((i < tamanho - 1) && (p0.orientacao(pontos[i], pontos[i + 1]) == 0))
      i++;
    pontos[m] = pontos[i];
    m++; // Atualiza o tamanho do array modificado
  }

  Pilha S;

  // Empilha os primeiros três pontos
  S.empilhar(pontos[0]);
  S.empilhar(pontos[1]);
  S.empilhar(pontos[2]);

  // Constrói o casco convexo
  for (int i = 3; i < m; i++) {
    // Enquanto os pontos formam uma orientação não à esquerda, remove o ponto do topo
    while (S.tamanho() > 1 && proxAoTopo(S).orientacao(S.valorTopo(), pontos[i]) != 2) {
      S.desempilhar();
    }
    S.empilhar(pontos[i]);
  }

  // Desempilha os pontos restantes e adiciona-os ao casco convexo
  while (!S.vazia()) {
    grahamHull->addPontoLista(S.valorTopo());
    S.desempilhar();
  }
}



FechoConvexo Graham::getHull() {
  return *grahamHull;
}