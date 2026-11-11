#include "battle/mage.hpp"
namespace battle
{
Mage::Mage(IdType id, std::string_view name, std::int32_t hp, std::int32_t x, std::int32_t y)
    : BaseUnit(id, name, hp, x, y, "magic", "uses elemental energy") {}
    std::string Mage::Attack() const { return m_name + " casts a fireball"; }
    std::unique_ptr<BaseUnit> Mage::Clone() const
{
    auto copy = std::make_unique<Mage>(*this);
    copy->MakeProfileUnique();
    return copy;
}
}
