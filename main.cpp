#include "battle/healer.hpp"
#include "battle/warrior.hpp"

#include <algorithm>
#include <exception>
#include <iostream>
#include <memory>
#include <vector>

using namespace battle;

static void DemonstrateLab05()
{
    std::cout << "===== LAB 05 =====\n";

    Warrior warrior(20, "Sentinel", 100, 0, 0);
    Healer healer(21, "Medic", 80, 1, 0);

    // Early binding: the non-virtual method is selected by the reference type.
    BaseUnit& base = warrior;

    std::cout << "Early binding: "
              << base.BindingLabel() << " / "
              << warrior.BindingLabel() << '\n';

    // Late binding: the virtual method is selected by the actual object type.
    std::cout << "Late binding: " << base.Attack() << '\n';

    // Interface-based polymorphism.
    ICombatant& actor = healer;

    std::cout << "Interface dispatch: "
              << actor.CombatAction() << '\n';

    actor.Support(warrior);

    // Sorting objects through the interface.
    std::vector<const ICombatant*> combatants{&warrior, &healer};

    std::sort(
        combatants.begin(),
        combatants.end(),
        [](const ICombatant* first, const ICombatant* second)
        {
            return first->CompareCombatants(*second) < 0;
        });

    std::cout << "Sorted combatants: ";

    for (const ICombatant* combatant : combatants)
    {
        std::cout << combatant->CombatAction() << '\n';
    }

    // Runtime type identification and safe downcasting.
    BaseUnit& inspected = healer;

    if (auto* typed = dynamic_cast<Healer*>(&inspected))
    {
        std::cout << "dynamic_cast: " << typed->GetName() << '\n';
    }

    // Strategy pattern: change the ability at runtime.
    std::unique_ptr<IAbilityStrategy> strategy =
        std::make_unique<PoisonStrategy>();

    std::cout << strategy->Apply(warrior, healer) << '\n';

    strategy = std::make_unique<RegenerationStrategy>();

    std::cout << strategy->Apply(healer, warrior) << '\n';

    // Custom exception and exception handling.
    healer.TakeDamage(healer.GetMaxHealth());

    try
    {
        strategy->Apply(healer, warrior);
    }
    catch (const InvalidCombatAction& error)
    {
        std::cout << "Specific catch: " << error.what() << '\n';
    }
    catch (const std::exception& error)
    {
        std::cout << "General catch: " << error.what() << '\n';
    }
}

int main()
{
    DemonstrateLab05();
    return 0;
}
