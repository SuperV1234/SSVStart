/* The MIT License (MIT)
 * Copyright (c) 2012 Vittorio Romeo
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef UTILS_H_SSVS
#define UTILS_H_SSVS

#include <math.h>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Timeline/Timeline.h"
#include <SFML/Graphics.hpp>

namespace ssvs
{
	namespace Utils
	{
		// std::string
		template<typename T> std::string toStr(const T &mValue) { std::ostringstream oss; oss << mValue; return std::string(oss.str()); }
		int countNewLines(const std::string& mString);
		std::string replace(const std::string& mString, const std::string& mFrom, const std::string& mTo);
		bool endsWith(const std::string &mString, const std::string &mEnding);
		std::string toLower(const std::string &mString);

		// Collections
		template<typename T, typename V> void eraseRemove(T& mItems, const V& mValue) { mItems.erase(std::remove(std::begin(mItems), std::end(mItems), mValue), std::end(mItems)); }

		// std::map
		template<typename K, typename V>std::vector<K> getKeys(std::map<K, V> mMap)
		{
			std::vector<K> result;
			for(auto itr = mMap.begin(); itr != mMap.end(); ++itr) result.push_back(itr->first);
			return result;
		}

		// Maths
		template<typename T> constexpr int getSign(const T& mValue) { return mValue > 0 ? 1 : -1; }
		template<typename T> constexpr T clamp(const T& mValue, const T& mLow, const T& mHigh) { return mValue < mLow ? mLow : (mValue > mHigh ? mHigh : mValue); }
		float getSaturated(float);
		float getSmootherStep(float, float, float);

		// Angles
		template<typename T> constexpr T toRadians(const T& mValue) { return mValue / 57.3f; }
		template<typename T> constexpr T toDegrees(const T& mValue) { return mValue * 57.3f; }
		template<typename T> T wrapRadians(const T& mValue) { T result = fmod(mValue, 6.28f); if (result < 0) result += 6.28f; return result; }
		template<typename T> T wrapDegrees(const T& mValue) { T result = fmod(mValue, 360.f); if (result < 0) result += 360.f; return result; }
		template<typename T> T getRadiansToPoint(const sf::Vector2<T>& mStart, const sf::Vector2<T>& mEnd) { return atan2(mEnd.y - mStart.y, mEnd.x - mStart.x); }
		template<typename T> T getDegreesToPoint(const sf::Vector2<T>& mStart, const sf::Vector2<T>& mEnd) { return toDegrees(atan2(mEnd.y - mStart.y, mEnd.x - mStart.x)); }
		template<typename T, typename J> T getRotatedRadians(const T& mStart, const T& mEnd, const J& mSpeed) { T start = wrapRadians(mStart), end = wrapRadians(mEnd); if (abs(start - end) < mSpeed) return end; return wrapRadians(start + (sin(end - start))*mSpeed); }
		template<typename T, typename J> T getRotatedDegrees(const T& mStart, const T& mEnd, const J& mSpeed) { T start = wrapDegrees(mStart), end = wrapDegrees(mEnd); if (abs(start - end) < mSpeed) return end; return wrapDegrees(start + (sin((end - start)/57.3f))*mSpeed); }

		// Random
		int getRnd(int, int);

		// Collision
		bool isPointInPolygon(std::vector<sf::Vector2f*>, sf::Vector2f);

		// Vectors
		sf::Vector2f getOrbit(const sf::Vector2f&, const float, const float);
		sf::Vector2f getNormalized(const sf::Vector2f);
		void movePointTowardsCenter(sf::Vector2f &mVector, const sf::Vector2f mCenter, const float mSpeed);

		// Timelines
		void clearAndResetTimeline(Timeline& mTimeline);
	}
}

#endif /* UTILS_H_SSVS */
