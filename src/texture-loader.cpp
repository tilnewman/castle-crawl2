// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// texture-loader.cpp
//
#include "texture-loader.hpp"

#include "context.hpp"
#include "game-config.hpp"
#include "util.hpp"

#include <algorithm>
#include <iostream>
#include <locale>
#include <sstream>
#include <vector>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Image.hpp>

namespace util
{

    bool TextureLoader::load(
        sf::Texture & t_texture, const std::string & t_pathStr, const bool t_willSmooth)
    {
        if (t_texture.loadFromFile(t_pathStr))
        {
            t_texture.setSmooth(t_willSmooth);

            TextureRecord & record = m_pathRecordtMap[t_pathStr];
            ++record.loads;
            record.size = t_texture.getSize();

            return true;
        }
        else
        {
            // SFML already prints a very nice message including paths upon failure

            static const sf::Image image({ 64, 64 }, sf::Color::Red);
            if (!t_texture.loadFromImage(image))
            {
                std::clog << "Not even the default solid red image could be loaded!\n";
            }

            return false;
        }
    }

    void TextureLoader::dumpInfo(const castlecrawl::Context & t_context)
    {
        std::ostringstream ss;
        ss.imbue(std::locale("")); // this is only to put commas in the big numbers

        struct Record
        {
            std::string path{};
            std::size_t loads{ 0 };
            sf::Vector2u size{};
            std::size_t memory_bytes{ 0 };
            std::size_t file_bytes{ 0 };
        };

        std::vector<Record> records;
        records.reserve(m_pathRecordtMap.size());

        std::size_t totalLoadCount        = 0;
        std::size_t uniqueMemoryByteCount = 0;
        std::size_t uniqueFileByteCount   = 0;
        std::size_t longestFilename       = 0;
        for (const auto & pathCountPair : m_pathRecordtMap)
        {
            totalLoadCount += pathCountPair.second.loads;

            const std::size_t memoryBytes = static_cast<std::size_t>(
                pathCountPair.second.size.x * pathCountPair.second.size.y *
                (t_context.config.video_mode.bitsPerPixel / 8u));

            uniqueMemoryByteCount += (memoryBytes * pathCountPair.second.loads);

            std::error_code errorCode;

            uintmax_t fileSizeBytes =
                std::filesystem::file_size(std::filesystem::path(pathCountPair.first), errorCode);

            if (errorCode)
            {
                fileSizeBytes = 0;
            }

            uniqueFileByteCount += (fileSizeBytes * pathCountPair.second.loads);

            const std::filesystem::path path{ pathCountPair.first };
            const std::size_t filenameLength = path.filename().string().size();
            if (filenameLength > longestFilename)
            {
                longestFilename = filenameLength;
            }

            Record record;
            record.path         = pathCountPair.first;
            record.loads        = pathCountPair.second.loads;
            record.size         = pathCountPair.second.size;
            record.memory_bytes = memoryBytes;
            record.file_bytes   = fileSizeBytes;
            records.push_back(record);
        }

        ss << m_pathRecordtMap.size() << " textures (" << (uniqueMemoryByteCount / 1'000_st)
           << "k in memeory)  (" << (uniqueFileByteCount / 1'000_st) << "k on disk) were loaded "
           << totalLoadCount << " times:";

        std::clog << ss.str() << '\n';

        std::sort(std::begin(records), std::end(records), [](const Record & a, const Record & b) {
            return (a.memory_bytes < b.memory_bytes);
        });

        ss.str("");
        for (const Record & record : records)
        {
            const std::filesystem::path path{ record.path };
            std::string filename = path.filename().string();
            filename += std::string((longestFilename - filename.size()), ' ');

            ss << '\t' << filename << '\t' << record.size.x << 'x' << record.size.y << "\t\t"
               << (record.memory_bytes / 1000_st) << "k\t " << '\t' << record.file_bytes << "\t\tx"
               << record.loads << '\n';
        }

        std::clog << ss.str() << '\n';
    }

} // namespace util
