#include "tauler.hpp"	
#include <iostream>
#include <fstream>

stringstream& operator<<(stringstream& fitxer, Posicio& pos)
{
	fitxer << pos.toString(); return fitxer;
}

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
		int posX = POS_X_TAULER + CASELLA_INICIAL_X + ((fitcha.getColumna())*AMPLADA_CASELLA);
		int posY = POS_Y_TAULER + CASELLA_INICIAL_Y + ((fitcha.getFila())*ALCADA_CASELLA);
		switch (mirarFitxa)
		{
			case 'O':
				m_tauler[fitcha.getFila()][fitcha.getColumna()].inicialitza(COLOR_BLANC,TIPUS_NORMAL);
				GraphicManager::getInstance()->drawSprite(GRAFIC_FITXA_BLANCA, posX, posY);
				break;
			case 'D':
				m_tauler[fitcha.getFila()][fitcha.getColumna()].inicialitza(COLOR_BLANC,TIPUS_DAMA);
				GraphicManager::getInstance()->drawSprite(GRAFIC_DAMA_BLANCA, posX, posY);
				break;
			case 'X':
				m_tauler[fitcha.getFila()][fitcha.getColumna()].inicialitza(COLOR_NEGRE,TIPUS_NORMAL);
				GraphicManager::getInstance()->drawSprite(GRAFIC_FITXA_NEGRA, posX, posY);
				break;
			case 'R':
				m_tauler[fitcha.getFila()][fitcha.getColumna()].inicialitza(COLOR_NEGRE,TIPUS_DAMA);
				GraphicManager::getInstance()->drawSprite(GRAFIC_DAMA_NEGRA, posX, posY);
				break;
		default:
			break;
		}
	}
	fitxer.close();
}

void escriureFitxes(const Fitxa tauler[N_FILES][N_COLUMNES], int fila, int columna, string& res)
{
	switch (tauler[fila][columna].getTipus())
	{
	case TIPUS_DAMA:
		if (tauler[fila][columna].getColor() == COLOR_BLANC)
			res.append("D ");
		else
			res.append("R ");
		break;
	case TIPUS_NORMAL:
		if (tauler[fila][columna].getColor() == COLOR_BLANC)
			res.append("O ");
		else
			res.append("X ");
		break;
	case TIPUS_EMPTY:
		res.append("_ ");
		break;
	default:
		break;
	}
}

string Tauler::toString() const
{
	string res = "";
	string x;
	for (int files = 0; files <= N_FILES; files++)
	{
		if (files < N_FILES)
		{
			x = 7 - files + '1';
			res.append(x);
			res.append(": ");
		}
		else
			res.append("   ");
		if (files < N_FILES)
		{
			for (int columna = 0; columna < N_COLUMNES; columna++)
				escriureFitxes(m_tauler, files, columna, res);
			res.append("\n");
		}
		else
			res.append("a " "b " "c " "d " "e " "f " "g " "h ");
	}
	return res;
}

void Tauler::actualitzaMovimentsValids()
{
	Posicio fitxa;
	for (int fila = 0; fila < N_FILES; fila++)
	{
		for (int columna = 0; columna < N_COLUMNES; columna++)
		{
			fitxa.setPos(fila, columna);
			m_tauler[fila][columna].actualitzaMovimentsFitxa(m_tauler, fitxa);
		}
	}
}

void Tauler::inicialitza() //inicialitzar partida desde zero
{
	for (int fila = 0; fila < N_FILES; fila++)
	{
		for (int columna = 0; columna < N_COLUMNES; columna++)
		{
			if (((fila % 2 == 0) && (columna % 2 != 0)) || ((fila % 2 != 0) && (columna % 2 == 0)))
			{
				int posX = POS_X_TAULER + CASELLA_INICIAL_X + ((columna) * AMPLADA_CASELLA);
				int posY = POS_Y_TAULER + CASELLA_INICIAL_Y + ((fila) * ALCADA_CASELLA);
				if (fila >= 0 && fila <= 2)
				{
					m_tauler[fila][columna].inicialitza(COLOR_NEGRE, TIPUS_NORMAL);
					GraphicManager::getInstance()->drawSprite(GRAFIC_FITXA_NEGRA, posX, posY);
				}
				else if (fila >= 5 && fila <= 7)
				{
					m_tauler[fila][columna].inicialitza(COLOR_BLANC, TIPUS_NORMAL);
					GraphicManager::getInstance()->drawSprite(GRAFIC_FITXA_BLANCA, posX, posY);
					
				}
			}
		}
	}
}

void Tauler::getPosicionsPossibles(const Posicio& origen, int& nPosicions, Posicio posicionsPossibles[])
{
	nPosicions = 0;
	getFitxa(m_tauler, origen).afegeixPosicionsValides(posicionsPossibles, nPosicions);
}
