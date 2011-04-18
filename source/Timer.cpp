#include "Timer.hpp"

CTimer::CTimer(void) {
	//Initialisierung
	m_fCurTime = 0.0f; // na das ist ja mal komsich, das CurTime != LastTime TODO???
	m_fLastTime = SDL_GetTicks() / 1000.0f;
	m_fElapsed = 0.0f;
}

//Updated werte die in CTimer gespeichert sind
void CTimer::Update() {
	m_fCurTime = SDL_GetTicks() / 1000.0f;
	m_fElapsed = m_fCurTime - m_fLastTime;
	m_fLastTime = m_fCurTime;
}





