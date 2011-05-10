/*
 * MenuSystem.cpp
 *
 *  Created on: 10.05.2011
 *      Author: Sebastian
 */

#include "MenuSystem.hpp"
#include "../Framework.hpp"
#include "../Game.hpp"

//TODO really need the following 2 lines?
#include <string>
using namespace std;

#define ENTRY_START		4001
#define ENTRY_OPTIONS	4002
#define ENTRY_QUIT		4003

void CMenuSystem::ProcessSelection(int messageID) {
	switch (messageID) {
	case ENTRY_START: {

		g_pFramework->DestroyViewPorts();
		//TODO ist das gut so das sopiel in ein anderes Object, das menu auszulagern oder lieber per Singleton?
		CGame * pGame;
		pGame = new CGame(2,100,20); //wir erstelllen das spiel im stack, im buch macht ers auch so (im heap w�re per new)
		//^^ergibt nur 1 bildschirmvoll, da 40*BlockSize=800 und co...

		g_pPhysics->init(pGame);

		pGame->run();

		pGame->quit();

		delete(pGame);
		g_pFramework->DestroyViewPorts();
		g_pFramework->InitViewPorts(1);

	} break;
	case ENTRY_OPTIONS: {
		//m_bIsAlive = false;
	} break;
	case ENTRY_QUIT: {
		m_bIsAlive = false;
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
	g_pFramework->InitViewPorts(1); //init Viewport for Menusystem!

	m_bIsAlive = true;
}
//TODO make alive if player enters menu in game!
void CMenuSystem::run() {
	while (m_bIsAlive) {
		SDL_Delay(10);
		if (g_pFramework->ProcessEvents() == ESCAPED) {//react on escape for close...
			m_bIsAlive = false;
		}

		g_pFramework->Update();
		g_pFramework->Clear();

		m_pCurrentMenu->update();
		m_pCurrentMenu->render();

		g_pFramework->Flip();
	}
}

void CMenuSystem::quit() {
	m_mainMenu.quit();
	g_pFramework->DestroyViewPorts();
}
