#include "../includes/Algoritmo.h"
#include "../includes/Busquedas.h"

Algoritmo::Algoritmo(int clientes, int vehiculos,std::vector<std::vector<int> > matrix){
    customers = clientes;
    vehicles = vehiculos;
    matriz = matrix;
}

Algoritmo::~Algoritmo(){
    customers = 0;
    vehicles = 0;
    matriz.clear();
}

bool Algoritmo::isZero(std::vector<int> array){

    for (int i = 1; i < array.size(); i++) {
    if (array[i] != 0) {
      return false;
    }
  }
  return true;
}

void Algoritmo::generateRLC(std::vector<int>& RLCR, std::vector<int>& RLCV, std::vector<int> fila, int size_RLC){
    int elemento;
  std::vector<int> matrix = fila;
  for (int i = 0; i < size_RLC; i++) {
    int minimo = 999999;
    for (int j = 1; j < matrix.size(); j++) {
      if ((minimo > matrix[j]) && (matrix[j] != 0)) {
        elemento = j;
        minimo = matrix[j];
      }
    }

    matrix[elemento] = 0;
    if (RLCR.size() < size_RLC) {
      RLCR.push_back(elemento);
      RLCV.push_back(minimo);
    }
  }
}

bool Algoritmo::isEmpty(std::vector<std::vector<int> > matrix){
    for (int i = 0; i < matrix.size(); i++) {
    for(int j = 1; j < matrix.size(); j++){
    if (matrix[i][j] != 0) {
      return false;
    }
  }
  }
  return true;
}

void Algoritmo::Greedy(){
   int size_route = 0;
  float prueba = 0;
  prueba = (customers / vehicles) + (customers * 0.1);
  size_route = ceil(prueba);
  std::vector<std::vector<int> > copia_matrix = matriz;


std::cout << std::endl << "ProblemSize\t\tDistanciaTotalRecorrida\t\tCPUTime" << std::endl;
	std::cout << "___________________________________________________________________" << std::endl;
  int contruta = 0;
  int contador = 0;
  int distanciaTotal = 0;
  std::vector<int> rutaParcial;
  std::vector<int> valorParcial;
  std::vector<int> rutafinal(1,0);
  long start = getCurrentTime();
  for (int i = 0; i < matriz.size(); i++) {
    int elemento = 0;
    int minimo = 999999;
    for (int j = 1; j < matriz.size(); j++) {
      if (isZero(matriz[i]) == true) {
        elemento = 0;
        minimo = matriz[i][elemento];
        contador = size_route - 1;
      } else if (minimo > matriz[i][j] && matriz[i][j] != 0) {
        elemento = j;
        minimo = matriz[i][j];
      }
    }

    //std::cout << "El menor elemento en la fila: " << i << ", es el: " << elemento << ", con valor: " << matriz[i][elemento] << std::endl;
    valorParcial.push_back(matriz[i][elemento]);
    rutaParcial.push_back(elemento);
    for (int j = 0; j < matriz.size(); j++) {
      matriz[j][elemento] = 0;
    }

    
    i = elemento - 1;
    contador++;//

    //std::cout << std::endl;
    /*for (int j = 0; j < matriz.size(); j++) {
      for (int k = 0; k < matriz.size(); k++) {
        std::cout << matriz[j][k] << " ";
      }
      std::cout << std::endl;
    }*/

    if (contador == size_route || isEmpty(matriz)) {
      i = -1;
      rutaParcial.push_back(0);
      valorParcial.push_back(matriz[elemento][0]);

      int distancia = 0;
      for (int j = 0; j < rutaParcial.size(); j++) {
        rutafinal.push_back(rutaParcial[j]);
        distancia += valorParcial[j];
      }
      contruta++;
      rutaParcial.clear();
      valorParcial.clear();
      distanciaTotal += distancia;

      contador = 0;
      if (contruta == vehicles) {
        std::cout << std::endl;
        long totalTime = getCurrentTime() - start;
        std::cout << matriz.size() - 1 << "\t\t\t\t" << distanciaTotal << "\t\t\t" << totalTime << std::endl;
        std::cout << "---------------------------------------------------------------" << std::endl;
        std::cout << "Mejor Ruta: " << std::endl;
        for (int j = 0; j < rutafinal.size(); j++){
          std::cout << rutafinal[j] << " ";
        }
        std::cout << std::endl;
        break;
      }
    }
  }

  Busquedas *busquedaLocal = new Busquedas(copia_matrix,rutafinal,distanciaTotal,vehicles);
  busquedaLocal ->IntercambioIntraRuta();
  busquedaLocal ->IntercambioEntreRutas();
  busquedaLocal ->InsercionIntraRuta(); 
  busquedaLocal ->InsercionEntreRutas(); 
}

