// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// sound-player.cpp
//
#include "sound-player.hpp"

#include <algorithm>
#include <iostream>
#include <sstream>

namespace util
{
    SoundPlayer::SoundPlayer(const Random & t_random, const std::string & t_pathStr)
        : m_random(t_random)
        , m_pathStr(t_pathStr)
        , m_isMuted(false)
        , m_volume(0.0f)
        , m_volumeMin(0.0f)                 // this is what sfml uses
        , m_volumeMax(100.0f)               // this is what sfml uses
        , m_volumeInc(m_volumeMax / 10.0f)  // only ten different vol levels possible
        , m_fileExtensions(".ogg.flac.wav") // dots are required here
        , m_soundEffects()
    {
        m_volume = (m_volumeMin + ((m_volumeMax - m_volumeMin) * 0.5f));
    }

    void SoundPlayer::reset()
    {
        stopAll();
        m_soundEffects.clear();
    }

    void SoundPlayer::setMediaPath(const std::string & t_pathStr) { m_pathStr = t_pathStr; }

    void SoundPlayer::play(const std::string & t_name, const float t_pitch)
    {
        if (m_volume < 1.0f)
        {
            return;
        }

        if (t_name.empty())
        {
            std::cerr << "SoundPlayer::play() called with an empty name." << std::endl;
            return;
        }

        std::vector<std::size_t> nameMatchingIndexes(findCacheIndexesByName(t_name));
        if (nameMatchingIndexes.empty())
        {
            std::cout << "SoundPlayer::play(\"" << t_name
                      << "\") called, but none had that name...";

            if (!loadFiles(t_name))
            {
                std::cout << "AND none were found to load either.  So nothing will happen."
                          << std::endl;
                return;
            }

            nameMatchingIndexes = findCacheIndexesByName(t_name);
            if (nameMatchingIndexes.empty())
            {
                std::cout
                    << "AND even though some sound effects with that name were loaded, something "
                       "else went wrong away.  Go figure.  So nothing will happen."
                    << std::endl;

                return;
            }

            std::cout << "BUT was able to find and load it.  So it's gonna play now." << std::endl;
        }

        const std::size_t index(m_random.from(nameMatchingIndexes));
        auto & sfx(m_soundEffects.at(index));

        // if (sfx->sound.getStatus() == sf::SoundSource::Playing)
        //{
        //    return;
        //}

        sfx->sound.setPitch(t_pitch);
        sfx->sound.play();
    }

    void SoundPlayer::stopAll()
    {
        for (auto & sfx : m_soundEffects)
        {
            sfx->sound.stop();
        }
    }

    void SoundPlayer::stop(const std::string & t_name)
    {
        for (const std::size_t index : findCacheIndexesByName(t_name))
        {
            m_soundEffects[index]->sound.stop();
        }
    }

    void SoundPlayer::loadAll()
    {
        reset();
        loadFiles();
    }

    bool SoundPlayer::load(const std::initializer_list<std::string> & t_names)
    {
        bool success{ true };

        for (const std::string & name : t_names)
        {
            if (!load(name))
            {
                success = false;
            }
        }

        return success;
    }

    bool SoundPlayer::load(const std::string & t_name)
    {
        if (t_name.empty())
        {
            std::cerr << "SoundPlayer::load("
                         ") called with an empty name."
                      << std::endl;

            return false;
        }

        if (!findCacheIndexesByName(t_name).empty())
        {
            std::cout << "SoundPlayer::load(\"" << t_name << "\") but already loaded." << std::endl;
            return true;
        }

        loadFiles(t_name);

        return !findCacheIndexesByName(t_name).empty();
    }

    std::vector<std::size_t> SoundPlayer::findCacheIndexesByName(const std::string & t_name) const
    {
        std::vector<std::size_t> indexes;

        for (std::size_t i(0); i < m_soundEffects.size(); ++i)
        {
            const bool startsWith{ m_soundEffects.at(i)->filename.find(t_name, 0) == 0 };
            if (startsWith)
            {
                indexes.push_back(i);
            }
        }

        return indexes;
    }

    void SoundPlayer::volumeUp()
    {
        if (m_isMuted)
        {
            m_isMuted = false;
        }

        volume(m_volumeMin + m_volumeInc);
    }

    void SoundPlayer::volumeDown()
    {
        if (m_isMuted)
        {
            return;
        }

        volume(m_volume - m_volumeInc);
    }

