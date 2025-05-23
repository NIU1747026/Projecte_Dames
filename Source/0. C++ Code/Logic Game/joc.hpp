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
    
    bool actualitza(int mousePosX, int mousePosY, bool mouseStatus); // cambiar para que use el visualitza de tauler
    Tauler getTauler() { return taulerJoc; }
    void dibuixaFons(); //quitar cuando se use el visualitza de tauler, ya que este ya dibuja el fondo
    void inicialitza(ifstream nomFitxer); //inicialitza tauler a través d'un fitxer, substituye joc.getTauler().inicialitza();
    
private:
    Tauler taulerJoc;
};

#endif 
