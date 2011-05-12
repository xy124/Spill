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
	//We don't really need keylock because we use is new event and it's NO new event if a key is holded!
	//but there are some lines left using it together with g_pFramework->Keydown();
public:
	CMenu() {};
	void init(std::string heading);
	void render();
	void update();
	void addItem(std::string name, int messageID, EntryType entryType);
	std::string getSelectedItemText(); //gets Text of currently selected item!
	std::string getItemText(int messageID);
	void setItemText(int messageID, std::string text);

	void quit();
	virtual ~CMenu() {};
};

#endif /* MENU_HPP_ */
