// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_GAMESYSTEM_TIMERS_BASE
#define SSVS_GAMESYSTEM_TIMERS_BASE

#include <SFML/System.hpp>
#include "SSVStart/Global/Typedefs.hpp"

namespace ssvs
{
	class GameWindow;

	class TimerBase
	{
		protected:
			GameWindow& gameWindow;
			sf::Clock clock;
			FT frameTime{0};
			float fps{0};

		public:
			TimerBase(GameWindow& mGameWindow) : gameWindow(mGameWindow) { }
			virtual ~TimerBase() { }

			inline virtual void runUpdate()		{ }
			inline virtual void runFrameTime()	{ frameTime = clock.restart().asSeconds() * 60.f; }
			inline virtual void runFps()		{ fps = 60.f / frameTime; }
			virtual void runDraw();

			inline FT getFrameTime() const noexcept	{ return frameTime; }
			inline float getFps() const noexcept	{ return fps; }
	};
}

#endif
