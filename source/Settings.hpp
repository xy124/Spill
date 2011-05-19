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

class CSettings;

struct S_WormSettings {
friend class CSettings;
	SDLKey KeyJump;
	SDLKey KeyLeft;
	SDLKey KeyRight;
	SDLKey KeyMine;
	SDLKey KeySelectBlockType;
	SDLKey KeyBuild;
	SDLKey KeyBlockActions;//that key will let all blocks do their actions, shooting...
	SDLKey KeyNextItem;
	SDLKey KeyUseItem;

private:
	char name [30];
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

	const char* getName(int arrayIndex);
	void setName(int arrayIndex, std::string str);

};

#endif /* SETTINGS_HPP_ */
