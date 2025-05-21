#include "fitxes.h"	
#include <iostream>
#include <fstream>

const bool noEsRepeteix(const Posicio array[], const int& nPosicionsArray, const Posicio& pos)
{
	for (int i = 0; i < nPosicionsArray; i++) 
		if (array[i] == pos)
			return false;
	return true;
}

// Afegeix a l'array valides, les posicions valides de la fitxa, amb compte de no repetir-ne cap que ja estigui
void Fitxa::afegeixPosicionsValides(Posicio Valides[MAX_POSICIONS], int& nValides) const
{
	for (int i = 0; i < m_nPosicionsValides; i++)
		if (noEsRepeteix(Valides, nValides, m_posicionsValides[i]))
			Valides[nValides++] = m_posicionsValides[i];
}

//mira destins de la llista de moviments y retorna true si hi es i el posa a mov.
const bool Fitxa::movimentEsValid(const Posicio& desti, Moviment& mov) const
{
	for (int i = 0; i < m_nMovimentsValids; i++)
	{
		if (m_movimentValids[i].getPosFinal() == desti)
		{
			mov = m_movimentValids[i];
			return true;
		}
	}
	return false;
}

//retorna true si no hi ha cap millor moviment
const bool Fitxa::esMillorMoviment(const Moviment& mov) const
{
	for (int i = 0; i < m_nMovimentsValids; i++)
		if (m_movimentValids[i] > mov)
			return false;
	return true;
}

void Fitxa::insertaPos(const Posicio& pos)
{
	if (noEsRepeteix(m_posicionsValides, m_nPosicionsValides, pos))
		m_posicionsValides[m_nPosicionsValides++] = pos;
}

Fitxa getFitxa(const Fitxa tauler[N_FILES][N_COLUMNES], const Posicio& pos)
{
	return tauler[pos.getFila()][pos.getColumna()];
}
