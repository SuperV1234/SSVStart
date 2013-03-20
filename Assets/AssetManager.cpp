// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#include <SSVUtils/SSVUtils.h>
#include "Assets/AssetManager.h"
#include "Assets/AssetFolder.h"

using namespace std;
using namespace sf;
using namespace ssvu;

namespace ssvs
{
	AssetManager::~AssetManager()
	{
		for(auto& pair : images) delete pair.second;
		for(auto& pair : textures) delete pair.second;
		for(auto& pair : soundBuffers) delete pair.second;
		for(auto& pair : sounds) delete pair.second;
		for(auto& pair : musics) delete pair.second;
	}

	void AssetManager::loadFolder(const std::string& mPath) { AssetFolder folder{mPath}; folder.loadToManager(*this); }
	void AssetManager::loadFont(const string& mId, const string& mPath)
	{
		Font* font{new Font}; font->loadFromFile(mPath); fonts[mId] = font;
		log(mId + " font added", "loadFonts");
	}
	void AssetManager::loadImage(const string& mId, const string& mPath)
	{
		Image* image{new Image}; image->loadFromFile(mPath); images[mId] = image;
		log(mId + " image added", "loadImages");
		Texture* texture{new Texture}; texture->loadFromImage(*image); textures[mId] = texture;
		log(mId + " texture added", "loadImages");
	}
	void AssetManager::loadSound(const string& mId, const string& mPath)
	{
		SoundBuffer* soundBuffer{new SoundBuffer}; soundBuffer->loadFromFile(mPath); soundBuffers[mId] = soundBuffer;
		log(mId + " soundBuffer added", "loadSound");
		Sound* sound{new Sound{*soundBuffer}}; sounds[mId] = sound;
		log(mId + " sound added", "loadSound");
	}
	void AssetManager::loadMusic(const string& mId, const string& mPath)
	{
		Music* music{new Music}; music->openFromFile(mPath); musics[mId] = music;
		log(mId + " music added", "loadMusic");
	}

	Font& AssetManager::getFont(const string& mId)
	{
		#ifndef SSVS_RELEASE
			if(fonts.count(mId) == 0) log(mId + " font doesn't exist", "getFont");
		#endif
		
		return *fonts[mId];
	}
	Texture& AssetManager::getTexture(const string& mId)
	{
		#ifndef SSVS_RELEASE
			if(textures.count(mId) == 0) log(mId + " texture doesn't exist", "getTexture");
		#endif

		return *textures[mId];
	}
	Sound& AssetManager::getSound(const string& mId)
	{
		#ifndef SSVS_RELEASE
			if(sounds.count(mId) == 0) log(mId + " sound doesn't exist", "getSound");
		#endif

		return *sounds[mId];
	}
	Music& AssetManager::getMusic(const string& mId)
	{
		#ifndef SSVS_RELEASE
			if(musics.count(mId) == 0) log(mId + " music doesn't exist", "getMusic");
		#endif

		return *musics[mId];
	}

	map<string, Font*>& AssetManager::getFonts()				{ return fonts; }
	map<string, Image*>& AssetManager::getImages()				{ return images; }
	map<string, Texture*>& AssetManager::getTextures()			{ return textures; }
	map<string, SoundBuffer*>& AssetManager::getSoundBuffers() 	{ return soundBuffers; }
	map<string, Sound*>& AssetManager::getSounds()				{ return sounds; }
	map<string, Music*>& AssetManager::getMusics()				{ return musics; }

	void AssetManager::stopSounds() { for(auto& pair : sounds) pair.second->stop(); }
}