    void SoundPlayer::muteButton()
    {
        m_isMuted = !m_isMuted;

        if (m_isMuted)
        {
            volume(m_volumeMin);
        }
        else
        {
            volume(m_volume);
        }
    }

    void SoundPlayer::volume(const float t_newVolume)
    {
        m_volume = std::clamp(t_newVolume, m_volumeMin, m_volumeMax);

        for (auto & sfx : m_soundEffects)
        {
            sfx->sound.setVolume(m_volume);
        }
    }

    bool SoundPlayer::loadFiles(const std::string & t_nameMustMatch)
    {
        std::filesystem::path path(m_pathStr);
        if (!std::filesystem::exists(path) || !std::filesystem::is_directory(path))
        {
            std::cout << "SoundPlayer::loadFiles(\"" << t_nameMustMatch
                      << "\") called with invalid path=\"" << path
                      << "\", switching to current path=\"" << std::filesystem::current_path()
                      << "\"" << std::endl;

            path = std::filesystem::current_path();
        }

        std::filesystem::recursive_directory_iterator dirIter(path);

        bool success{ false };
        for (const std::filesystem::directory_entry & entry : dirIter)
        {
            if (!willLoad(entry))
            {
                continue;
            }

            if (loadFile(entry, t_nameMustMatch))
            {
                success = true;
            }
        }

        if (!success || m_soundEffects.empty())
        {
            std::cerr << "SoundPlayer Error:  No sound files were found.  Remember that "
                         "MP3s are not supported, only: "
                      << m_fileExtensions << std::endl;

            return false;
        }

        return true;
    }

    bool SoundPlayer::loadFile(
        const std::filesystem::directory_entry & t_entry, const std::string & t_nameMustMatch)
    {
        const std::string filename{ t_entry.path().filename().string() };

        const bool filenameStartsWith{ filename.find(t_nameMustMatch, 0) == 0 };

        if (!t_nameMustMatch.empty() && !filenameStartsWith)
        {
            return false;
        }

        auto sfx(std::make_unique<SoundEffect>());

        if (!sfx->buffer.loadFromFile(t_entry.path().string()))
        {
            std::cerr << "SoundPlayer Error:  Found a supported file: \"" << t_entry.path().string()
                      << "\", but an error occurred while loading it." << std::endl;

            return false;
        }

        sfx->sound.setBuffer(sfx->buffer);

        sfx->filename = filename;

        const bool sfxStartsWith{ sfx->filename.find(t_nameMustMatch, 0) == 0 };

        if (!t_nameMustMatch.empty() && !sfxStartsWith)
        {
            return false;
        }

        if ((m_volume > 0.0f) && !m_isMuted)
        {
            sfx->sound.setVolume(m_volume);
        }
        else
        {
            sfx->sound.setVolume(0.0f);
        }

        // std::cout << "Loaded Sound Effect: " << sfx->toString() << std::endl;
        m_soundEffects.push_back(std::move(sfx));
        return true;
    }

    bool SoundPlayer::willLoad(const std::filesystem::directory_entry & t_entry) const
    {
        if (!t_entry.is_regular_file())
        {
            return false;
        }

        const std::string extension(t_entry.path().filename().extension().string());

        if ((extension.size() != 4) && (extension.size() != 5))
        {
            return false;
        }

        return (m_fileExtensions.find(extension) < m_fileExtensions.size());
    }

    std::string SoundPlayer::SoundEffect::toString() const
    {
        const std::string pad("  ");

        std::ostringstream ss;

        ss << std::setw(20) << std::right;
        ss << filename << pad;

        // duration in seconds
        const auto durationMs(buffer.getDuration().asMilliseconds());
        const double durationSec(static_cast<double>(durationMs) / 1000.0);

        ss << std::setprecision(2) << std::setw(3) << std::setfill('0') << std::fixed;
        ss << durationSec << "s" << pad;

        // channels
        const auto channelCount(buffer.getChannelCount());
        if (1 == channelCount)
        {
            ss << "mono  ";
        }
        else if (2 == channelCount)
        {
            ss << "stereo";
        }
        else
        {
            ss << channelCount << "ch";
        }
        ss << pad;

        // sample rate in kHz
        const auto sampleRateHz(buffer.getSampleRate());
        const double sampleRakeKHz(static_cast<double>(sampleRateHz) / 1000.0);

        ss << std::setprecision(1) << std::setw(1) << std::setfill('0') << sampleRakeKHz << "kHz";

        return ss.str();
    }

} // namespace util
