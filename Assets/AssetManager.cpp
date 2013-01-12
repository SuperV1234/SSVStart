#include "AssetManager.h"
#include "AssetFolder.h"

using namespace std;
using namespace sf;
using namespace ssvs::FileSystem;
using namespace ssvs::Utils;

namespace ssvs
{
	AssetManager::~AssetManager() { uninitImages(); uninitSounds(); uninitMusics(); }

	void AssetManager::loadFolder(const std::string& mPath)
	{
		AssetFolder folder{mPath};
		folder.loadToManager(*this);
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

	inline void AssetManager::uninitImages() { for(auto pair : images) delete pair.second; for(auto pair : textures) delete pair.second; }
	inline void AssetManager::uninitSounds() { for(auto pair : soundBuffers) delete pair.second; for(auto pair : sounds) delete pair.second; }
	inline void AssetManager::uninitMusics() { for(auto pair : musics) delete pair.second; }

	Texture& AssetManager::getTexture(const string& mId) { return *textures[mId]; }
	Sound& AssetManager::getSound(const string& mId) { return *sounds[mId]; }
	Music& AssetManager::getMusic(const string& mId) { return *musics[mId]; }
}
