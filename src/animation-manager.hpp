#ifndef ANIMATION_MANAGER_HPP_INCLUDED
#define ANIMATION_MANAGER_HPP_INCLUDED
//
// animation-manager.hpp
//
#include "animation-player.hpp"
#include "campfire.hpp"
#include "dust-particle.hpp"
#include "flat-smoke-anim.hpp"
#include "inferno.hpp"
#include "random.hpp"
#include "rising-text-anim.hpp"
#include "smoke.hpp"
#include "sparkle-particle.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <memory>

namespace castlecrawl
{
    struct Context;
    struct GameConfig;

    class AnimationManager
    {
      public:
        AnimationManager(const util::Random & t_random, const std::string & t_pathStr);

        void setup(const GameConfig & t_config);

        [[nodiscard]] inline DustParticleManager & dust() { return *m_dustManagerUPtr; }
        [[nodiscard]] inline SparkleParticleManager & sparkle() { return *m_sparkleManagerUPtr; }
        [[nodiscard]] inline CampfireAnimationManager & campfire() { return *m_campfiresUPtr; }
        [[nodiscard]] inline SmokeEffectManager & smoke() { return *m_smokeEffectManagerUPtr; }
        [[nodiscard]] inline InfernoAnimationManager & inferno() { return *m_infernoManagerUPtr; }
        [[nodiscard]] inline RisingTextAnimationManager & risingText() { return *m_risingUPtr; }
        [[nodiscard]] inline FlatSmokeAnimManager & flatSmoke() { return *m_flatSmokeUPtr; }
        [[nodiscard]] inline util::AnimationPlayer & player() { return *m_playerUPtr; }

        void update(const Context & t_context, const float t_elapsedSec);
        void draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const;
        void clear();

        std::size_t particleCount() const;

      private:
        std::unique_ptr<DustParticleManager> m_dustManagerUPtr;
        std::unique_ptr<SparkleParticleManager> m_sparkleManagerUPtr;
        std::unique_ptr<CampfireAnimationManager> m_campfiresUPtr;
        std::unique_ptr<SmokeEffectManager> m_smokeEffectManagerUPtr;
        std::unique_ptr<InfernoAnimationManager> m_infernoManagerUPtr;
        std::unique_ptr<RisingTextAnimationManager> m_risingUPtr;
        std::unique_ptr<FlatSmokeAnimManager> m_flatSmokeUPtr;
        std::unique_ptr<util::AnimationPlayer> m_playerUPtr;
    };

} // namespace castlecrawl

#endif // ANIMATION_MANAGER_HPP_INCLUDED