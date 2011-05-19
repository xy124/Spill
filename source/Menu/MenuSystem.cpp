/*
 * MenuSystem.cpp
 *
 *  Created on: 10.05.2011
 *      Author: Sebastian
 */
#include "MenuSystem.hpp"
#include "../Framework.hpp"
#include "../Game.hpp"
#include "../Settings.hpp"
#include "../Highscorelist.hpp"

void CMenuSystem::ProcessSelection(int messageID) {
	switch (messageID) {
	case ENTRY_START: {

		g_pFramework->DestroyViewPorts();
		//TODO ist das gut so das sopiel in ein anderes Object, das menu auszulagern oder lieber per Singleton?
		CGame * pGame = new CGame(2,100,20); //wir erstelllen das spiel im heap, im buch macht ers im stack (im heap w�re per new)
		//^^ergibt nur 1 bildschirmvoll, da 40*BlockSize=800 und co...

		g_pPhysics->init(pGame);

		pGame->run();

		pGame->quit();

		delete(pGame);
		g_pFramework->DestroyViewPorts();
		g_pFramework->InitViewPorts(1);

	} break;
	case ENTRY_OPTIONS: {
		m_pCurrentMenu = &m_optionMenu;
		m_optionMenu.setItemText(ENTRY_TEXTOX_P1, g_pSettings->getName(0));
		m_optionMenu.setItemText(ENTRY_TEXTOX_P2, g_pSettings->getName(1));
	} break;
	case ENTRY_TEXTOX_P1: {
		/*g_pLogfile->fTextout("<br /> player is in optn menu and now p1 name =",
				m_optionMenu.getItemText());*/
		//nothing
	} break;
	case ENTRY_TEXTOX_P2: {
		//nothing
	} break;
	case ENTRY_CHECKBOX: {
		//nothing
	} break;
	case ENTRY_BACKMAIN: {
		if (m_pCurrentMenu == &m_optionMenu) {
			g_pSettings->setName(0, m_optionMenu.getItemText(ENTRY_TEXTOX_P1)) ;
			g_pSettings->setName(1, m_optionMenu.getItemText(ENTRY_TEXTOX_P2)) ;
		}
		m_pCurrentMenu = &m_mainMenu;
	} break;
	case ENTRY_HIGHSCORE: {
		g_pHighscorelist->generateHighscoreMenu(&m_highscoreMenu);
		m_pCurrentMenu = &m_highscoreMenu;
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

	m_mainMenu.init("MainMenu");
	m_mainMenu.addItem("Start",		ENTRY_START,	CMenu::BUTTON);
	m_mainMenu.addItem("Options",	ENTRY_OPTIONS,	CMenu::BUTTON);
	m_mainMenu.addItem("Highscores",ENTRY_HIGHSCORE,CMenu::BUTTON);
	m_mainMenu.addItem("Quit",		ENTRY_QUIT,		CMenu::BUTTON);

	m_optionMenu.init("Options");
	m_optionMenu.addItem("Name Player one: ",	ENTRY_TEXTOX_P1,	CMenu::TEXTBOX);
	m_optionMenu.addItem("Name Player two: ",	ENTRY_TEXTOX_P2,	CMenu::TEXTBOX);
	m_optionMenu.addItem("Senseless Checkbox: ",ENTRY_CHECKBOX,		CMenu::CHECKBOX);
	m_optionMenu.addItem("Back: ",				ENTRY_BACKMAIN,			CMenu::BUTTON);

	m_pCurrentMenu = &m_mainMenu;
	g_pFramework->InitViewPorts(1); //init Viewport for Menusystem!

	m_bIsAlive = true;
}

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
