#include "tauler.hpp"	
#include "moviment.h"
#include "fitxes.h"
#include <iostream>
#include <fstream>

bool Tauler::mouFitxa(const Posicio& origen, const Posicio& desti)
{
	Moviment mov;
	Fitxa fOrg = getFitxa(m_tauler, origen);

	if (fOrg.movimentEsValid(desti, mov))
	{
		Fitxa f;
		Posicio millorMov;
		mov.menja(m_tauler);
		for (int i = 0; i < N_FILES; i++)
		{
			for (int y = 0; y < N_COLUMNES; y++)
			{
				Posicio pos(i, y);
				if (getFitxa(m_tauler, pos).getColor() == fOrg.getColor() && !(pos == origen) && !getFitxa(m_tauler, pos).esMillorMoviment(mov))
					millorMov.setPos(i, y);
			}
		}
		if(millorMov.getFila() != -1)
			m_tauler[millorMov.getFila()][millorMov.getColumna()] = f;
		if (fOrg.esMillorMoviment(mov))
			m_tauler[desti.getFila()][desti.getColumna()] = fOrg;
		m_tauler[origen.getFila()][origen.getColumna()] = f;
		if (desti.getFila() == 0 && m_tauler[desti.getFila()][desti.getColumna()].getColor() == COLOR_BLANC)
			m_tauler[desti.getFila()][desti.getColumna()].changeTipus(TIPUS_DAMA);
		if (desti.getFila() == 8 && m_tauler[desti.getFila()][desti.getColumna()].getColor() == COLOR_NEGRE)
			m_tauler[desti.getFila()][desti.getColumna()].changeTipus(TIPUS_DAMA);
		return true;
	}
	return false;
}
