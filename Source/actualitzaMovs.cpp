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

	Posicio menjadas[MAX_POSICIONS];
	Posicio nein;
	FStatus arrPOSpotmenjar[MAX_POSICIONS];
	FStatus arrMOVpotmenjar[MAX_MOVIMENTS];
	arrMOVpotmenjar[0].init(true, true, TOT);

	Posicio posicioActual = origen;
	Fitxa fitxa = tauler[origen.getFila()][origen.getColumna()];
	FStatus potmenjar;
	do
	{
		movimentActual = movimentsPendents[--nMovPendents];
		potmenjar = arrMOVpotmenjar[nMovPendents];
		if (movimentActual.getnRecorregut() != 0)
			posicioActual = movimentActual.getPosFinal();
		getPosicionsValides(tauler, posicioActual, fitxa, potmenjar, posicionsValides, nPosValides, arrPOSpotmenjar, menjadas, movimentActual);
		while (nPosValides > 0)
		{
			for (int i = 1; i < nPosValides; i++)
			{
				insertaPos(posicionsValides[i]);
				movimentPendent = movimentActual;
				movimentPendent.afegeixPos(posicionsValides[i]);
				if (!(menjadas[i] == nein))
					movimentPendent.afegeixMenjada(menjadas[i]);
				movimentsPendents[nMovPendents] = movimentPendent;
				arrMOVpotmenjar[nMovPendents++] = arrPOSpotmenjar[i];
			}
			movimentActual.afegeixPos(posicionsValides[0]);
			if (!(menjadas[0] == nein))
				movimentActual.afegeixMenjada(menjadas[0]);
			potmenjar = arrPOSpotmenjar[0];
			posicioActual = posicionsValides[0];
			insertaPos(posicioActual);
			getPosicionsValides(tauler, posicioActual, fitxa, potmenjar, posicionsValides, nPosValides, arrPOSpotmenjar, menjadas, movimentActual);
		}
		if (movimentActual.getnRecorregut() > 0) {
			m_movimentValids[m_nMovimentsValids] = movimentActual;
			m_movimentValids[m_nMovimentsValids].evaluaMoviment(tauler, origen);
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

void Fitxa::getPosicionsValides(Fitxa tauler[N_FILES][N_COLUMNES], const Posicio& origen, const Fitxa& fitxa, FStatus& status, Posicio posicionsPossibles[MAX_POSICIONS], int& nPossibles, FStatus arrStatus[MAX_POSICIONS], Posicio menjada[MAX_POSICIONS], Moviment& movimentActual)
{
	int col = origen.getColumna();
	int fila = origen.getFila();
	TipusFitxa tipus = fitxa.getTipus();
	ColorFitxa color = fitxa.getColor();
	bool potmenjar = status.getPotMenjar();
	bool potmoure = status.getPotMoure();
	DireccioMov dir = status.getDireccio();
	nPossibles = 0;

	Posicio check;

	if (tipus == TIPUS_EMPTY || !potmenjar || !dinsLimits(col, fila))
		return;

	if (color == COLOR_BLANC || tipus == TIPUS_DAMA)
	{
		check.setPos(fila - 1, col - 1);
		if (dinsLimits(fila - 1, col - 1) && (dir == TOT || dir == DALT_ESQUERRA))
			if (tauler[fila - 1][col - 1].getTipus() == TIPUS_EMPTY && potmoure)
			{
				posicionsPossibles[nPossibles] = { fila - 1, col - 1 };
				if (tipus == TIPUS_DAMA)
					arrStatus[nPossibles++].init(true, true, DALT_ESQUERRA);
				else
					arrStatus[nPossibles++].init(false, false, DALT_ESQUERRA);
			}
			else if (dinsLimits(fila - 2, col - 2))
				if (tauler[fila - 1][col - 1].getColor() == !color && tauler[fila - 1][col - 1].getTipus() != TIPUS_EMPTY &&
					tauler[fila - 2][col - 2].getTipus() == TIPUS_EMPTY &&
					!movimentActual.esMenjada(check))
				{
					posicionsPossibles[nPossibles] = { fila - 2, col - 2 };
					menjada[nPossibles] = { fila - 1, col - 1 };
					arrStatus[nPossibles++].init(true, false, TOT);
				}

		check.setPos(fila - 1, col + 1);
		if (dinsLimits(fila - 1, col + 1) && (dir == TOT || dir == DALT_DRETA))
			if (tauler[fila - 1][col + 1].getTipus() == TIPUS_EMPTY && potmoure)
			{
				posicionsPossibles[nPossibles] = { fila - 1, col + 1 };
				if (tipus == TIPUS_DAMA)
					arrStatus[nPossibles++].init(true, true, DALT_DRETA);
				else
					arrStatus[nPossibles++].init(false, false, DALT_DRETA);
			}
			else if (dinsLimits(fila - 2, col + 2))
				if (tauler[fila - 1][col + 1].getColor() == !color && tauler[fila - 1][col + 1].getTipus() != TIPUS_EMPTY &&
					tauler[fila - 2][col + 2].getTipus() == TIPUS_EMPTY &&
					!movimentActual.esMenjada(check))
				{
					posicionsPossibles[nPossibles] = { fila - 2, col + 2 };
					menjada[nPossibles] = { fila - 1, col + 1 };
					arrStatus[nPossibles++].init(true, false, TOT);
				}
	}
	if (color == COLOR_NEGRE || tipus == TIPUS_DAMA)
	{
		check.setPos(fila + 1, col - 1);
		if (dinsLimits(fila + 1, col - 1) && (dir == TOT || dir == BAIX_ESQUERRA))
			if (tauler[fila + 1][col - 1].getTipus() == TIPUS_EMPTY && potmoure)
			{
				posicionsPossibles[nPossibles] = { fila + 1, col - 1 };
				if (tipus == TIPUS_DAMA)
					arrStatus[nPossibles++].init(true, true, BAIX_ESQUERRA);
				else
					arrStatus[nPossibles++].init(false, false, BAIX_ESQUERRA);
			}
			else if (dinsLimits(fila + 2, col - 2))
				if (tauler[fila + 1][col - 1].getColor() == !color && tauler[fila + 1][col - 1].getTipus() != TIPUS_EMPTY &&
					tauler[fila + 2][col - 2].getTipus() == TIPUS_EMPTY &&
					!movimentActual.esMenjada(check))
				{
					posicionsPossibles[nPossibles] = { fila + 2, col - 2 };
					menjada[nPossibles] = { fila + 1, col - 1 };
					arrStatus[nPossibles++].init(true, false, TOT);
				}

		check.setPos(fila + 1, col + 1);
		if (dinsLimits(fila + 1, col + 1) && (dir == TOT || dir == BAIX_DRETA))
			if (tauler[fila + 1][col + 1].getTipus() == TIPUS_EMPTY && potmoure)
			{
				posicionsPossibles[nPossibles] = { fila + 1, col + 1 };
				if (tipus == TIPUS_DAMA)
					arrStatus[nPossibles++].init(true, true, BAIX_DRETA);
				else
					arrStatus[nPossibles++].init(false, false, BAIX_DRETA);
			}
			else if (dinsLimits(fila + 2, col + 2))
				if (tauler[fila + 1][col + 1].getColor() == !color && tauler[fila + 1][col + 1].getTipus() != TIPUS_EMPTY &&
					tauler[fila + 2][col + 2].getTipus() == TIPUS_EMPTY &&
					!movimentActual.esMenjada(check))
				{
					posicionsPossibles[nPossibles] = { fila + 2, col + 2 };
					menjada[nPossibles] = { fila + 1, col + 1 };
					arrStatus[nPossibles++].init(true, false, TOT);
				}
	}
}
