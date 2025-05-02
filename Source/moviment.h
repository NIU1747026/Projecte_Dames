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

	const Posicio getPosFinal() const { 
		if (m_nRecorregut > 0)
			return m_recorregut[m_nRecorregut - 1];
		return {-1,-1};
	};
	const int getFitxesMenjades() const { return m_nFitxesMenjades; };
	const int getDamesMenjades() const { return m_nDamesMenjades; };
	const int getnRecorregut() const { return m_nRecorregut; };

	void evaluaMoviment(Fitxa tauler[N_FILES][N_COLUMNES], const Posicio& origen); //Observa el recorregut del moviment i, si hi ha un salt (ex: a1 -> c3) vol dir que a l'espai del mitg s'ha menjat una peça, aquesta posicio s'afegeix a l'array menjades i s'incrementa nFitxesMenjades(SEMPRE) i nDames nomes si es una dama
	void menja(Fitxa tauler[N_FILES][N_COLUMNES]); //Recorre menjades i posa a TIPUS_EMPTY (es menja) les fitxes del tauler

	const bool esMenjada(Posicio& pos) const { return !comprovarRepeticio(m_menjades, m_nMenjades, pos); }
	void afegeixMenjada(Posicio& pos) { if (comprovarRepeticio(m_menjades, m_nMenjades, pos)) { m_menjades[m_nMenjades] = pos; m_nMenjades++; } };
	void afegeixPos(Posicio& pos) { m_recorregut[m_nRecorregut] = pos; m_nRecorregut++; };
	const bool operator>(const Moviment& mov) const; //retorna true si el primer moviment es millor que l'altre

private:
	int m_nFitxesMenjades;
	int m_nDamesMenjades;

	int m_nRecorregut;
	Posicio m_recorregut[MAX_RECORREGUT];

	int m_nMenjades;
	Posicio m_menjades[MAX_POSICIONS];
};

#endif