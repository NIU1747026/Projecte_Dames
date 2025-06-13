#ifndef JOC_H
#define JOC_H

#include <stdio.h>
#include "info_joc.hpp"
#include "tauler.hpp"
#include <queue>
#include "posicio.hpp"

using namespace std;

class CuaMoviments
{
public:
    CuaMoviments() {}
    void inicialtzaJocReplay(const string& nomFitxer); //MODE REPLAY Al principi de la partida s’inicialitza amb tots els moviments guardats al fitxer indicat.
    void getSeguentMov(Posicio pos[2]); // MODE REPLAY guarda en la array [posInicio, posFinal], elimina el movimiento returneado
    void finalitzaJocNormal(const string& nomFitxer); //MODE NORMAL guarda al fitxer tots els mov de m_cuaMov i els va eliminants conforme els guarda
    //SE TIENEN QUE PASSAR AL TOSTRING PRIMERO
    void guardaMov(const Posicio& posInicial, const Posicio& posFinal); //MODE NORMAL guarda en la cola 1ro la pos inicial y luego la final
    bool noMesMoviments() { return m_cuaPosFinal.empty(); }
private:
    queue<Posicio> m_cuaPosInicial;
    queue<Posicio> m_cuaPosFinal;// se guarda de dos en dos los mov, primero pos inicial, luego pos final
};

class Joc 
{

public:
    Joc() { m_modeJoc = MODE_JOC_NONE; m_torn = COLOR_BLANC; taulerJoc = new Tauler;};
    
    bool actualitza(int mousePosX, int mousePosY, bool mouseStatus, Screen& p, bool& act); // cambiar para que use el visualitza de tauler HA DE RETORNAR TRUE AL ACABAR
    //I MOSTRAR EL JUGADOR QUE HA GUANYAT amb bool comprobaSiAcabat(); 
    Tauler& getTauler() { return* taulerJoc; }
    void inicialitza(ModeJoc mode, const string& nomFitxerTauler, const string& nomFitxerMoviments, Screen& p); //inicialitza tauler a través d'un fitxer, substituye joc.getTauler().inicialitza(); inicialitza segons mode joc
    void finalitza(const string& nomFitxer); //escribe en un fichero los movimientos hechos en la partida.

    void escullModeJoc(Screen& p, int mousePosX, int mousePosY, bool mouseStatus);// bucle que no para hasta que escojas mode de joc  
    bool comprobaSiAcabat(); //retorna true si la partida ha finalitzat (jugador sense fitxes o no pot moure) Si la partida ja s’ha  
    //acabat s’haurà de mostrar per pantalla quin és el jugador que ha guanyat i retornar
    //true com a resultat de la funció.
    void cambiaTorn(); //cambia el torn del jugador q està jugant després de mirar si la partida ha finalitzat amb el metode comprobaSiFinalitzat.
    void mostraModeITorn(); //mostra per pantalla el mode en el que s'està jugant i el torn actual

    void dibuixaTauler();

    ModeJoc getMode() { return m_modeJoc; }
    string getFitxer() { return m_nomFitxer; }
    string getGuanyador() { if (m_guanyador == COLOR_BLANC) { return "Blanques"; } else { return "Negres"; } }
private:
    Tauler* taulerJoc;
    CuaMoviments m_cua;

    ModeJoc m_modeJoc;
    string m_nomFitxer;
    ColorFitxa m_torn, m_guanyador;
};

#endif 
