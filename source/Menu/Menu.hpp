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
public:
	enum EntryType {
		CHECKBOX,
		BUTTON,
		TEXTBOX
	};
private:
	std::string m_Heading;
	struct S_MenuItem {
		std::string m_Name;
		std::string m_Text;//for checkbox "" or "1"
		int m_MessageID;
		EntryType m_EntryType;
	};
	std::vector<S_MenuItem> m_Items;
	std::vector<S_MenuItem>::iterator m_selectedItem;

	void ProcessKeys();

	static bool m_bKeyLock;
public:
	CMenu() {};
	void init(std::string heading);
	void render();
	void update();
	void addItem(std::string name, int messageID, EntryType entryType);
	std::string getItemText(); //gets Text of currently selected item!
	void quit();
	virtual ~CMenu() {};
};

#endif /* MENU_HPP_ */
