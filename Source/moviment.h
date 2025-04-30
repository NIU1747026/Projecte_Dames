#ifndef MOVIMENT_H_
	#define MOVIMENT_H_

const int MAX_RECORREGUT = 20;
const int MAX_POSICIONS = 65;

#include "posicio.hpp"

using namespace std;

class Moviment
{
public:
	Moviment() : m_nRecorregut(0), m_nFitxesMenjades(0), m_nDamesMenjades(0) {};
	void inicialitza() { m_nRecorregut = 0; m_nFitxesMenjades = 0; m_nDamesMenjades = 0; };

	const Posicio getPosFinal() const { 
		if (m_nRecorregut > 0)
			return m_recorregut[m_nRecorregut - 1];
		return {-1,-1};
	};
	int getFitxesMenjades() const { return m_nFitxesMenjades; };
	int getDamesMenjades() const { return m_nDamesMenjades; };
	int getnRecorregut() const { return m_nRecorregut; };
	//retornar recorregut?

	void afegeixPos(Posicio& pos) { m_recorregut[m_nRecorregut] = pos; m_nRecorregut++; };
	bool operator==(const Moviment& mov) const; //devuelve true si mov es el mismo
	bool operator>(const Moviment& mov) const; //retorna true si el primer moviment es millor que l'altre

	int recuperaFitxesMenjades(const Posicio& mov, Posicio menjades[MAX_POSICIONS]) { return 0; }; // Posa a menjades la posicio de les fitxes menjades en el moviment. (Si dos moviments acaben a mateix desti?????)
private:
	//Posicio m_posFinal = recorregut[m_nRecorregut];
	int m_nFitxesMenjades;
	int m_nDamesMenjades;

	int m_nRecorregut;
	Posicio m_recorregut[MAX_RECORREGUT];
};

#endif