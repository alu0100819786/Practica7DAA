#ifndef ALGORITMO_H_
#define ALGORITMO_H_
#pragma once
#include "Problema.h"

#include <sys/time.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <cmath>


class Algoritmo : public Problema{

    private:
        int customers;
        int vehicles;
        std::vector<std::vector<int> > matriz;

    public:
        Algoritmo(int customers, int vehicles,std::vector<std::vector<int> > matriz);
        ~Algoritmo();
       
        void Greedy();
        void Grasp();
        void GVNS();


};
#endif /* ALGORITMO_H_ */