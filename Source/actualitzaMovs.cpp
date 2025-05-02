#include "fitxes.h"
#include "tauler.hpp"

void Fitxa::actualitzaMovimentsFitxa(Fitxa tauler[N_FILES][N_COLUMNES], const Posicio& origen)
{
	Moviment movimentsPendents[MAX_MOVIMENTS];
	int nMovPendents = 1;
	Moviment movimentActual;
	Moviment movimentPendent;

	Posicio posicionsValides[MAX_POSICIONS];
	int nPosValides = 0;
	
	FStatus arrPOSpotmenjar[MAX_POSICIONS];
	FStatus arrMOVpotmenjar[MAX_MOVIMENTS];
	arrMOVpotmenjar[0].init(true, true);

	
	Posicio posicioActual = origen;
	Fitxa fitxa = tauler[origen.getFila()][origen.getColumna()];
	FStatus potmenjar;
	do
	{
		movimentActual = movimentsPendents[--nMovPendents];
		potmenjar = arrMOVpotmenjar[nMovPendents];
		if (movimentActual.getnRecorregut() != 0)
			posicioActual = movimentActual.getPosFinal();
		getPosicionsValides(tauler, posicioActual, fitxa, potmenjar, posicionsValides, nPosValides, arrPOSpotmenjar);
		while (nPosValides > 0)
		{
			for (int i = 1; i < nPosValides; i++)
			{
				insertaPos(posicionsValides[i]);
				movimentPendent = movimentActual;
				movimentPendent.afegeixPos(posicionsValides[i]);
				movimentsPendents[nMovPendents] = movimentPendent;
				arrMOVpotmenjar[nMovPendents++] = arrPOSpotmenjar[i];
			}
			movimentActual.afegeixPos(posicionsValides[0]);
			potmenjar = arrPOSpotmenjar[0];
			posicioActual = posicionsValides[0];
			insertaPos(posicioActual);
			getPosicionsValides(tauler, posicioActual, fitxa, potmenjar, posicionsValides, nPosValides, arrPOSpotmenjar);
		}
		if (movimentActual.getnRecorregut() > 0) {
			movimentActual.evaluaMoviment(tauler, origen);//
			m_movimentValids[m_nMovimentsValids] = movimentActual;
			m_nMovimentsValids++;
		}
	} while (nMovPendents > 0);
}

bool dinsLimits(int fila, int columna)
{
	if (fila < 0 || columna < 0 || fila >= N_FILES || columna >= N_COLUMNES)
		return false;
	return true;
}

void Fitxa::getPosicionsValides(Fitxa tauler[N_FILES][N_COLUMNES], const Posicio& origen, const Fitxa& fitxa, FStatus& status, Posicio posicionsPossibles[MAX_POSICIONS], int& nPossibles, FStatus arrStatus[MAX_POSICIONS])
{
	int col = origen.getColumna();
	int fila = origen.getFila();
	TipusFitxa tipus = fitxa.getTipus();
	ColorFitxa color = fitxa.getColor();
	bool potmenjar = status.getPotMenjar();
	bool potmoure = status.getPotMoure();
	nPossibles = 0;

	if (tipus == TIPUS_EMPTY || !potmenjar || !dinsLimits(col, fila))
		return;

	if (color == COLOR_BLANC)
	{
		if (dinsLimits(fila - 1, col - 1))
			if (tauler[fila - 1][col - 1].getTipus() == TIPUS_EMPTY && potmoure)
			{
				posicionsPossibles[nPossibles] = { fila - 1, col - 1 };
				arrStatus[nPossibles++].init(false, false);
			}
			else if (dinsLimits(fila - 2, col - 2))
				if (tauler[fila - 1][col - 1].getColor() == COLOR_NEGRE &&
					tauler[fila - 2][col - 2].getTipus() == TIPUS_EMPTY)
				{
					posicionsPossibles[nPossibles] = { fila - 2, col - 2 };
					arrStatus[nPossibles++].init(true, false);
				}

		if (dinsLimits(fila - 1, col + 1))
			if (tauler[fila - 1][col + 1].getTipus() == TIPUS_EMPTY && potmoure)
			{
				posicionsPossibles[nPossibles] = { fila - 1, col + 1 };
				arrStatus[nPossibles++].init(false, false);
			}
			else if (dinsLimits(fila - 2, col + 2))
				if (tauler[fila - 1][col + 1].getColor() == COLOR_NEGRE &&
					tauler[fila - 2][col + 2].getTipus() == TIPUS_EMPTY)
				{
					posicionsPossibles[nPossibles] = { fila - 2, col + 2 };
					arrStatus[nPossibles++].init(true, false);
				}
	}
	if (color == COLOR_NEGRE)
	{
		if (dinsLimits(fila + 1, col - 1))
			if (tauler[fila + 1][col - 1].getTipus() == TIPUS_EMPTY && potmoure)
			{
				posicionsPossibles[nPossibles] = { fila + 1, col - 1 };
				arrStatus[nPossibles++].init(false, false);
			}
			else if (dinsLimits(fila + 2, col - 2))
				if (tauler[fila + 1][col - 1].getColor() == COLOR_BLANC &&
					tauler[fila + 2][col - 2].getTipus() == TIPUS_EMPTY)
				{
					posicionsPossibles[nPossibles] = { fila + 2, col - 2 };
					arrStatus[nPossibles++].init(true, false);
				}

		if (dinsLimits(fila + 1, col + 1))
			if (tauler[fila + 1][col + 1].getTipus() == TIPUS_EMPTY && potmoure)
			{
				posicionsPossibles[nPossibles] = { fila + 1, col + 1 };
				arrStatus[nPossibles++].init(false, false);
			}
			else if (dinsLimits(fila + 2, col + 2))
				if (tauler[fila + 1][col + 1].getColor() == COLOR_BLANC &&
					tauler[fila + 2][col + 2].getTipus() == TIPUS_EMPTY)
				{
					posicionsPossibles[nPossibles] = { fila + 2, col + 2 };
					arrStatus[nPossibles++].init(true, false);
				}
	}
}
