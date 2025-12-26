#ifndef LOOK_EVENT_HPP_INCLUDED
#define LOOK_EVENT_HPP_INCLUDED
//
// look-event.hpp
//
#include "json-wrapper.hpp"
#include "map-types.hpp"

#include <optional>
#include <string>
#include <vector>

namespace castlecrawl
{

    struct Context;

    //

    struct Stats
    {
        [[nodiscard]] constexpr bool empty() const noexcept
        {
            return ((0 == acc) && (0 == arc) && (0 == dex && 0 == lck) && (0 == str));
        }

        int acc{ 0 };
        int arc{ 0 };
        int dex{ 0 };
        int lck{ 0 };
        int str{ 0 };
    };

    inline void to_json(nlohmann::json & j, const Stats & s)
    {
        j = nlohmann::json{
            { "acc", s.acc }, { "arc", s.arc }, { "dex", s.dex }, { "lck", s.lck }, { "str", s.str }
        };
    }

    inline void from_json(const nlohmann::json & j, Stats & s)
    {
        j.at("acc").get_to(s.acc);
        j.at("arc").get_to(s.arc);
        j.at("dex").get_to(s.dex);
        j.at("lck").get_to(s.lck);
        j.at("str").get_to(s.str);
    }

    //

    struct LookEvent
    {
        [[nodiscard]] constexpr bool empty() const noexcept { return message.empty(); }

        [[nodiscard]] constexpr bool hasRequirements() const noexcept
        {
            return (
                !stats_required.empty() || !item_required.empty() ||
                !item_keyword_required.empty() || (gold_required > 0));
        }

        bool has_happened{ false };
        bool will_always_happen{ false };

        // this is the unique ID for a LookEvent
        MapPos_t map_pos{ invalidMapPos };

        // this message is always displayed and so must not be empty for this event to be valid
        std::string message{};

        // all requirements
        Stats stats_required{};
        std::string item_required{};
        std::string item_keyword_required{};
        int gold_required{ 0 };

        // all bonuses/things given if requirments are met
        std::string message_pass{};
        std::string item_given_pass{};
        int health_adj_pass{ 0 };
        int gold_adj_pass{ 0 };
        Stats stats_adj_pass{};
        bool will_spawn_monster{ false };

        // all consequences if the requirements are NOT met
        std::string message_fail{};
        int health_adj_fail{ 0 };
    };

    using LookEvents_t   = std::vector<LookEvent>;
    using LookEventOpt_t = std::optional<LookEvent>;

    inline void to_json(nlohmann::json & j, const LookEvent & le)
    {
        j = nlohmann::json{ { "has_happened", le.has_happened },
                            { "will_always_happen", le.will_always_happen },
                            { "map_pos_x", le.map_pos.x },
                            { "map_pos_y", le.map_pos.y },
                            { "message", le.message },
                            { "stats_required", le.stats_required },
                            { "item_required", le.item_required },
                            { "item_keyword_required", le.item_keyword_required },
                            { "gold_required", le.gold_required },
                            { "message_pass", le.message_pass },
                            { "item_given_pass", le.item_given_pass },
                            { "health_adj_pass", le.health_adj_pass },
                            { "gold_adj_pass", le.gold_adj_pass },
                            { "stats_adj_pass", le.stats_adj_pass },
                            { "will_spawn_monster", le.will_spawn_monster },
                            { "message_fail", le.message_fail },
                            { "health_adj_fail", le.health_adj_fail } };
    }

    inline void from_json(const nlohmann::json & j, LookEvent & le)
    {
        j.at("has_happened").get_to(le.has_happened);
        j.at("will_always_happen").get_to(le.will_always_happen);
        j.at("map_pos_x").get_to(le.map_pos.x);
        j.at("map_pos_y").get_to(le.map_pos.y);
        j.at("message").get_to(le.message);
        j.at("stats_required").get_to(le.stats_required);
        j.at("item_required").get_to(le.item_required);
        j.at("item_keyword_required").get_to(le.item_keyword_required);
        j.at("message_pass").get_to(le.message_pass);
        j.at("item_given_pass").get_to(le.item_given_pass);
        j.at("health_adj_pass").get_to(le.health_adj_pass);
        j.at("gold_adj_pass").get_to(le.gold_adj_pass);
        j.at("stats_adj_pass").get_to(le.stats_adj_pass);
        j.at("will_spawn_monster").get_to(le.will_spawn_monster);
        j.at("message_fail").get_to(le.message_fail);
        j.at("health_adj_fail").get_to(le.health_adj_fail);
    }

    //

    class LookEventHandler
    {
      public:
        LookEventHandler();

        [[nodiscard]] static bool
            areAllRequirementsMet(const Context & t_context, const LookEvent & t_lookEvent);

        static const std::string
            takePassActions(const Context & t_context, const LookEvent & t_lookEvent);

        static const std::string
            takeFailActions(const Context & t_context, const LookEvent & t_lookEvent);
    };

} // namespace castlecrawl

#endif // LOOK_EVENT_HPP_INCLUDED
