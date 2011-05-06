/*
 * CAA_Laser.cpp
 *
 *  Created on: 06.05.2011
 *      Author: Sebastian
 */

#include "CAA_Laser.hpp"
#include "../Logfile.hpp"
#include "../Framework.hpp"

void CAA_Laser::init(float liveTime, CVec &from, CWorm * pTo, int r, int g, int b) {
	initKillTime(liveTime);
	m_rValue = r;
	m_gValue = g;
	m_bValue = b;

	m_From = from;
	m_pTo = pTo;
}

void CAA_Laser::render() {
	CVec to(m_pTo->getRect());
	to.x += WORMWIDTH/2;
	to.y += WORMHEIGHT/2;
	g_pFramework->drawLine(m_From, to, m_rValue, m_gValue, m_bValue);
}

void CAA_Laser::quit() {
	g_pLogfile->Textout("</br>quit Laser");
}
