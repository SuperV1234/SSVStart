// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#include <SSVUtils/SSVUtils.h>
#include "SSVStart/Assets/AssetManager.h"
#include "SSVStart/Assets/AssetFolder.h"

using namespace std;
using namespace sf;
using namespace ssvu;
using namespace ssvu::FileSystem;

namespace ssvs
{
	AssetFolder::AssetFolder(const string& mRootPath) : rootPath{mRootPath}, files{getScan<Mode::Recurse, Type::File>(rootPath)} { }
	void AssetFolder::loadToManager(AssetManager& mAssetManager)
	{
		loadImagesToManager(mAssetManager);
		loadTexturesToManager(mAssetManager);
		loadSoundBuffersToManager(mAssetManager);
		loadMusicsToManager(mAssetManager);
		loadFontsToManager(mAssetManager);
		loadShadersToManager(mAssetManager);
	}

	vector<string> AssetFolder::getFilteredFiles(const vector<string>& mExtensions)
	{
		vector<string> result;
		for(const auto& f : files) for(const auto& e : mExtensions) if(hasExtension(f, e)) result.push_back(f);
		return result;
	}
	void AssetFolder::loadFontsToManager(AssetManager& mAssetManager)
	{
		for(const auto& f : getFilteredFiles({".ttf", ".otf", ".pfm"}))
		{
			string id{getReplaced(f, rootPath, "")};
			mAssetManager.loadFont(id, f);
			log(id + " font added", "ssvs::AssetFolder::loadFontsToManager(" + rootPath + ")");
		}
	}
	void AssetFolder::loadImagesToManager(AssetManager& mAssetManager)
	{
		for(const auto& f : getFilteredFiles({".png", ".jpg", ".bmp", ".jpeg"}))
		{
			string id{getReplaced(f, rootPath, "")};
			mAssetManager.loadImage(id, f);
			log(id + " image added", "ssvs::AssetFolder::loadImagesToManager(" + rootPath + ")");
		}
	}
	void AssetFolder::loadTexturesToManager(AssetManager& mAssetManager)
	{
		for(const auto& f : getFilteredFiles({".png", ".jpg", ".bmp", ".jpeg"}))
		{
			string id{getReplaced(f, rootPath, "")};
			mAssetManager.loadTexture(id, f);
			log(id + " texture added", "ssvs::AssetFolder::loadTexturesToManager(" + rootPath + ")");
		}
	}
	void AssetFolder::loadSoundBuffersToManager(AssetManager& mAssetManager)
	{
		for(const auto& f : getFilteredFiles({".wav", ".ogg"}))
		{
			string id{getReplaced(f, rootPath, "")};
			mAssetManager.loadSoundBuffer(id, f);
			log(id + " soundBuffer added", "ssvs::AssetFolder::loadSoundsToManager(" + rootPath + ")");
		}
	}
	void AssetFolder::loadMusicsToManager(AssetManager& mAssetManager)
	{
		for(const auto& f : getFilteredFiles({".wav", ".ogg"}))
		{
			string id{getReplaced(f, rootPath, "")};
			mAssetManager.loadMusic(id, f);
			log(id + " music added", "ssvs::AssetFolder::loadMusicsToManager(" + rootPath + ")");
		}
	}
	void AssetFolder::loadShadersToManager(AssetManager& mAssetManager)
	{
		for(const auto& f : getFilteredFiles({".vert"}))
		{
			string id{getReplaced(f, rootPath, "")};
			mAssetManager.loadShader(id, f, Shader::Type::Vertex, Internal::ShaderFromPath{});
			log(id + " vertex shader added", "ssvs::AssetFolder::loadShadersToManager(" + rootPath + ")");
		}
		for(const auto& f : getFilteredFiles({".frag"}))
		{
			string id{getReplaced(f, rootPath, "")};
			mAssetManager.loadShader(id, f, Shader::Type::Fragment, Internal::ShaderFromPath{});
			log(id + " fragment shader added", "ssvs::AssetFolder::loadShadersToManager(" + rootPath + ")");
		}
	}
}

