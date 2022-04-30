#ifndef BUSQUEDAS_H_
#define BUSQUEDAS_H_
#pragma once


#include <sys/time.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <cmath>

class Busquedas{

    private:
        std::vector<std::vector<int> > matrix;
        std::vector<int> ruta;
        int distancia;
        int vehicles;
        

    public:
        std::vector<int> mejorRuta;
        Busquedas(std::vector<std::vector<int> > matriz, std::vector<int> inputRuta, int inputDistancia, int vehiculos);
        Busquedas();
        ~Busquedas();
        void IntercambioIntraRuta();
        void IntercambioEntreRutas();
        void InsercionIntraRuta();
        void InsercionEntreRutas();
        void setMejorRuta(std::vector<int> ruta);
        std::vector<int> getMejorRuta();

};
#endif /* BUSQUEDAS_H_ */