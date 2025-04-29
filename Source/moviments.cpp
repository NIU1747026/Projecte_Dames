#include "moviment.h"	
#include <iostream>
#include <fstream>
using namespace std;

bool Moviment::operator==(const Moviment& mov) const
{
	if (m_nDamesMenjades + m_nFitxesMenjades  == mov.m_nDamesMenjades + mov.m_nFitxesMenjades)
	{
		return true;
	}
	return false;
}
bool Moviment::operator>(const Moviment& mov) const
{
	if (m_nDamesMenjades + m_nFitxesMenjades > mov.m_nDamesMenjades + mov.m_nFitxesMenjades)
	{
		return true;
	}
	return false;
}