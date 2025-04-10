#ifndef TAULER_H_
	#define TAULER_H_

#include "fitxes.h"
#include "posicio.h"
#include "moviment.h"
#include <string>

using namespace std;

const int N_FILES = 8;
const int N_COLUMNES = 8;

class Tauler
{
public:
	Tauler() {
		for (int i = 0; i < N_FILES; i++)
			for (int j = 0; j < N_COLUMNES; j++)
				m_tauler[i][j].inicialitza(COLOR_NEGRE, TIPUS_EMPTY);
	};

	void inicialitza(const string& nomFitxer); //Tauler a partir de fitxer
	void inicialitza(); // Tauler en posició inicial
	void actualitzaMovimentsValids(); //Fitxa per fitxa, actualitzar moviments possibles
	bool mouFitxa(const Posicio& origen, const Posicio& desti); //Anar a fitxa a posicio y moure a desti si es un moviment valid (comparar desti amb posfinal de moviments)
	void getPosicionsPossibles(const Posicio& origen, int& nPosicions, Posicio posicionsPossibles[]); //Retorna tots moviments possibles de fitxa a l'origen (també intermitjos en cadena de menjar)
	string& toString() const; //genera string representant estat del tauler
private:
	Fitxa m_tauler[N_FILES][N_COLUMNES];
};

#endif