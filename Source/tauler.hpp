#ifndef TAULER_H_
	#define TAULER_H_

#include "posicio.hpp"
#include "moviment.h"
#include "fitxes.h"
#include <string>

using namespace std;

class Tauler
{
public:
	Tauler();

	void inicialitza(const string& nomFitxer); //Tauler a partir de fitxer
	void inicialitza(); // Tauler en posició inicial
	void actualitzaMovimentsValids(); //Fitxa per fitxa, actualitzar moviments possibles
	bool mouFitxa(const Posicio& origen, const Posicio& desti); //Anar a fitxa a origen y moure a desti si es un moviment valid (fer una cerca comparant desti amb posfinal de moviments). Ha de convertir la fitxa en dama (si cal) i eliminar les fitxes que menja
	void getPosicionsPossibles(const Posicio& origen, int& nPosicions, Posicio posicionsPossibles[]); //Retorna tots moviments possibles de fitxa a l'origen (també intermitjos en cadena de menjar)
	string toString() const; //genera string representant estat del tauler
private:
	Fitxa m_tauler[N_FILES][N_COLUMNES];
};

#endif