#ifndef FITXES_H
	#define FITXES_H

using namespace std;

const int MAX_MOVIMENTS = 50;

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

const int N_FILES = 8;
const int N_COLUMNES = 8;

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
private:
	//const bool trobaMoviment(const Posicio& desti, Moviment& mov) const;
	//void insertaPos(const Posicio& pos) {}; // inserta la pos a posicions valides, sempre que no estigui ja posada
	void getPosicionsValides(Fitxa tauler[N_FILES][N_COLUMNES], const Posicio& origen, bool potmenjar, Posicio posicionsPossibles[MAX_POSICIONS], int& nPossibles, bool arrpotmenjar[MAX_POSICIONS]); //Donats una posicio d'origen i si pot menjar, retorna a l'array les posicions a les que pot anar junt amb un array on a la posició corresponent a la de la posicio possible diu si pot seguir menjant o no. npossibles s'inicialitza a 0.
	//metode per afegir moviment a llista y mirar consecutius(?) // 
	// Posició[MAX_POSICIONS] getPosicionsValides(const Posicio& origen int& nPosValides);
	// afegeixMoviment(Moviment& nouMoviment);

	ColorFitxa m_color;
	TipusFitxa m_tipus;

	int m_nMovimentsValids;
	Moviment m_movimentValids[MAX_MOVIMENTS];
	int m_nPosicionsValides;
	Posicio m_posicionsValides[MAX_POSICIONS];
};

#endif