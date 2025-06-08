#include "joc.hpp"
#include <iostream>
#include <fstream>
#include "GraphicManager.h"  
using namespace std;

void CuaMoviments::guardaMov(const Posicio& posInicial, const Posicio& posFinal)
{
	m_cuaPosInicial.push(posInicial);
	m_cuaPosFinal.push(posFinal);
}
void CuaMoviments::finalitzaJocNormal(const string& nomFitxer)
{
	string posInici, posFinal;
	ofstream fitxer(nomFitxer);
	while (!m_cuaPosFinal.empty())
	{
		posInici = m_cuaPosInicial.front().toString();
		m_cuaPosInicial.pop();
		posFinal = m_cuaPosFinal.front().toString();
		m_cuaPosFinal.pop();
		fitxer << posInici << " " << posFinal << endl;
	}
}