/*
 * Menu.cpp
 *
 *  Created on: 10.05.2011
 *      Author: Sebastian
 */

#include "Menu.hpp"

#include "../Framework.hpp"
#include "MenuSystem.hpp" //MBE Kreisincludierung!?!

using namespace std;

void CMenu::init( std::string heading) {
	m_selectedItem = m_Items.begin();
	m_Heading = heading;
	m_bKeyLock = false;
}

void CMenu::addItem(string name, int messageID) {
	S_MenuItem item;
	item.m_MessageID = messageID;
	item.m_Name = name;
	m_Items.push_back(item);
}

void CMenu::render() {
	//Draw Heading: MBE: Viewport????!?!!
	g_pFramework->TextOut(m_Heading, 50, 10, 0);
	//draw items!
	vector<S_MenuItem>::iterator it;
	int y = 50 + 14;
	for (it = m_Items.begin(); it !=  m_Items.end(); ++it) {
		y += 18;
		g_pFramework->TextOut(it->m_Name, 70, y, 0);
		if (it == m_selectedItem) { //draw line under it!
			g_pFramework->drawLine(CVec(0, y+17), CVec(800,y+17), 0, 255, 0, false);
			//MBE draws line just on viewport!
		}
	}
}

void CMenu::quit() {
	m_Items.clear();
}

void CMenu::update() {
	if ( (!m_bKeyLock) && (g_pFramework->KeyDown(SDLK_DOWN)) ) {
		m_selectedItem ++;
		m_bKeyLock = true;
	}
	if ( (!m_bKeyLock) && (g_pFramework->KeyDown(SDLK_UP)) ) {
		m_selectedItem --;
		m_bKeyLock = true;
	}

	//MBE operator wirklich richtig definiert????
	if (m_selectedItem < m_Items.begin()) {
		m_selectedItem = m_Items.end();
		m_selectedItem --;
	}

	if (m_selectedItem >= m_Items.end())
		m_selectedItem = m_Items.begin();

	if ( (!m_bKeyLock) && (g_pFramework->KeyDown(SDLK_RETURN)) ) {
		//do process!
		g_pMenuSystem->ProcessSelection(m_selectedItem->m_MessageID);
		m_bKeyLock = true;
	}

	if ( (m_bKeyLock)
				&& (g_pFramework->KeyDown(SDLK_DOWN) 	== false )
				&& (g_pFramework->KeyDown(SDLK_UP) 		== false )
				&& (g_pFramework->KeyDown(SDLK_RETURN) 	== false ) )
			m_bKeyLock = false;

}
