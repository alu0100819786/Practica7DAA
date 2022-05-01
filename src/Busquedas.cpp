#include "../includes/Busquedas.h"


Busquedas::Busquedas(std::vector<std::vector<int> > matriz, std::vector<int> inputRuta, int inputDistancia, int vehiculos){

        matrix = matriz;
        ruta = inputRuta;
        distancia = inputDistancia;
        vehicles = vehiculos;
        mejorRuta=inputRuta;
}

Busquedas::Busquedas(){

}
Busquedas::~Busquedas(){
    matrix.clear();
    ruta.clear();
    distancia = 0;
    vehicles = 0;
    mejorRuta.clear();
}

void Busquedas::IntercambioIntraRuta(){

  /*for(int l = 0; l < ruta.size(); l ++){
    std::cout << ruta[l] << " ";
  }
  std::cout << std::endl;
  std::cout << distancia << std::endl;
*/
//for( int x = 0; x < vehicles ; x++){}
std::vector<int> copia_ruta;
std::vector<int> ruta_final;
std::vector<int> copia_resultado;
ruta_final = ruta;
int distancia_final;
distancia_final = distancia;
copia_ruta = ruta;
int contador = 0;
int aux = 0;
int resultadoIntermedio = 0;
int resta = 0;
int suma = 0;
int copia_distancia = 0;
copia_distancia = distancia;

//std::cout << "Distancia antes de mejorar: " << distancia << std::endl;
for(int i = 1; i < copia_ruta.size(); i++){
  copia_ruta = ruta;
  if(copia_ruta[i] == 0){
    i++;
    contador++;
    if(contador == vehicles){
      break;
    }
  }
  for(int j = i+1; j < copia_ruta.size(); j++){
    copia_ruta = ruta;
    if(copia_ruta[j] == 0){
      break;
    }else{
      //std::cout <<"cambio: " << copia_ruta[i] << " por: " << copia_ruta[j] << std::endl;
      if(copia_ruta[i+1] == copia_ruta[j]){
        resta = 0;
        resta = matrix[copia_ruta[i-1]][copia_ruta[i]] + matrix[copia_ruta[i]][copia_ruta[j]] + matrix[copia_ruta[j]][copia_ruta[j+1]];
        //std::cout << "resta: " << resta << std::endl;
        aux = copia_ruta[i];
        copia_ruta[i] = copia_ruta[j];
        copia_ruta[j] = aux;
        suma = 0;
        suma = matrix[copia_ruta[i-1]][copia_ruta[i]] + matrix[copia_ruta[i]][copia_ruta[j]] + matrix[copia_ruta[j]][copia_ruta[j+1]];
        //std::cout << "suma: " << suma << std::endl;
          //for(int l = 0; l < copia_ruta.size(); l ++){
            //std::cout << copia_ruta[l] << " ";
          //}
        //std::cout << std::endl;
      }
      if(copia_ruta[i+1] != copia_ruta[j]){
        resta = 0;
        resta = matrix[copia_ruta[i-1]][copia_ruta[i]] + matrix[copia_ruta[i]][copia_ruta[i+1]] + matrix[copia_ruta[j-1]][copia_ruta[j]] + matrix[copia_ruta[j]][copia_ruta[j+1]];
        //std::cout << "resta: " << resta << std::endl;
        aux = copia_ruta[i];
        copia_ruta[i] = copia_ruta[j];
        copia_ruta[j] = aux;
        suma = 0;
        suma = matrix[copia_ruta[i-1]][copia_ruta[i]] + matrix[copia_ruta[i]][copia_ruta[i+1]] + matrix[copia_ruta[j-1]][copia_ruta[j]] + matrix[copia_ruta[j]][copia_ruta[j+1]];
        //std::cout << "suma: " << suma << std::endl;
          //for(int l = 0; l < copia_ruta.size(); l ++){
            //std::cout << copia_ruta[l] << " ";
          //}
        //std::cout << std::endl;
      }
  //std::cout << "aaaa: " << copia_distancia<< std::endl;
  resultadoIntermedio = suma - resta;
  copia_distancia = copia_distancia + (suma - resta);
  //std::cout << "pepe: " << copia_distancia << std::endl;
  if(copia_distancia < distancia_final){
    distancia_final = copia_distancia;
    ruta_final = copia_ruta;
    copia_distancia = distancia;
    copia_ruta = ruta;
  }else{
    copia_distancia = distancia;
    copia_ruta = ruta;
  }
    }
    
  }
}

//std::cout << "Distancia Inicial: " << distancia << std::endl;
//std::cout << "Distancia Mejorada: " << distancia_final << std::endl;
if(distancia_final < distancia){
  
  ruta = ruta_final;
  distancia = distancia_final;
  //std::cout << "Nueva distancia: " <<  distancia << std::endl;
  IntercambioIntraRuta();
}
else{
  
std::cout << "La nueva mejor ruta (óptimo Local) conseguida con Intercambio IntraRuta es: " << std::endl;
for(int m = 0; m < ruta_final.size(); m ++){
    std::cout << ruta_final[m] << " ";
  }
std::cout << std::endl;
std::cout << "Con una distancia de: " << distancia_final << std::endl;
std::cout << "-----------------------------------------------------" << std::endl;
setMejorRuta(ruta_final);
}

//Hacerla al final paso por referencia la ruta y la distancia para que al volver al grasp la devuelva modificada y poder aplicarla en las demás funciones.
}