void Algoritmo::Grasp(){
    srand(time(NULL));
  int size_route = 0;
  float prueba = 0;
  prueba = (customers / vehicles) + (customers * 0.1);
  size_route = ceil(prueba);

  int iterations = getNumberIterations();
  int RLCSize = getRLCVectorSize();
  int noImprove = getTimesWithoutImprove();
  
  std::cout << std::endl << "ProblemSize\t\t|LRC|\t\tEjecucion\t\tDistanciaTotalRecorrida\t\tCPUTime" << std::endl;
	std::cout << "________________________________________________________________________________________________________________________" << std::endl;

  long start = getCurrentTime();
  std::vector<int> valorParcial;
  std::vector<int> rutaSolucion;
  std::vector<int> rutaParcial;
  int mejorDistancia = 9999999;
  int contadorIteraciones = 0;
  int contadorNoImprove = 0;
  int distanciaTotal = 0;
  int contruta = 0;
  int contador = 0;
  std::vector<std::vector<int> > copia_matrix = matriz;
  while ((contadorIteraciones < iterations) && (contadorNoImprove != noImprove)) {
    std::vector<std::vector<int> > matrix = matriz;
    std::vector<int> rutafinal(1,0);
    for (int i = 0; i < matrix.size(); i++) {
      std::vector<int> RLCValor;
      std::vector<int> RLCRuta;
      int minimo = 999999;
      int elemento = 0;
      int ind = 0;
      for (int j = 1; j < matrix.size(); j++) {
        if (isZero(matrix[i]) == true) {
          elemento = 0;
          minimo = matrix[i][elemento];
          contador = size_route - 1;
        } else {
          generateRLC(RLCRuta, RLCValor, matrix[i], RLCSize);
          elemento = RLCRuta[ind];
          minimo = RLCValor[ind];
          ind = rand() % RLCRuta.size();
        }
      }
      
      valorParcial.push_back(matrix[i][elemento]);
      rutaParcial.push_back(elemento);
      for (int j = 0; j <matrix.size(); j++){
        matrix[j][elemento] = 0;
      }
      i = elemento -1;
      contador++;//
      
      if (contador == size_route || isEmpty(matrix)) {
        i = -1;
        rutaParcial.push_back(0);
        valorParcial.push_back(matrix[elemento][0]);

        int distancia = 0;
        for (int j = 0; j < rutaParcial.size(); j++) {
          rutafinal.push_back(rutaParcial[j]);
          distancia += valorParcial[j];
        }
        distanciaTotal += distancia;
        valorParcial.clear();
        rutaParcial.clear();
        contador = 0;//
        contruta++;

        if (contruta == vehicles) {

          long totalTime = getCurrentTime() - start;
          std::cout << matriz.size() - 1 << "\t\t\t" << RLCSize << "\t\t" << contadorIteraciones + 1 << "\t\t\t\t" << distanciaTotal << "\t\t\t" << totalTime << std::endl;
          if (mejorDistancia > distanciaTotal) {
            mejorDistancia = distanciaTotal;
            rutaSolucion = rutafinal;
            contadorNoImprove = 0;
            distanciaTotal = 0;
            rutafinal.clear();
          } else {
            contadorNoImprove++;
            distanciaTotal = 0;
          }
          contadorIteraciones++;
          matrix.clear();
          contruta = 0;
          break;
        }
      }
    }
  }
  std::cout << std::endl << "--------------------------------------------------------------------------------" << std::endl;
  std::cout << std::endl << "Mejor Distancia Final: " << mejorDistancia << std::endl << " --------------";
  std::cout << std::endl << "Mejor Ruta Final: " ;
  for (int i = 0; i < rutaSolucion.size(); i++) {
    std::cout << rutaSolucion[i] << " ";
  }
  std::cout << std::endl;

  Busquedas *busquedaLocal = new Busquedas(copia_matrix,rutaSolucion,mejorDistancia,vehicles);
  busquedaLocal ->IntercambioIntraRuta();
  busquedaLocal ->IntercambioEntreRutas();
  busquedaLocal ->InsercionIntraRuta(); 
  busquedaLocal ->InsercionEntreRutas(); 
}

int Algoritmo::getNumberIterations(){
    	std::string input = "";
	while (true) {
		std::cout << "Introduzca el número de iteraciones que llevará a cabo el algoritmo Grasp: " << std::endl << "\t>> ";
		std::cin >> input;
		if (input.find_first_not_of("0123456789") == std::string::npos) {
			return stoi(input);
		} else {
			std::cout << std::endl << "Introduzca un numero entero." << std::endl << std::endl;
			input = "";
		}
	}
}

int Algoritmo::getRLCVectorSize(){
      std::string input = "";
	while (true) {
		std::cout << "Introduzca el tamaño deseado para la RLC: " << std::endl << "\t>> ";
		std::cin >> input;
		if (input.find_first_not_of("0123456789") == std::string::npos) {
			return stoi(input);
		} else {
			std::cout << std::endl << "Introduzca un numero entero." << std::endl << std::endl;
			input = "";
		}
	}
}

int Algoritmo::getTimesWithoutImprove(){
    std::string input = "";
	while (true) {
		std::cout << "Introduzca el número de iteraciones antes de parar la ejecución, sin una mejora en la solución: " << std::endl << "\t>> ";
		std::cin >> input;
		if (input.find_first_not_of("0123456789") == std::string::npos) {
			return stoi(input);
		} else {
			std::cout << std::endl << "Introduzca un numero entero." << std::endl << std::endl;
			input = "";
		}
	}
}

long Algoritmo::getCurrentTime(){
      struct timeval tv;
  gettimeofday(&tv, NULL);
  return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}