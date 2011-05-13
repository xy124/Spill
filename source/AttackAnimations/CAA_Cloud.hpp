/*
 * CAA_Cloud.hpp
 *
 *  Created on: 13.05.2011
 *      Author: Sebastian
 */

#ifndef CAA_CLOUD_H_
#define CAA_CLOUD_H_

#include "AttackAnimation.hpp"
#include "../Sprite.hpp"
#include "../Worm.hpp"

class CWorm;

class CAA_Cloud: public CAttackAnimation {
private:
	static CSprite * m_pSprite;
	static CSprite * m_pTextureSprite;
	int m_TeamID;
	CWorm * m_pAimWorm;
	CWorm * m_pOwnerWorm;

	float m_fLighteningState;

	std::list<CAttackAnimation*> * m_pAttackAnimations;
public:


	virtual void render();
	virtual void quit();
	virtual void init(CVec StartPos, CWorm * pAimWorm, CWorm * pOwnerWorm, int TeamID);
	virtual void update();

	~CAA_Cloud() {};

	static void setSprite(CSprite * pSprite);
	static void setTextureSprite(CSprite * pSprite);

};

#endif /* CAA_CANNONBALL_H_ */
