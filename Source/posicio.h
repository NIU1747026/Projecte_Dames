#ifndef POSICIO_H_
	#define POSICIO_H_

#include <string>
#include <fstream>

using namespace std;

class Posicio
{
public:
	Posicio() { m_fila = -1; m_columna = -1; };
	Posicio(int fila, int columna) { m_fila = fila; m_columna = columna; };
	Posicio(const string& posicio) { m_fila = 7 - posicio[1] + '1'; m_columna = posicio[0] - 'a'; };

	void setPos(int fila, int columna) { m_fila = fila; m_columna = columna; };
	int getFila() const { return m_fila; };
	int getColumna() const { return m_columna; };

	string toString() const { char x = 7 - m_fila + '1'; char y = m_columna + 'a'; return { y,x }; };

	bool operator==(Posicio& posicio) { return (m_fila == posicio.m_fila && m_columna == posicio.m_columna); };

private:
	int m_fila, m_columna;
};

#endif
