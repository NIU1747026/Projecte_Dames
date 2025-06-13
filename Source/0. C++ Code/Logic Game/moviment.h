#ifndef MOVIMENT_H_
	#define MOVIMENT_H_

#include "posicio.hpp"
using namespace std;

const int MAX_MOVIMENTS = 20;
const int MAX_RECORREGUT = 10;
const int MAX_POSICIONS = 20;

const int N_FILES = 8;
const int N_COLUMNES = 8;

class Fitxa;

class Moviment
{
public:
	Moviment() : m_nRecorregut(0), m_nFitxesMenjades(0), m_nDamesMenjades(0), m_nMenjades(0) {};
	void inicialitza() { m_nRecorregut = 0; m_nFitxesMenjades = 0; m_nDamesMenjades = 0; };

	const Posicio getPosFinal() const { if (m_nRecorregut > 0)return m_recorregut[m_nRecorregut - 1]; return { -1,-1 }; };
	const int getFitxesMenjades() const { return m_nFitxesMenjades; };
	const int getDamesMenjades() const { return m_nDamesMenjades; };

	void menja(Fitxa** tauler); //Recorre menjades i posa a TIPUS_EMPTY (es menja) les fitxes del tauler

	const bool esBuit() const { return m_nRecorregut == 0; };
	const bool esMenjada(Posicio& pos) const { return !noEsRepeteix(m_menjades, m_nMenjades, pos); }
	void afegeixMenjada(Posicio& pos, bool esDama) { if (noEsRepeteix(m_menjades, m_nMenjades, pos)) { m_menjades[m_nMenjades] = pos; m_nMenjades++; m_nFitxesMenjades++; if (esDama) { m_nDamesMenjades++; } } };
	void afegeixPos(Posicio& pos) { m_recorregut[m_nRecorregut] = pos; m_nRecorregut++; };
	const bool operator>(const Moviment& mov) const; //retorna true si el primer moviment es millor que l'altre

	void visualtzaRecorregut(); //permite visualizar los mov validos de la fixa seleccionada

private:
	int m_nFitxesMenjades;
	int m_nDamesMenjades;

	int m_nRecorregut;
	Posicio m_recorregut[MAX_RECORREGUT];

	int m_nMenjades;
	Posicio m_menjades[MAX_POSICIONS];
};

#endif