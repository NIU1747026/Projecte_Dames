#include "tauler.hpp"	
#include "moviment.h"
#include "fitxes.h"
#include <iostream>
#include <fstream>
using namespace std;

bool Tauler::mouFitxa(const Posicio& origen, const Posicio& desti)
{
	Moviment mov;
	if (m_tauler[origen.getFila()][origen.getColumna()].movimentEsValid(desti, mov))
	{
		Fitxa f;
		Posicio millorMov;
		mov.evaluaMoviment(m_tauler,origen);
		mov.menja(m_tauler);
		//m_tauler[origen.getFila()][origen.getColumna()].calculaMenjades(m_tauler); 
		//mirar si altre fitxa tenia millor moviment
		for (int i = 0; i < N_FILES; i++)
		{
			for (int y = 0; y < N_COLUMNES; y++)
			{
				if (m_tauler[i][y].getColor() == m_tauler[origen.getFila()][origen.getColumna()].getColor() && (i != origen.getFila() && y != origen.getColumna()) && !m_tauler[i][y].esMillorMoviment(mov))
					millorMov.setPos(i, y);
			}
		}
		if(millorMov.getFila() != -1)
			m_tauler[millorMov.getFila()][millorMov.getColumna()] = f;
		if (m_tauler[origen.getFila()][origen.getColumna()].esMillorMoviment(mov))
			m_tauler[desti.getFila()][desti.getColumna()] = m_tauler[origen.getFila()][origen.getColumna()];
		m_tauler[origen.getFila()][origen.getColumna()] = f;
		if (desti.getFila() == 8 && m_tauler[desti.getFila()][desti.getColumna()].getColor() == COLOR_BLANC)
			m_tauler[desti.getFila()][desti.getColumna()].changeTipus(TIPUS_DAMA);
		if (desti.getFila() == 0 && m_tauler[desti.getFila()][desti.getColumna()].getColor() == COLOR_NEGRE)
			m_tauler[desti.getFila()][desti.getColumna()].changeTipus(TIPUS_DAMA);
		return true;
	}
	return false;
}