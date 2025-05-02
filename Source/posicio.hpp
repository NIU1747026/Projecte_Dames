#ifndef POSICIO_H_
	#define POSICIO_H_

#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class Posicio
{
public:
	Posicio() { m_fila = -1; m_columna = -1; };
	Posicio(int fila, int columna) { m_fila = fila; m_columna = columna; };
	Posicio(const string& posicio) { m_fila = 7 - posicio[1] + '1'; m_columna = posicio[0] - 'a'; };

	void setPos(int fila, int columna) { m_fila = fila; m_columna = columna; };
	void setPos(const string& posicio) { m_fila = 7 - posicio[1] + '1'; m_columna = posicio[0] - 'a'; };
	const int getFila() const { return m_fila; };
	const int getColumna() const { return m_columna; };

	const string toString() const { char x = 7 - m_fila + '1'; char y = m_columna + 'a'; return { y,x }; };
	const bool operator==(const Posicio& posicio) const { return (m_fila == posicio.m_fila && m_columna == posicio.m_columna); };

private:
	int m_fila, m_columna;
};

stringstream& operator<<(stringstream& fitxer, Posicio& pos);
const bool comprovarRepeticio(const Posicio array[], const int& nPosicionsArray, const Posicio& pos);

#endif
