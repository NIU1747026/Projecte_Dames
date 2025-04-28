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

//movimentsValids = []
//movimentsPendents = []
//movimentActual = []
//afegir movimentActual a movimentsPendents
//posicioActual = posicio de la Fitxa
//do
//{
//	movimentActual = primer element de movimentsPendents
//		posValides = PosicionsValides(posicioActual)
//		while (posValides != [])
//		{
//			afegir a movimentActual la primera posicio valida
//				per la resta de posicions valides
//				movimentPendent = duplicaMoviment(movimentActual)
//				afegir la posicio a movimentPendent
//				afegir movimentPendent a movimentsPendents
//				posicioActual = primera posicio valida
//				posValides = PosicionsValides(posicioActual)
//		}
//	if (movimentActual != [])
//		afegir movimentActual a movimentsValids
//} while movimentsPendents != []

//movimentsValids = []
//movimentActual = []
//posicioActual = posicio de la fitxa
//posValides = PosicionsValides(posicioActual)
//while (posValides != [])
//{
//	afegir a movimentActual la posició vàlida
//		posicioActual = última posició de movimentActual
//		posValides = PosicionsValides(posicioActual)
//}
//if (movimentActual != [])
//afegir movimentActual a movimentsValids
