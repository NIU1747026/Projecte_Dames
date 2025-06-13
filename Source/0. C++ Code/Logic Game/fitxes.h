#ifndef FITXES_H
	#define FITXES_H

#include "moviment.h"
#include <iostream>
using namespace std;

typedef enum
{
	TIPUS_NORMAL,
	TIPUS_DAMA,
	TIPUS_EMPTY
} TipusFitxa;

typedef enum
{
	COLOR_NEGRE,
	COLOR_BLANC
} ColorFitxa;

typedef enum
{
	TOT,
	DALT_ESQUERRA,
	DALT_DRETA,
	BAIX_ESQUERRA,
	BAIX_DRETA
}DireccioMov;

class FStatus
{
public:
	FStatus() : potMenjar(false), potMoure(false), direccio(TOT) {};
	void init(bool potmenjar, bool potmoure, DireccioMov dir) { setPotMenjar(potmenjar); setPotMoure(potmoure); setDireccio(dir); }

	bool getPotMenjar() { return potMenjar; }
	bool getPotMoure() { return potMoure; }
	DireccioMov getDireccio() { return direccio; }

	void setPotMenjar(bool pot) { potMenjar = pot; }
	void setPotMoure(bool pot) { potMoure = pot; }
	void setDireccio(DireccioMov dir) { direccio = dir; }

private:
	bool potMenjar;
	bool potMoure;
	DireccioMov direccio;
};

class Fitxa
{
public:
	Fitxa() : m_color(COLOR_NEGRE), m_tipus(TIPUS_EMPTY), m_nMovimentsValids(0), m_nPosicionsValides(0) {};
	void inicialitza(ColorFitxa color, TipusFitxa tipus) { m_color = color; m_tipus = tipus; m_nMovimentsValids = 0; m_nPosicionsValides = 0; };
	
	void visualitza(int x, int y); //que visualice la fixa

	const ColorFitxa getColor() const { return m_color; };
	const TipusFitxa getTipus() const { return m_tipus; };
	void changeTipus(TipusFitxa nouTipus) { m_tipus = nouTipus; };

	void actualitzaMovimentsFitxa(Fitxa** tauler, const Posicio& origen); // actualitza/refa llista de moviments valids de fitxa, tambe posa a les posicions valides;

	void afegeixPosicionsValides(Posicio Valides[MAX_POSICIONS], int& nValides) const; // afegeix a l'array valides, les posicions valides de la fitxa, amb compte de no repetir-ne cap que ja estigui

	const bool movimentEsValid(const Posicio& desti, Moviment& mov) const; //mira destins de la llista de moviments y retorna true si hi es i el posa a mov.
	const bool esMillorMoviment(const Moviment& mov) const; //retorna true si no hi ha cap millor moviment

	int getNMovimentsValids() { return m_nMovimentsValids; }
	void visualtzaMovValids(); //permite visualizar los mov validos de la fixa seleccionada

private:
	void insertaPos(const Posicio& pos); // inserta la pos a posicions valides, sempre que no estigui ja posada
	void getPosicionsValides(Fitxa** m_tauler, const Posicio& origen, const Fitxa& fitxa, FStatus& status, Posicio posicionsPossibles[MAX_POSICIONS], int& nPossibles, FStatus arrStatus[MAX_POSICIONS], Posicio menjada[MAX_POSICIONS], Moviment& movimentActual); //Donats una posicio d'origen i si pot menjar, retorna a l'array les posicions a les que pot anar junt amb un array on a la posició corresponent a la de la posicio possible diu si pot seguir menjant o no. npossibles s'inicialitza a 0.

	ColorFitxa m_color;
	TipusFitxa m_tipus;

	int m_nMovimentsValids;
	Moviment m_movimentValids[MAX_MOVIMENTS];
	int m_nPosicionsValides;
	Posicio m_posicionsValides[MAX_POSICIONS];
};

Fitxa getFitxa(Fitxa** m_tauler, const Posicio& pos);


#endif