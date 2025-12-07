#ifndef LOOK_EVENT_HPP_INCLUDED
#define LOOK_EVENT_HPP_INCLUDED
//
// look-event.hpp
//
#include "map-types.hpp"

#include <string>

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
                !item_keyword_required.empty());
        }

        bool has_happened{ false };

        // both must be negative to be invalid
        MapPos_t map_pos{ -1, -1 };

        // this message is always displayed and so must not be empty for this event to be valid
        std::string message{};

        // this message is only displayed if the all the requirements are met
        std::string message_pass{};

        // this message is only displayed if all the requirements are NOT met
        std::string message_fail{};

        // all requirements
        Stats stats_required{};
        std::string item_required{};
        std::string item_keyword_required{};

        // all bonuses and things given if requirments are met
        std::string item_given_pass{};
        int health_adj_pass{ 0 };
        int gold_adj_pass{ 0 };
        Stats stats_adj_pass{};

        // all consequences if the requirements are NOT met
        int health_adj_fail{ 0 };
    };

    //

    class LookEventHandler
    {
      public:
        LookEventHandler();

        [[nodiscard]] static bool
            areAllRequirementsMet(const Context & t_context, const LookEvent & t_lookEvent);

        static void takePassActions(const Context & t_context, const LookEvent & t_lookEvent);
        static void takeFailActions(const Context & t_context, const LookEvent & t_lookEvent);
    };

} // namespace castlecrawl

#endif // LOOK_EVENT_HPP_INCLUDED
