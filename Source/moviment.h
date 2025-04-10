#ifndef MOVIMENT_H_
	#define MOVIMENT_H_

using namespace std;

#include "posicio.h"

const int MAX_RECORREGUT = 20;

class Moviment
{
public:
	Moviment(): m_nRecorregut(0) {};

	const Posicio getPosFinal() const { 
		if (m_nRecorregut > 0)
			return m_recorregut[m_nRecorregut - 1];
		return {-1,-1};
	};
	//retornar recorregut?
	//ret fitxes menjades


	//void afegeixPos(Posicio& pos) { m_recorregut[m_nRecorregut] = pos; m_nRecorregut++; };
	//bool operator==(const Moviment& mov);
private:
	//Posicio m_posFinal = recorregut[m_nRecorregut];
	int m_fitxesMenjades;

	int m_nRecorregut;
	Posicio m_recorregut[MAX_RECORREGUT];
};

#endif