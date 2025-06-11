//
//  main.cpp
//
//  Copyright � 2018 Compiled Creations Limited. All rights reserved.
//

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined  (_WIN64)

#include <iostream>
//Definicio necesaria per poder incloure la llibreria i que trobi el main
#define SDL_MAIN_HANDLED
#include <windows.h>
//Llibreria grafica
#include "../Graphic Lib/libreria.h"
#include "../Graphic Lib/NFont/NFont.h"
#include <conio.h>      /* getch */ 

#elif __APPLE__
//Llibreria grafica
#include "../Graphic Lib/libreria.h"
#include "../Graphic Lib/NFont/NFont.h"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#include <SDL2/SDL.h>
#pragma clang diagnostic pop

#endif

#include "./joc.hpp"
#include "./info_joc.hpp"


int main(int argc, const char* argv[])
{
    //Instruccions necesaries per poder incloure la llibreria i que trobi el main
    SDL_SetMainReady();
    SDL_Init(SDL_INIT_VIDEO);

    //Inicialitza un objecte de la classe Screen que s'utilitza per gestionar la finestra grafica
    Screen pantalla(TAMANY_PANTALLA_X, TAMANY_PANTALLA_Y);
    //Mostrem la finestra grafica
    pantalla.show();

    Joc joc;
    bool final = false;
    //cuando tengamos fichero cambiar
    do 
    {
        // Captura tots els events de ratolí i teclat de l'ultim cicle
        pantalla.processEvents();

        bool mouseStatus = Mouse_getBtnLeft();
        int mousePosX = Mouse_getX();
        int mousePosY = Mouse_getY();
        if (joc.getMode() == MODE_JOC_NONE)
        {
            joc.escullModeJoc(pantalla, mousePosX, mousePosY, mouseStatus);
            joc.inicialitza(joc.getMode(), "tauler_inicial_1", "games/joc.txt", pantalla);
        }
        
        // Actualitza la pantalla
        if (!final)
            final = joc.actualitza(mousePosX, mousePosY, mouseStatus, pantalla);
        else
        {
            GraphicManager::getInstance()->drawSprite(GRAFIC_FONS, 0, 0);
            int posTextX = POS_X_TAULER;
            int posTextY = POS_Y_TAULER;
            string msg = "WINNER WINNER CHICKEN DINNER: " + joc.getGuanyador() + "!!";
            GraphicManager::getInstance()->drawFont(FONT_WHITE_30, posTextX, posTextY, 0.8, msg);
            pantalla.update();
        }
    } while (!Keyboard_GetKeyTrg(KEYBOARD_ESCAPE));
    // Sortim del bucle si pressionem ESC
    joc.finalitza(joc.getFitxer());
 
    //Instruccio necesaria per alliberar els recursos de la llibreria 
    SDL_Quit();
    return 0;
}