void Busquedas::IntercambioEntreRutas(){

std::vector<int> copia_ruta;
std::vector<int> ruta_final;
ruta_final = ruta;
int distancia_final;
distancia_final = distancia;
copia_ruta = ruta;
int contador = 0;
int aux = 0;
int resultadoIntermedio = 0;
int resta = 0;
int suma = 0;
int copia_distancia = 0;
copia_distancia = distancia;
int conthastacero = 1;
int contj = 0;
//std::cout << "Distancia antes de mejorar: " << distancia << std::endl;
  for(int i = 1; i < copia_ruta.size(); i ++){
    copia_ruta = ruta;
    if(copia_ruta[i] == 0){
      i++;
      contador++;
    }
    if(contador == vehicles){
      break;
    }
    for(int z=i+1;z<copia_ruta.size();z++){
      if(copia_ruta[z] != 0){
        conthastacero++;
      }
      if(copia_ruta[z] == 0){
        break;
      }
    }
    contj = i + conthastacero + 1;
    //std::cout << "Posicion i: " << i << std::endl;
    //std::cout << "Contador J: " << contj << std::endl;
    if(contj == copia_ruta.size()){
      //std::cout << "estamos en la misma ruta" << std::endl;
      break;
    }
    
    
    conthastacero = 1;
  for(int j=contj; j<copia_ruta.size()-1;j++){
    copia_ruta = ruta;
    if(copia_ruta[j] == 0 && copia_ruta[j+1] == 0){
      break;
    }
    if(copia_ruta[j] == 0){
        j++;
    }
    
      //std::cout <<"cambio: " << copia_ruta[i] << " por: " << copia_ruta[j] << std::endl;
      resta = 0;
        resta = matrix[copia_ruta[i-1]][copia_ruta[i]] + matrix[copia_ruta[i]][copia_ruta[i+1]] + matrix[copia_ruta[j-1]][copia_ruta[j]] + matrix[copia_ruta[j]][copia_ruta[j+1]];
        //std::cout << "resta: " << resta << std::endl;
        aux = copia_ruta[i];
        copia_ruta[i] = copia_ruta[j];
        copia_ruta[j] = aux;
        suma = 0;
        suma = matrix[copia_ruta[i-1]][copia_ruta[i]] + matrix[copia_ruta[i]][copia_ruta[i+1]] + matrix[copia_ruta[j-1]][copia_ruta[j]] + matrix[copia_ruta[j]][copia_ruta[j+1]];
        //std::cout << "suma: " << suma << std::endl;
          //for(int l = 0; l < copia_ruta.size(); l ++){
            //std::cout << copia_ruta[l] << " ";
          //}
        //std::cout << std::endl;
        //std::cout << "aaaa: " << copia_distancia<< std::endl;
  resultadoIntermedio = suma - resta;
  copia_distancia = copia_distancia + (suma - resta);
  //std::cout << "pepe: " << copia_distancia << std::endl;
  if(copia_distancia < distancia_final){
    //std::cout << "Intercambio con Mejora:" << copia_ruta[i] << ", " << copia_ruta[j] << std::endl;
    distancia_final = copia_distancia;
    ruta_final = copia_ruta;
    copia_distancia = distancia;
    copia_ruta = ruta;
  }else{
    copia_distancia = distancia;
    copia_ruta = ruta;
  }
  }
  }
//std::cout << "Distancia Inicial: " << distancia << std::endl;
//std::cout << "Distancia Mejorada: " << distancia_final << std::endl;
if(distancia_final < distancia){
  ruta = ruta_final;
  distancia = distancia_final;
//std::cout << "Nueva distancia: " <<  distancia << std::endl;
  IntercambioEntreRutas();
}
else{
std::cout << "La nueva mejor ruta (óptimo Local) conseguida con Intercambio Entre Rutas es: " << std::endl;
for(int m = 0; m < ruta_final.size(); m ++){
    std::cout << ruta_final[m] << " ";
  }
std::cout << std::endl;
std::cout << "Con una distancia de: " << distancia_final << std::endl;
std::cout << "-----------------------------------------------------" << std::endl;
setMejorRuta(ruta_final);
}
//Hacerla al final paso por referencia la ruta y la distancia para que al volver al grasp la devuelva modificada y poder aplicarla en las demás funciones.
}

