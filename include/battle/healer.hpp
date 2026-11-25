#pragma once

#include "unit.hpp"

namespace battle
{

class Healer : public BaseUnit, public ICombatant
{
public:
    Healer(
        IdType id,
        std::string_view name,
        std::int32_t hp,
        std::int32_t x,
        std::int32_t y);

    std::string Attack() const override;
    std::string GetClassName() const override { return "Healer"; }

    std::unique_ptr<BaseUnit> Clone() const override;

    std::string CombatAction() const override { return Attack(); }
    void Support(BaseUnit& target) const override;
    int CompareCombatants(const ICombatant& other) const override;
};

}
