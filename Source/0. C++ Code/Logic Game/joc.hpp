#ifndef JOC_H
#define JOC_H

#include <stdio.h>
#include "info_joc.hpp"
#include "tauler.hpp"

using namespace std;


class Joc 
{

public:
    Joc();
    
    bool actualitza(int mousePosX, int mousePosY, bool mouseStatus);
    Tauler getTauler() { return taulerJoc; }
    void dibuixaFons(); 
    void inicialitza(ifstream nomFitxer); //inicialitza tauler a través d'un fitxer, substituye joc.getTauler().inicialitza();
    
private:
    Tauler taulerJoc;
};

#endif 
