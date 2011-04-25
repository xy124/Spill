#include "Physics.hpp"

using namespace std;

bool CPhysics::doPhysics() {
	vector<CWorm*>::iterator it;
	for (it = m_pGame->m_vWorms.begin(); it!=m_pGame->m_vWorms.end(); ++it) {
		if ( !((*it)->getCanMove() && (*it)->isAlive()) )
			break; //auf zum n�chsten Wurm!

		float timeElapsed = g_pTimer->getElapsed();
		if (timeElapsed == 0.0f)
			break; //macht keinen Sinn....
		FloatRect FR = (*it)->getRect(); //rect of worm
		CVec dir = (*it)->getDir(); //dir of Worm

		//CBlockKoord BC = CBlockKoord(FR);
		//g_pFramework->showDebugValue("WormBlockKoord %i, %i", BC.x, BC.y);


		//Fallbeschleunigung dazu!
		//HINT: Fallkurve hängt von getTimeelapsed ab!! evtl mit s=g/2t² arbeieten
		dir.y += Gravity*g_pTimer->getElapsed(); //graviy muss nach unten zeigen...



		//TODO: wir testen noch keine kollission auf dem weg dahin, nur ob das ziel frei ist!
		//--> h�ngt also von pcspeed ab!!!


		float time = timeElapsed;
		int i;//Anzahl der Kleinschritte herrausbekommen:
		for (i = 1; dir.quad_abs()*time > BLOCKSIZE*BLOCKSIZE; i++) {
			time = timeElapsed/i;
		}

		bool bNoCollision = true;

		g_pFramework->showDebugValue("i:%i",i);

		for (i = 1; (i*time <= timeElapsed)
					&& (bNoCollision); i++) {
			////////////////////
			//X-Collisions:
			FR.x += dir.x*time;
			S_Collision XCollision;
			XCollision = getCollision(FR);
			if (XCollision.bIsCollision) { //kollission durch x-Rutschen?
				FR.x -= dir.x*time; //dann x-Rutschen wieder r�ckg�ngig machen
				dir.x *= (-1 * XCollision.fBouncingFactorX);
				bNoCollision = false;//braucht nicht weiter zu machen
			}

			////////////////////
			//Y-Collisions:
			(*it)->setCanJump(false); //kann auf jeden erstmal nciht springen
			//Kollission durch y-Verschiebung??
			FR.y += dir.y*time;
			S_Collision YCollision;
			YCollision = getCollision(FR);
			if (YCollision.bIsCollision) { //kollission durch y-Rutschen?
				//JumpingBoard...
				//getBouncingfactor from Blocktype
				FR.y -= dir.y*time; //dann y-Rutschen wieder r�ckg�ngig machen
				dir.y *= (-1 * YCollision.fBouncingFactorY);//neues Y
				if ((Abs(dir.y) < 10.0f) || (YCollision.BlockType == CBlock::JUMPBOARD)) {
					(*it)->setCanJump(true);
				}
				bNoCollision = false;
			}

			//TODO: falls es noch andere solid-physicalobjets gibt, diese berücksichtigen!!!

			//Wenn keine kollission dann Verschieben !...^^

			//HINT:Reibung://Flugreibung ist Sinnlos!
			dir.x *= (Friction ) ; //TODO TimeElapsed einrechnen!


			if (FR.x < 0.0f) FR.x = 0.0f; //man kann nicht aus dem linken bildschirm fallen!!
			(*it)->setDir(dir);
			(*it)->setRect(FR);

			//gegebenenfalls neue collision setzen
			if (YCollision.BlockType != CBlock::AIR)
				(*it)->setLastCollisionY(YCollision);

		}//für jeden SChritt...
	}//FÜPR JEDEN WURM

	return true;
}

CBlock::BlockType CPhysics::getBlockType(CVec &vec) {
	CBlock* b;
	b= m_pGame->getBlock(vec.toBlockKoord());
	if (b != NULL) //vec existiert tats�chlich!
		return b->getBlockType();
	else
		return CBlock::NORMAL;
}

bool CPhysics::rectCollision(const FloatRect &FR1, const FloatRect &FR2) { //überprüft ob sich zwei rects schneiden!
	return ( (FR1.y < FR2.y+FR2.h) && (FR1.y+FR1.h > FR2.y)
			&& (FR1.x < FR2.x+FR2.w) && (FR1.x+FR1.w > FR2.x) );
}

S_Collision CPhysics::getCollision(const FloatRect &FR) {
#define CHECKPOINTS 4//jez reichen 4 Punke, da Worm kleiner Block!!

	//TODO USE RECTCOLLISION!!!
	//HINT: reicht z.z.T wenn wir die Ecken + 2 Mitten überprüfen, da unser Worm maximal auf vier verschiedenen Feldern Sein kann!!
	S_Collision result;//init Result:
	result.fBouncingFactorX = 0.0f;
	result.fBouncingFactorY = 0.0f;
	result.bIsCollision = false;
	result.BlockType = CBlock::AIR;

	CVec vecs[CHECKPOINTS];

	vecs[0] = CVec (FR);
	vecs[1] = CVec (FR.x+FR.w, FR.y);
	vecs[2] = CVec (FR.x, FR.y+FR.h);
	vecs[3] = CVec (FR.x+FR.w, FR.y+FR.h);
	/*vecs[4] = CVec (FR.x+FR.w/2, FR.y);
	vecs[5] = CVec (FR.x+FR.w/2, FR.y+FR.h);*/

	for (int i=0; i<CHECKPOINTS; i++) {
		CBlock::BlockType curType = CPhysics::getBlockType(vecs[i]);
		if (curType != CBlock::AIR)
			result.bIsCollision = true;
		if (CBlock::BlockBouncingX[curType] > result.fBouncingFactorX)
			result.fBouncingFactorX = CBlock::BlockBouncingX[curType];
		if (CBlock::BlockBouncingY[curType] > result.fBouncingFactorY)
			result.fBouncingFactorY = CBlock::BlockBouncingY[curType];
		if (curType > result.BlockType) {
			result.BlockType = curType;
		}
	}


	return result;
}

void CPhysics::init(CGame * Game) {
	m_pGame = Game;
}



