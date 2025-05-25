#ifndef JOC_H
#define JOC_H

#include <stdio.h>
#include "info_joc.hpp"
#include "tauler.hpp"
#include <queue>
#include "posicio.hpp"

using namespace std;

class Node
{
public:
    void setPosicioInicial(const string& inici) { m_posInici = inici; }
    void setPosicioFinal(const string& final) { m_posFinal = final; }
    string getPosInicial() { return m_posInici; }
    string getPosFinal() { return m_posFinal; }
private:
    string m_posInici;
    string m_posFinal;
};
class CuaMoviments
{
public:
    CuaMoviments() {}
    void inicialtzaJocReplay(const string& nomFitxer); //Al principi de la partida s’inicialitza amb tots els moviments guardats al fitxer indicat.
    void getSeguentMov(Posicio pos[2]); // guarda en la array [posInicio, posFinal], elimina el movimiento returneado
    void finalitzaJocNormal(const string& nomFitxer); //guarda al fitxer tots els mov de m_cuaMov i els va eliminants conforme els guarda
    void guardaMov(const Posicio& posInicial, const Posicio& posFinal); //guarda en la cola 1ro la pos inicial y luego la final
private:
    queue<Posicio> m_cuaMov; // se guarda de dos en dos los mov, primero pos inicial, luego pos final
};

class Joc 
{

public:
    Joc();
    
    bool actualitza(int mousePosX, int mousePosY, bool mouseStatus); // cambiar para que use el visualitza de tauler HA DE RETORNAR TRUE AL ACABAR
    //I MOSTRAR EL JUGADOR QUE HA GUANYAT amb bool comprobaSiAcabat(); 
    Tauler getTauler() { return taulerJoc; }
    void dibuixaFons(); //quitar cuando se use el visualitza de tauler, ya que este ya dibuja el fondo
    void inicialitza(ModeJoc mode, const string& nomFitxerTauler, const string& nomFitxerMoviments); //inicialitza tauler a través d'un fitxer, substituye joc.getTauler().inicialitza(); inicialitza segons mode joc
    void finalitza(const string& nomFitxer); //escribe en un fichero los movimientos hechos en la partida.

    void escullModeJoc(); // bucle que no para hasta que escojas mode de joc  
    bool comprobaSiAcabat(); //retorna true si la partida ha finalitzat (jugador sense fitxes) Si la partida ja s’ha acabat s’haurà de mostrar 
    //per pantalla quin és el jugador que ha guanyat i retornar
    //true com a resultat de la funció.
    void cambiaTorn(); //cambia el torn del jugador q està jugant després de mirar si la partida ha finalitzat amb el metode comprobaSiFinalitzat.
    void mostraModeITorn(); //mostra per pantalla el mode en el que s'està jugant i el torn actual
private:
    Tauler taulerJoc;
    CuaMoviments m_cua;

    ModeJoc modeJoc;
    string nomFitxer;
    ColorFitxa torn;
};

#endif 
