#include "moviment.h"	
#include "fitxes.h"
#include "GraphicManager.h"
#include "info_joc.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>

const bool Moviment::operator>(const Moviment& mov) const
{
	if ((m_nFitxesMenjades > mov.m_nFitxesMenjades) || (m_nFitxesMenjades == mov.m_nFitxesMenjades && m_nDamesMenjades > mov.m_nDamesMenjades))
		return true;
	return false;
}

void Moviment::menja(Fitxa tauler[N_FILES][N_COLUMNES])
{
	Fitxa f;
	for (int i = 0; i < m_nMenjades; i++)
	{
		tauler[m_menjades[i].getFila()][m_menjades[i].getColumna()] = f;
	}
}
void Moviment::visualtzaRecorregut()
{
	for (int i = 0; i < m_nRecorregut; i++)
	{
		int posX = POS_X_TAULER + CASELLA_INICIAL_X + (m_recorregut[i].getColumna() * AMPLADA_CASELLA);
		int posY = POS_Y_TAULER + CASELLA_INICIAL_Y + (m_recorregut[i].getFila() * ALCADA_CASELLA);
		GraphicManager::getInstance()->drawSprite(GRAFIC_POSICIO_VALIDA, posX, posY);
	}
	
}