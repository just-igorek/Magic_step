#include "battle/healer.hpp"
namespace battle
{
Healer::Healer(IdType id, std::string_view name, std::int32_t hp, std::int32_t x, std::int32_t y)
    : BaseUnit(id, name, hp, x, y, "support", "restores allies' health") {}
    std::string Healer::Attack() const { return m_name + " uses a staff strike"; }
    std::unique_ptr<BaseUnit> Healer::Clone() const
{
    auto copy = std::make_unique<Healer>(*this);
    copy->MakeProfileUnique();
    return copy;
}
}
