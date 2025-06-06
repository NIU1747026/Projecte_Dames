#include "fitxes.h"	
#include <iostream>
#include "GraphicManager.h"
#include "info_joc.hpp"
#include <fstream>

const bool noEsRepeteix(const Posicio array[], const int& nPosicionsArray, const Posicio& pos)
{
	for (int i = 0; i < nPosicionsArray; i++) 
		if (array[i] == pos)
			return false;
	return true;
}
void Fitxa::afegeixPosicionsValides(Posicio Valides[MAX_POSICIONS], int& nValides) const
{
	for (int i = 0; i < m_nPosicionsValides; i++)
		if (noEsRepeteix(Valides, nValides, m_posicionsValides[i]))
			Valides[nValides++] = m_posicionsValides[i];
}
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
void Fitxa::visualitza(int x, int y)
{
	int posX = POS_X_TAULER + CASELLA_INICIAL_X + (y*AMPLADA_CASELLA);
	int posY = POS_Y_TAULER + CASELLA_INICIAL_Y + (x*ALCADA_CASELLA);
	IMAGE_NAME g = GRAFIC_FITXA_BLANCA;
	switch (m_color)
	{
	case COLOR_BLANC:
		if (m_tipus == TIPUS_NORMAL)
			g = GRAFIC_FITXA_BLANCA;
		else
			g = GRAFIC_DAMA_BLANCA;
		break;
	case COLOR_NEGRE: 
		if (m_tipus == TIPUS_NORMAL)
			g = GRAFIC_FITXA_NEGRA;
		else
			g = GRAFIC_DAMA_NEGRA;
		break;
	}
	GraphicManager::getInstance()->drawSprite(g, posX, posY);
}
