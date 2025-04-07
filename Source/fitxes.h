#ifndef FITXES_H
	#define FITXES_H

using namespace std;

typedef enum
{
	TIPUS_NORMAL,
	TIPUS_DAMA,
	TIPUS_EMPTY
} TipusFitxa;

typedef enum
{
	COLOR_NEGRE,
	COLOR_BLANC,
} ColorFitxa;


class Fitxa
{
public:
	Fitxa();
private:
	ColorFitxa m_color;
	TipusFitxa m_tipus;
	//moviment?
};

#endif