/*
 * Texture.cpp
 *
 *  Created on: 13.05.2011
 *      Author: Sebastian
 */

#include "Texture.hpp"

#include "Framework.hpp"
#include "Logfile.hpp"

using namespace std;

void CTexture::Load(const string sFilename) {
	m_pSurface = SDL_LoadBMP(sFilename.c_str());
	if (m_pSurface == NULL) {
		string describtion("Error while Loading "+sFilename);
		describtion = describtion + SDL_GetError();
		g_pLogfile->FunctionResult("CTexture::Load", L_FAIL, describtion);

		g_pFramework->Quit();

		exit(1);
	}
	SDL_DisplayFormat(m_pSurface);
}

CTexture::~CTexture() {
	SDL_FreeSurface(m_pSurface);
}
