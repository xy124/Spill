/*
 * consts.hpp
 *
 *  Created on: 20.04.2011
 *      Author: Sebastian
 */

#ifndef CONSTS_HPP_
#define CONSTS_HPP_


//TODO als const-singleton???
//FIXME: alle Prameter klein beginnen!!!
//FIXME Parameter mehr als Referenz machen!!!
//s. icqchatg albert 22.04.2011


//Game.hpp:
#define MAXGAMEBOARDWIDTH 500
#define MAXGAMEBOARDHEIGHT 50
#define NOBODY -1



//Worm.hpp:
#define WORMWIDTH 25
#define WORMHEIGHT 18
#define MAXENERGY 100.0f
#define WORMJUMPSPEED_Y -500.0f
#define WORMMAXSPEED_X 175.0f
#define WORMACCELERATION 100.0f
#define LOADINGTIME 2.0f //it takes seven secs for reloading Blockactions
//forDebugreasons^^
//Orientation:
#define OLEFT true
#define ORIGHT false



//BLock.hpp:
#define BLOCKAMOUNT 6
#define BLOCKSIZE 30
/*
 * IMPORTANT: 	if you change amount of blocktypes also change
 * 				CBlock::BlockTypeString and CBlock::nextBlockType(BlockType Now)
 */
							//AIR,NORMAL,SHOOTING,JUMPBOARD,INVISIBLE,CANNON
#define BLOCKCOSTS 			{0   ,     5,      40,       10,       10,   100}
#define BLOCKBOUNCING_X 	{0.3f,  0.3f,    0.0f,     0.9f,     0.3f,  0.3f}//Bouncingfactors...
#define BLOCKBOUNCING_Y 	{0.3f,  0.3f,    0.0f,     0.9f,     0.3f,  0.3f}//Bouncingfactors...

#define QUADSHOOTINGBLOCKRANGE 10000
#define SHOOTINGBLOCKDAMAGE 20



//Physics.hpp:
#define GRAVITY 981.0f
#define FRICTION 0.8f



//DATA:
#define _DIRDATA_ std::string("data")



//Framework:
#define VIEWPORTFRAMEWIDTH 12



//Sprite:
#define MAXCOLORID 4
//StandardColorKey
#define COLORKEYR 0
#define COLORKEYG 255
#define COLORKEYB 255




#endif /* CONSTS_HPP_ */
