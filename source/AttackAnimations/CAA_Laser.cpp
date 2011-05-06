/*
 * CAA_Laser.cpp
 *
 *  Created on: 06.05.2011
 *      Author: Sebastian
 */

#include "CAA_Laser.hpp"
#include "../Logfile.hpp"
#include "../Framework.hpp"

void CAA_Laser::init(float liveTime, CVec &from, CVec &to, int r, int g, int b) {
	init(liveTime);
	m_rValue = r;
	m_gValue = g;
	m_bValue = b;

	m_From = from;
	m_To = to;
}

void CAA_Laser::render() {
	g_pFramework->drawLine(m_From, m_To, m_rValue, m_gValue, m_bValue);
}

void CAA_Laser::quit() {
	g_pLogfile->Textout("</br>quited Laser");
}

CAA_Laser::~CAA_Laser() {
	// TODO Auto-generated destructor stub
}
