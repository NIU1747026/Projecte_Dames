#ifndef MOVIMENT_H_
	#define MOVIMENT_H_

using namespace std;

#include "posicio.h"

const int MAX_RECORREGUT = 20;

class Moviment
{
public:
	Moviment(): m_nRecorregut(0), m_menjat(false) {};

	const Posicio getPosFinal() const { 
		if (m_nRecorregut > 0)
			return m_recorregut[m_nRecorregut - 1];
		return {-1,-1};
	};
	//retornar recorregut?
	//ret fitxes menjades

	void setMenjat(bool menjat) { m_menjat = menjat; };

	void afegeixPos(Posicio& pos) { m_recorregut[m_nRecorregut] = pos; m_nRecorregut++; };

private:
	//Posicio m_posFinal = recorregut[m_nRecorregut];
	//int m_fitxesMenjades = m_nRecorregut;

	bool m_menjat;
	int m_nRecorregut;
	Posicio m_recorregut[MAX_RECORREGUT];
};

#endif