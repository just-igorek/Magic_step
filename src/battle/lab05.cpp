#include "battle/lab05.hpp"
#include "battle/warrior.hpp"
#include "battle/healer.hpp"
#include <algorithm>
#include <iostream>
#include <typeinfo>
#include <vector>

namespace battle {
std::string PoisonStrategy::Apply(BaseUnit& user, BaseUnit& target) const {
    if (!user.IsAlive() || !target.IsAlive()) throw InvalidCombatAction("Poison requires living units");
    target.TakeDamage(10);
    return user.GetName() + " applies poison to " + target.GetName();
}
std::string RegenerationStrategy::Apply(BaseUnit& user, BaseUnit& target) const {
    if (!user.IsAlive() || !target.IsAlive()) throw InvalidCombatAction("Regeneration requires living units");
    target.Heal(10);
    return user.GetName() + " restores " + target.GetName();
}
void PerformSupport(const ICombatant& actor, BaseUnit& target) { actor.Support(target); }

void DemonstrateLab05() {
    std::cout << "\n===== LAB 05: INTERFACES AND POLYMORPHISM =====\n";
    Warrior warrior(20, "Sentinel", 100, 0, 0);
    Healer healer(21, "Medic", 80, 1, 0);
    BaseUnit& baseRef = warrior;
    std::cout << "Late binding (virtual): " << baseRef.Attack() << '\n';
    std::cout << "Interface call: " << static_cast<const ICombatant&>(healer).CombatAction() << '\n';
    PerformSupport(healer, warrior);

    std::vector<const ICombatant*> order{&warrior, &healer};
    std::sort(order.begin(), order.end(), [](auto* a, auto* b) { return a->CompareCombatants(*b) < 0; });
    std::cout << "Sorted combatants: " << order.size() << '\n';

    BaseUnit& inspected = healer;
    if (auto* healerType = dynamic_cast<Healer*>(&inspected))
        std::cout << "dynamic_cast succeeded: " << healerType->GetName() << '\n';

    std::unique_ptr<IAbilityStrategy> strategy = std::make_unique<PoisonStrategy>();
    std::cout << strategy->Apply(warrior, healer) << '\n';
    strategy = std::make_unique<RegenerationStrategy>();
    std::cout << strategy->Apply(healer, warrior) << '\n';

    try {
        strategy->Apply(healer, warrior);
        throw InvalidCombatAction("Example rule violation: action already used");
    } catch (const InvalidCombatAction& error) {
        std::cout << "Handled rule violation: " << error.what() << '\n';
    } catch (const std::exception& error) {
        std::cout << "Unexpected standard exception: " << error.what() << '\n';
    }
}
}
