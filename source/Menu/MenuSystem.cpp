/*
 * MenuSystem.cpp
 *
 *  Created on: 10.05.2011
 *      Author: Sebastian
 */

#include "MenuSystem.hpp"
#include "../Framework.hpp"

//TODO really need the following 2 lines?
#include <string>
using namespace std;

#define ENTRY_START		4001
#define ENTRY_OPTIONS	4002
#define ENTRY_QUIT		4003

void CMenuSystem::ProcessSelection(int messageID) {
	switch (messageID) {
	case ENTRY_START: {

	} break;
	case ENTRY_OPTIONS: {
		//FIXME showoptions!
	} break;
	case ENTRY_QUIT: {
		//m_bIsAlive = false;
	} break;
	default: //nothing
		break;
	}
}


void CMenuSystem::init() {
	//TODO irwie gehts mit fktzeigern net

	m_mainMenu.init(string("MainMenu"));
	m_mainMenu.addItem("Start",		ENTRY_START);
	m_mainMenu.addItem("Options",	ENTRY_OPTIONS);
	m_mainMenu.addItem("Quit",		ENTRY_QUIT);

	m_pCurrentMenu = &m_mainMenu;
	m_bIsAlive = true;
}

void CMenuSystem::run() {
	while (m_bIsAlive) {
		SDL_Delay(10);
		g_pFramework->Update();
		g_pFramework->Clear();

		m_pCurrentMenu->update();
		m_pCurrentMenu->render();

		g_pFramework->Flip();
	}
}

void CMenuSystem::quit() {
	m_mainMenu.quit();
}
