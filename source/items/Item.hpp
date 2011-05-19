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
public:
	virtual ~CItem() {};

	void init() {m_pOwner = NULL; setCanMove(false);};
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


	static void renderIcon(int x, int y);
	static void setIcon(CSprite * pIcon);
};

#endif /* ITEM_HPP_ */
