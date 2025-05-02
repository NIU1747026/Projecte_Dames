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
		mov.evaluaMoviment(m_tauler);
		mov.menja(m_tauler);
		m_tauler[origen.getFila()][origen.getColumna()].calculaMenjades(m_tauler); 
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