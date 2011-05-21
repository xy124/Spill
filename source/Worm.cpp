#include "Worm.hpp"
#include <map>
#include "Framework.hpp"

#include "Collision.hpp"
#include "BlockAction.hpp"
#include "Spritepool.hpp"


using namespace std;

CWorm::CWorm(CGame *pGame) {
	m_pWormSprite = NULL;
	m_pGame = pGame;
	m_pSettings = NULL;
}

void CWorm::init(int WormID) {
	init(WormID, WormID, 0, 0, WC_RED);
}

void CWorm::init(int WormID, float X, float Y) {
	init(WormID, WormID, X, Y, WC_RED);
}

void CWorm::init(int WormID, WORMCOLORS WC){
	init(WormID, WormID, 0, 0, WC);
}

void CWorm::init(int WormID, int TeamID, float X, float Y, WORMCOLORS WC) {
	m_WormID = WormID;
	m_TeamID = TeamID;
	setCanJump(false);
	m_Color = WC;
	m_Money = 140;//MBE ForDebugReasons
	m_Points = 0;
	m_Energy = MAXENERGY;
	m_fLastActionTime = 0.0f;
	m_SelectedpItem = m_pItems.end();

	setCanMove(true);
	
	m_bJumpKeyLock = false;
	m_bBuildKeyLock = false;

	m_bNextBTypeKeyLock = false;
	m_selectedBType = CBlock::NORMAL;

	m_bOrientation = ORIGHT;
	
	m_pWormSprite = g_pSpritepool->at(SPRITEID::WORM);
	m_fAnimphase = 0.0f;
	m_isWalking = false;
	setIsSolid(false);

	FloatRect FR;
	FR = m_pWormSprite->GetRect();
	FR.x = 800.0f * WormID;
	setRect(FR);
	setDir(CVec(0,0));

	S_Collision lastCollisionY = getLastCollisionY();

	lastCollisionY.BlockType = CBlock::AIR;
	lastCollisionY.fBouncingFactorX = 0.0f;
	lastCollisionY.fBouncingFactorY = 0.0f;
	lastCollisionY.bIsCollision = false;

	setLastCollisionY(lastCollisionY);

	m_Alive = true;
	m_bIsVisible = true;
	CLogfile::get()->fTextout("<br />New Worm. ID:%i",m_WormID);

	m_pSettings = &(g_pSettings->s.WormSet[m_WormID]);

}

void CWorm::reset() { //HINT: resettet nicht die Position
	setDir(CVec(0,0));
	m_Money = 0;
	m_Points = 0;
	m_Energy = MAXENERGY;
}

void CWorm::render() {
	//render worm!
	if (m_bIsVisible) {
		CVec newWormPos = CVec(getRect());
		m_pWormSprite->SetPos( newWormPos);
		m_pWormSprite->Render(m_fAnimphase, m_bOrientation, m_TeamID);
	}

	int x = g_pFramework->ViewPorts.at(m_WormID).m_ScreenPosition.x;
	int y = 100;

	//render Itembar-Background
	g_pSpritepool->at(SPRITEID::ITEMBARBACK)->SetPos(x, y);
	g_pSpritepool->at(SPRITEID::ITEMBARBACK)->Render();

	//render ItemIcons!
	list<CItem*>::iterator it;

	for (it = m_pItems.begin(); it != m_pItems.end();/**/) {
		if ((*it)->isAlive())  {//alive
			(*it)->renderIcon(x,y);
			y += BLOCKSIZE;
			++it;
		} else {
			it = m_pItems.erase(it);
			m_SelectedpItem = it;
		}
	}

	y = 100;
	//render Itembar-Background
	g_pSpritepool->at(SPRITEID::ITEMBARFRONT)->SetPos(x, y);
	g_pSpritepool->at(SPRITEID::ITEMBARFRONT)->Render();

	//render selected Item again!
	x += 100;
	y = 100;
	if (m_SelectedpItem == m_pItems.end()) {
		m_pGame->m_pDummyItemIcon->SetPos(x,y);
		m_pGame->m_pDummyItemIcon->Render();
	} else {
		(*m_SelectedpItem)->renderIcon(x,y);
	}
}

void CWorm::ProcessMoving() {
	CVec newDir = getDir();
	if (g_pFramework->KeyDown(m_pSettings->KeyJump) && getCanJump() && !m_bJumpKeyLock) { //Jump!
		m_bJumpKeyLock = true;

		S_Collision lastCollisionY = getLastCollisionY();

		if (lastCollisionY.BlockType == CBlock::JUMPBOARD)
			newDir.y = 1.25f*WORMJUMPSPEED_Y;
		else
			newDir.y = WORMJUMPSPEED_Y;
	}

	if (!g_pFramework->KeyDown(m_pSettings->KeyJump))
		m_bJumpKeyLock = false;


	m_isWalking = false;
	//Left or Right!!
	if (g_pFramework->KeyDown(m_pSettings->KeyLeft) == true) {
		newDir.x += -WORMACCELERATION;
		m_isWalking = true;
		m_bOrientation = OLEFT;
		if (newDir.x < -WORMMAXSPEED_X) newDir.x = -WORMMAXSPEED_X;
	} else if (g_pFramework->KeyDown(m_pSettings->KeyRight) == true ) {
		newDir.x += +WORMACCELERATION;
		m_isWalking = true;
		m_bOrientation = ORIGHT;
		if (newDir.x > WORMMAXSPEED_X) newDir.x = WORMMAXSPEED_X;
	}

	setDir(newDir);
}

