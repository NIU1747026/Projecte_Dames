#include "moviment.h"	
#include <iostream>
#include <fstream>
using namespace std;

bool Moviment::operator==(const Moviment& mov)
{
	if (m_nDamesMenjades == mov.m_nDamesMenjades && m_nFitxesMenjades == mov.m_nFitxesMenjades && m_nRecorregut == mov.m_nRecorregut)
	{
		return true;
	}
	return false;
}
bool Moviment::operator>(const Moviment& mov)
{
	if ((m_nDamesMenjades > mov.m_nDamesMenjades) || (m_nDamesMenjades == mov.m_nDamesMenjades && m_nFitxesMenjades > mov.m_nFitxesMenjades) || 
		(m_nDamesMenjades == mov.m_nDamesMenjades && m_nFitxesMenjades == mov.m_nFitxesMenjades && m_nRecorregut > mov.m_nRecorregut))
	{
		return true;
	}
	return false;
}