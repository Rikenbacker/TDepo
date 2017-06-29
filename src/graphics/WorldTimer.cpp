#include "WorldTimer.h"



WorldTimer::WorldTimer()
{
	m_startTime = m_timer.getMicroseconds();
}

WorldTimer::WorldTimer(float newRate)
{
	m_startTime = m_timer.getMicroseconds();
	m_timeSpeedRate = newRate;
}

WorldTimer::~WorldTimer()
{
}

unsigned long WorldTimer::tick()
{
	unsigned long endTime = m_timer.getMicroseconds();
	if (endTime < m_startTime)
		endTime = m_startTime;
	m_lastTicks = double(endTime - m_startTime);
	m_lastSecundes = (float)m_lastTicks / 1000000.0 * m_timeSpeedRate;
	m_startTime = endTime;

	return m_lastTicks;
}

unsigned long WorldTimer::getLastTicks()
{
	return m_lastTicks;
}

float WorldTimer::getLastSecundes()
{
	return m_lastSecundes;
}

 void WorldTimer::setTimeSpeedRate(float newRate)
{
	m_timeSpeedRate = newRate;
}

 float WorldTimer::getTimeSpeedRate()
{
	return m_timeSpeedRate;
}