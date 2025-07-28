#ifndef TEXTURE_LOADER_HPP_INCLUDED
#define TEXTURE_LOADER_HPP_INCLUDED
//
// texture-loader.hpp
//
#include <filesystem>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace util
{

    struct Counts
    {
        std::size_t loads{ 0 };
        std::size_t bytes{ 0 };
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

                const std::size_t byteCount =
                    static_cast<std::size_t>(t_texture.getSize().x * t_texture.getSize().y * 4u);

                Counts & counts = m_pathCountMap[t_pathStr];
                ++counts.loads;
                counts.bytes = byteCount;
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

            std::size_t totalLoadCount  = 0;
            std::size_t totalByteCount  = 0;
            std::size_t uniqueByteCount = 0;
            for (const auto & pathCountPair : m_pathCountMap)
            {
                totalLoadCount += pathCountPair.second.loads;
                totalByteCount += (pathCountPair.second.loads * pathCountPair.second.bytes);
                uniqueByteCount += pathCountPair.second.bytes;
            }

            ss << totalLoadCount << " loads of " << m_pathCountMap.size()
               << " unqiue texture files, and " << totalByteCount << "bytes loaded with "
               << uniqueByteCount << "bytes being unique.";

            std::clog << ss.str() << '\n';
        }

      private:
        static inline std::map<std::string, Counts> m_pathCountMap;
    };

} // namespace util

#endif // TEXTURE_LOADER_HPP_INCLUDED
