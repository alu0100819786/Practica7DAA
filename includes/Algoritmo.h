#ifndef ALGORITMO_H_
#define ALGORITMO_H_
#pragma once

#include <sys/time.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <cmath>

class Algoritmo{

    private:
        int customers;
        int vehicles;
        std::vector<std::vector<int> > matriz;

    public:
        Algoritmo(int customers, int vehicles,std::vector<std::vector<int> > matriz);
        ~Algoritmo();
        bool isZero(std::vector<int> array);
        void generateRLC(std::vector<int>& RLCR, std::vector<int>& RLCV, std::vector<int> fila, int size_RLC);
        bool isEmpty(std::vector<std::vector<int> > matrix);
        void Greedy();
        void Grasp ();
        int getNumberIterations();
        int getRLCVectorSize();
        int getTimesWithoutImprove();
        long getCurrentTime();


};
#endif /* ALGORITMO_H_ */