void CWorm::ProcessBuilding() {
	/*
	 * KeyDown:	MineBlock
	 * STRG:	BuildBlock
	 * Shift:	SelectBuildBlockType
	 */

	if (g_pFramework->KeyDown(m_pSettings->KeyMine)) {
		//get Block under Worm!
		CVec vec(getRect());
		vec.x += getRect().w/2;//Block UNDER worm
		CBlockKoord pos = vec.toBlockKoord();
		pos.y++;//Block UNDER worm
		CBlock* miningBlock = m_pGame->getBlock(pos);//returns NULL if for example out of Gameboard
		if (miningBlock != NULL) {
			int miningBlockTeamID = miningBlock->getTeamID();
			int miningBlockBuilderID = miningBlock->getBuilderID();
			if ( ((miningBlockTeamID == NOBODY) || (miningBlockTeamID == m_TeamID))//you can't mine other teams blocks
					&& (miningBlock->getBlockType() != CBlock::AIR) ){
				int newMoney = m_Money + CBlock::BlockCosts[miningBlock->getBlockType()]; //da blocktype sich dann ja ändert... bei buildblock
				if (m_pGame->BuildBlock(pos, CBlock::AIR, m_WormID, m_TeamID)) { //block konnte gebaut werden!:
					m_Money = newMoney;
					m_Points++;
					g_pLogfile->fTextout(BLUE, false, "Mined Block");
					//delete block from playerlist!
					if (miningBlockBuilderID != NOBODY) {
						list<CBlockKoord>::iterator it;
						for (it = m_BuiltBlocks.begin();
							(it != m_BuiltBlocks.end()) && ((*it) != pos);
							++it) /*nothing*/;
						m_BuiltBlocks.erase(it);

						//m_pGame->m_vWorms.at(miningBlockBuilderID)->m_BuiltBlocks.erase();
					}

				}
			}
		} else g_pLogfile->Textout("<br /> Couldn't mine Block because miningBlock == NULL");
	}//Keydown

	if ( (g_pFramework->KeyDown(m_pSettings->KeySelectBlockType)) && (m_bNextBTypeKeyLock == false) ) {
		m_selectedBType = CBlock::nextBlockType(m_selectedBType);
		m_bNextBTypeKeyLock = true;
	}
	if (!g_pFramework->KeyDown(m_pSettings->KeySelectBlockType))
		m_bNextBTypeKeyLock = false;

	if ( (g_pFramework->KeyDown(m_pSettings->KeyBuild))
			&& (m_bBuildKeyLock == false)
			&& (m_selectedBType != CBlock::AIR)//Build Air has no sense...
			&& (m_Money >= CBlock::BlockCosts[m_selectedBType]) //player has enough money
			) {
		m_bBuildKeyLock = true;
		//get field next to worm
		CVec vec(getRect());
		if (m_bOrientation == ORIGHT)
			vec.x += (getRect().w + BLOCKSIZE);//next block
		else
			vec.x -= BLOCKSIZE;

		CBlockKoord pos = vec.toBlockKoord();

		//is field free???
		CBlock* buildingBlock = m_pGame->getBlock(pos);
		if ( (buildingBlock != NULL)
				&& (buildingBlock->getBlockType() == CBlock::AIR)
				&& (g_pPhysics->isEmpty(pos)) ) {
			if (m_pGame->BuildBlock(pos, m_selectedBType, m_WormID, m_TeamID)) {
				m_Money -= CBlock::BlockCosts[m_selectedBType];
				m_Points++;
				m_BuiltBlocks.push_back(pos);

				g_pLogfile->fTextout("</br >Built BLock: "+CBlock::BlockTypeString(m_selectedBType)+" Costs:%i", CBlock::BlockCosts[m_selectedBType]);
			}

		}
//FIXME: Key!
	}
	if (!g_pFramework->KeyDown(m_pSettings->KeyBuild))
			m_bBuildKeyLock = false;


}

void CWorm::ProcessAnim() {
	if (m_isWalking)
		m_fAnimphase += 10.0f*g_pTimer->getElapsed();
	if (m_fAnimphase >= 3.0f)
		m_fAnimphase -= 3.0f;
}

