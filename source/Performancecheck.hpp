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

//#define ac//Switch<----

float lalalaTIME;
void startWatch() {
	#ifdef ac //Debug ist eine vorgefertigte Definition
		lalalaTIME = SDL_GetTicks();
	#endif
}
void stopWatch(const char* name) {
	#ifdef ac
		lalalaTIME = SDL_GetTicks()-lalalaTIME;
		//g_pLogfile->fTextout(" %s : %f", name, lalalaTIME);
		//for excell:
		g_pLogfile->fTextout("%f;", lalalaTIME);
	#endif

}

#endif /* PERFORMANCECHECK_HPP_ */
