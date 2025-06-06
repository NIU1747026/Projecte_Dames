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
void Joc::escullModeJoc(Screen p)
{
	while (modeJoc == MODE_JOC_NONE)
	{
		GraphicManager::getInstance()->drawSprite(GRAFIC_FONS, 0, 0);
		int posTextX = POS_X_TAULER;
		int posTextY = POS_Y_TAULER;
		string msg = "Escull mode joc:";
		GraphicManager::getInstance()->drawFont(FONT_WHITE_30, posTextX, posTextY, 0.8, msg);
		msg = " 1- MODE JOC NORMAL ";
		GraphicManager::getInstance()->drawFont(FONT_WHITE_30, posTextX, posTextY + 100, 0.8, msg);
		msg = " 2- MODE JOC REPLAY";
		GraphicManager::getInstance()->drawFont(FONT_WHITE_30, posTextX, posTextY + 200, 0.8, msg);
		p.update();
	}
}
void Joc::cambiaTorn()
{
	if (!comprobaSiAcabat())
	{
		switch (m_torn)
		{
		COLOR_BLANC:
			m_torn = COLOR_NEGRE;
			break;
		COLOR_NEGRE:
			m_torn = COLOR_BLANC;
		default:
			break;
		}
	}
}
void Joc::mostraModeITorn()
{
	int posTextX = POS_X_TAULER;
	int posTextY = POS_Y_TAULER + (ALCADA_CASELLA * NUM_FILES_TAULER) + 120;
	string mode, torn;
	switch (modeJoc)
	{
	MODE_JOC_NORMAL:
		mode = "Normal";
		break;
	MODE_JOC_REPLAY:
		mode = "Replay";
		break;
	}
	switch (m_torn)
	{
	COLOR_BLANC:
		torn = "Blanc";
		break;
	COLOR_NEGRE:
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
	MODE_JOC_NORMAL:
		/*S�haur� de guardar la cua de moviments al fitxer que s�ha indicat al par�metre nomFitxerMoviments
quan s�ha fet la crida al m�tode inicialitza.
*/
		break;
	MODE_JOC_REPLAY:
		break;
	}
}
void Joc::inicialitza(ModeJoc mode, const string& nomFitxerTauler, const string& nomFitxerMoviments)
{
	switch (modeJoc)
	{
	MODE_JOC_NORMAL:
		
		//El fitxer indicat al par�metre nomFitxerMoviments s�haur� d�utilitzar per guardar, al final de la partida, tots
		//els moviments que s�hagin fet durant el desenvolupament de la partida.

		break;
	MODE_JOC_REPLAY:
		//S�haur� d�inicialitzar la cua de moviments a reproduir amb la informaci� del fitxer indicat al par�metre
		//nomFitxerMoviments

		break;
	}
}
bool Joc::actualitza(int mousePosX, int mousePosY, bool mouseStatus) 
{
	GraphicManager::getInstance()->drawSprite(GRAFIC_FONS, 0, 0);
	GraphicManager::getInstance()->drawSprite(GRAFIC_TAULER, POS_X_TAULER, POS_Y_TAULER);
	taulerJoc.visualitza();
	if (modeJoc == MODE_JOC_NORMAL)
	{
		GraphicManager::getInstance()->drawSprite(GRAFIC_FONS, 0, 0);
		GraphicManager::getInstance()->drawSprite(GRAFIC_TAULER, POS_X_TAULER, POS_Y_TAULER);
		taulerJoc.visualitza();
		/*Si s�ha fet clic amb el ratol� a sobre d�una fitxa del color del jugador que t� el torn, aquesta fitxa ha de
quedar seleccionada com la fitxa que es vol moure i s�hauran de recuperar els moviments v�lids que pot
fer la fitxa (utilitzant els m�todes de la classe Tauler ja implementats a la primera part del projecte).
Quan es visualitzi el tauler i les fitxes, s�hauran de mostrar les posicions dels moviments v�lids
superposant a cada casella un requadre transparent verd (gr�fic GRAFIC_POSICIO_VALIDA)

Si s�ha fet clic amb el ratol� a una de les posicions dels moviments v�lids de la pe�a seleccionada s�haur�
d�executar el moviment de la fitxa a aquesta nova posici� (utilitzant el m�tode mouFitxa de la classe
Tauler ja implementat a la primera part del projecte) i guardar el moviment a la cua de moviments
realitzats. Tamb� s�haur� de comprovar si s�ha acabat la partida perqu� algun jugador es queda sense
fitxes i, si no s�acaba, canviar el jugador que t� el torn.

Si no s�interactua amb el ratol� o es fa clic a sobre de qualsevol altra posici� de pantalla, no s�ha de fer res,
simplement visualitzar el tauler, les fitxes i les posicions dels moviments v�lids (si hi ha alguna fitxa
seleccionada)
*/
	}
	if (modeJoc == MODE_JOC_REPLAY)
	{
		/*Si s�ha fet clic amb el ratol� a sobre del tauler de joc s�ha de recuperar i eliminar el primer moviment de la
cua de moviments, executar-lo i visualitzar el nou estat del tauler i de les fitxes. Tamb� s�haur� de
comprovar si s�ha acabat la partida perqu� algun jugador es queda sense fitxes i, si no s�acaba, canviar el
jugador que t� el torn.

Si no queden moviments a la cua i encara no s�ha arribat al final de la partida s�haur� de mostrar un
missatge per pantalla indicant que no es poden fer m�s moviments.

Si no s�interactua amb el ratol� o es fa clic a sobre de qualsevol altra posici� de pantalla, no s�ha de fer res,
simplement visualitzar el tauler i les fitxes.
*/
	}



	//TODO 1: Interactuar amb la crida per dibuixar gr�fics (sprites).
	// 	      Dibuixar a pantalla el fons i el gr�fic amb el tauler buit.
	//------------------------------------------------------------------
	//TODO 1.1 Afegir l'include de GraphicManager --> #include "GraphicManager.h"
	//TODO 1.2 Fer la crida de dibuixar un sprite --> GraphicManager::getInstance()->drawSprite(image, posX, posY);
	//	    Per comen�ar podem cridar el drawSprite amb els params --> 
	//          (GRAFIC_FONS,0,0) i 
	//          (GRAFIC_TAULER, POS_X_TAULER, POS_Y_TAULER)

 


	//TODO 1.3: Dibuixar a pantalla el gr�fic amb el tauler i una fitxa blanca a la posici� (fila, columna ) del tauler
	/*int fila = (mousePosY - POS_Y_TAULER)/ALCADA_CASELLA;
	int columna = (mousePosX-POS_X_TAULER)/AMPLADA_CASELLA;
	if ((mouseStatus) && (mousePosX >= (POS_X_TAULER + CASELLA_INICIAL_X)) &&
		(mousePosY >= POS_Y_TAULER + CASELLA_INICIAL_Y) &&
		(mousePosX <= (POS_X_TAULER + CASELLA_INICIAL_X + AMPLADA_CASELLA * NUM_COLS_TAULER)) &&
		(mousePosY <= (POS_Y_TAULER + CASELLA_INICIAL_Y + ALCADA_CASELLA * NUM_FILES_TAULER)))
	{
		int posX = POS_X_TAULER + CASELLA_INICIAL_X + ((columna - 1) * AMPLADA_CASELLA);
		int posY = POS_Y_TAULER + CASELLA_INICIAL_Y + ((fila - 1) * ALCADA_CASELLA);
		GraphicManager::getInstance()->drawSprite(GRAFIC_FITXA_BLANCA, posX, posY);
	}*/
	
	//TODO 2: Interactuar amb el ratol�.
	//------------------------------------------------------------------
	//TODO 2.1: Dibuixar la fitxa blanca al tauler nom�s si estem pressionant el bot� del ratol�



    //TODO 2.2: Dibuixar la fitxa blanca al tauler nom�s si estem pressionant el bot� del ratol� i el ratol�
    // est� dins del l�mits del tauler

 

    //TODO 2.3: Dibuixar la fitxa blanca al tauler nom�s si estem pressionant el bot� del ratol� i el ratol�
    // est� dins del l�mits del tauler. Dibuixa la fitxa a la casella on est� el ratol�



    //TODO 2.4: Dibuixar la fitxa blanca a la casella on cliquem al ratol�. La fitxa s'ha de mantenir dibuixada
    // a la casella quan deixem de clicar amb el ratol�. Quan cliquem a una altra casella, la fitxa canvia de posici�
    // a la nova casella

        
        
    // TODO 3: Imprimir text per pantalla
    //------------------------------------------
    // TODO 3.1: Mostrar la posici� actual del ratol� a sota del tauler

	int posTextX = POS_X_TAULER;
	int posTextY = POS_Y_TAULER + (ALCADA_CASELLA * NUM_FILES_TAULER) + 120;
	string msg = "PosX: " + to_string(mousePosX) + ", PosY: " + to_string(mousePosY);
	GraphicManager::getInstance()->drawFont(FONT_WHITE_30, posTextX, posTextY, 0.8, msg);

	return false;
}




