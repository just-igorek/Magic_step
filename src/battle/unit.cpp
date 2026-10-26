#include "battle/unit.hpp"

#include <iostream>

namespace battle
{

Unit::Unit(IdType id, std::string_view name, ClassType classType, std::int32_t maxHealth,
           std::int32_t x, std::int32_t y)
    : m_id{ id }
    , m_name{ name }
    , m_class{ classType }
    , m_health{ maxHealth }
    , m_maxHealth{ maxHealth }
    , m_x{ x }
    , m_y{ y }
    , m_isAlive{ maxHealth > 0 }
{
    if (maxHealth <= 0)
    {
        std::cout << "[Unit] Error: maximum health must be greater than zero. "
                  << "Unit '" << m_name << "' created dead.\n";
    }
}

Unit::~Unit()
{
    std::cout << "[Unit] Destructor: " << m_name << " (id=" << m_id << ")\n";
}

void Unit::TakeDamage(std::int32_t amount)
{
    if (amount <= 0)
    {
        std::cout << "[Unit] Error: damage must be positive.\n";
        return;
    }

    if (!m_isAlive)
    {
        std::cout << "[Unit] Error: cannot attack a dead unit '" << m_name << "'.\n";
        return;
    }

    m_health -= amount;
    if (m_health <= 0)
    {
        m_health = 0;
        m_isAlive = false;
        std::cout << "[Unit] Unit '" << m_name << "' died.\n";
    }
}

void Unit::Heal(std::int32_t amount)
{
    if (amount <= 0)
    {
        std::cout << "[Unit] Error: the treatment must be positive.\n";
        return;
    }

    if (!m_isAlive)
    {
        std::cout << "[Unit] Error: Cannot heal a dead unit. '" << m_name << "'.\n";
        return;
    }

    m_health += amount;
    if (m_health > m_maxHealth)
    {
        m_health = m_maxHealth;
    }
}

void Unit::MoveTo(std::int32_t newX, std::int32_t newY)
{
    if (!m_isAlive)
    {
        std::cout << "[Unit] Error: dead unit '" << m_name << "' cannot move.\n";
        return;
    }

    m_x = newX;
    m_y = newY;
}

void Unit::Print() const
{
    std::cout << "Unit{id=" << m_id
              << ", name=" << m_name
              << ", hp=" << m_health << "/" << m_maxHealth
              << ", pos=(" << m_x << "," << m_y << ")"
              << ", alive=" << (m_isAlive ? "yes" : "no")
              << "}\n";
}

}