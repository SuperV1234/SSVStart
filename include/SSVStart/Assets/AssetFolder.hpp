// Copyright (c) 2013-2015 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#pragma once

#include "SSVStart/Global/Typedefs.hpp"

#include <SSVUtils/Core/Log/Log.hpp>
#include <SSVUtils/Core/FileSystem/FileSystem.hpp>
#include <SSVUtils/Core/String/Utils.hpp>

#include <vector>
#include <string>

namespace ssvs
{

template <typename>
class AssetManager;

class AssetFolder
{
private:
    ssvufs::Path rootPath;
    std::vector<ssvufs::Path> files;

    auto getFilteredFiles(const std::vector<std::string>& mExtensions)
    {
        std::vector<ssvufs::Path> result;

        for(const auto& f : files)
            for(const auto& e : mExtensions)
                if(f.hasExtension(e)) result.emplace_back(f);

        return result;
    }

    template <typename T, typename TM>
    void loadImpl(TM& mMgr, const std::vector<std::string>& mExtensions,
        const std::string& mLoTitle)
    {
        for(const auto& f : getFilteredFiles(mExtensions))
        {
            std::string id{ssvu::getReplaced(f, rootPath, "")};
            mMgr.template load<T>(id, f);
            ssvu::lo("ssvs::AssetFolder::" + mLoTitle + "(" +
                     rootPath.getStr() + ")")
                << id + " added\n";
        }
    }

    template <typename TM>
    void loadFontsToManager(TM& mMgr)
    {
        loadImpl<sf::Font>(
            mMgr, {".ttf", ".otf", ".pfm"}, "loadFontsToManager");
    }

    template <typename TM>
    void loadImagesToManager(TM& mMgr)
    {
        loadImpl<sf::Image>(
            mMgr, {".png", ".jpg", ".bmp", ".jpeg"}, "loadImagesToManager");
    }

    template <typename TM>
    void loadTexturesToManager(TM& mMgr)
    {
        loadImpl<sf::Texture>(
            mMgr, {".png", ".jpg", ".bmp", ".jpeg"}, "loadTexturesToManager");
    }

    template <typename TM>
    void loadSoundBuffersToManager(TM& mMgr)
    {
        loadImpl<sf::SoundBuffer>(
            mMgr, {".wav", ".ogg"}, "loadSoundBuffersToManager");
    }

    template <typename TM>
    void loadMusicsToManager(TM& mMgr)
    {
        loadImpl<sf::Music>(mMgr, {".wav", ".ogg"}, "loadMusicsToManager");
    }

    template <typename TM>
    void loadShadersToManager(TM& mMgr)
    {
        for(const auto& f : getFilteredFiles({".vert"}))
        {
            std::string id{ssvu::getReplaced(f, rootPath, "")};
            mMgr.template load<sf::Shader>(
                id, f, sf::Shader::Type::Vertex, Impl::ShaderFromPath{});
            ssvu::lo("ssvs::AssetFolder::loadShadersToManager(" +
                     rootPath.getStr() + ")")
                << id + " vertex shader added\n";
        }

        for(const auto& f : getFilteredFiles({".frag"}))
        {
            std::string id{ssvu::getReplaced(f, rootPath, "")};
            mMgr.template load<sf::Shader>(
                id, f, sf::Shader::Type::Fragment, Impl::ShaderFromPath{});
            ssvu::lo("ssvs::AssetFolder::loadShadersToManager(" +
                     rootPath.getStr() + ")")
                << id + " fragment shader added\n";
        }
    }

public:
    AssetFolder(const ssvufs::Path& mRootPath)
        : rootPath{mRootPath},
          files{ssvufs::getScan<ssvufs::Mode::Recurse, ssvufs::Type::File>(
              rootPath)}
    {
    }

    template <typename TM>
    void loadToManager(TM& mMgr)
    {
        loadImagesToManager(mMgr);
        loadTexturesToManager(mMgr);
        loadSoundBuffersToManager(mMgr);
        loadMusicsToManager(mMgr);
        loadFontsToManager(mMgr);
        loadShadersToManager(mMgr);

        ssvu::lo().flush();
    }
};

} // namespace ssvs
