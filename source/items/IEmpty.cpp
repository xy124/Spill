/*
 * IEmpty.cpp
 *
 *  Created on: 24.05.2011
 *      Author: Sebastian
 */

#include "IEmpty.hpp"

void CIEmpty::init() {
	this->CItem::init();
	setIcon(g_pSpritepool->at(SPRITEID::DUMMYICON));
	setDropable(false);
	setName("Nothing");
}
