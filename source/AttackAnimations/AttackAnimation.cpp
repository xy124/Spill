#include "AttackAnimation.hpp"
#include "../Timer.hpp"

void CAttackAnimation::init(float liveTime) {
	m_fKillTime = g_pTimer->now() + liveTimer;
}

bool CAttackAnimation::isAlive() {
	return (g_pTimer->now < m_fKillTime);
}

