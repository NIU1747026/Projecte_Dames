#include "moviment.h"	
#include "fitxes.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

bool Moviment::operator==(const Moviment& mov) const
{
	if (m_nDamesMenjades == mov.m_nDamesMenjades && m_nFitxesMenjades == mov.m_nFitxesMenjades)
	{
		return true;
	}
	return false;
}
bool Moviment::operator>(const Moviment& mov) const
{
	if ((m_nFitxesMenjades > mov.m_nFitxesMenjades) || (m_nFitxesMenjades == mov.m_nFitxesMenjades && m_nDamesMenjades > mov.m_nDamesMenjades))
	{
		return true;
	}
	return false;
}
void Moviment::evaluaMoviment(Fitxa tauler[N_FILES][N_COLUMNES])
{
	for (int i = 0; i < m_nRecorregut - 1; i++)
	{
		int fila = m_recorregut[i].getFila() + m_recorregut[i + 1].getFila() / 2;
		int colmna = m_recorregut[i].getColumna() + m_recorregut[i + 1].getColumna() / 2; 
		if (abs(m_recorregut[i].getFila() - m_recorregut[i + 1].getFila()) == 2 && abs(m_recorregut[i].getColumna() - m_recorregut[i + 1].getColumna()) == 2)
		{
			m_menjades[m_nMenjades].setPos(fila , colmna);
			m_nFitxesMenjades++;
			if (tauler[m_menjades[m_nMenjades].getFila()][m_menjades[m_nMenjades].getColumna()].getTipus() == TIPUS_DAMA)
				m_nDamesMenjades++;
			m_nMenjades++;
		}
	}
}
void Moviment::menja(Fitxa tauler[N_FILES][N_COLUMNES])
{
	for (int i = 0; i < m_nMenjades; i++)
	{
		tauler[m_menjades[i].getFila()][m_menjades[i].getColumna()].changeTipus(TIPUS_EMPTY);
	}
}