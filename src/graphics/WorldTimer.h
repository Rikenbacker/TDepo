#pragma once

class WorldTimer
{
	public:
		WorldTimer();
		WorldTimer(float newRate);
		~WorldTimer();

		unsigned long tick();
		unsigned long getLastTicks();
		float getLastSecundes();

		float getTimeSpeedRate();
		void setTimeSpeedRate(float newRate);

	private:
//		Ogre::Timer m_timer;
		unsigned long m_startTime;
		unsigned long m_lastTicks = 0;
		float m_lastSecundes = 0;
		float m_timeSpeedRate = 1.0;
};

