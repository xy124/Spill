/*
 * MenuSystem.hpp
 *
 *  Created on: 10.05.2011
 *      Author: Sebastian
 */

#ifndef MENUSYSTEM_HPP_
#define MENUSYSTEM_HPP_

#include "Menu.hpp"

class CMenuSystem {
private:
	CMenu * m_pCurrentMenu;

	CMenu m_mainMenu;

	void ProcesSelection(int messageID);

	bool bIsAlive;
public:
	CMenuSystem() {};
	void init();
	void run();
	void quit();
	virtual ~CMenuSystem() {};
};

#endif /* MENUSYSTEM_HPP_ */