void Busquedas::InsercionIntraRuta(){

std::vector<int> copia_ruta;
std::vector<int> vector_erased;
std::vector<int> ruta_final;
ruta_final = ruta;
int distancia_final;
distancia_final = distancia;
copia_ruta = ruta;
int contador = 0;
int aux = 0;
int resultadoIntermedio = 0;
int resta = 0;
int suma = 0;
int copia_distancia = 0;
copia_distancia = distancia;
int indice = 0;
int inicio = 1;

/*
std::cout << copia_ruta[3] << std::endl;
copia_ruta.erase(copia_ruta.begin() + 3);
std::cout << copia_ruta[3] << std::endl;
for(int l = 0; l < copia_ruta.size(); l ++){
            std::cout << copia_ruta[l] << " ";
          }
          std::cout << std::endl;
copia_ruta.insert(copia_ruta.begin() +1, 2);
for(int l = 0; l < copia_ruta.size(); l ++){
            std::cout << copia_ruta[l] << " ";
          }

  */ 
//std::cout << "Distancia antes de mejorar: " << distancia << std::endl;       
for(int i = 1; i < copia_ruta.size(); i++){
  copia_ruta = ruta;
  if(copia_ruta[i] == 0){
    i++;
    contador++;
    inicio = i;
    if(contador == vehicles){
      break;
    }
  }
  indice = copia_ruta[i];
  //std::cout << "erased: " << indice << std::endl;
  copia_ruta.erase(copia_ruta.begin() + i);
  vector_erased = copia_ruta;
  for(int j = inicio; j < vector_erased.size(); j++){
      if( j != inicio && vector_erased[j-1] == 0){
        break;
      }
      //std::cout << "insert: " << j << std::endl;
      if(i==j){
        //std::cout << "(i=j)quitamos: " << ruta[i-1] << "-" << ruta[i] << " luego " << ruta[i] << "-" << ruta[i+1] << " por ultimo: " << ruta[j-1]<< "-" << ruta[j] << std::endl;
        resta = matrix[ruta[i-1]][ruta[i]] + matrix[ruta[i]][ruta[i+1]] + matrix[ruta[j-1]][ruta[j]];
      }
      if(i<j){
        //std::cout << "(i<j)quitamos: " << ruta[i-1] << "-" << ruta[i] << " luego " << ruta[i] << "-" << ruta[i+1] << " por ultimo: " << ruta[j]<< "-" << ruta[j+1] << std::endl;
        resta = matrix[ruta[i-1]][ruta[i]] + matrix[ruta[i]][ruta[i+1]] + matrix[ruta[j]][ruta[j+1]];
      //std::cout << "Resta:" << resta << std::endl;
      }
      if(i>j){
        //std::cout << "(i>j)quitamos: " << ruta[i-1] << "-" << ruta[i] << " luego " << ruta[i] << "-" << ruta[i+1] << " por ultimo: " << ruta[j-1]<< "-" << ruta[j] << std::endl;
        resta = matrix[ruta[i-1]][ruta[i]] + matrix[ruta[i]][ruta[i+1]] + matrix[ruta[j-1]][ruta[j]]; 
      }
      vector_erased.insert(vector_erased.begin() +j, indice);
      if(i==j){
        //std::cout << "(i=j)ponemos: " << vector_erased[j-1] << "-" << vector_erased[j] << " luego " << vector_erased[j] << "-" << vector_erased[j+1] << " por ultimo: " << vector_erased[i-1]<< "-" << vector_erased[i] << std::endl;
        suma = matrix[vector_erased[j-1]][vector_erased[j]] + matrix[vector_erased[j]][vector_erased[j+1]] + matrix[vector_erased[i-1]][vector_erased[i]];
       }
      if(i<j){
        //std::cout << "(i<j)ponemos: " << vector_erased[j-1] << "-" << vector_erased[j] << " luego " << vector_erased[j] << "-" << vector_erased[j+1] << " por ultimo: " << vector_erased[i-1]<< "-" << vector_erased[i] << std::endl;
        suma = matrix[vector_erased[j-1]][vector_erased[j]] + matrix[vector_erased[j]][vector_erased[j+1]] + matrix[vector_erased[i-1]][vector_erased[i]];
       //std::cout << "Suma:" << suma << std::endl;
       }
      if(i>j){
        //std::cout << "(i>j)ponemos: " << vector_erased[j-1] << "-" << vector_erased[j] << " luego " << vector_erased[j] << "-" << vector_erased[j+1] << " por ultimo: " << vector_erased[i]<< "-" << vector_erased[i+1] << std::endl;
        suma = matrix[vector_erased[j-1]][vector_erased[j]] + matrix[vector_erased[j]][vector_erased[j+1]] + matrix[vector_erased[i]][vector_erased[i+1]];
      }
      
resultadoIntermedio = suma - resta;
//vector_erased = copia_ruta;
//std::cout << "Distancia Pre Intercambio: " << copia_distancia << std::endl;
//std::cout << "Resultado Intermedio: " << resultadoIntermedio << std::endl;
      //for(int l = 0; l < vector_erased.size(); l ++){
            //std::cout << vector_erased[l] << " ";
          //}
          //std::cout << std::endl;
//int pruebita = 0;
//int auxprueba = 0;
      //for(int n = 1; n < vector_erased.size(); n ++){
           // auxprueba = matrix[vector_erased[n-1]][vector_erased[n]];
            //pruebita += auxprueba;
          //}

          
copia_distancia = copia_distancia + resultadoIntermedio;
//copia_distancia = pruebita;
//std::cout << "Resultado esperado: " << pruebita << std::endl;
//auxprueba = 0;
//pruebita = 0;
//std::cout << "Distancia Post Intercambio: " << copia_distancia << std::endl;
//std::cout << std::endl;
if(copia_distancia < distancia_final){
  distancia_final = copia_distancia;
  ruta_final = vector_erased;
  copia_distancia = distancia;
  vector_erased = copia_ruta;
}else{
  copia_distancia = distancia;
  vector_erased = copia_ruta;
}

  }
}

//std::cout << "Distancia Inicial: " << distancia << std::endl;
//std::cout << "Distancia Mejorada: " << distancia_final << std::endl;
if(distancia_final < distancia){
  //for(int n = 0; n < ruta.size(); n ++){
    //std::cout << ruta[n] << " ";
 // }
//std::cout << std::endl;
//for(int m = 0; m < ruta_final.size(); m ++){
   // std::cout << ruta_final[m] << " ";
  //}
//std::cout << std::endl;
  distancia = distancia_final;
  ruta = ruta_final;
//std::cout << "Nueva distancia: " <<  distancia << std::endl;
//contadorintra++;
//if(contadorintra == 3){
  //exit(0);
//}
  InsercionIntraRuta();
}
else{
std::cout << "La nueva mejor ruta (óptimo Local) conseguida con Inserción IntraRuta es: " << std::endl;
for(int m = 0; m < ruta_final.size(); m ++){
    std::cout << ruta_final[m] << " ";
  }
std::cout << std::endl;
std::cout << "Con una distancia de: " << distancia_final << std::endl;
std::cout << "-----------------------------------------------------" << std::endl;
setMejorRuta(ruta_final);
}

//Hacerla al final paso por referencia la ruta y la distancia para que al volver al grasp la devuelva modificada y poder aplicarla en las demás funciones.   
}

