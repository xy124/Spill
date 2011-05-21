/*
 * IBlockActionWand.hpp
 *
 *  Created on: 21.05.2011
 *      Author: Sebastian
 */

#ifndef IBLOCKACTIONWAND_HPP_
#define IBLOCKACTIONWAND_HPP_

#include "Item.hpp"

class CGame;

class CIBlockActionWand: public CItem {
private:
	CGame * m_pGame;
	float m_fLastActionTime;
public:
	void init(CGame * pGame);
	void use();
	void render();
	void update() {};
	void quit()   {};
	CIBlockActionWand();
	virtual ~CIBlockActionWand();
};

#endif /* IBLOCKACTIONWAND_HPP_ */
