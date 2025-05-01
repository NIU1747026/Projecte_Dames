#include "fitxes.h"	
#include <iostream>
#include <fstream>

bool comprovarRepeticio(const Posicio array[], const int& nPosicionsArray, const Posicio& pos)
{
	for (int i = 0; i < nPosicionsArray; i++) 
	{
		if (array[i] == pos)
		{
			return false;
		}
	}
	return true;
}

void Fitxa::afegeixPosicionsValides(Posicio Valides[MAX_POSICIONS], int& nValides) const
{
	for (int i = 0; i < m_nPosicionsValides; i++)
	{
		if (comprovarRepeticio(Valides, nValides, m_posicionsValides[i]))
		{
			Valides[nValides++] = m_posicionsValides[i];
		}
	}
}
// afegeix a l'array valides, les posicions valides de la fitxa, amb compte de no repetir-ne cap que ja estigui

const bool Fitxa::movimentEsValid(const Posicio& desti, Moviment& mov) const 
{
	for (int i = 0; i < m_nMovimentsValids; i++)
	{
		for (int z = 0; z < m_movimentValids[i].getnRecorregut(); z++)
		{
			if (m_movimentValids[i].getPosFinal() == desti) 
				return true;
		}
	}
	return false;
}//mira destins de la llista de moviments y retorna true si hi es i el posa a mov.

const bool Fitxa::esMillorMoviment(const Moviment& mov) const
{
	for (int i = 0; i < m_nMovimentsValids; i++)
	{
		if (m_movimentValids[i] > mov)
			return false;
	}
	return true;
}//retorna true si no hi ha cap millor moviment

void Fitxa::insertaPos(const Posicio& pos)
{
	if (comprovarRepeticio(m_posicionsValides, m_nPosicionsValides, pos))
		m_posicionsValides[m_nPosicionsValides++] = pos;
}
