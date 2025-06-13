#ifndef TAULER_H_
	#define TAULER_H_

#include "posicio.hpp"
#include "moviment.h"
#include "fitxes.h"
#include "GraphicManager.h"
#include "info_joc.hpp"
#include <string>

using namespace std;

class Tauler
{
public:
	Tauler() {
		m_tauler = new Fitxa * [N_FILES];
		for (int i = 0; i < N_FILES; i++)
		{
			m_tauler[i] = new Fitxa[N_COLUMNES];
			for (int j = 0; j < N_COLUMNES; j++)
				m_tauler[i][j].inicialitza(COLOR_NEGRE, TIPUS_EMPTY);
		}
	};
	~Tauler() {
		for (int i = 0; i < N_FILES; i++)
			delete[] m_tauler[i];
		delete[] m_tauler;
	}

	Fitxa getFitxaPos(int x, int m) { return m_tauler[x][m]; }


	void inicialitza(const string& nomFitxer); //Tauler a partir de fitxer, HAY QUE HACER QUE DIBUJE FIXAS
	void inicialitza(); // Tauler en posició inicial
	void actualitzaMovimentsValids(); //Fitxa per fitxa, actualitzar moviments possibles
	bool mouFitxa(const Posicio& origen, const Posicio& desti); //Anar a fitxa a origen y moure a desti si es un moviment valid (fer una cerca comparant desti amb posfinal de moviments). Ha de convertir la fitxa en dama (si cal) i eliminar les fitxes que menja
	void getPosicionsPossibles(const Posicio& origen, int& nPosicions, Posicio posicionsPossibles[]); //Retorna tots moviments possibles de fitxa a l'origen (també intermitjos en cadena de menjar)
	string toString() const; //genera string representant estat del tauler

	void visualitza(); //permite visualizar todas las piezas del tablero, dibujar el fondo, usar metodo visualiza de fitxa
	void visualtzaMovValids(int x, int y) { m_tauler[x][y].visualtzaMovValids(); }//permite visualizar los mov validos de la fixa seleccionada
private:
	Fitxa **m_tauler;
};

#endif