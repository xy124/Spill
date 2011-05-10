/*
 * Menu.hpp
 *
 *  Created on: 10.05.2011
 *      Author: Sebastian
 */

#ifndef MENU_HPP_
#define MENU_HPP_

#include <string>
#include <vector>

class CMenu {
private:
	std::string m_Heading;
	struct S_MenuItem {
		std::string m_Name;
		int m_MessageID;
	};
	std::vector<S_MenuItem> m_Items;
	std::vector<S_MenuItem>::iterator m_selectedItem;

	void (*m_pProcessSelection) (int messageID);
	void ProcessKeys();

	bool m_bKeyLock;
public:
	CMenu();
	void init(std::string heading, void (*pProcessSelection) (int messageID));
	void render();
	void update();
	void addItem(std::string name, int messageID);
	void quit();
	virtual ~CMenu();
};

#endif /* MENU_HPP_ */
