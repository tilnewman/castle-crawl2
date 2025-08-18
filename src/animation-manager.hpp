#ifndef ANIMATION_MANAGER_HPP_INCLUDED
#define ANIMATION_MANAGER_HPP_INCLUDED
//
// animation-manager.hpp
//
#include "anim-campfire.hpp"
#include "anim-crossbones.hpp"
#include "anim-dust-particle.hpp"
#include "anim-flat-smoke.hpp"
#include "anim-inferno.hpp"
#include "anim-music-notes.hpp"
#include "anim-rising-text.hpp"
#include "anim-smoke.hpp"
#include "anim-sparkle-particle.hpp"
#include "animation-player.hpp"
#include "random.hpp"

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
        [[nodiscard]] inline MusicAnimationManager & musicalNotes() { return *m_musicalNotesUPtr; }
        
        [[nodiscard]] inline CrossbonesAnimationManager & crossbones()
        {
            return *m_crossbonesUPtr;
        }

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
        std::unique_ptr<MusicAnimationManager> m_musicalNotesUPtr;
        std::unique_ptr<CrossbonesAnimationManager> m_crossbonesUPtr;
        std::unique_ptr<util::AnimationPlayer> m_playerUPtr;
    };

} // namespace castlecrawl

#endif // ANIMATION_MANAGER_HPP_INCLUDED