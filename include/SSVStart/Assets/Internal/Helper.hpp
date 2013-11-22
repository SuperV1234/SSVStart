// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_ASSETS_INTERNAL_HELPER
#define SSVS_ASSETS_INTERNAL_HELPER

#include <stdexcept>
#include <SSVUtils/Utils/UtilsMakeUnique.hpp>

namespace ssvs
{
	namespace Internal
	{
		enum class Mode{Load, Open, Image, Samples, Shader, BitmapFont, Tileset};

		template<bool> struct ShaderDisambiguationTag {};
		using ShaderFromMemory = ShaderDisambiguationTag<true>;
		using ShaderFromPath = ShaderDisambiguationTag<false>;

		inline void fail(const std::string& mMessage = "") { throw std::runtime_error("Failed to load resource - " + mMessage); }

		template<Mode TT, typename T> struct Helper;
		template<typename T> struct Helper<Mode::Load, T>
		{
			inline static Uptr<T> load(const Path& mPath)
			{
				auto result(std::make_unique<T>());
				if(!result->loadFromFile(mPath)) fail("from path");
				return result;
			}
			inline static Uptr<T> load(const void* mData, std::size_t mSize)
			{
				auto result(std::make_unique<T>());
				if(!result->loadFromMemory(mData, mSize)) fail("from memory");
				return result;
			}
			inline static Uptr<T> load(sf::InputStream& mStream)
			{
				auto result(std::make_unique<T>());
				if(!result->loadFromStream(mStream)) fail("from stream");
				return result;
			}
		};
		template<typename T> struct Helper<Mode::Open, T>
		{
			inline static Uptr<T> load(const Path& mPath)
			{
				auto result(std::make_unique<T>());
				if(!result->openFromFile(mPath)) fail("from open path");
				return result;
			}
			inline static Uptr<T> load(const void* mData, std::size_t mSize)
			{
				auto result(std::make_unique<T>());
				if(!result->openFromMemory(mData, mSize)) fail("from open memory");
				return result;
			}
			inline static Uptr<T> load(sf::InputStream& mStream)
			{
				auto result(std::make_unique<T>());
				if(!result->openFromStream(mStream)) fail("from open stream");
				return result;
			}
		};
		template<> struct Helper<Mode::Image, sf::Texture>
		{
			using T = sf::Texture;
			inline static Uptr<T> load(const sf::Image& mImage)
			{
				auto result(std::make_unique<T>());
				if(!result->loadFromImage(mImage)) fail("from image");
				return result;
			}
		};
		template<> struct Helper<Mode::Samples, sf::SoundBuffer>
		{
			using T = sf::SoundBuffer;
			inline static Uptr<T> load(const sf::Int16* mSamples, std::size_t mSampleCount, unsigned int mChannelCount, unsigned int mSampleRate)
			{
				auto result(std::make_unique<T>());
				if(!result->loadFromSamples(mSamples, mSampleCount, mChannelCount, mSampleRate)) fail("from samples");
				return result;
			}
		};
		template<> struct Helper<Mode::Shader, sf::Shader>
		{
			using T = sf::Shader;
			inline static Uptr<T> load(const Path& mPath, sf::Shader::Type mType, ShaderFromPath)
			{
				auto result(std::make_unique<T>());
				if(!result->loadFromFile(mPath, mType)) fail("shader from path");
				return result;
			}
			inline static Uptr<T> load(const Path& mPathVertex, const Path& mPathFragment, ShaderFromPath)
			{
				auto result(std::make_unique<T>());
				if(!result->loadFromFile(mPathVertex, mPathFragment)) fail("shader from path (2)");
				return result;
			}
			inline static Uptr<T> load(const std::string& mShader, sf::Shader::Type mType, ShaderFromMemory)
			{
				auto result(std::make_unique<T>());
				if(!result->loadFromMemory(mShader, mType)) fail("shader from memory");
				return result;
			}
			inline static Uptr<T> load(const std::string& mShaderVertex, const std::string& mShaderFragment, ShaderFromMemory)
			{
				auto result(std::make_unique<T>());
				if(!result->loadFromMemory(mShaderVertex, mShaderFragment)) fail("shader from memory (2)");
				return result;
			}
			inline static Uptr<T> load(sf::InputStream& mStream, sf::Shader::Type mType)
			{
				auto result(std::make_unique<T>());
				if(!result->loadFromStream(mStream, mType)) fail("shader from stream");
				return result;
			}
			inline static Uptr<T> load(sf::InputStream& mStreamVertex, sf::InputStream& mStreamFragment)
			{
				auto result(std::make_unique<T>());
				if(!result->loadFromStream(mStreamVertex, mStreamFragment)) fail("shader from stream (2)");
				return result;
			}
		};
		template<> struct Helper<Mode::BitmapFont, BitmapFont>
		{
			using T = BitmapFont;
			inline static Uptr<T> load(const sf::Texture& mTexture, const BitmapFontData& mData)
			{
				return std::make_unique<T>(mTexture, mData);
			}
		};
		template<> struct Helper<Mode::Tileset, Tileset>
		{
			using T = Tileset;
			inline static Uptr<T> load(const Tileset& mTileset) { return std::make_unique<T>(mTileset); }

			#ifndef SSVS_N_USE_JSON
				inline static Uptr<T> load(const Path& mPath) { return std::make_unique<T>(ssvuj::as<Tileset>(ssvuj::readFromFile(mPath))); }
			#endif
		};
	}
}

#endif