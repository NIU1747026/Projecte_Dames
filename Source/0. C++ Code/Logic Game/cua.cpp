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
	fitxer.close();
}
void CuaMoviments::getSeguentMov(Posicio pos[2])
{
	if (m_cuaPosFinal.empty())
		return;
	pos[0] = m_cuaPosInicial.front();
	pos[1] = m_cuaPosFinal.front();
	m_cuaPosInicial.pop();
	m_cuaPosFinal.pop();
}
void CuaMoviments::inicialtzaJocReplay(const string& nomFitxer)
{
	ifstream fitxer(nomFitxer);
	string s1, s2;

	fitxer >> s1 >> s2;

	while (!fitxer.eof())
	{
		Posicio p1(s1), p2(s2);
		m_cuaPosInicial.push(p1);
		m_cuaPosFinal.push(p2);
		fitxer >> s1 >> s2;
	}

	fitxer.close();
}