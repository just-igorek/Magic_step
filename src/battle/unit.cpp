#include "battle/unit.hpp"

#include <algorithm>
#include <iostream>
#include <utility>

namespace battle
{
std::size_t BaseUnit::s_aliveObjects = 0;

BaseUnit::BaseUnit()
    : m_profile(std::make_shared<UnitProfile>())
{
    ++s_aliveObjects;
    std::cout << "[BaseUnit] default constructor\n";
}

BaseUnit::BaseUnit(IdType id, std::string_view name, std::int32_t maxHealth,
                   std::int32_t x, std::int32_t y, std::string specialization,
                   std::string description)
    : m_id(id),
      m_name(name.empty() ? "noname" : name),
      m_health(std::max(0, maxHealth)),
      m_maxHealth(std::max(0, maxHealth)),
      m_x(x),
      m_y(y),
      m_isAlive(maxHealth > 0),
      m_profile(std::make_shared<UnitProfile>(
          UnitProfile{std::move(specialization), std::move(description)}))
{
    ++s_aliveObjects;
    std::cout << "[BaseUnit] parameterized constructor: " << m_name << '\n';
}

BaseUnit::BaseUnit(const BaseUnit& other)
    : m_id(other.m_id), m_name(other.m_name), m_health(other.m_health),
      m_maxHealth(other.m_maxHealth), m_x(other.m_x), m_y(other.m_y),
      m_isAlive(other.m_isAlive), m_profile(other.m_profile)
{
    ++s_aliveObjects;
    std::cout << "[BaseUnit] copy constructor (shared profile): " << m_name << '\n';
}

BaseUnit::BaseUnit(BaseUnit&& other) noexcept
    : m_id(other.m_id), m_name(std::move(other.m_name)),
      m_health(other.m_health), m_maxHealth(other.m_maxHealth),
      m_x(other.m_x), m_y(other.m_y), m_isAlive(other.m_isAlive),
      m_profile(std::move(other.m_profile))
{
    ++s_aliveObjects;
    other.m_isAlive = false;
    std::cout << "[BaseUnit] move constructor: " << m_name << '\n';
}

BaseUnit& BaseUnit::operator=(const BaseUnit& other)
{
    if (this != &other)
    {
        m_id = other.m_id;
        m_name = other.m_name;
        m_health = other.m_health;
        m_maxHealth = other.m_maxHealth;
        m_x = other.m_x;
        m_y = other.m_y;
        m_isAlive = other.m_isAlive;
        m_profile = other.m_profile; // Поверхностное копирование вложенного объекта.
    }
    return *this;
}

BaseUnit& BaseUnit::operator=(BaseUnit&& other) noexcept
{
    if (this != &other)
    {
        m_id = other.m_id;
        m_name = std::move(other.m_name);
        m_health = other.m_health;
        m_maxHealth = other.m_maxHealth;
        m_x = other.m_x;
        m_y = other.m_y;
        m_isAlive = other.m_isAlive;
        m_profile = std::move(other.m_profile);
        other.m_isAlive = false;
    }
    return *this;
}

BaseUnit::~BaseUnit()
{
    std::cout << "[BaseUnit] virtual destructor: " << m_name << '\n';
    --s_aliveObjects;
}

std::string BaseUnit::Describe() const
{
    return GetClassName() + " '" + m_name + "' HP=" +
           std::to_string(m_health) + "/" + std::to_string(m_maxHealth) +
           " at (" + std::to_string(m_x) + "," + std::to_string(m_y) + ")";
}

void BaseUnit::TakeDamage(std::int32_t amount)
{
    if (amount <= 0 || !m_isAlive) return;
    m_health = std::max(0, m_health - amount);
    if (m_health == 0) m_isAlive = false;
}

void BaseUnit::Heal(std::int32_t amount)
{
    if (amount > 0 && m_isAlive)
        m_health = std::min(m_maxHealth, m_health + amount);
}

void BaseUnit::MoveTo(std::int32_t newX, std::int32_t newY)
{
    if (m_isAlive) { m_x = newX; m_y = newY; }
}

BaseUnit& BaseUnit::SetName(std::string name)
{
    if (!name.empty()) m_name = std::move(name);
    return *this; // Возврат текущего объекта.
}

void BaseUnit::ChangeSpecialization(std::string specialization)
{
    // Обычная копия делит профиль: изменение видно и через оригинал.
    m_profile->specialization = std::move(specialization);
}

void BaseUnit::MakeProfileUnique()
{
    if (!m_profile) m_profile = std::make_shared<UnitProfile>();
    else if (!m_profile.unique())
        m_profile = std::make_shared<UnitProfile>(*m_profile);
}

void BaseUnit::PrintBaseDescription(std::string& result) const
{
    result += " | " + m_profile->specialization + ": " + m_profile->description;
}

std::size_t BaseUnit::GetAliveObjectCount() noexcept
{
    return s_aliveObjects;
}
}
