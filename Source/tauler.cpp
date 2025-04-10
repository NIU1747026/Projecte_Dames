#include "tauler.h"	
#include <iostream>
#include <fstream>
using namespace std;
//falta tauler i que fitxa tingui posicio
void Tauler::inicialitza(const string& nomFitxer)
{
	ifstream fitxer;
	string coordenada;
	char mirarFitxa;
	Posicio fitcha;

	fitxer.open(nomFitxer);
	
	if (!fitxer.is_open())
		return;
	
	while (!fitxer.eof())
	{
		fitxer >> mirarFitxa >> coordenada;
		fitcha.setPos(coordenada);
		switch (mirarFitxa)
		{
			case 'O':
				m_tauler[fitcha.getFila()][fitcha.getColumna()].inicialitza(COLOR_BLANC,TIPUS_NORMAL);
				break;
			case 'D':
				m_tauler[fitcha.getFila()][fitcha.getColumna()].inicialitza(COLOR_BLANC,TIPUS_DAMA);
				break;
			case 'X':
				m_tauler[fitcha.getFila()][fitcha.getColumna()].inicialitza(COLOR_NEGRE,TIPUS_NORMAL);
				break;
			case 'R':
				m_tauler[fitcha.getFila()][fitcha.getColumna()].inicialitza(COLOR_NEGRE,TIPUS_DAMA);
				break;
		default:
			break;
		}
	}
	fitxer.close();
}

//hay que cambiarlo para que sea viable en el tauler
void escriureFitxes(const Fitxa tauler[N_FILES][N_COLUMNES], int fila, int columna, string& res)
{
	switch (tauler[fila][columna].getTipus())
	{
	case TIPUS_DAMA:
		if (tauler[fila][columna].getColor() == COLOR_BLANC)
		{
			res.append("D");
		}
		else
		{
			res.append("R");
		}
		break;
	case TIPUS_NORMAL:
		if (tauler[fila][columna].getColor() == COLOR_BLANC)
		{
			res.append("O");
		}
		else
		{
			res.append("X");
		}
		break;
	case TIPUS_EMPTY:
		res.append("_");
		break;
	default:
		break;
	}
}
string Tauler::toString() const
{
	string res = "";
	for (int files = 0; files < N_FILES; files++)
	{
		for (int columna = 0; columna < N_COLUMNES; columna++)
		{
			escriureFitxes(m_tauler, files, columna, res); 
		}
	}
}