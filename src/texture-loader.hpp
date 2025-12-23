#ifndef TEXTURE_LOADER_HPP_INCLUDED
#define TEXTURE_LOADER_HPP_INCLUDED
//
// texture-loader.hpp
//
#include <filesystem>
#include <map>
#include <string>

#include <SFML/Graphics/Texture.hpp>

namespace castlecrawl
{
    struct Context;
}

namespace util
{

    struct TextureRecord
    {
        std::size_t loads{ 0 };
        sf::Vector2u size{};
    };

    //

    class TextureLoader
    {
      public:
        static inline bool load(
            sf::Texture & t_texture,
            const std::filesystem::path & t_path,
            const bool t_willSmooth = false)
        {
            return load(t_texture, t_path.string(), t_willSmooth);
        }

        static bool load(
            sf::Texture & t_texture,
            const std::string & t_pathStr,
            const bool t_willSmooth = false);

        static void dumpInfo(const castlecrawl::Context & t_context);

      private:
        static inline std::map<std::string, TextureRecord> m_pathRecordtMap;
    };

} // namespace util

#endif // TEXTURE_LOADER_HPP_INCLUDED
