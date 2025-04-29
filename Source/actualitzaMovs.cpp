#include "fitxes.h"

void Fitxa::actualitzaMovimentsFitxa(Fitxa tauler[N_FILES][N_COLUMNES], const Posicio& origen)
{
	//Posicio pos_actual = origen;
	//Posicio pos_valides[MAX_POSICIONS];
	//int n_pvalides = 0;
	//Moviment mov_actual;
	//getPosicionsValides(tauler, pos_actual, pos_valides, n_pvalides, potmenjar);
	//while (n_pvalides > 0)
	//{
	//	n_pvalides--;
	//	mov_actual.afegeixPos(pos_valides[n_pvalides]);
	//	pos_actual = pos_valides[n_pvalides];
	//	getPosicionsValides(tauler, pos_actual, pos_valides, n_pvalides, true);
	//}
	//if (mov_actual.getnRecorregut() > 0) {
	//	m_movimentValids[m_nMovimentsValids] = mov_actual;
	//	m_nMovimentsValids++;
	//}

	Moviment movimentsValids[MAX_MOVIMENTS];
	int nMovValids = 0;
	Moviment movimentsPendents[MAX_MOVIMENTS];
	int nMovPendents = 1;
	Moviment movimentActual;
	Moviment movimentPendent;

	Posicio posicionsValides[MAX_POSICIONS];
	int nPosValides = 0;
	
	bool arrPOSpotmenjar[MAX_POSICIONS];
	bool arrMOVpotmenjar[MAX_MOVIMENTS];
	arrMOVpotmenjar[0] = true;

	
	Posicio posicioActual = origen;
	bool potmenjar;
	do
	{
		movimentActual = movimentsPendents[nMovPendents - 1];
		potmenjar = arrMOVpotmenjar[nMovPendents - 1];
		nMovPendents--;
		posicioActual = movimentActual.getPosFinal();
		getPosicionsValides(tauler, posicioActual, potmenjar, posicionsValides, nPosValides, arrPOSpotmenjar);
		while (nPosValides > 0)
		{
			for (int i = 1; i < nPosValides; i++)
			{
				movimentPendent = movimentActual;
				movimentPendent.afegeixPos(posicionsValides[i]);
				movimentsPendents[nMovPendents] = movimentPendent;
				arrMOVpotmenjar[nMovPendents] = arrPOSpotmenjar[i];
				nMovPendents++;
				insertaPos(posicionsValides[i]);//
			}
			insertaPos(posicionsValides[0]);//
			movimentActual.afegeixPos(posicionsValides[0]);
			potmenjar = arrPOSpotmenjar[0];
			posicioActual = posicionsValides[0];
			getPosicionsValides(tauler, posicioActual, potmenjar, posicionsValides, nPosValides, arrPOSpotmenjar);
		}
		if (movimentActual.getnRecorregut() > 0) {
			movimentsValids[nMovValids] = movimentActual;
			nMovValids++;
		}
	} while (nMovPendents > 0);
}

bool dinsLimits(int fila, int columna)
{
	if (fila < 0 || columna < 0 || fila > N_FILES || columna > N_COLUMNES)
		return false;
	return true;
}

void Fitxa::getPosicionsValides(Fitxa tauler[N_FILES][N_COLUMNES], const Posicio& origen, bool potmenjar, Posicio posicionsPossibles[MAX_POSICIONS], int& nPossibles, bool arrpotmenjar[MAX_POSICIONS])
{
	int col = origen.getColumna();
	int fila = origen.getFila();
	TipusFitxa tipus = tauler[fila][col].getTipus();
	ColorFitxa color = tauler[fila][col].getColor();
	nPossibles = 0;

	if (tipus == TIPUS_EMPTY)
		return;

	if (color == COLOR_BLANC)
	{
		if (dinsLimits(fila - 1, col - 1))
			if (tauler[fila - 1][col - 1].getTipus() == TIPUS_EMPTY)
			{
				posicionsPossibles[nPossibles] = { fila - 1, col - 1 };
				arrpotmenjar[nPossibles++] = false;
			}
			else if (dinsLimits(fila - 2, col - 2) && potmenjar)
				if (tauler[fila - 1][col - 1].getColor() == COLOR_NEGRE &&
					tauler[fila - 2][col - 2].getTipus() == TIPUS_EMPTY)
				{
					posicionsPossibles[nPossibles++] = { fila - 2, col - 2 };
					arrpotmenjar[nPossibles++] = true;
				}

		if (dinsLimits(fila - 1, col + 1))
			if (tauler[fila - 1][col + 1].getTipus() == TIPUS_EMPTY)
			{
				posicionsPossibles[nPossibles++] = { fila - 1, col + 1 };
				arrpotmenjar[nPossibles++] = false;
			}

			else if (dinsLimits(fila - 2, col + 2) && potmenjar)
				if (tauler[fila - 1][col + 1].getColor() == COLOR_NEGRE &&
					tauler[fila - 2][col + 2].getTipus() == TIPUS_EMPTY)
				{
					posicionsPossibles[nPossibles++] = { fila - 2, col + 2 };
					arrpotmenjar[nPossibles++] = true;
				}
	}
	if (color == COLOR_NEGRE)
	{
		if (dinsLimits(fila + 1, col - 1))
			if (tauler[fila + 1][col - 1].getTipus() == TIPUS_EMPTY)
			{
				posicionsPossibles[nPossibles++] = { fila + 1, col - 1 };
				arrpotmenjar[nPossibles++] = false;
			}
			else if (dinsLimits(fila + 2, col - 2))
				if (tauler[fila + 1][col - 1].getColor() == COLOR_NEGRE &&
					tauler[fila + 2][col - 2].getTipus() == TIPUS_EMPTY)
				{
					posicionsPossibles[nPossibles++] = { fila + 1, col - 1 };
					arrpotmenjar[nPossibles++] = true;
				}

		if (dinsLimits(fila + 1, col + 1))
			if (tauler[fila + 1][col + 1].getTipus() == TIPUS_EMPTY)
			{
				posicionsPossibles[nPossibles++] = { fila + 1, col + 1 };
				arrpotmenjar[nPossibles++] = true;
			}
			else if (dinsLimits(fila + 2, col + 2))
				if (tauler[fila + 1][col + 1].getColor() == COLOR_NEGRE &&
					tauler[fila + 2][col + 2].getTipus() == TIPUS_EMPTY)
				{
					posicionsPossibles[nPossibles++] = { fila + 2, col + 2 };
					arrpotmenjar[nPossibles++] = true;
				}
	}
}
