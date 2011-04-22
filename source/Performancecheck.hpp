/*
 * Performancecheck.hpp
 *
 *  Created on: 21.04.2011
 *      Author: Sebastian
 */
//TODO: surround it with a debug-tag
//		do the same with the show DebugValue....
#ifndef PERFORMANCECHECK_HPP_
#define PERFORMANCECHECK_HPP_
#include <SDL.h>
#include "Logfile.hpp"
#include <string>
using namespace std;

float lalalaTIME;
void startWatch() {
	lalalaTIME = SDL_GetTicks();
}
void stopWatch(char name[]) {
	lalalaTIME = SDL_GetTicks()-lalalaTIME;
	g_pLogfile->fTextout("<br> %s : %f", name, lalalaTIME);
}

#endif /* PERFORMANCECHECK_HPP_ */
