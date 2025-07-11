#include "fitxes.h"
#include "tauler.hpp"

void Fitxa::actualitzaMovimentsFitxa(Fitxa** tauler, const Posicio& origen)
{
	Moviment* movimentsPendents = new Moviment[MAX_MOVIMENTS];
	int nMovPendents = 1;
	Moviment movimentActual;
	Moviment movimentPendent;

	Posicio* posicionsValides = new Posicio[MAX_POSICIONS];
	int nPosValides = 0;

	Posicio* menjadas = new Posicio[MAX_POSICIONS];
	Posicio nein;
	FStatus* arrPosEstat = new FStatus[MAX_POSICIONS];
	FStatus* arrMovEstat = new FStatus[MAX_MOVIMENTS];
	arrMovEstat[0].init(true, true, TOT);

	Posicio posicioActual = origen;
	Fitxa fitxa = getFitxa(tauler, origen);
	FStatus estatFitxa;
	m_nMovimentsValids = 0;
	m_nPosicionsValides = 0;
	do
	{
		movimentActual = movimentsPendents[--nMovPendents];
		estatFitxa = arrMovEstat[nMovPendents];
		if (!movimentActual.esBuit())
			posicioActual = movimentActual.getPosFinal();
		getPosicionsValides(tauler, posicioActual, fitxa, estatFitxa, posicionsValides, nPosValides, arrPosEstat, menjadas, movimentActual);
		if (!movimentActual.esBuit()) {
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
					movimentPendent.afegeixMenjada(menjadas[i], getFitxa(tauler, menjadas[i]).getTipus() == TIPUS_DAMA);
				movimentsPendents[nMovPendents] = movimentPendent;
				arrMovEstat[nMovPendents++] = arrPosEstat[i];
			}
			movimentActual.afegeixPos(posicionsValides[0]);
			if (!(menjadas[0] == nein))
				movimentActual.afegeixMenjada(menjadas[0], getFitxa(tauler, menjadas[0]).getTipus() == TIPUS_DAMA);
			estatFitxa = arrPosEstat[0];
			posicioActual = posicionsValides[0];
			insertaPos(posicioActual);
			if (!movimentActual.esBuit()) {
				m_movimentValids[m_nMovimentsValids] = movimentActual;
				m_nMovimentsValids++;
			}
			getPosicionsValides(tauler, posicioActual, fitxa, estatFitxa, posicionsValides, nPosValides, arrPosEstat, menjadas, movimentActual);
		}
	} while (nMovPendents > 0);

	delete[] movimentsPendents;
	delete[] posicionsValides;
	delete[] menjadas;
	delete[] arrPosEstat;
	delete[] arrMovEstat;
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

void Fitxa::getPosicionsValides(Fitxa** tauler, const Posicio& origen, const Fitxa& fitxa, FStatus& status, Posicio posicionsPossibles[MAX_POSICIONS], int& nPossibles, FStatus arrStatus[MAX_POSICIONS], Posicio menjada[MAX_POSICIONS], Moviment& movimentActual)
{
	TipusFitxa tipus = fitxa.getTipus();
	ColorFitxa color = fitxa.getColor();
	nPossibles = 0;

	Posicio check1, check2;
	Posicio c[4] = {{-1, -1}, {-1, +1}, {+1, -1}, {+1, +1}};
	DireccioMov dirs[4] = {DALT_ESQUERRA, DALT_DRETA, BAIX_ESQUERRA, BAIX_DRETA};

	if (tipus == TIPUS_EMPTY || !status.getPotMenjar() || !dinsLimits(origen))
		return;

	for (int i = 0; i < 4; i++)
	{
		check1 = origen + c[i];
		check2 = origen + c[i] + c[i];
		if (dinsLimits(check1) && movValid(status.getDireccio(), dirs[i], color, tipus))
			if (getFitxa(tauler, check1).getTipus() == TIPUS_EMPTY && status.getPotMoure())
			{
				posicionsPossibles[nPossibles] = check1;
				menjada[nPossibles] = c[0];
				if (tipus == TIPUS_DAMA)
					arrStatus[nPossibles++].init(true, true, dirs[i]);
				else
					arrStatus[nPossibles++].init(false, false, dirs[i]);
			}
			else
				if (dinsLimits(check2) &&
					getFitxa(tauler, check2).getTipus() == TIPUS_EMPTY &&
					getFitxa(tauler, check1).getTipus() != TIPUS_EMPTY &&
					getFitxa(tauler, check1).getColor() != color &&
					!movimentActual.esMenjada(check1))
				{
					posicionsPossibles[nPossibles] = check2;
					menjada[nPossibles] = check1;
					arrStatus[nPossibles++].init(true, false, TOT);
				}
	}
}
