/*
 * Item.hpp
 *
 *  Created on: 19.05.2011
 *      Author: Sebastian
 */

#ifndef ITEM_HPP_
#define ITEM_HPP_

#include "../Sprite.hpp"
#include "../PhysicalObject.hpp"

class CItem : public CPhysicalObject {
private:
	bool m_bOwned;
	static CSprite * m_pIcon;
public:
	CItem() {};
	~CItem() {};//MBE make virtual??

	void init() {m_bOwned = false; setCanMove(false);};
	virtual void use();
	virtual void update();
	virtual void render();
	virtual void quit();

	bool getOwned() {return m_bOwned;}
	void setOwned(bool owned) {
		m_bOwned = owned;
	}


	static void renderIcon(int x, int y);
	static void setIcon(CSprite * pIcon);
};

#endif /* ITEM_HPP_ */
