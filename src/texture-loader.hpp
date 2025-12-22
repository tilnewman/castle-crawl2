#ifndef TEXTURE_LOADER_HPP_INCLUDED
#define TEXTURE_LOADER_HPP_INCLUDED
//
// texture-loader.hpp
//
#include <filesystem>
#include <iostream>
#include <locale>
#include <map>
#include <sstream>
#include <string>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace util
{

    struct TextureCounts
    {
        std::size_t loads{ 0 };
        std::size_t memory_bytes{ 0 };
        std::size_t file_bytes{ 0 };
    };

    class TextureLoader
    {
      public:
        static void load(
            sf::Texture & t_texture,
            const std::filesystem::path & t_path,
            const bool t_willSmooth = false)
        {
            load(t_texture, t_path.string(), t_willSmooth);
        }

        static void load(
            sf::Texture & t_texture, const std::string & t_pathStr, const bool t_willSmooth = false)
        {
            if (t_texture.loadFromFile(t_pathStr))
            {
                t_texture.setSmooth(t_willSmooth);

                TextureCounts & counts = m_pathCountMap[t_pathStr];
                ++counts.loads;

                counts.memory_bytes =
                    static_cast<std::size_t>(t_texture.getSize().x * t_texture.getSize().y * 4u);

                std::error_code errorCode;
                const uintmax_t fileSizeBytes =
                    std::filesystem::file_size(std::filesystem::path(t_pathStr), errorCode);

                if (!errorCode)
                {
                    counts.file_bytes = fileSizeBytes;
                }
            }
            else
            {
                // SFML already prints a very nice message including paths upon failure

                static const sf::Image image({ 64, 64 }, sf::Color::Red);
                if (!t_texture.loadFromImage(image))
                {
                    std::clog << "Not even the default solid red image could be loaded!\n";
                }
            }
        }

        static void dumpInfo()
        {
            std::ostringstream ss;
            ss.imbue(std::locale("")); // this is only to put commas in the big numbers

            std::size_t totalLoadCount        = 0;
            std::size_t uniqueMemoryByteCount = 0;
            std::size_t uniqueFileByteCount   = 0;
            std::size_t longestFilename       = 0;
            for (const auto & pathCountPair : m_pathCountMap)
            {
                totalLoadCount += pathCountPair.second.loads;
                uniqueMemoryByteCount +=
                    (pathCountPair.second.memory_bytes * pathCountPair.second.loads);

                uniqueFileByteCount +=
                    (pathCountPair.second.file_bytes * pathCountPair.second.loads);

                const std::filesystem::path path{ pathCountPair.first };
                const std::size_t filenameLength = path.filename().string().size();
                if (filenameLength > longestFilename)
                {
                    longestFilename = filenameLength;
                }
            }

            ss << m_pathCountMap.size() << " textures (" << (uniqueMemoryByteCount / 1'000_st)
               << "k in memeory)  (" << (uniqueFileByteCount / 1'000_st)
               << "k on disk) were loaded " << totalLoadCount << " times:";

            std::clog << ss.str() << '\n';

            ss.str("");
            for (const auto & pathCountPair : m_pathCountMap)
            {
                const std::filesystem::path path{ pathCountPair.first };
                std::string filename = path.filename().string();
                filename += std::string((longestFilename - filename.size()), ' ');

                ss << '\t' << filename << "\t" << (pathCountPair.second.memory_bytes / 1000_st)
                   << "k\t" << '\t' << pathCountPair.second.file_bytes << "\t\tx"
                   << pathCountPair.second.loads << '\n';
            }

            std::clog << ss.str() << '\n';
        }

      private:
        static inline std::map<std::string, TextureCounts> m_pathCountMap;
    };

} // namespace util

#endif // TEXTURE_LOADER_HPP_INCLUDED
