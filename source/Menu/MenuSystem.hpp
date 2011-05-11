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

class CMenuSystem : public TSingleton<CMenuSystem>{
private:
	CMenu * m_pCurrentMenu;

	CMenu m_mainMenu;
	CMenu m_optionMenu;

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
