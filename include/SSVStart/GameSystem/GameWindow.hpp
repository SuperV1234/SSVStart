// Copyright (c) 2013-2014 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_GAMESYSTEM_GAMEWINDOW
#define SSVS_GAMESYSTEM_GAMEWINDOW

#include "SSVStart/Input/InputState.hpp"

namespace ssvs
{
	class GameWindow : ssvu::NoCopy
	{
		private:
			Input::InputState inputState;
			ssvu::Uptr<GameEngine> gameEngine{new GameEngine()}; // TODO: should the user create a GameEngine?
			sf::RenderWindow renderWindow;
			std::string title;
			FT msUpdate, msDraw;
			float maxFPS{60.f}, pixelMult{1.f};
			unsigned int width{640}, height{480}, antialiasingLevel{3};
			bool fpsLimited{false}, focus{true}, mustRecreate{true}, vsync{false}, fullscreen{false};

			inline void runEvents()
			{
				SSVU_ASSERT(gameEngine != nullptr);

				sf::Event event;
				while(renderWindow.pollEvent(event))
				{
					switch(event.type)
					{
						case sf::Event::Closed:					gameEngine->stop();											break;
						case sf::Event::GainedFocus:			focus = true;												break;
						case sf::Event::LostFocus:	inputState.reset();	focus = false;												break;
						case sf::Event::KeyPressed:				inputState.setKeyPressed(event.key.code, true);				break;
						case sf::Event::KeyReleased:			inputState.setKeyPressed(event.key.code, false);			break;
						case sf::Event::MouseButtonPressed:		inputState.setBtnPressed(event.mouseButton.button, true);	break;
						case sf::Event::MouseButtonReleased:	inputState.setBtnPressed(event.mouseButton.button, false);	break;
						default:																							break;
					}

					gameEngine->handleEvent(event);
				}
			}

			inline void recreateWindow()
			{
				if(renderWindow.isOpen()) renderWindow.close();
				inputState.reset();

				renderWindow.create({width, height}, title, fullscreen ? sf::Style::Fullscreen : sf::Style::Default, sf::ContextSettings{0, 0, antialiasingLevel, 0, 0});
				renderWindow.setSize(Vec2u(width * pixelMult, height * pixelMult));
				renderWindow.setVerticalSyncEnabled(vsync);
				mustRecreate = false; onRecreation();
			}

		public:
			ssvu::Delegate<void()> onRecreation;

			inline GameWindow() { gameEngine->setInputState(inputState); }

			inline void run()
			{
				SSVU_ASSERT(gameEngine != nullptr);

				while(gameEngine->isRunning())
				{
					if(mustRecreate) recreateWindow();

					renderWindow.setActive(true);
					this->clear();

					gameEngine->refreshTimer();

					auto tempMs(HRClock::now());
					{
						runEvents();
						gameEngine->runUpdate();
					}
					msUpdate = std::chrono::duration_cast<FTDuration>(HRClock::now() - tempMs).count();

					tempMs = HRClock::now();
					{
						gameEngine->runDraw();
						renderWindow.display();
					}
					msDraw = std::chrono::duration_cast<FTDuration>(HRClock::now() - tempMs).count();

					gameEngine->runFPS();
				}
			}
			inline void stop() noexcept
			{
				SSVU_ASSERT(gameEngine != nullptr);
				gameEngine->stop();
			}

			inline void clear(const sf::Color& mColor = sf::Color::Transparent) { renderWindow.clear(mColor); }
			inline void draw(const sf::Drawable& mDrawable, const sf::RenderStates& mStates = sf::RenderStates::Default) { renderWindow.draw(mDrawable, mStates); }

			inline void saveScreenshot(const ssvufs::Path& mPath) const { renderWindow.capture().saveToFile(mPath); }

			inline void setFullscreen(bool mFullscreen) noexcept					{ fullscreen = mFullscreen;			mustRecreate = true; }
			inline void setSize(unsigned int mWidth, unsigned int mHeight) noexcept	{ width = mWidth; height = mHeight;	mustRecreate = true; }
			inline void setAntialiasingLevel(unsigned int mLevel) noexcept			{ antialiasingLevel = mLevel;		mustRecreate = true; }
			inline void setVsync(bool mEnabled) noexcept							{ vsync = mEnabled;					mustRecreate = true; }
			inline void setPixelMult(float mPixelMult) noexcept						{ pixelMult = mPixelMult;			mustRecreate = true; }

			inline void setMouseCursorVisible(bool mEnabled)						{ renderWindow.setMouseCursorVisible(mEnabled); }
			inline void setTitle(std::string mTitle)								{ title = std::move(mTitle); renderWindow.setTitle(mTitle); }
			inline void setMaxFPS(float mMaxFPS)									{ maxFPS = mMaxFPS; renderWindow.setFramerateLimit(fpsLimited ? maxFPS : 0); }
			inline void setFPSLimited(bool mFPSLimited)								{ fpsLimited = mFPSLimited; renderWindow.setFramerateLimit(fpsLimited ? maxFPS : 0); }
			inline void setGameState(GameState& mGameState) noexcept				{ gameEngine->setGameState(mGameState); }

			inline operator sf::RenderWindow&() noexcept				{ return renderWindow; }
			inline sf::RenderWindow& getRenderWindow() noexcept			{ return renderWindow; }
			inline bool getFullscreen() const noexcept					{ return fullscreen; }
			inline unsigned int getWidth() const noexcept				{ return width; }
			inline unsigned int getHeight() const noexcept				{ return height; }
			inline unsigned int getAntialiasingLevel() const noexcept	{ return antialiasingLevel; }
			inline bool hasFocus() const noexcept						{ return focus; }
			inline bool getVsync() const noexcept						{ return vsync; }

			inline FT getMsUpdate() const noexcept						{ return msUpdate; }
			inline FT getMsDraw() const noexcept						{ return msDraw; }

			inline Vec2f getMousePosition() const							{ return renderWindow.mapPixelToCoords(sf::Mouse::getPosition(renderWindow)); }
			inline const Input::InputState& getInputState() const noexcept	{ return inputState; }

			template<typename T, typename... TArgs> inline void setTimer(TArgs&&... mArgs) { gameEngine->setTimer<T, TArgs...>(std::forward<TArgs>(mArgs)...); }
			inline auto getFPS() const noexcept -> decltype(gameEngine->getFPS()) { return gameEngine->getFPS(); }
	};
}

#endif
