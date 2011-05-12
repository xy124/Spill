/*
 * Settings.hpp
 *
 *  Created on: 27.04.2011
 *      Author: Sebastian
 */

#ifndef SETTINGS_HPP_
#define SETTINGS_HPP_

#include <string>
#include <SDL.h>

#include "Singleton.hpp"

struct S_WormSettings {
	SDLKey KeyJump;
	SDLKey KeyLeft;
	SDLKey KeyRight;
	SDLKey KeyMine;
	SDLKey KeySelectBlockType;
	SDLKey KeyBuild;
	SDLKey KeyBlockActions;//that key will let all blocks do their actions, shooting...

	std::string name;
};

struct S_saveIt {
	S_WormSettings WormSet[2];
};


#define g_pSettings CSettings::get()
class CSettings : public TSingleton<CSettings>{
public:
	CSettings();
	virtual ~CSettings() {};

	S_saveIt s;
	//S_s.WormSettings s.WormSet[2];



	void SaveToFile	(std::string sFilename);
	void LoadFromFile(std::string sFilename);

};

#endif /* SETTINGS_HPP_ */
