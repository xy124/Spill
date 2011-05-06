#include "AttackAnimation.hpp"
#include "../Timer.hpp"

void CAttackAnimation::initKillTime(float liveTime) {
	m_fKillTime = g_pTimer->now() + liveTime;
}

bool CAttackAnimation::isAlive() {
	return (g_pTimer->now() < m_fKillTime);
}

