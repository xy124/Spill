#include "Worm.hpp"
#include <map>
#include "Framework.hpp"

#include "Collision.hpp"
#include "BlockAction.hpp"
#include "Spritepool.hpp"

#include "items/IBlockActionWand.hpp"
#include "items/IBlockBuilder.hpp"
#include "items/IEmpty.hpp"


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

	setCanMove(true);
	
	m_bJumpKeyLock = false;
	m_bBuildKeyLock = false;

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

	CLogfile::get()->fTextout("<br />New Worm. ID:%i",m_WormID);

	m_pSettings = &(g_pSettings->s.WormSet[m_WormID]);

	//give the worm some items... for building blocks and doing blockactions!
	//FirstItem is the item u use to pickup other Items (Empty!):
	CIEmpty * pEmpty = new CIEmpty;
	pEmpty->init();
	//don't need to set owner for this!
	m_pItems.push_back(pEmpty);
	pEmpty = NULL;

	//Now it makes sense to set this up:
	m_SelectedpItem = m_pItems.begin();

	CIBlockActionWand * pActionWand = new CIBlockActionWand();
	pActionWand->init(m_pGame);
	pActionWand->setOwner(this);
	m_pItems.push_back(pActionWand);
	pActionWand = NULL;

	CIBlockBuilder * pBlockBuilder;
	for (int i=0; i< BLOCKAMOUNT ;i++) {
		pBlockBuilder = new CIBlockBuilder();
		pBlockBuilder->init(CBlock::BlockType(i), m_pGame);
		pBlockBuilder->setOwner(this);
		m_pItems.push_back(pBlockBuilder);
		pBlockBuilder = NULL;
	}


	//let's have fun:
	m_Alive = true;
	m_bIsVisible = true;
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
	int y = g_pFramework->ViewPorts.at(m_WormID).m_ScreenPosition.h;

	//render Itembar-Background
	g_pSpritepool->at(SPRITEID::ITEMBARBACK)->SetPos(x, y);
	g_pSpritepool->at(SPRITEID::ITEMBARBACK)->Render();

	//render ItemIcons!
	list<CItem*>::iterator it;
	y+=2;
	x+=2;

	it = m_SelectedpItem;//start with selected item!
	for (int i = 1; i<=8; i++) {
		if (it == m_pItems.end())
			it = m_pItems.begin();
		if ((*it)->isAlive())  {//alive
			(*it)->renderIcon(x,y);
			x += BLOCKSIZE+5;//+5 because of the frames of the itembar!
			++it;
		} else {
			it = m_pItems.erase(it);
			m_SelectedpItem = it;
		}
	}
	if (m_SelectedpItem == m_pItems.end())
		m_SelectedpItem = m_pItems.begin();

	x = g_pFramework->ViewPorts.at(m_WormID).m_ScreenPosition.x+2;
		//render Itembar-Background
	g_pSpritepool->at(SPRITEID::ITEMBARFRONT)->SetPos(x, y);
	g_pSpritepool->at(SPRITEID::ITEMBARFRONT)->Render();
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

void CWorm::ProcessMining() {//HINT Mining without item!
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


	//FIXME: use keylock also for useitem keys and so on....
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

	if (m_SelectedpItem == m_pItems.end())
		s = "[Item]::END!";
	else
		s = "[Item]::"+(*m_SelectedpItem)->getName()+"::";
	g_pFramework->TextOut(s, 0, 15, m_ViewPort);


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

	ProcessMining();

	ProcessNextItemKey();

	ProcessUseItemKey();

	ProcessPickDropItem();

	ProcessAnim();

	//Physics happens in do physics!
}

bool CWorm::isAlive() {
	return m_Alive;
}

void CWorm::ProcessPickDropItem() {
	//for all items in range: pick them up, if no item selected
	if ((g_pFramework->isNewEvent()) && (g_pFramework->KeyDown(m_pSettings->KeyPickDropItem))) {
		if (m_SelectedpItem == m_pItems.begin()) { //pick item up!
			list<CItem*>::iterator it;
			for (it = m_pGame->m_pItems.begin(); it != m_pGame->m_pItems.end(); ++it) {
				if ((*it)->getOwner() == NULL) { //nobody owns it
					//calculate distance to item:
					CVec posItem = CVec((*it)->getRect(), true);
					CVec dist = CVec(getRect());
					dist -= posItem;

					if (dist.quad_abs() < QUADMAXITEMPICKUPDIST) { //in range...., so its mine now!
						(*it)->setOwner(this);
						m_pItems.push_back((*it));
						//new item = selected one:
						m_SelectedpItem = m_pItems.end();
						m_SelectedpItem--;
					}
				}
			}//for
		} else {//drop item!
			if ((*m_SelectedpItem)->isDropable()) {//can drop item
				(*m_SelectedpItem)->setOwner(NULL);
				m_SelectedpItem = m_pItems.erase(m_SelectedpItem);
			}
		}
	}//keydown
}


void CWorm::ProcessNextItemKey() {
	if (g_pFramework->isNewEvent() && //Keylog
			g_pFramework->KeyDown(m_pSettings->KeyNextItem)) {
		m_SelectedpItem++;
		if (m_SelectedpItem == m_pItems.end())
			m_SelectedpItem = m_pItems.begin();
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
