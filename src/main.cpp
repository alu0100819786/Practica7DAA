/*=======================================================================================
=========================================================================================
    =                                                                              =
    =            Proyect:       Practica 7 VRP con Greedy y Grasp                  =
    =            File name:     main.cpp                                           =
    =            Author:        Gabriel Melián Hernández                           =
    =            Email:         alu0100819786@ull.edu.es                           =
    =                                                                              =
=========================================================================================
=======================================================================================*/

#ifndef MAIN_
#define MAIN_

/*-----DECLARACIÓN DE LBIRERIAS-----*/
#include <sys/time.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <cmath>
/*-----DECLARACIÓN DE FUNCIONES-----*/
void help();
bool useGreedy();
long getCurrentTime();
int getRLCVectorSize();
int getNumberIterations();
int getTimesWithoutImprove();
bool isZero(std::vector<int> array);
std::string deleteWhiteSpacesSurround(std::string str);
void Greedy(int customers, int vehicles, std::vector<std::vector<int> > matriz);
void Grasp (int customers, int vehicles, std::vector<std::vector<int> > matriz);
void generateRLC(std::vector<int>& RLCR, std::vector<int>& RLCV, std::vector<int> fila, int size_RLC);

/**
Función main en la que vamos a recibir como argumentos en la llamada al programa, el fichero de entrada de datos, vamos a almacenar su contenido en las variables 
correspondientes, además de crear la matriz de distancias entre clientes. Por último llamaremos a la función "useGreedy" que devolverá true o false para conocer
que tipo de algoritmo tenemos que ejecutar.
*/
int main(int argc, char *argv[]) {
  int n_customers = 0;
  int n_vehicles = 0;
  std::vector<std::vector<int> > matrix = std::vector<std::vector<int> >();

	if (argc != 2) {
		std::cerr << "Numero de argumentos incorrecto." << std::endl;
		help();
		return 1;
	}

	std::string fileName = argv[1];
  std::ifstream input(fileName.c_str());
  if (input.is_open()) {
    int lineCounter = 1;
    std::string line;
    while (std::getline(input, line)) {
      int found;
      if ((found = line.find("n_clientes:")) != std::string::npos) {
        line = line.substr(found + 11);
        line = deleteWhiteSpacesSurround(line);
        if (line.find_first_not_of("0123456789") != std::string::npos) {
          std::cerr << "Ha introducido caracteres en vez de numeros." << std::endl;
          return 1;
        }
        n_customers = std::stoi(line);
      } else if ((found = line.find("n_vehiculos:")) != std::string::npos) {
        line = line.substr(found + 12);
        line = deleteWhiteSpacesSurround(line);
        if (line.find_first_not_of("0123456789") != std::string::npos) {
          std::cerr << "Ha introducido caracteres en vez de numeros." << std::endl;
          return 1;
        }
        n_vehicles = std::stoi(line);
      } else if (lineCounter > 3) {
        std::vector<int> row = std::vector<int>();
        line = deleteWhiteSpacesSurround(line);
        while (!line.empty()) {
          found = line.find_first_of(" \t");
          std::string aux = line.substr(0, found);

          if (aux.find_first_not_of("0123456789") != std::string::npos) {
            std::cerr << "Ha introducido caracteres en vez de numeros." << std::endl;
            return 1;
          }
          row.push_back(std::stoi(aux));

          line.erase(0, aux.size());
          line = deleteWhiteSpacesSurround(line);
        }
        matrix.push_back(row);
      }

      lineCounter++;
    }
  } else {
    std::cerr << "No se ha podido abrir el fichero de entrada. " << fileName << std::endl;
    return 1;
  }

  if (useGreedy()) {
    Greedy(n_customers, n_vehicles, matrix);
  } else {
    Grasp(n_customers, n_vehicles, matrix);
  }
};

/**
Función de ayuda que devuelve diferentes mensajes de texto por pantalla, para ayudar al usuario a ejecutar de correcta forma nuestro
programa.
*/
void help() {
	std::cout << std::endl << "Se requiere de 1 parámetro:" << std::endl;
	std::cout << "\t1º- Nombre del fichero de entrada." << std::endl;
	std::cout << "./vrp <input-file-name>" << std::endl;
}

/**
Función booleana, que recibirá la respuesta del usuario al tipo de algoritmo que vamos a ejecutar, si la respuesta es Sí, se llamará y ejecutará el algoritmo Greedy, mientras
que en caso contrario, llamaríamos y ejecutaríamos el algoritmo Grasp.
*/
bool useGreedy() {
  std::string input = "";
	while (true) {
		std::cout << "¿Ejecutar el algoritmo greedy (si/no)?: " << std::endl << "\t>> ";
		std::cin >> input;
		if ((input == "si") || (input == "SI") || (input == "Si")) {
			return true;
		} else if ((input == "no") || (input == "NO") || (input == "No")) {
      return false;
    } else {
			std::cout << std::endl << "Escriba una opcion correcta." << std::endl << std::endl;
			input = "";
		}
	}
}

