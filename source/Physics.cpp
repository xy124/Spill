#include "Physics.hpp"

using namespace std;

const float CPhysics::Gravity = 9.81f;
const float CPhysics::BouncingFactor = 0.7f;

bool CPhysics::doPhysics(CGame * Game) {
	//Hint: Nur hier sollte der Timer eingesetzt werden!!! und bei animphasen!!
	vector<CWorm*>::iterator i;
	for (i = CGame->m_vWorms.begin(); i<=m_vWorms.end(); i++) {
		if ( !(i->getCanMove() && i->isAlive()) )
			break; //auf zum nächsten Wurm!
		FloatRect FR = i->getRect();
		CVec dir = i->getDir();
		//Fallbeschleunigung dazu!
		dir.y += Gravity*g_pTimer->getElapsed(); //graviy muss nach unten zeigen...



		//TODO: wir testen noch keine kollission auf dem weg dahin, nur ob das ziel frei ist!
		//--> hängt also von pcspeed ab!!!
		//TODO: zudem tun wir so als ob unser Worm nur 1 Feld Groß wäre. aber das ist ja ok
		//Kollission rechts, links, oben, unten

		//Kollission durch x-Verschiebung??
		FR.x += dir.x*g_pTimer->getElapsed();
		if (isCollission(FR, Game)) //kollission durch X-Rutschen?
			FR.x -= dir.x*g_pTimer->getElapsed(); //dann x-Rutschen wieder rückgängig machen
		//TODO: eigentlich muss jez geprüft werden wie weit man denn rutschen darf....., wie weits noch geht.

		//Kollission durch y-Verschiebung??
		FR.y += dir.y*g_pTimer->getElapsed();
				if (isCollission(FR, Game)) //kollission durch y-Rutschen?
					FR.y -= dir.y*g_pTimer->getElapsed(); //dann y-Rutschen wieder rückgängig machen
				//TODO: eigentlich muss jez geprüft werden wie weit man denn rutschen darf....., wie weits noch geht.


		//Wenn keine kollission dann Verschieben !...^^

		// Kollission mit bildschirmrändern!!
	}

	return true;
}

bool CPhysics::isCollission(const FloatRect &FR, const CGame * Game) {
	//TODO wir überprüfen nur die ecken!
	CBlock::BlockType BT_TopLeft  = getBlockType(CVec(FR)					,	Game);//TODO: game als membervariable!
	CBlock::BlockType BT_TopRight = getBlockType(CVec(FR.x+FR.w, FR.y)		,	Game);
	CBlock::BlockType BT_BotLeft  = getBlockType(CVec(FR.x, FR.y+FR.h)		,	Game);
	CBlock::BlockType BT_BopRight = getBlockType(CVec(FR.x+FR.w, FR.y+FR.h)	,	Game);

	CBlock::BlockType air = CBlock::AIR;
	if (    (BT_TopLeft == air) &&
			(BT_TopRight == air) &&
			(BT_BotLeft == air) &&
			(BT_BotRight == air) )
		return true;
	 else
		return false;
}

CBlock::BlockType CPhysics::getBlockType(const CVec &vec, const CGame * Game) {
	CBlockKoord blockKoord(vec);
	map<CBlockKoord, CBlock*>::iterator it;
	it = Game->m_Gameboard.find(blockKoord);
	if (it != Game->m_Gameboard.end) { //vec existiert tatsächlich!
		CBlock::BlockType res = it->second->getBlockType();
		return res;
	}
	return CBlock::NORMAL;
}

