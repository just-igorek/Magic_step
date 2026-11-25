#include "battle/warrior.hpp"
#include <iostream>
namespace battle {
Warrior::Warrior() : BaseUnit() { std::cout << "[Warrior] default constructor\n"; }
Warrior::Warrior(IdType id, std::string_view name, std::int32_t hp, std::int32_t x, std::int32_t y)
    : BaseUnit(id, name, hp, x, y, "front line", "close combat specialist") { std::cout << "[Warrior] parameterized constructor\n"; }
Warrior::Warrior(const Warrior& other) : BaseUnit(other) { std::cout << "[Warrior] copy constructor\n"; }
std::string Warrior::Attack() const { return m_name + " strikes with a sword"; }
std::string Warrior::Describe() const { std::string result = BaseUnit::Describe(); PrintBaseDescription(result); return result; }
std::unique_ptr<BaseUnit> Warrior::Clone() const { auto copy = std::make_unique<Warrior>(*this); copy->MakeProfileUnique(); return copy; }
void Warrior::Support(BaseUnit& target) const {
    if (!IsAlive() || !target.IsAlive()) throw InvalidCombatAction("Support requires living units");
    target.Heal(5);
}
int Warrior::CompareCombatants(const ICombatant& other) const { return CombatAction().compare(other.CombatAction()); }
}
