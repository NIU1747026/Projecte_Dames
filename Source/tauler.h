#ifndef TAULER_H_
	#define TAULER_H_

#include "fitxes.h"
#include <string>

using namespace std;

class Tauler
{
public:
	Tauler();

	void inicialitza(const string& nomFitxer);
	void actualitzaMovimentsValids();
	bool mouFitxa(const Posicio& origen, const Posicio& desti);
	void getPosicionsPossibles(cont Posicio& origen, int& nPosicions, Posicio posicionsPossibles[]);
	string toString() const;
private:
	Fitxa m_tauler[N_FILES][N_COLUMNES];
};

#endif