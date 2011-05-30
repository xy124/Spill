/*
 * Settings.cpp
 *
 *  Created on: 27.14.2111
 *      Author: Sebastian
 */

#include "Settings.hpp"

#include <fstream>
#include "Logfile.hpp"

#include <stdio.h>

#include "Block.hpp"
#include "BlockKoord.hpp"
#include <map>


using namespace std;

const int formatVersion = 1;//TODO whaa globals -__-

CSettings::CSettings() {
	s.WormSet[0].KeyJump 				= SDLK_w;
	s.WormSet[0].KeyLeft	 			= SDLK_a;
	s.WormSet[0].KeyMine 				= SDLK_s;
	s.WormSet[0].KeyRight 				= SDLK_d;
	s.WormSet[0].KeyPickDropItem		= SDLK_TAB;
	s.WormSet[0].KeyNextItem			= SDLK_LSHIFT;
	s.WormSet[0].KeyUseItem				= SDLK_LCTRL;

	setName(0, "Trottel");


	//////////////////////////////
	//Second Player
	//////////////////////////////

	s.WormSet[1].KeyJump 				= SDLK_UP;
	s.WormSet[1].KeyLeft	 			= SDLK_LEFT;
	s.WormSet[1].KeyMine 				= SDLK_DOWN;
	s.WormSet[1].KeyRight 				= SDLK_RIGHT;
	s.WormSet[1].KeyPickDropItem		= SDLK_RETURN;
	s.WormSet[1].KeyNextItem			= SDLK_RSHIFT;
	s.WormSet[1].KeyUseItem				= SDLK_RCTRL;

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

void CSettings::SaveWorldToFile	(std::string sFilename, CGame * pGame) {

	FILE * pFile;
	pFile = fopen((sFilename+".world").c_str(), "w");
	if (pFile == NULL) {
		g_pLogfile->FunctionResult("CSettings::SaveWorldToFile", L_FAIL,
				("error while opening "+sFilename));
		return;
	}
	//Header:
	fwrite(pFile, formatVersion);
	fwrite(pFile, pGame->m_Gameboard.size());

	std::map<CBlockKoord,CBlock*>::iterator Mit;

	for (Mit = pGame->m_Gameboard.begin(); Mit != pGame->m_Gameboard.end(); ++Mit) {
		fwrite(pFile, Mit->first);
		fwrite(pFile, *(Mit->second));
	}

	fclose(pFile);


	//TODO: find a way to save the items!
	//Header:
	/*
	fwrite(pFile, formatVersion);
	fwrite(pFile, pGame->m_pItems.size());

	pFile = fopen((sFilename+".items").c_str(), "w");
	std::list<CItem*>::iterator Iit;

	for (Iit = pGame->m_pItems.begin(); Iit != pGame->m_pItems.end(); ++Iit) {
		fwrite(pFile,(*Iit));
	}

	fclose(pFile);
	*/

}


bool CSettings::LoadWorldFromFile	(std::string sFilename, CGame * pGame) {
	FILE * pFile;
	pFile = fopen((sFilename+".world").c_str(), "r");
	if (pFile == NULL) {
		g_pLogfile->FunctionResult("CSettings::LoadWorldFromFile", L_FAIL,
				("error while opening "+sFilename));
		return false;
	}

	int version;
	version = fread(pFile);
	if (version != formatVersion) {//wrong format!
		return false;
	}

	long size;
	size = fread(pFile);


	pair<CBlockKoord, CBlock*> Gamefield;
	for (long i = 0; i < size; ++i) {
		CBlockKoord pos = fread(pFile);
		CBlock block = fread(pFile);
		Gamefield = make_pair( pos, new CBlock(block));//ion heap kopieren!

		pGame->m_Gameboard.insert(Gamefield);
	}





	fclose(pFile);

	return true;
}


