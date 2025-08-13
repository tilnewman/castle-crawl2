// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// animation-manager.cpp
//
#include "animation-manager.hpp"

#include "context.hpp"
#include "game-config.hpp"

namespace castlecrawl
{

    AnimationManager::AnimationManager(const util::Random & t_random, const std::string & t_pathStr)
        : m_dustManagerUPtr{ std::make_unique<DustParticleManager>() }
        , m_sparkleManagerUPtr{ std::make_unique<SparkleParticleManager>() }
        , m_campfiresUPtr{ std::make_unique<CampfireAnimationManager>() }
        , m_smokeEffectManagerUPtr{ std::make_unique<SmokeEffectManager>() }
        , m_infernoManagerUPtr{ std::make_unique<InfernoAnimationManager>() }
        , m_risingUPtr{ std::make_unique<RisingTextAnimationManager>() }
        , m_flatSmokeUPtr{ std::make_unique<FlatSmokeAnimManager>() }
        , m_playerUPtr{ std::make_unique<util::AnimationPlayer>(t_random, t_pathStr) }
    {}

    void AnimationManager::setup(const GameConfig & t_config)
    {
        m_dustManagerUPtr->setup(t_config);
        m_sparkleManagerUPtr->setup(t_config);
        m_campfiresUPtr->setup(t_config);
        m_smokeEffectManagerUPtr->setup(t_config);
        m_infernoManagerUPtr->setup(t_config);
        // m_risingUPtr has no setup() function
        m_flatSmokeUPtr->setup(t_config);
        m_playerUPtr->loadAll();
    }

    void AnimationManager::update(const Context & t_context, const float t_elapsedTimeSec)
    {
        m_dustManagerUPtr->update(t_context, t_elapsedTimeSec);
        m_sparkleManagerUPtr->update(t_context, t_elapsedTimeSec);
        m_campfiresUPtr->update(t_context, t_elapsedTimeSec);
        m_smokeEffectManagerUPtr->update(t_context, t_elapsedTimeSec);
        m_infernoManagerUPtr->update(t_context, t_elapsedTimeSec);
        m_risingUPtr->update(t_context, t_elapsedTimeSec);
        m_flatSmokeUPtr->update(t_context, t_elapsedTimeSec);
        m_playerUPtr->update(t_elapsedTimeSec);
    }

    void AnimationManager::draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        // this order is important for things to look right
        m_sparkleManagerUPtr->draw(t_target, t_states);
        m_dustManagerUPtr->draw(t_target, t_states);
        m_campfiresUPtr->draw(t_target, t_states);
        m_infernoManagerUPtr->draw(t_target, t_states);
        m_smokeEffectManagerUPtr->draw(t_target, t_states);
        m_risingUPtr->draw(t_target, t_states);
        m_flatSmokeUPtr->draw(t_target, t_states);
        m_playerUPtr->draw(t_target, t_states);
    }

    void AnimationManager::clear()
    {
        m_dustManagerUPtr->clear();
        m_sparkleManagerUPtr->clear();
        m_campfiresUPtr->clear();
        m_smokeEffectManagerUPtr->clear();
        m_infernoManagerUPtr->clear();
        m_risingUPtr->clear();
        m_flatSmokeUPtr->clear();
        m_playerUPtr->stopAll();
    }

    std::size_t AnimationManager::particleCount() const
    {
        // m_playerUPtr is not considered a player of particles so don't consider it here
        return (
            m_dustManagerUPtr->particleCount() + m_sparkleManagerUPtr->particleCount() +
            m_campfiresUPtr->particleCount() + m_smokeEffectManagerUPtr->particleCount() +
            m_infernoManagerUPtr->particleCount() + m_risingUPtr->particleCount() +
            m_flatSmokeUPtr->particleCount());
    }

} // namespace castlecrawl
