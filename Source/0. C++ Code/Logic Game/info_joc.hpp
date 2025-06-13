#ifndef INFO_JOC_H
#define INFO_JOC_H

// Posici� del tauler a la pantalla
const int POS_X_TAULER = 75;
const int POS_Y_TAULER = 20;

// Posici� de la primera casella del tauler respecte a la cantonada superior esquerra del gr�fic del tauler
const int CASELLA_INICIAL_X = 52;
const int CASELLA_INICIAL_Y = 67;

// Tamany de les caselles del tauler
const int AMPLADA_CASELLA = 62;
const int ALCADA_CASELLA = 62;

const int NUM_COLS_TAULER = 8;
const int NUM_FILES_TAULER = 8;

const int TAMANY_PANTALLA_X = 750;
const int TAMANY_PANTALLA_Y = 850;

const int TAMANY_BOTO_x = 270;
const int TAMANY_BOTO_y = 30;

const int POS_X_BOTO = 200;

typedef enum 
{
    MODE_JOC_NORMAL,
    MODE_JOC_REPLAY,
    MODE_JOC_NONE
} ModeJoc;

#endif 