void Busquedas::InsercionEntreRutas(){
  std::vector<int> copia_ruta = ruta;
  std::vector<int> ruta_final = ruta;
  int distancia_final = distancia;
  int contador = 0;
  int aux = 0;
  int resultadoIntermedio = 0;
  int resta = 0;
  int suma = 0;
  int copia_distancia = distancia;
  int conthastacero = 1;
  int contj = 0;
//std::cout << "Distancia antes de mejorar: " << distancia << std::endl;
  for(int i = 1; i < copia_ruta.size(); i ++){
    copia_ruta = ruta;
    if (copia_ruta[i] == 0) {
      i++;
      contador++;
    }
    if (contador == vehicles) {
      break;
    }
    for (int z=i+1; z<copia_ruta.size(); z++) {
      if(copia_ruta[z] != 0){
        conthastacero++;
      }
      if(copia_ruta[z] == 0){
        break;
      }
    }
    contj = i + conthastacero + 1;
    conthastacero = 1;
    for (int j=contj; j<copia_ruta.size(); j++) {
      copia_ruta = ruta;
      //std::cout <<"cambio: " << copia_ruta[i] << " en: " << j << std::endl;
      resta = matrix[copia_ruta[i-1]][copia_ruta[i]] + matrix[copia_ruta[i]][copia_ruta[i+1]] + matrix[copia_ruta[j-1]][copia_ruta[j]];
      /*std::cout << "resta= ";
      std::cout << matrix[copia_ruta[i-1]][copia_ruta[i]] << "(" << copia_ruta[i-1] << "," << copia_ruta[i] << ")";
      std::cout << " + " << matrix[copia_ruta[i]][copia_ruta[i+1]] << "(" << copia_ruta[i] << "," << copia_ruta[i+1] << ")";
      std::cout << " + " << matrix[copia_ruta[j-1]][copia_ruta[j]] << "(" << copia_ruta[j-1] << "," << copia_ruta[j] << ")";
      std::cout << " = " << resta << std::endl;*/
        
      aux = copia_ruta[i];
      copia_ruta.erase(copia_ruta.begin() + i);
      copia_ruta.insert(copia_ruta.begin() + j - 1, aux);

      suma = matrix[copia_ruta[i-1]][copia_ruta[i]] + matrix[copia_ruta[j-2]][copia_ruta[j-1]] + matrix[copia_ruta[j-1]][copia_ruta[j]];
      /*std::cout << "suma= ";
      std::cout << matrix[copia_ruta[i-1]][copia_ruta[i]] << "(" << copia_ruta[i-1] << "," << copia_ruta[i] << ")";
      std::cout << " + " << matrix[copia_ruta[j-2]][copia_ruta[j-1]] << "(" << copia_ruta[j-2] << "," << copia_ruta[j-1] << ")";
      std::cout << " + " << matrix[copia_ruta[j-1]][copia_ruta[j]] << "(" << copia_ruta[j-1] << "," << copia_ruta[j] << ")";
      std::cout << " = " << suma << std::endl;
      for(int l = 0; l < copia_ruta.size(); l ++){
        std::cout << copia_ruta[l] << " ";
      }
      std::cout << std::endl;*/
      //std::cout << "aaaa: " << copia_distancia<< std::endl;
      resultadoIntermedio = suma - resta;
      copia_distancia = copia_distancia + (suma - resta);
      //std::cout << "pepe: " << copia_distancia << std::endl;
      int auxdistancia = 0;
      auxdistancia = Evaluate(copia_ruta);
      //std::cout << "Evaluate pepe: " << auxdistancia << std::endl;
      if(auxdistancia < distancia_final){
        distancia_final = auxdistancia;
        ruta_final = copia_ruta;
        copia_distancia = distancia;
        copia_ruta = ruta;
      }else{
        copia_distancia = distancia;
        copia_ruta = ruta;
      }
    }
  }
//std::cout << "Distancia Inicial: " << distancia << std::endl;
//std::cout << "Distancia Mejorada: " << distancia_final << std::endl;
  if(distancia_final < distancia){
    distancia = distancia_final;
    ruta = ruta_final;
    //std::cout << "Nueva distancia: " <<  distancia << std::endl;
    InsercionEntreRutas();
  }
  else{
  std::cout << "La nueva mejor ruta (óptimo Local) conseguida con Inserción EntreRutas es: " << std::endl;
  for(int m = 0; m < ruta_final.size(); m ++){
    std::cout << ruta_final[m] << " ";
  }
  std::cout << std::endl;
  std::cout << "Con una distancia de: " << distancia_final << std::endl;
  std::cout << "-----------------------------------------------------" << std::endl;
  setMejorRuta(ruta_final);
  }
  
  //Hacerla al final paso por referencia la ruta y la distancia para que al volver al grasp la devuelva modificada y poder aplicarla en las demás funciones.    
}

