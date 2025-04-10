#ifndef FITXES_H
	#define FITXES_H

using namespace std;

#include "moviment.h"
#include "tauler.h"

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

const int MAX_MOVIMENTS = 50;
const int MAX_POSICIONS = 65;

class Fitxa
{
public:
	Fitxa() : m_color(COLOR_NEGRE), m_tipus(TIPUS_EMPTY), m_nMovimentsValids(0) {};
	void inicialitza(ColorFitxa color, TipusFitxa tipus) { m_color = color; m_tipus = tipus; m_nMovimentsValids = 0; };

	const ColorFitxa getColor() const { return m_color; };
	const TipusFitxa getTipus() const { return m_tipus; };
	void changeTipus(TipusFitxa nouTipus) { m_tipus = nouTipus; };

	void afegeixPosicionsValides(Posicio Valides[MAX_POSICIONS], int& nValides); // afegeix a l'array valides, les posicions valides de la fitxa, amb compte de no repetir-ne cap que ja estigui

	void actualitzaMovimentsFitxa(Tauler tauler[N_FILES][N_COLUMNES], const Posicio& origen); // actualitza/refa llista de moviments vàlids de fitxa,

	bool fesMoviment(Tauler tauler[N_FILES][N_COLUMNES], const Posicio& destí);
private:
	bool movimentEsValid(const Posicio& destí); //mira destins de la llista de moviments y retorna true si hi es.
	
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