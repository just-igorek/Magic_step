#include "battle/archer.hpp"
#include <iostream>

namespace battle
{
Archer::Archer() : BaseUnit() { std::cout << "[Archer] default constructor\n"; }

Archer::Archer(IdType id, std::string_view name, std::int32_t hp, std::int32_t x, std::int32_t y)
    : BaseUnit(id, name, hp, x, y, "ranged", "attacks from a distance")
    { std::cout << "[Archer] parameterized constructor\n"; }

Archer::Archer(const Archer& other) : BaseUnit(other)
    { std::cout << "[Archer] copy constructor\n"; }
    std::string Archer::Attack() const { return m_name + " shoots an arrow"; }
    std::string Archer::Describe() const
{
    return "Archer '" + m_name + "' | " + m_profile->specialization;
}
    std::unique_ptr<BaseUnit> Archer::Clone() const
{
    auto copy = std::make_unique<Archer>(*this);
    copy->MakeProfileUnique();
    return copy;
}
}
