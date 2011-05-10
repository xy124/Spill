/*
 * MenuSystem.cpp
 *
 *  Created on: 10.05.2011
 *      Author: Sebastian
 */

#include "MenuSystem.hpp"
#include "../Framework.hpp"

#define ENTRY_START		4001
#define ENTRY_OPTIONS	4002
#define ENTRY_QUIT		4003

void CMenuSystem::init() {
	m_mainMenu.init("MainMenu", m_pCurrentMenu);
	m_mainMenu.addItem("Start",		ENTRY_START);
	m_mainMenu.addItem("Options",	ENTRY_OPTIONS);
	m_mainMenu.addItem("Quit",		ENTRY_QUIT);

	m_pCurrentMenu = &m_mainMenu;
	bIsALive = true;
}

CMenuSystem::CMenuSystem() {
	// TODO Auto-generated constructor stub

}

CMenuSystem::~CMenuSystem() {
	// TODO Auto-generated destructor stub
}

void CMenuSystem::run() {
	while (bIsAlive) {
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

void CMenuSystem::ProcesSelection(int messageID) {
	switch (messageID) {
	case ENTRY_START: {

	} break;
	case ENTRY_Options: {
		//FIXME showoptions!
	} break;
	case ENTRY_QUIT: {
		m_bIsAlive = false;
	} break;
	default: //nothing
		break;
	}
}
