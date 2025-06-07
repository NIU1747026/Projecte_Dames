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