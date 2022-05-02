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




/**
Algoritmo Greedy que buscará la mejor ruta avanzando de cliente en cliente utilizando como medida para desplazarse, la menor distancia entre clientes. En el momento que 
haya visitado el número máximo de clientes, volverá al depósito y realizará una nueva ruta para los demás clientes.
Conseguiremos el tamaño de la ruta dividiendo el número de clientes entre los vehículos disponibles.
Recorreremos la fila inicial de la matriz buscando el vecino mas cercano, nos moveremos a dicho vecino, almacenando su distancia y que vecino es, antes de poner toda la
columna asociada a dicho vecino a 0 ya que ya lo hemos recogido y no volveremos a necesitar su información desde cualquier otro vecino, a partir de aqui repetimos proceso
desde la nueva fila asociada al vecino que acabamos de recoger e iremos rellenando nuestra ruta a la vez que vacíamos la matriz, hasta dejarla totalmente a 0.
*/
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
  int distanciaFINAL = 999999;
  std::vector<int> rutaFINAL;
  std::vector<int> rutaParcial;
  std::vector<int> valorParcial;
  std::vector<int> rutafinal(1,0);
  long start = getCurrentTime();
  for (int i = 0; i < copia_matrix.size(); i++) {
    int elemento = 0;
    int minimo = 999999;
    for (int j = 1; j < copia_matrix.size(); j++) {
      if (isZero(copia_matrix[i]) == true) {
        elemento = 0;
        minimo = copia_matrix[i][elemento];
        contador = size_route - 1;
      } else if (minimo > copia_matrix[i][j] && copia_matrix[i][j] != 0) {
        elemento = j;
        minimo = copia_matrix[i][j];
      }
    }

    //std::cout << "El menor elemento en la fila: " << i << ", es el: " << elemento << ", con valor: " << copia_matrix[i][elemento] << std::endl;
    valorParcial.push_back(copia_matrix[i][elemento]);
    rutaParcial.push_back(elemento);
    for (int j = 0; j < copia_matrix.size(); j++) {
      copia_matrix[j][elemento] = 0;
    }

    
    i = elemento - 1;
    contador++;//

    //std::cout << std::endl;
    /*for (int j = 0; j < copia_matrix.size(); j++) {
      for (int k = 0; k < copia_matrix.size(); k++) {
        std::cout << copia_matrix[j][k] << " ";
      }
      std::cout << std::endl;
    }*/

    if (contador == size_route || isEmpty(copia_matrix)) {
      i = -1;
      rutaParcial.push_back(0);
      valorParcial.push_back(copia_matrix[elemento][0]);

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
        std::cout << copia_matrix.size() - 1 << "\t\t\t\t" << distanciaTotal << "\t\t\t" << totalTime << std::endl;
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
int auxdecision = 0;
std::cout<< "Que tipo de busqueda quieres llevar a cabo: " << std::endl;
std::cout<< "0.-IntercambioIntraRuta." << std::endl;
std::cout<< "1.-IntercambioEntreRutas." << std::endl;
std::cout<< "2.-InsercionIntraRuta." << std::endl;
std::cout<< "3.-InsercionEntreRutas." << std::endl;
std::cin >> auxdecision;
  Busquedas *busquedaLocal = new Busquedas(matriz,rutafinal,distanciaTotal,vehicles,customers);
  if(auxdecision == 0){
busquedaLocal ->IntercambioIntraRuta();
  }
  if(auxdecision == 1){
    busquedaLocal ->IntercambioEntreRutas();
  }
  if(auxdecision == 2){
    busquedaLocal ->InsercionIntraRuta(); 
  }
  if(auxdecision == 3){
    busquedaLocal ->InsercionEntreRutas(); 
  }
  rutaFINAL = busquedaLocal -> getMejorRuta();
distanciaFINAL = Evaluate(rutaFINAL);
  
  std::cout << std::endl << "--------------------------------------------------------------------------------" << std::endl;
  std::cout << std::endl << "Mejor Distancia Final: " << distanciaFINAL << std::endl << " --------------";
  std::cout << std::endl << "Mejor Ruta Final: " ;
  for (int i = 0; i < rutaFINAL.size(); i++) {
    std::cout << rutaFINAL[i] << " ";
  }
  std::cout << std::endl;
  
  
}

/**
Función para nuestro algoritmo Grasp que funcionará de forma similar al Greedy, pero añadiendo una RLC desde la que escogerá de forma aleatoria uno de los valores
y este valor será el nuevo vecino recogido. Además también tendrá un nuevo bucle While que ejecutará el algoritmo hasta que se cumpla alguna de sus dos condiciones
de parada (nº de iteraciones o nº de iteraciones sin mejorar la solución). Se irá almacenando la solución de cada una de las iteraciones para compararla con la siguiente
almacenando la mejor, para así poder dar un resultado final a la hora de finalizar la ejecución.
*/
void Algoritmo::Grasp(){
    srand(time(NULL));
  int size_route = 0;
  float prueba = 0;
  prueba = (customers / vehicles) + (customers * 0.1);
  size_route = ceil(prueba);
  long totalTime;
  int iterations = getNumberIterations();
  int RLCSize = getRLCVectorSize();
  int noImprove = getTimesWithoutImprove();
  
  std::cout << std::endl << "ProblemSize\t\t|LRC|\t\tEjecucion\t\tDistanciaTotalRecorrida\t\tCPUTime" << std::endl;
	std::cout << "________________________________________________________________________________________________________________________" << std::endl;

  long start = getCurrentTime();
  std::vector<int> mecagoenmivida;
  int mecagoenmividaV = 0;
  std::vector<int> valorParcial;
  std::vector<int> rutaSolucion;
  std::vector<int> rutaParcial;
  std::vector<int> rutaFINAL;
  int distanciaFINAL = 99999;
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
          //Llamar aquí a las busquedas y tenemso que conseguir su resultado ya que ese resultado va a ser el rutasolución y ademas conseguir su distancia total
          //Para poder ponerla en la tabla.
          totalTime = getCurrentTime() - start;
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
    
    Busquedas *busqueda = new Busquedas(copia_matrix,rutaSolucion,mejorDistancia,vehicles,customers);
  busqueda -> GVNS();
    //aqui. llamar GVNS.
  mecagoenmivida = busqueda -> getRutaGVNS();
  
  //std::cout << "pepeeeeeee" << std::endl;
  //for (int i = 0; i < mecagoenmivida.size(); i++) {
    //std::cout << mecagoenmivida[i] << " ";
  //}
  //std::cout << std::endl;
  mecagoenmividaV = Evaluate(mecagoenmivida);
std::cout << matriz.size() - 1 << "\t\t\t" << RLCSize << "\t\t" << contadorIteraciones << "\t\t\t\t" << mecagoenmividaV << "\t\t\t" << totalTime << std::endl;
  //std::cout << "MeCagoEnMiVida: " << mecagoenmividaV << std::endl;
  if(mecagoenmividaV < distanciaFINAL){
    rutaFINAL = mecagoenmivida;
    distanciaFINAL = mecagoenmividaV;
  }
  
  }

  
  std::cout << std::endl << "--------------------------------------------------------------------------------" << std::endl;
  std::cout << std::endl << "Mejor Distancia Final: " << distanciaFINAL << std::endl << " --------------";
  std::cout << std::endl << "Mejor Ruta Final: " ;
  for (int i = 0; i < rutaFINAL.size(); i++) {
    std::cout << rutaFINAL[i] << " ";
  }
  std::cout << std::endl;

//int a_ver = 0;

  //Busquedas *busqueditadePrueba = new Busquedas();
        //Busquedas *busqueda = new Busquedas(copia_matrix,rutaSolucion,mejorDistancia,vehicles,customers);
        //busqueda -> GVNS();
  //busquedaLocalII ->IntercambioIntraRuta();
  //mecagoenmivida = getMejorRuta();
  //std::cout << "PEPEEEE" << std::endl;
  //for(int n = 0; n < mecagoenmivida.size(); n ++){
   // std::cout << mecagoenmivida[n] << " ";
  //}
  //std::cout << std::endl;
  //a_ver = Evaluate(copia_matrix,pepe);
  //std::cout << " a ver vale: " << a_ver << std::endl;
  //Busquedas *busquedaLocalIE = new Busquedas(copia_matrix,rutaSolucion,mejorDistancia,vehicles);
  //busquedaLocalIE ->IntercambioEntreRutas();
  //Busquedas *busquedaLocalINI = new Busquedas(copia_matrix,rutaSolucion,mejorDistancia,vehicles);
  //busquedaLocalINI ->InsercionIntraRuta(); 
  //Busquedas *busquedaLocalINE = new Busquedas(copia_matrix,rutaSolucion,mejorDistancia,vehicles);
  //busquedaLocalINE ->InsercionEntreRutas(); 

}

int Algoritmo::Evaluate(std::vector<int> rutita){
int resultado = 0;
int aux = 0;

      for(int i = 1; i < rutita.size(); i ++){
            aux = matriz[rutita[i-1]][rutita[i]];
            resultado += aux;
          }
      return resultado;
}

