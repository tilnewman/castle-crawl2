#ifndef LOOK_EVENT_HPP_INCLUDED
#define LOOK_EVENT_HPP_INCLUDED
//
// look-event.hpp
//
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
