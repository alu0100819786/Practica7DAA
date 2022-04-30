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
        int contadorintra = 0;

    public:
        Busquedas(std::vector<std::vector<int> > matriz, std::vector<int> inputRuta, int inputDistancia, int vehiculos);
        ~Busquedas();
        void IntercambioIntraRuta();
        void IntercambioEntreRutas();
        void InsercionIntraRuta();
        void InsercionEntreRutas();

};
#endif /* BUSQUEDAS_H_ */