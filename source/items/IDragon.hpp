/*
 * IDragon.hpp
 *
 *  Created on: 24.05.2011
 *      Author: Sebastian
 */

#ifndef IDRAGON_HPP_
#define IDRAGON_HPP_

#include "Item.hpp"

class CGame;

class CIDragon: public CItem {
private:
	CSprite * m_pSpriteBody;
	CSprite * m_pSpriteWings;
	CSprite * m_pSpriteFire;
	float m_fAnimPhase;
	bool m_bActive;

	float m_fFireCreateTime;
	float m_fFireRelativeX;
	bool m_bFireOrientation;

	void ProcessMovingKeys();

	CGame * m_pGame;
public:
	void onSetOwner(CWorm * pNewOwner);
	void init(CGame * pGame);
	void update();
	void render();
	void use();//burns!
	CIDragon();
	virtual ~CIDragon();
};

#endif /* IDRAGON_HPP_ */
