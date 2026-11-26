#include "battle/healer.hpp"
#include "battle/warrior.hpp"

#include <algorithm>
#include <exception>
#include <iostream>
#include <memory>
#include <vector>

using namespace battle;

int main()
{
    std::cout << "===== LAB 05 =====\n";

    Warrior warrior(20, "Sentinel", 100, 0, 0);
    Healer healer(21, "Medic", 80, 1, 0);

    // Раннее связывание: невиртуальный метод выбирается на основе типа ссылки.
    BaseUnit& base = warrior;

    std::cout << "Early binding: "
              << base.BindingLabel() << " / "
              << warrior.BindingLabel() << '\n';

    // Позднее связывание: виртуальный метод выбирается в зависимости от фактического типа объекта.
    std::cout << "Late binding: " << base.Attack() << '\n';

    // Полиморфизм на основе интерфейсов.
    ICombatant& actor = healer;

    std::cout << "Interface dispatch: "
              << actor.CombatAction() << '\n';

    actor.Support(warrior);

    // Сортировка объектов через интерфейс.
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

    // Идентификация типа во время выполнения и безопасное приведение к производному типу.
    BaseUnit& inspected = healer;

    if (auto* typed = dynamic_cast<Healer*>(&inspected))
    {
        std::cout << "dynamic_cast: " << typed->GetName() << '\n';
    }

    // изменение функциональности во время выполнения программы.
    std::unique_ptr<IAbilityStrategy> strategy =
        std::make_unique<PoisonStrategy>();

    std::cout << strategy->Apply(warrior, healer) << '\n';

    strategy = std::make_unique<RegenerationStrategy>();

    std::cout << strategy->Apply(healer, warrior) << '\n';

    // Пользовательское исключение и обработка исключений.
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
    return 0;
}
