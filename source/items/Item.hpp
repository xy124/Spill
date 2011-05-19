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

//To be able to declare prototype of setowner:
class CWorm;

class CItem : public CPhysicalObject {
private:
	static CSprite * m_pIcon;
	CWorm * m_pOwner;
	bool m_bIsAlive;
public:
	virtual ~CItem() {};

	void init() {
		m_pOwner = NULL;
		setCanMove(true);
		m_bIsAlive = true;
	};
	virtual void use() {};
	virtual void update() {};
	virtual void render() {};
	virtual void quit() {};



	virtual void onSetOwner(CWorm * pOwner) {};
	void setOwner(CWorm * pOwner) {
		m_pOwner = pOwner;
		onSetOwner(pOwner);
	};

	CWorm * getOwner() {
		return m_pOwner;
	};

//FIXME: zauberstab zum unsichtbar machen!

	static void renderIcon(int x, int y);
	static void setIcon(CSprite * pIcon);

	void setIsAlive(bool alive) {
		m_bIsAlive = alive;
	}

	bool isAlive() {
		return m_bIsAlive;
	}
};


#endif /* ITEM_HPP_ */