void Busquedas::setMejorRuta(std::vector<int> ruta){
for(int m = 0; m < ruta.size(); m ++){
    mejorRuta[m] = ruta[m];
  }
}

std::vector<int> Busquedas::getMejorRuta(){

  return mejorRuta;
}

int Busquedas::Evaluate(std::vector<int> ruta){
int resultado = 0;
int aux = 0;
      for(int i = 1; i < ruta.size(); i ++){
            aux = matrix[ruta[i-1]][ruta[i]];
            resultado += aux;
          }
      return resultado;
}

void Busquedas::GVNS(){

int saltos = 0;
int contador = 0;
int distancia_GVNS = 0;
std::vector<int> ruta_Intermedia = ruta;

/*while(saltos <3){//Este es el Shaking.

InsercionEntreRutasAleatorio();
std::cout << "Ruta Despues del Shaking: " << std::endl;
for(int m = 0; m < ruta.size(); m ++){
    std::cout << ruta[m] << " ";
  }
  std::cout << std::endl;

ruta_Intermedia = ruta;
for(int m = 0; m < ruta_Intermedia.size(); m ++){
    std::cout << ruta_Intermedia[m] << " ";
}
  std::cout << std::endl;
  std::cout << "Evaluate del Shaking: " << Evaluate(ruta) << " " << Evaluate(ruta_Intermedia) << std::endl;*/
  while(contador < 4){ //Este While es el VND.
    if(contador == 0){
      std::cout << "Entramos a Contador = 0 con: "<< Evaluate(ruta) << std::endl;
      InsercionEntreRutas();
      std::cout << "Miramos La Ruta de Antes: " << std::endl;
      for(int m = 0; m < ruta_Intermedia.size(); m ++){
    std::cout << ruta_Intermedia[m] << " ";
  }
  std::cout << std::endl;
  std::cout << "Miramos La Ruta Nueva: " << std::endl;
  for(int m = 0; m < ruta.size(); m ++){
    std::cout << ruta[m] << " ";
  }
  std::cout << std::endl;
      std::cout << Evaluate(ruta_Intermedia) << " " << Evaluate(ruta)<< std::endl;
      if(Evaluate(ruta_Intermedia) <= Evaluate(ruta)){
        contador = 1;
      }
      else{
        contador = 0;
        ruta_Intermedia = ruta;
      }
    }
    if(contador == 1){
      std::cout << "Entramos a Contador = 1 con: "<< Evaluate(ruta) << std::endl;
      InsercionIntraRuta();
      std::cout << Evaluate(ruta_Intermedia) << " " << Evaluate(ruta)<< std::endl;
      if(Evaluate(ruta_Intermedia) <= Evaluate(ruta)){
        contador = 2;
      }
      else{
        contador = 0;
        ruta_Intermedia = ruta;
      }
    }
    if(contador == 2){
      std::cout << "Entramos a Contador = 2 con: "<< Evaluate(ruta) << std::endl;
      IntercambioEntreRutas();
      std::cout << Evaluate(ruta_Intermedia) << " " << Evaluate(ruta)<< std::endl;
      if(Evaluate(ruta_Intermedia) <= Evaluate(ruta)){
        contador = 3;
      }
      else{
        contador = 0;
        ruta_Intermedia = ruta;
      }
    }
    if(contador == 3){
      std::cout << "Entramos a Contador = 3 con: "<< Evaluate(ruta) << std::endl;
      IntercambioIntraRuta();
      std::cout << Evaluate(ruta_Intermedia) << " " << Evaluate(ruta)<< std::endl;
      if(Evaluate(ruta_Intermedia) <= Evaluate(ruta)){
        contador = 4;
      }
      else{
        contador = 0;
        ruta_Intermedia = ruta;
      }
    }
  }
  //saltos++;
  //contador = 0;
//}
std::cout << "El óptimo local Conseguido con GVNS es: "<< std::endl;
  for(int m = 0; m < ruta.size(); m ++){
    std::cout << ruta[m] << " ";
  }
  std::cout << std::endl;
  distancia_GVNS = Evaluate(ruta);
  std::cout << "Con distancia: " << distancia_GVNS << std::endl;
}

