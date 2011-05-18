/*
 * BlockAction.cpp
 *
 *  Created on: 18.05.2011
 *      Author: Sebastian
 */

#include "BlockAction.hpp"

#include "Vec.hpp"
#include "consts.hpp"
#include <list>

//Attackanimations
#include "AttackAnimations/AttackAnimation.hpp"
#include "AttackAnimations/CAA_Laser.hpp"
#include "AttackAnimations/CAA_CannonBall.hpp"
#include "AttackAnimations/CAA_Cloud.hpp"


using namespace std;

void CBlockAction::action(CGame * pGame, CWorm * pOwner) {
//TODO fill it
//FIXME: handle blockactions in diffrent funcs per block
	//For All Blocks By owner:

	list<CBlockKoord*>::iterator blockIt;





	vector<CWorm*>::iterator wIt;
	CVec dist, blockPos;

	for (blockIt = pOwner->m_BuiltBlocks.begin();
			blockIt != pOwner->m_BuiltBlocks.end(); ++blockIt) {
		//Process actions for that block...
		CBlock * block = pGame->getBlock(*(*blockIt));


		if (block->getBlockType() == CBlock::SHOOTING) {
			for (wIt = pGame->m_vWorms.begin(); wIt != pGame->m_vWorms.end(); ++wIt) {
				//damage all near worms!!;
				if ((*wIt)->getTeamID() != pOwner->getTeamID()) { //opponent!!!
					dist = (*wIt)->getRect();
					blockPos = CVec(*(*blockIt));
					dist-= blockPos;

					if (dist.quad_abs()<QUADSHOOTINGBLOCKRANGE) {
						float e;
						e = (*wIt)->getEnergy()-SHOOTINGBLOCKDAMAGE;
						(*wIt)->setEnergy(e);
						//DrawAttackAnimation
						//get midWorm, midBlock
						blockPos.x += BLOCKSIZE/2;
						blockPos.y += BLOCKSIZE/2;
						CAA_Laser * pLaser = new CAA_Laser();
						pLaser->init(1.5f, blockPos, (*wIt), 255, 0, 0);
						pGame->m_AttackAnimations.push_back(pLaser);
						//earn points!
						pOwner->changePointsBy(10);
						pOwner->changeMoneyBy(5);
					}

				}
				//TODO: worms have to die if hp<0!

			}
		}//Shooting & Cloud
		if ( (block->getBlockType() == CBlock::CANNON)
				|| (block->getBlockType() == CBlock::CLOUDGEN) ){
			float minDist=0.01f;//MBE: hope thats beig enoough
			CWorm * pMinDistWorm = NULL;
			//findNearest opponent Worm:
			for (wIt = pGame->m_vWorms.begin(); wIt != pGame->m_vWorms.end(); ++wIt) {
				if ((*wIt)->getTeamID() != pOwner->getTeamID()) { //opponent!!!
					dist  = (*wIt)->getRect();
					blockPos = CVec(*(*blockIt));
					dist -= blockPos;
					if (dist.quad_abs()<minDist || minDist <= 0.1f) {
						pMinDistWorm = (*wIt); //aktueller wurm am nächsten...
					}
				}
			}

			if (block->getBlockType() == CBlock::CANNON) {
				//set nearest worm as aim!!;
				CAA_CannonBall * pCannonBall = new CAA_CannonBall();
				pCannonBall->init(blockPos, pMinDistWorm, pOwner,
						&(pGame->m_AttackAnimations));
				pGame->m_AttackAnimations.push_back(pCannonBall);
			}

			if (block->getBlockType() == CBlock::CLOUDGEN) {
				CAA_Cloud * pCloud = new CAA_Cloud();
				pCloud->init(CVec(0,0), pMinDistWorm, pOwner, 0);
				pGame->m_AttackAnimations.push_back(pCloud);
				pCloud = NULL;
			}


			pMinDistWorm = NULL;

		}//Cannon

	}// for all owned blocks

}

