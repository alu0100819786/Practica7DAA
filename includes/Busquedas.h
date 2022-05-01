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
#include <random>

class Busquedas{

    private:
        std::vector<std::vector<int> > matrix;
        std::vector<int> ruta;
        int distancia;
        int vehicles;
        std::vector<int> mejorRuta;

    public:
        Busquedas(std::vector<std::vector<int> > matriz, std::vector<int> inputRuta, int inputDistancia, int vehiculos);
        Busquedas();
        ~Busquedas();
        void IntercambioIntraRuta();
        void IntercambioEntreRutas();
        void InsercionIntraRuta();
        void InsercionEntreRutas();
        void InsercionEntreRutasAleatorio();
        void GVNS();
        void setMejorRuta(std::vector<int> ruta);
        std::vector<int> getMejorRuta();
        int Evaluate(std::vector<int> ruta);

};
#endif /* BUSQUEDAS_H_ */