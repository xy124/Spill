/*
 * Settings.cpp
 *
 *  Created on: 27.14.2111
 *      Author: Sebastian
 */

#include "Settings.hpp"

#include <fstream>
#include "Logfile.hpp"

using namespace std;

CSettings::CSettings() {
	s.WormSet[0].KeyJump 				= SDLK_w;
	s.WormSet[0].KeyLeft	 			= SDLK_a;
	s.WormSet[0].KeyMine 				= SDLK_s;
	s.WormSet[0].KeyRight 				= SDLK_d;
	s.WormSet[0].KeySelectBlockType 	= SDLK_LSHIFT;
	s.WormSet[0].KeyBuild 				= SDLK_LCTRL;
	s.WormSet[0].KeyBlockActions		= SDLK_TAB;
	s.WormSet[0].KeyNextItem			= SDLK_1;

	setName(0, "Trottel");


	//////////////////////////////
	//Second Player
	//////////////////////////////

	s.WormSet[1].KeyJump 				= SDLK_UP;
	s.WormSet[1].KeyLeft	 			= SDLK_LEFT;
	s.WormSet[1].KeyMine 				= SDLK_DOWN;
	s.WormSet[1].KeyRight 				= SDLK_RIGHT;
	s.WormSet[1].KeySelectBlockType 	= SDLK_RSHIFT;
	s.WormSet[1].KeyBuild 				= SDLK_RCTRL;
	s.WormSet[1].KeyBlockActions		= SDLK_RETURN;
	s.WormSet[0].KeyNextItem			= SDLK_INSERT;

	setName(1, "John");
}

void CSettings::SaveToFile(std::string sFilename) {
	ofstream Output (sFilename.c_str(), ios::binary);
	if (Output == NULL) {
		g_pLogfile->FunctionResult("CSettings::SaveToFile",L_FAIL, "Couldn't write " + sFilename);
		return;
	}
	Output.write((char*) (&s), sizeof(s));
	Output.close();
	g_pLogfile->FunctionResult("CSettings::SaveToFile",L_OK, "Successfull saved settings to " + sFilename);
}



void CSettings::LoadFromFile(std::string sFilename) {
	ifstream Input (sFilename.c_str(), ios::binary);
	if (Input == NULL) {
		g_pLogfile->FunctionResult("CSettings::LoadFromFile",L_FAIL, "Couldn't load " + sFilename);
		return;
	}
	Input.read((char*) &s, sizeof(s));
	Input.close();
	g_pLogfile->FunctionResult("CSettings::LoadFromFile",L_OK, "Successfull loaded settings from " + sFilename);
	//string ss = s.WormSet[0].name+"Loaded"+s.WormSet[1].name;
	string ss = "0";
	g_pLogfile->Textout(ss);
}

const char* CSettings::getName(int arrayIndex) {
	return &( s.WormSet[arrayIndex].name[0] );

}

void CSettings::setName(int arrayIndex, std::string str) {
	for (unsigned int i = 0; ( (i<str.length()) && (i<30) ); i++)
		s.WormSet[arrayIndex].name[i] = str.at(i);
}


