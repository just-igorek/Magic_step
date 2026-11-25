#include "battle/healer.hpp"
#include <iostream>
namespace battle {
Healer::Healer(IdType id,std::string_view name,std::int32_t hp,std::int32_t x,std::int32_t y)
: BaseUnit(id,name,hp,x,y,"support","restores allies' health") { std::cout << "[Healer] parameterized constructor\n"; }
std::string Healer::Attack() const { return m_name+" uses a staff strike"; }
std::unique_ptr<BaseUnit> Healer::Clone() const { auto copy=std::make_unique<Healer>(*this); copy->MakeProfileUnique(); return copy; }
void Healer::Support(BaseUnit& target) const { if(!IsAlive() || !target.IsAlive()) throw InvalidCombatAction("Healing requires living units"); target.Heal(15); }
int Healer::CompareCombatants(const ICombatant& other) const noexcept { return Attack().compare(other.CombatAction()); }
}