void CWorm::ProcessView() {
	FloatRect WormRect = getRect();
	SDL_Rect ViewRect  = g_pFramework->ViewPorts.at(m_ViewPort).m_View;//MBE at nimmt performance raus!

	const int scrollForeward = static_cast<int>(ViewRect.w/2)+100;
	const int scrollBackward = static_cast<int>(ViewRect.w/2)-150;

	if (static_cast<int>(WormRect.x) > ViewRect.x+scrollForeward) {
		//move View rect that worm is at 300
		ViewRect.x = static_cast<int>(WormRect.x) - scrollForeward;
	}

	if (static_cast<int>(WormRect.x) < ViewRect.x + scrollBackward)
		ViewRect.x = static_cast<int>(WormRect.x) - scrollBackward;

	//handle right Border of World
	if (ViewRect.x + ViewRect.w > m_pGame->getWorldRect().w)
		ViewRect.x = m_pGame->getWorldRect().w - ViewRect.w;

	//handle left Border of World
	if (ViewRect.x < 0)
		ViewRect.x = 0;

	g_pFramework->ViewPorts[m_ViewPort].m_View = ViewRect;//MBE per at????

	char buffer[1024];
	sprintf(buffer, "Money: %iEur, Points: %i, Energy: %.0f/%.0f",m_Money, m_Points, m_Energy, MAXENERGY);
	string s = buffer;
	g_pFramework->TextOut(s, 0, 0, m_ViewPort);
	s = g_pSettings->getName(m_WormID);
	g_pFramework->TextOut(s, 0, 70, m_ViewPort);

	s = "::"+CBlock::BlockTypeString(m_selectedBType)+"::";
	g_pFramework->TextOut(s, 0, 15, m_ViewPort);

	int BlockEnergyState = static_cast<int>(100*(g_pTimer->now()-m_fLastActionTime)/LOADINGTIME);
	if (BlockEnergyState > 100) BlockEnergyState = 100;
	sprintf(buffer, "BlockEnergy: %i %%", BlockEnergyState);
	s = buffer;
	g_pFramework->TextOut(s, 0, 30, m_ViewPort);
}

CWorm::~CWorm() {
	if (m_pWormSprite != NULL) {
		delete (m_pWormSprite);
	}
	m_pWormSprite = NULL;
	m_pGame = NULL;
	m_pSettings = NULL;


	CLogfile::get()->fTextout("<br />Deleted Worm; ID:%i",m_WormID);
}

string CWorm::getWormColorString() {
	string result;
	switch (m_Color) {
		case WC_RED:
			result = "red";
			break;
		case WC_BLUE:
			result = "blue";
			break;
		case WC_GREEN:
			result = "green";
			break;
		case WC_YELLOW:
			result = "yellow";
			break;
		default:
			result = "noColor!";
			CLogfile::get()->Textout("Couldn't get the Colorstring!<br />");			
			break;
	}
	return result;
}

void CWorm::update() {
	ProcessMoving();

	ProcessBuilding();

	ProcessBlockActions();

	ProcessAnim();

	ProcessNextItemKey();

	ProcessUseItemKey();

	//Physics happens in do physics!
}

bool CWorm::isAlive() {
	return m_Alive;
}

void CWorm::ProcessBlockActions() {
	bool canDoBlockAction = (g_pTimer->now()-m_fLastActionTime > LOADINGTIME);
	if (g_pFramework->KeyDown(m_pSettings->KeyBlockActions) && canDoBlockAction) {
		m_fLastActionTime = g_pTimer->now();
		CBlockAction::action(m_pGame, this);

//HINT: Blockaction also drops/takes item
		//for all items in range: pick them up, if no item selected
		if (m_SelectedpItem == m_pItems.end()) { //pick item up!
			list<CItem*>::iterator it;
			for (it = m_pGame->m_pItems.begin(); it != m_pGame->m_pItems.end(); ++it) {
				if ((*it)->getOwner() == NULL) { //nobody owns it
					//calculate distance to item:
					CVec posItem = CVec((*it)->getRect());
					CVec dist = CVec(getRect());
					dist -= posItem;
					if (dist.quad_abs() < QUADMAXITEMPICKUPDIST) { //in range...., so its mine now!
						(*it)->setOwner(this);
						m_pItems.push_back((*it));
					}
				}
			}

		} else {//drop item!
			(*m_SelectedpItem)->setOwner(NULL);
			m_SelectedpItem = m_pItems.erase(m_SelectedpItem);

		}

	}//can do blockaction
}

void CWorm::ProcessNextItemKey() {
	if (g_pFramework->isNewEvent() && //Keylog
			g_pFramework->KeyDown(m_pSettings->KeyNextItem)) {
		if (m_SelectedpItem == m_pItems.end())
			m_SelectedpItem = m_pItems.begin();
		else {
			m_SelectedpItem++;
		}
	}
}

void CWorm::ProcessUseItemKey() {
	if (g_pFramework->isNewEvent() && //Keylog
				g_pFramework->KeyDown(m_pSettings->KeyUseItem)) {
		if (m_SelectedpItem != m_pItems.end()) {
			(*m_SelectedpItem)->use();
		}
	}
}
