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

const int MAX_MOVIMENTS = 100;

class Fitxa
{
public:
	Fitxa() : m_color(COLOR_NEGRE), m_tipus(TIPUS_EMPTY) {};
	void inicialitza(ColorFitxa color, TipusFitxa tipus) { m_color = color; m_tipus = tipus; };

	const ColorFitxa getColor() const { return m_color; };
	const TipusFitxa getTipus() const { return m_tipus; };
	void changeTipus(TipusFitxa nouTipus) { m_tipus = nouTipus; };

	void actualitzaMovimentsValids(Tauler tauler[N_FILES][N_COLUMNES], Posicio origen); // actualitza/refer llista de moviments vàlids de fitxa,

private:
	//metode per afegir moviment a llista y mirar consecutius(?)

	ColorFitxa m_color;
	TipusFitxa m_tipus;

	int m_nMovimentsValids;
	Moviment m_movimentValids[MAX_MOVIMENTS];
};

#endif