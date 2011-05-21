/*
 * Item.cpp
 *
 *  Created on: 19.05.2011
 *      Author: Sebastian
 */

#include "Item.hpp"

void CItem::renderIcon(int x, int y) {
	m_pIcon->SetPos(static_cast<float>(x), static_cast<float>(y));
	m_pIcon->Render();
}

void CItem::setIcon(CSprite * pIcon) {
	m_pIcon = pIcon;
}

void CItem::init() {
	m_pOwner = NULL;
	setCanMove(true);
	m_bIsAlive = true;
	m_bDropable = true;
	m_Name = "[Item]";
	setIcon(g_pSpritepool->at(SPRITEID::DUMMYICON));
};