/**
Función para conseguir el tiempo actual, que usaremos en los algoritmos, para conseguir el tiempo de ejecución para ambos.
*/
long getCurrentTime() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

/**
Función para conseguir el tamaño deseado para la RLC a la hora de ejecutar nuestro algoritmo Grasp. Pedimos al usuario que introduzca un número entero que será
el tamaño del vector que contendrá nuestra RLC.
*/
int getRLCVectorSize() {
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

/**
Función donde conseguiremos el número de iteraciones que llevará a cabo nuestro algoritmo Grasp antes de terminar su ejecución. Este número será una de nuestras condiciones
de parada en el bucle while perteneciente al algoritmo Grasp.
*/
int getNumberIterations() {
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

/**
Función para conseguir la segunda condición de parada de nuestro bucle While para la ejecución del algoritmo Grasp. En este caso necesitaremos conseguir por parte del usuario
un número entero que ejemplifique el número de iteraciones seguidas sin que se mejore la solución obtenida previamente antes de parar la ejecución.
*/
int getTimesWithoutImprove() {
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

/**
Función booleana que nos devolverá verdadero si el array que recibe tiene todos sus valores a cero y falso en caso contrario. con esto sabremos que tenemos visitados
a todos los clientes y debemos volver al depósito. 
*/
bool isZero(std::vector<int> array) {
  for (int i = 1; i < array.size(); i++) {
    if (array[i] != 0) {
      return false;
    }
  }
  return true;
}

/**
Función que eliminará los espacios en blanco, tabulaciones y retornos de carro de nuestra entrada.
*/
std::string deleteWhiteSpacesSurround(std::string str) {
  while (!str.empty()) {
    if ((str[0] == ' ') || (str[0] == '\t') || ((int)str[0] == 13)) {
      str.erase(str.begin());
    } else if ((str[str.size() - 1] == ' ')  || (str[str.size() - 1] == '\t') || ((int)str[str.size() - 1] == 13)) {
      str.erase(str.size() - 1);
    } else {
      break;
    }
  }
  return str;
}

/**
Algoritmo Greedy que buscará la mejor ruta avanzando de cliente en cliente utilizando como medida para desplazarse, la menor distancia entre clientes. En el momento que 
haya visitado el número máximo de clientes, volverá al depósito y realizará una nueva ruta para los demás clientes.
Conseguiremos el tamaño de la ruta dividiendo el número de clientes entre los vehículos disponibles.
Recorreremos la fila inicial de la matriz buscando el vecino mas cercano, nos moveremos a dicho vecino, almacenando su distancia y que vecino es, antes de poner toda la
columna asociada a dicho vecino a 0 ya que ya lo hemos recogido y no volveremos a necesitar su información desde cualquier otro vecino, a partir de aqui repetimos proceso
desde la nueva fila asociada al vecino que acabamos de recoger e iremos rellenando nuestra ruta a la vez que vacíamos la matriz, hasta dejarla totalmente a 0.
*/
void Greedy(int customers, int vehicles ,std::vector<std::vector<int> > matriz) {
  int size_route = 0;
  if ((customers % vehicles) == 0) {
    size_route = customers / vehicles;
  } else {
    size_route = customers / vehicles + 1;
  }

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

    if (contador == size_route) {
      i = -1;
      rutaParcial.push_back(0);
      valorParcial.push_back(matriz[elemento][0]);

      int distancia = 0;
      for (int j = 0; j < size_route + 1; j++) {
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
        exit(0);
      }
    }
  }
}

/**
Función para nuestro algoritmo Grasp que funcionará de forma similar al Greedy, pero añadiendo una RLC desde la que escogerá de forma aleatoria uno de los valores
y este valor será el nuevo vecino recogido. Además también tendrá un nuevo bucle While que ejecutará el algoritmo hasta que se cumpla alguna de sus dos condiciones
de parada (nº de iteraciones o nº de iteraciones sin mejorar la solución). Se irá almacenando la solución de cada una de las iteraciones para compararla con la siguiente
almacenando la mejor, para así poder dar un resultado final a la hora de finalizar la ejecución.
*/
void Grasp(int customers, int vehicles ,std::vector<std::vector<int> > matriz){
  srand(time(NULL));
  int size_route = 0;
  if ((customers % vehicles) == 0){
    size_route = customers / vehicles;
  } else {
    size_route = customers / vehicles + 1;
  }

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
      
      if (contador == size_route) {
        i = -1;
        rutaParcial.push_back(0);
        valorParcial.push_back(matrix[elemento][0]);

        int distancia = 0;
        for (int j = 0; j < size_route + 1; j++) {
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
}

/**
Función que recibe una de las filas de la matriz, las RLC tanto de ruta como de valor y el tamaño de la RLC y genera la RLC correspondiente dependiendo de la fila y del tamaño
escogiendo los valores mas pequeños que representarán las menores distancias hasta el siguietne vecino.
*/
void generateRLC(std::vector<int>& RLCR, std::vector<int>& RLCV, std::vector<int> fila, int size_RLC) {
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
#endif