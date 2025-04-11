#ifndef MOVIMENT_H_
	#define MOVIMENT_H_

using namespace std;

#include "posicio.h"

const int MAX_RECORREGUT = 20;

class Moviment
{
public:
	Moviment() : m_nRecorregut(0), m_nFitxesMenjades(0) {};
	void inicialitza(): m_nRecorregut(0) ,m_nFitxesMenjades(0) {};

	const Posicio getPosFinal() const { 
		if (m_nRecorregut > 0)
			return m_recorregut[m_nRecorregut - 1];
		return {-1,-1};
	};
	int getFitxesMenjades() const {return m_nFitxesMenjades};
	//retornar recorregut?

	void afegeixPos(Posicio& pos) { m_recorregut[m_nRecorregut] = pos; m_nRecorregut++; };
	//bool operator==(const Moviment& mov);
	bool operator>(const Moviment& mov); //retorna true si el primer moviment es millor que l'altre

	int recuperaFitxesMenjades(const Posició& mov, Posicio menjades[MAX_POSICIONS]); // Posa a menjades la posició de les fitxes menjades en el moviment. (Si dos moviments acaben a mateix destí?????)
private:
	//Posicio m_posFinal = recorregut[m_nRecorregut];
	int m_nFitxesMenjades;

	int m_nRecorregut;
	Posicio m_recorregut[MAX_RECORREGUT];
};

#endif