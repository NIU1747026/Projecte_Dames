#include "moviment.h"	
#include "fitxes.h"
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
