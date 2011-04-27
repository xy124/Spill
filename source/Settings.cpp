/*
 * Settings.cpp
 *
 *  Created on: 27.04.2011
 *      Author: Sebastian
 */

#include "Settings.hpp"

#include <fstream>
#include "Logfile.hpp"

using namespace std;

CSettings::CSettings() {
	WormSet[0].KeyJump 				= SDLK_UP;
	WormSet[0].KeyLeft	 			= SDLK_LEFT;
	WormSet[0].KeyMine 				= SDLK_DOWN;
	WormSet[0].KeyRight 			= SDLK_RIGHT;
	WormSet[0].KeySelectBlockType 	= SDLK_RSHIFT;
	WormSet[0].KeyBuild 			= SDLK_RCTRL;

	WormSet[0].name 				= "John";



	WormSet[1].KeyJump 				= SDLK_w;
	WormSet[1].KeyLeft	 			= SDLK_a;
	WormSet[1].KeyMine 				= SDLK_s;
	WormSet[1].KeyRight 			= SDLK_d;
	WormSet[1].KeySelectBlockType 	= SDLK_LSHIFT;
	WormSet[1].KeyBuild 			= SDLK_LCTRL;

	WormSet[1].name 				= "Player2";
}

CSettings::~CSettings() {
	// TODO Auto-generated destructor stub
}

void CSettings::SaveToFile(std::string sFilename) {
	ofstream Output (sFilename.c_str(), ios::binary);
	if (Output == NULL) {
		g_pLogfile->FunctionResult("CSettings::SaveToFile",L_FAIL, "Couldn't write " + sFilename);
		return;
	}
	Output.write((char*) this, sizeof(this));
	Output.close();
}



void CSettings::LoadFromFile(std::string sFilename) {
	oifstream Input (sFilename.c_str(), ios::binary);
	if (Input == NULL) {
		g_pLogfile->FunctionResult("CSettings::LoadFromFile",L_FAIL, "Couldn't load " + sFilename);
		return;
	}
	Input.read((char*) this, sizeof(this));
	Input.close();
	g_pLogfile->FunctionResult("CSettings::LoadFromFile",L_OK, "Successfull loaded settings from " + sFilename);
}