void Busquedas::InsercionEntreRutasAleatorio(){
std::vector<int> copia_ruta = ruta;
int conthastacero = 0;
int inicioJ = 0;
int posErased = 0;
int posInserted = 0;
int aux = 0;
for(int i = 1; i < copia_ruta.size(); i ++){
 if(copia_ruta[i] != 0){
        conthastacero++;
      }
  if(copia_ruta[i] == 0){
        break;
      }
}
//std::cout << "Contador hasta cero: " << conthastacero << std::endl;
std::random_device rd;
std::default_random_engine eng(rd());
std::uniform_int_distribution<int> distr(1, conthastacero);
posErased = distr(eng);
//std::cout << posErased << std::endl;
inicioJ = conthastacero +3;
conthastacero = 0;
for(int j = inicioJ; j<copia_ruta.size(); j++){
    if(copia_ruta[j] != 0){
        conthastacero++;
      }
  if(copia_ruta[j] == 0){
        break;
      }
}
conthastacero += inicioJ;
std::uniform_int_distribution<int> distrJ(inicioJ, conthastacero);
posInserted = distrJ(eng);
//std::cout << posInserted << std::endl;

aux = copia_ruta[posErased];
copia_ruta.erase(copia_ruta.begin() + posErased);
copia_ruta.insert(copia_ruta.begin() + posInserted - 1, aux);
ruta = copia_ruta;
}