#ifndef FITXES_H
	#define FITXES_H

using namespace std;

const int MAX_MOVIMENTS = 20;

typedef enum
{
	TIPUS_NORMAL,
	TIPUS_DAMA,
	TIPUS_EMPTY
} TipusFitxa;

typedef enum
{
	COLOR_NEGRE,
	COLOR_BLANC,
} ColorFitxa;

#include "moviment.h"

class FStatus
{
public:
	FStatus() : potMenjar(false), potMoure(false) {};
	void init(bool potmenjar, bool potmoure) { setPotMenjar(potmenjar); setPotMoure(potmoure); }

	bool getPotMenjar() { return potMenjar; }
	bool getPotMoure() { return potMoure; }

	void setPotMenjar(bool pot) { potMenjar = pot; }
	void setPotMoure(bool pot) { potMoure = pot; }

private:
	bool potMenjar;
	bool potMoure;
};

class Fitxa
{
public:
	Fitxa() : m_color(COLOR_NEGRE), m_tipus(TIPUS_EMPTY), m_nMovimentsValids(0), m_nPosicionsValides(0) {};
	void inicialitza(ColorFitxa color, TipusFitxa tipus) { m_color = color; m_tipus = tipus; m_nMovimentsValids = 0; m_nPosicionsValides = 0; };

	const ColorFitxa getColor() const { return m_color; };
	const TipusFitxa getTipus() const { return m_tipus; };
	void changeTipus(TipusFitxa nouTipus) { m_tipus = nouTipus; };

	void actualitzaMovimentsFitxa(Fitxa tauler[N_FILES][N_COLUMNES], const Posicio& origen); // actualitza/refa llista de moviments valids de fitxa, tambe posa a les posicions valides;

	void afegeixPosicionsValides(Posicio Valides[MAX_POSICIONS], int& nValides) const; // afegeix a l'array valides, les posicions valides de la fitxa, amb compte de no repetir-ne cap que ja estigui

	const bool movimentEsValid(const Posicio& desti, Moviment& mov) const; //mira destins de la llista de moviments y retorna true si hi es i el posa a mov.
	const bool esMillorMoviment(const Moviment& mov) const; //retorna true si no hi ha cap millor moviment
	void calculaMenjades(Fitxa tauler[N_FILES][N_COLUMNES]);
private:
	void insertaPos(const Posicio& pos); // inserta la pos a posicions valides, sempre que no estigui ja posada
	void getPosicionsValides(Fitxa tauler[N_FILES][N_COLUMNES], const Posicio& origen, const Fitxa& fitxa, FStatus& status, Posicio posicionsPossibles[MAX_POSICIONS], int& nPossibles, FStatus arrStatus[MAX_POSICIONS]); //Donats una posicio d'origen i si pot menjar, retorna a l'array les posicions a les que pot anar junt amb un array on a la posició corresponent a la de la posicio possible diu si pot seguir menjant o no. npossibles s'inicialitza a 0.

	ColorFitxa m_color;
	TipusFitxa m_tipus;

	int m_nMovimentsValids;
	Moviment m_movimentValids[MAX_MOVIMENTS];
	int m_nPosicionsValides;
	Posicio m_posicionsValides[MAX_POSICIONS];
};

#endif