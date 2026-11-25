#pragma once
#include "unit.hpp"
namespace battle {
class Warrior final : public BaseUnit, public ICombatant {
public:
    Warrior();
    Warrior(IdType id, std::string_view name, std::int32_t maxHealth, std::int32_t x, std::int32_t y);
    Warrior(const Warrior& other);
    std::string Attack() const override;
    std::string Describe() const override;
    std::string GetClassName() const override { return "Warrior"; }
    std::unique_ptr<BaseUnit> Clone() const override;
    std::string CombatAction() const override { return Attack(); }
    void Support(BaseUnit& target) const override;
    int CompareCombatants(const ICombatant& other) const override;
    std::string BindingLabel() const { return "Warrior binding"; }
};
}
