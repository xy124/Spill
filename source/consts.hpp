/*
 * consts.hpp
 *
 *  Created on: 20.04.2011
 *      Author: Sebastian
 */

#ifndef CONSTS_HPP_
#define CONSTS_HPP_

//TODO als const-singleton???


//Game.hpp:
#define MAXGAMEBOARDWIDTH 500
#define MAXGAMEBOARDHEIGHT 50

//Worm.hpp:
#define MAXENERGY 100
#define WORMMAXSPEED_X 175.0f
#define WORMACCELLERATION 100.0f

//BLock.hpp:
#define BLOCKSIZE 20
#define BLOCKCOSTS {0, 5, 10, 10, 10}

//Physics.hpp:
#define GRAVITY 981.0f
#define BOUNCINGFACTOR 0.3f
#define FRICTION 0.8f

//DATA:
#define _DIRDATA_ std::string("data")



#endif /* CONSTS_HPP_ */
