/*
 * Item.cpp
 *
 *  Created on: 19.05.2011
 *      Author: Sebastian
 */

#include "Item.hpp"

CSprite * CItem::m_pIcon;

void CItem::renderIcon(int x, int y) {
	m_pIcon->SetPos(x, y);
	m_pIcon->Render();
}

void CItem::setIcon(CSprite * pIcon) {
	m_pIcon = pIcon;
}
