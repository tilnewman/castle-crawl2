#ifndef SOUND_PLAYER_HPP_INCLUDED
#define SOUND_PLAYER_HPP_INCLUDED
//
// sound-player.hpp
//
#include "random.hpp"

#include <filesystem>
#include <memory>
#include <string>
#include <vector>

#include <SFML/Audio.hpp>

namespace util
{
    class SoundPlayer
    {
      public:
        explicit SoundPlayer(const Random & random, const std::string & pathStr = {});

        void reset();

        void setMediaPath(const std::string & pathStr);

        void play(const std::string & name, const float pitch = 1.0f);

        void stop(const std::string & name);
        void stopAll();
        void loadAll();

        bool load(const std::initializer_list<std::string> & names);
        bool load(const std::string & name);

        void volume(const float newVolume);
        void volumeUp();
        void volumeDown();
        [[nodiscard]] inline float volume() const { return m_volume; }

        void muteButton();
        [[nodiscard]] inline bool isMuted() const { return m_isMuted; }

      private:
        [[nodiscard]] std::vector<std::size_t>
            findCacheIndexesByName(const std::string & name) const;

        bool loadFiles(const std::string & nameMustMatch = "");

        bool loadFile(
            const std::filesystem::directory_entry & entry, const std::string & nameMustMatch = "");

        bool willLoad(const std::filesystem::directory_entry & entry) const;

        struct SoundEffect
        {
            [[nodiscard]] std::string toString() const;

            std::string filename{};
            sf::SoundBuffer buffer{};
            sf::Sound sound{ buffer };
        };

      private:
        const Random & m_random;
        std::string m_pathStr;

        bool m_isMuted;

        float m_volume;
        float m_volumeMin;
        float m_volumeMax;
        float m_volumeInc;

        std::string m_fileExtensions;
        std::vector<std::unique_ptr<SoundEffect>> m_soundEffects;
    };
} // namespace util

#endif // SOUND_PLAYER_HPP_INCLUDED
