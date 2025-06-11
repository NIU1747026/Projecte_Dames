//
//  CurrentGame.cpp
//  LearnChess
//
//  Created by Enric Vergara on 21/2/22.
//

#include "joc.hpp"
#include <iostream>
#include <fstream>
#include "GraphicManager.h"


void Joc::dibuixaTauler()
{
	GraphicManager::getInstance()->drawSprite(GRAFIC_FONS, 0, 0);
	GraphicManager::getInstance()->drawSprite(GRAFIC_TAULER, POS_X_TAULER, POS_Y_TAULER);
	taulerJoc->visualitza(); 
	mostraModeITorn();
}
bool Joc::comprobaSiAcabat()
{
	Fitxa f;
	int blanques = 0;
	int negres = 0;
	bool nMovBlanques = false;
	bool nMovNegres = false;
	for (int i = 0; i < N_FILES; i++)
	{
		for (int y = 0; y < N_COLUMNES; y++)
		{
			f = taulerJoc->getFitxaPos(i, y);
			if (f.getColor() == COLOR_BLANC)
			{
				blanques++;
				if (f.getNMovimentsValids() != 0)
					nMovBlanques = true;
			}
			if (f.getColor() == COLOR_NEGRE)
			{
				negres++;
				if (f.getNMovimentsValids() != 0)
					nMovNegres = true;
			}
		}
	}
	if (nMovNegres == false || negres == 0)
	{
		m_guanyador = COLOR_BLANC;
		return true;
	}
	if (nMovBlanques == false || blanques == 0)
	{
		m_guanyador = COLOR_NEGRE;
		return true;
	}
	return false;
}
void Joc::escullModeJoc(Screen& p, int mousePosX, int mousePosY, bool mouseStatus)
{
		GraphicManager::getInstance()->drawSprite(GRAFIC_FONS, 0, 0);
		int posTextX = POS_X_TAULER;
		int posTextY = POS_Y_TAULER;
		string msg = "Escull mode joc:";
		GraphicManager::getInstance()->drawFont(FONT_WHITE_30, posTextX, posTextY, 0.8, msg);
		msg = " 2- MODE JOC REPLAY";
		GraphicManager::getInstance()->drawFont(FONT_WHITE_30, POS_X_BOTO, posTextY + 200, 0.8, msg);  
		msg = " 1- MODE JOC NORMAL";
		GraphicManager::getInstance()->drawFont(FONT_WHITE_30, POS_X_BOTO, posTextY + 100, 0.8, msg);
		p.update();
		if (mouseStatus && mousePosX >= POS_X_BOTO && mousePosX <= posTextY + 100 + TAMANY_BOTO_x && mousePosY >= posTextY + 100 && mousePosY <= posTextY + 100 + TAMANY_BOTO_y)
		{
			modeJoc = MODE_JOC_NORMAL;
		}
		if (mouseStatus && mousePosX >= POS_X_BOTO && mousePosX <= posTextY + 200 + TAMANY_BOTO_x && mousePosY >= posTextY + 200 && mousePosY <= posTextY + 200 + TAMANY_BOTO_y)
		{
			modeJoc = MODE_JOC_REPLAY;
		}
		
		
}
void Joc::cambiaTorn()
{
	switch (m_torn)
	{
	case COLOR_BLANC:
		m_torn = COLOR_NEGRE;
		break;
	case COLOR_NEGRE:
		m_torn = COLOR_BLANC;
	default:
		break;
	}
}
void Joc::mostraModeITorn()
{
	int posTextX = POS_X_TAULER;
	int posTextY = POS_Y_TAULER + (ALCADA_CASELLA * NUM_FILES_TAULER) + 120;
	string mode, torn;
	switch (modeJoc)
	{
	case MODE_JOC_NORMAL:
		mode = "Normal";
		break;
	case MODE_JOC_REPLAY:
		mode = "Replay";
		break;
	}
	switch (m_torn)
	{
	case COLOR_BLANC:
		torn = "Blanc";
		break;
	case COLOR_NEGRE:
		torn = "Negre";
		break;
	}
	string msg = "Mode: " + mode + ", Torn: " + torn;
	GraphicManager::getInstance()->drawFont(FONT_WHITE_30, posTextX, posTextY, 0.8, msg);
}
void Joc::finalitza(const string& nomFitxer)
{
	switch (modeJoc)
	{
	case MODE_JOC_NORMAL:
		m_cua.finalitzaJocNormal(nomFitxer);
		break;
	case MODE_JOC_REPLAY:
		break;
	}
}
void Joc::inicialitza(ModeJoc mode, const string& nomFitxerTauler, const string& nomFitxerMoviments, Screen& p)
{
	//falta tema de ficheros
	ifstream fitxer(nomFitxerTauler);   
	switch (modeJoc)
	{
	case MODE_JOC_NORMAL:
		//taulerJoc->inicialitza(nomFitxerTauler); arreglar
		taulerJoc->inicialitza(); //cuando tengamos fichero se quita
		taulerJoc->actualitzaMovimentsValids();
		dibuixaTauler();
		nomFitxer = nomFitxerMoviments; 
		p.update();
		break;
	case MODE_JOC_REPLAY:
		m_cua.inicialtzaJocReplay(nomFitxerMoviments);
		taulerJoc->inicialitza(); //cuando tengamos fichero se quita
		taulerJoc->actualitzaMovimentsValids();
		dibuixaTauler();
		nomFitxer = nomFitxerMoviments;
		p.update();
		break;
	}
}
bool Joc::actualitza(int mousePosX, int mousePosY, bool mouseStatus, Screen& p, bool &act) 
{
	int fila, columna;
	Posicio pos; 
	Moviment m; 
	switch (modeJoc)
	{
	case MODE_JOC_NORMAL:
		columna = (mousePosX - POS_X_TAULER - CASELLA_INICIAL_X) / AMPLADA_CASELLA;
		fila = (mousePosY - POS_Y_TAULER - CASELLA_INICIAL_Y) / ALCADA_CASELLA;
		static bool click;
		static int x, y;
		if (mouseStatus && taulerJoc->getFitxaPos(fila,columna).getTipus() != TIPUS_EMPTY && taulerJoc->getFitxaPos(fila, columna).getColor() == m_torn)
		{
			dibuixaTauler();
			taulerJoc->visualtzaMovValids(fila, columna);
			p.update();
			click = true;
			x = fila;
			y = columna;
		}
		if (mouseStatus && click == true)
		{
			pos.setPos(fila, columna);
			if (click == true && taulerJoc->getFitxaPos(x, y).movimentEsValid(pos, m))
			{
				Posicio origen(x, y);
				taulerJoc->mouFitxa(origen, pos);
				click = false;
				dibuixaTauler();
				p.update();
				m_cua.guardaMov(origen, pos);
				if (!comprobaSiAcabat())
				{
					cambiaTorn();
				}
				else
				{
					return true;
				}
			}
			if (taulerJoc->getFitxaPos(fila, columna).getColor() != m_torn)
			{
				dibuixaTauler();
				p.update();
				click = false;
			}
		}
		break;
	case MODE_JOC_REPLAY:
		//recuperar i eliminar de cua mov + moure la fitxa
		dibuixaTauler();
		if (mouseStatus)
		{
			if (!m_cua.noMesMoviments() && act)
			{
				Posicio next[2];
				m_cua.getSeguentMov(next);
				taulerJoc->mouFitxa(next[0], next[1]);
				act = false;
			}
		}
		else
			act = true;

		if (m_cua.noMesMoviments())
		{
			int posTextX = POS_X_TAULER;
			int posTextY = POS_Y_TAULER + (ALCADA_CASELLA * NUM_FILES_TAULER) + 200;
			string msg = "NO HI HA MES MOVIMENTS!!";
			GraphicManager::getInstance()->drawFont(FONT_WHITE_30, posTextX, posTextY, 0.8, msg);
		}

		p.update();
		break;
	}
	return false;
}




