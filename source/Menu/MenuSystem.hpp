/*
 * MenuSystem.hpp
 *
 *  Created on: 10.05.2011
 *      Author: Sebastian
 */

#ifndef MENUSYSTEM_HPP_
#define MENUSYSTEM_HPP_

#include "Menu.hpp"
#include "../Singleton.hpp"
#include "../Game.hpp"

#define ENTRY_START		4001
#define ENTRY_OPTIONS	4002
#define ENTRY_QUIT		4003
#define ENTRY_HIGHSCORE	4004

#define ENTRY_TEXTOX_P1	5001
#define ENTRY_TEXTOX_P2	5002
#define ENTRY_CHECKBOX  5003
#define ENTRY_BACKMAIN	5004

class CMenuSystem : public TSingleton<CMenuSystem>{
private:
	CMenu * m_pCurrentMenu;

	CMenu m_mainMenu;
	CMenu m_optionMenu;
	CMenu m_highscoreMenu;

	bool m_bIsAlive;


public:

	void ProcessSelection(int messageID);

	CMenuSystem() {};
	void init();
	void run();
	void quit();
	virtual ~CMenuSystem() {};
};

#define g_pMenuSystem CMenuSystem::get()

#endif /* MENUSYSTEM_HPP_ */
