#ifndef _TIMER_HPP_
#define _TIMER_HPP_

#include <SDL.h>
#include "Singleton.hpp"

#define g_pTimer CTimer::get()
class CTimer : public TSingleton<CTimer> {
	public:
		CTimer(void);
		void Update();

		//die einzige Variable die nach au�en kommt:
		float getElapsed() {return m_fElapsed;}//YesYes... here you can shit on the second ; after }
	
	private:
		float m_fElapsed; //vergangene zeit seit letztem Frame
		float m_fCurTime; //Aktuelle Zeit
		float m_fLastTime; //Zeit des letzten frame in s
};

#endif
