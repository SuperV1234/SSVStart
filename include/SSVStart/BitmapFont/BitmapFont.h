// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_BITMAPFONT
#define SSVS_BITMAPFONT

#include <SFML/Graphics.hpp>
#include "SSVStart/BitmapFont/BitmapFontData.h"

namespace ssvs
{
	class BitmapFont
	{
		private:
			const sf::Texture& texture;
			BitmapFontData data;

		public:
			BitmapFont(const sf::Texture& mTexture, const BitmapFontData& mData);

			const sf::Texture& getTexture() const;
			sf::IntRect getGlyphRect(char mChar) const;
			unsigned int getCellWidth() const;
			unsigned int getCellHeight() const;
	};
}

#endif