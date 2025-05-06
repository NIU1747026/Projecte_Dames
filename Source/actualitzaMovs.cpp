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
	FStatus arrPosEstat[MAX_POSICIONS];
	FStatus arrMovEstat[MAX_MOVIMENTS];
	arrMovEstat[0].init(true, true, TOT);

	Posicio posicioActual = origen;
	Fitxa fitxa = tauler[origen.getFila()][origen.getColumna()];
	FStatus estatFitxa;
	do
	{
		movimentActual = movimentsPendents[--nMovPendents];
		estatFitxa = arrMovEstat[nMovPendents];
		if (movimentActual.getnRecorregut() != 0)
			posicioActual = movimentActual.getPosFinal();
		getPosicionsValides(tauler, posicioActual, fitxa, estatFitxa, posicionsValides, nPosValides, arrPosEstat, menjadas, movimentActual);
		if (movimentActual.getnRecorregut() > 0) {
			m_movimentValids[m_nMovimentsValids] = movimentActual;
			m_nMovimentsValids++;
		}
		while (nPosValides > 0)
		{
			for (int i = 1; i < nPosValides; i++)
			{
				insertaPos(posicionsValides[i]);
				movimentPendent = movimentActual;
				movimentPendent.afegeixPos(posicionsValides[i]);
				if (!(menjadas[i] == nein))
					movimentPendent.afegeixMenjada(menjadas[i], tauler[menjadas[i].getFila()][menjadas[i].getColumna()].getTipus() == TIPUS_DAMA);
				movimentsPendents[nMovPendents] = movimentPendent;
				arrMovEstat[nMovPendents++] = arrPosEstat[i];
			}
			movimentActual.afegeixPos(posicionsValides[0]);
			if (!(menjadas[0] == nein))
				movimentActual.afegeixMenjada(menjadas[0], tauler[menjadas[0].getFila()][menjadas[0].getColumna()].getTipus() == TIPUS_DAMA);
			estatFitxa = arrPosEstat[0];
			posicioActual = posicionsValides[0];
			insertaPos(posicioActual);
			if (movimentActual.getnRecorregut() > 0) {
				m_movimentValids[m_nMovimentsValids] = movimentActual;
				m_nMovimentsValids++;
			}
			getPosicionsValides(tauler, posicioActual, fitxa, estatFitxa, posicionsValides, nPosValides, arrPosEstat, menjadas, movimentActual);
		}
	} while (nMovPendents > 0);
}

bool dinsLimits(const Posicio& p)
{
	int fila = p.getFila();
	int columna = p.getColumna();

	if (fila < 0 || columna < 0 || fila >= N_FILES || columna >= N_COLUMNES)
		return false;
	return true;
}

bool movValid(DireccioMov dir, DireccioMov dirValid, ColorFitxa color, TipusFitxa tipus)
{
	if (dir == TOT || dir == dirValid)
		switch (dirValid)
		{
		case DALT_ESQUERRA:
		case DALT_DRETA:
			if (color == COLOR_BLANC || tipus == TIPUS_DAMA)
				return true;
			break;
		case BAIX_ESQUERRA:
		case BAIX_DRETA:
			if (color == COLOR_NEGRE || tipus == TIPUS_DAMA)
				return true;
			break;
		case TOT:
			return true;
		default:
			break;
		}
	return false;
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

	Posicio check1, check2;
	int c[4][2] = {{-1, -1}, {-1, +1}, {+1, -1}, {+1, +1}};
	DireccioMov dirs[4] = {DALT_ESQUERRA, DALT_DRETA, BAIX_ESQUERRA, BAIX_DRETA};

	if (tipus == TIPUS_EMPTY || !potmenjar || !dinsLimits(origen))
		return;

	for (int i = 0; i < 4; i++)
	{
		check1.setPos(fila + c[i][0], col + c[i][1]);
		check2.setPos(fila + 2 * c[i][0], col + 2 * c[i][1]);
		if (dinsLimits(check1) && movValid(dir, dirs[i], color, tipus))
			if (tauler[fila + c[i][0]][col + c[i][1]].getTipus() == TIPUS_EMPTY && potmoure)
			{
				posicionsPossibles[nPossibles] = check1;
				if (tipus == TIPUS_DAMA)
					arrStatus[nPossibles++].init(true, true, dirs[i]);
				else
					arrStatus[nPossibles++].init(false, false, dirs[i]);
			}
			else
				if (dinsLimits(check2) &&
					tauler[fila + 2 * c[i][0]][col + 2 * c[i][1]].getTipus() == TIPUS_EMPTY &&
					tauler[fila + c[i][0]][col + c[i][1]].getTipus() != TIPUS_EMPTY &&
					tauler[fila + c[i][0]][col + c[i][1]].getColor() == !color &&
					!movimentActual.esMenjada(check1))
				{
					posicionsPossibles[nPossibles] = check2;
					menjada[nPossibles] = check1;
					arrStatus[nPossibles++].init(true, false, TOT);
				}
	}
}
