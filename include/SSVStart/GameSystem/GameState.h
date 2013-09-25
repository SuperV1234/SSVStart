// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_GAMESYSTEM_GAMESTATE
#define SSVS_GAMESYSTEM_GAMESTATE

#include <map>
#include <SSVUtils/SSVUtils.h>
#include <SFML/Window.hpp>
#include "SSVStart/Input/Manager.h"
#include "SSVStart/Input/Trigger.h"
#include "SSVStart/Global/Typedefs.h"

namespace ssvs
{
	class GameWindow;

	class GameState
	{
		friend class GameWindow;

		private:
			using ITrigger = Input::Trigger;
			using IType = ITrigger::Type;
			using IFunc = InputFunc;
			using EventDelegate = ssvu::Delegate<void(const sf::Event&)>;

			GameWindow* gameWindow{nullptr}; // not owned, just pointed to
			Input::Manager inputManager;
			std::map<sf::Event::EventType, EventDelegate> eventDelegates;

			inline void handleEvent(const sf::Event& mEvent)	{ eventDelegates[mEvent.type](mEvent); }
			inline void update(float mFT)				{ onUpdate(mFT); }
			inline void draw()									{ onDraw(); }
			inline void updateInput(float mFT)			{ inputManager.update(*gameWindow, mFT); }
			inline void refreshInput()							{ inputManager.refresh(*gameWindow); }

		public:
			ssvu::Delegate<void()> onDraw, onPostUpdate;
			ssvu::Delegate<void(float)> onUpdate;

			GameState() = default;
			GameState(const GameState&) = delete; // non construction-copyable
			GameState& operator=(const GameState&) = delete; // non copyable

			inline void addInput(ITrigger mTrigger, IFunc mFuncOn, IType mType = IType::Always)					{ mTrigger.setType(mType); inputManager.add({mTrigger, mFuncOn}); }
			inline void addInput(ITrigger mTrigger, IFunc mFuncOn, IFunc mFuncOff, IType mType = IType::Always)	{ mTrigger.setType(mType); inputManager.add({mTrigger, mFuncOn, mFuncOff}); }

			inline EventDelegate& onEvent(sf::Event::EventType mEventType) { return eventDelegates[mEventType]; }
		};
	}

#endif
