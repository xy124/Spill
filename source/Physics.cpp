#include "Physics.hpp"

using namespace std;

bool CPhysics::doPhysics(CGame * Game) {
	//Hint: Nur hier sollte der Timer eingesetzt werden!!! und bei animphasen!!
	vector<CWorm*>::iterator i;
	for (i = Game->m_vWorms.begin(); i<Game->m_vWorms.end(); ++i) {
		if ( !((*i)->getCanMove() && (*i)->isAlive()) )
			break; //auf zum n�chsten Wurm!
		FloatRect FR = (*i)->getRect();
		CVec dir = (*i)->getDir();
		//Fallbeschleunigung dazu!
		//HINT: Fallkurve hängt von getTimeelapsed ab!! evtl mit s=g/2t² arbeieten
		dir.y += Gravity*g_pTimer->getElapsed(); //graviy muss nach unten zeigen...



		//TODO: wir testen noch keine kollission auf dem weg dahin, nur ob das ziel frei ist!
		//--> h�ngt also von pcspeed ab!!!


		//Kollission durch x-Verschiebung??
		/*float deltaX = dir.x*g_pTimer->getElapsed();
		if (deltaX > BLOCKSIZE) { //per while alle möglichen blockschritte durchgehen
			/*float newX = FR.x;
			while (IdeltaX < deltaX) {
				FR.x += IdeltaX;
				if (isCollission(FR, Game)) {
					//Verschiebung erstmal rückgängig machen
					FR.x -= IdeltaX;
					//bis zur letztenblockgrenze zurückschieben
					if (IdeltaX > 0) { //rechtsverschiebung also nach links zurückschieben
						CBlockKoord CollisionBlockX = CVec(FR.x + FR.w, 0).toBlockKoord();//!y-Value doesn't matter!!!!
						FR.x = CVec(CollisionBlockX).x-FR.w -1; //-1 damit nicht gleich wieder kollission
					} else if (deltaX < 0) {
						CBlockKoord CollissionBlockX = CVec(FR.x, 0).toBlockKoord();
						CollissionBlockX.x += 1; //ein block weiter rechts
						FR.x = CVec(CollissionBlockX).x +1;
					}
				}

				IdeltaX += BLOCKSIZE;
			}*/

/*
		} else {
			FR.x += deltaX;
			if (isCollission(FR, Game)) {
				//Verschiebung erstmal rückgängig machen
				FR.x -= deltaX;
				//bis zur letztenblockgrenze zurückschieben
				if (deltaX > 0) { //rechtsverschiebung also nach links zurückschieben
					CBlockKoord CollisionBlockX = CVec(FR.x + FR.w, 0).toBlockKoord();//!y-Value doesn't matter!!!!
					FR.x = CVec(CollisionBlockX).x-FR.w -1; //-1 damit nicht gleich wieder kollission
				} else if (deltaX < 0) {
					CBlockKoord CollissionBlockX = CVec(FR.x, 0).toBlockKoord();
					CollissionBlockX.x += 1; //ein block weiter rechts
					FR.x = CVec(CollissionBlockX).x +1;
				}

				dir.x *= (-1 * BouncingFactor);
			}

		}*/

		////////////////////
		//X-Collissions:
		FR.x += dir.x*g_pTimer->getElapsed();
		if (isCollission(FR, Game)) { //kollission durch x-Rutschen?
			FR.x -= dir.x*g_pTimer->getElapsed(); //dann x-Rutschen wieder r�ckg�ngig machen
			dir.x *= (-1 * BouncingFactor);
		}

		////////////////////
		//Y-Collissions:
		(*i)->setCanJump(false); //kann auf jeden erstmal nciht springen
		//Kollission durch y-Verschiebung??
		FR.y += dir.y*g_pTimer->getElapsed();
		if (isCollission(FR, Game)) { //kollission durch y-Rutschen?
			FR.y -= dir.y*g_pTimer->getElapsed(); //dann y-Rutschen wieder r�ckg�ngig machen
			dir.y *= (-1 * BouncingFactor);
			if (Abs(dir.y) < 6.0f) {
				(*i)->setCanJump(true);
			}
			g_pFramework->showDebugValue("abs Y %f",Abs(dir.y));
		}


		//TODO: falls es noch andere solid-physicalobjets gibt, diese berücksichtigen!!!

		//Wenn keine kollission dann Verschieben !...^^

		//HINT:Reibung://Flugreibung ist Sinnlos!
		dir.x *= (Friction ) ; //TODO TimeElapsed einrechnen!
		// Kollission mit bildschirmr�ndern!!
		(*i)->setDir(dir);
		(*i)->setRect(FR);
	}

	return true;
}

CBlock::BlockType CPhysics::getBlockType(CVec vec, CGame * Game) {
	CBlockKoord blockKoord;
	blockKoord = vec.toBlockKoord();
	std::map<CBlockKoord,CBlock*>::iterator it;
	it = Game->m_Gameboard.find(blockKoord);
	if (it != Game->m_Gameboard.end()) { //vec existiert tats�chlich!
		CBlock::BlockType res = it->second->getBlockType();
		return res;
	}
	return CBlock::NORMAL;
}

bool CPhysics::rectCollission(const FloatRect &FR1, const FloatRect &FR2) { //überprüft ob sich zwei rects schneiden!
	return ( (FR1.y < FR2.y+FR2.h) && (FR1.y+FR1.h > FR2.y)
			&& (FR1.x < FR2.x+FR2.w) && (FR1.x+FR1.w > FR2.x) );
}

bool CPhysics::isCollission(const FloatRect &FR, CGame * Game) {
	//TODO Game as member
	//TODO wir �berpr�fen nur die ecken!
	//FIXME USE RECTCOLLISSION!!!
	//HINT: reicht z.z.T wenn wir die Ecken überprüfen, da unser Worm maximal auf vier verschiedenen Feldern Sein kann!!
	CBlock::BlockType BT_TopLeft  = CPhysics::getBlockType(CVec(FR)						,	Game);
	CBlock::BlockType BT_TopRight = CPhysics::getBlockType(CVec(FR.x+FR.w, FR.y)		,	Game);
	CBlock::BlockType BT_BotLeft  = CPhysics::getBlockType(CVec(FR.x, FR.y+FR.h)		,	Game);
	CBlock::BlockType BT_BotRight = CPhysics::getBlockType(CVec(FR.x+FR.w, FR.y+FR.h)	,	Game);

	CBlock::BlockType air = CBlock::AIR;
	if (    (BT_TopLeft == air) &&
			(BT_TopRight == air) &&
			(BT_BotLeft == air) &&
			(BT_BotRight == air) )
		return false;
	 else
		return true;
}



