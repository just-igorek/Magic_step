#include "battle/archer.hpp"
#include "battle/battlefield.hpp"
#include "battle/healer.hpp"
#include "battle/mage.hpp"
#include "battle/warrior.hpp"

#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace battle;

static void Inspect(const BaseUnit& unit)
{
    std::cout << unit.Describe() << '\n';
}

static void RegisterUnit(const BaseUnit& unit)
{
    std::cout << "[registry] registered: " << unit.GetName() << '\n';
}

static void DemonstrateLab05()
{
    std::cout << "\n===== LAB 05 =====\n";

    Warrior warrior(20, "Sentinel", 100, 0, 0);
    Healer healer(21, "Medic", 80, 1, 0);

    BaseUnit& base = warrior;

    std::cout << "Early binding: "
              << base.BindingLabel() << " / "
              << warrior.BindingLabel() << '\n';

    std::cout << "Late binding: " << base.Attack() << '\n';

    ICombatant& actor = healer;

    std::cout << "Interface dispatch: "
              << actor.CombatAction() << '\n';

    actor.Support(warrior);

    std::vector<const ICombatant*> order{&warrior, &healer};

    std::sort(
        order.begin(),
        order.end(),
        [](auto* first, auto* second)
        {
            return first->CompareCombatants(*second) < 0;
        });

    std::cout << "Sorted via interface: " << order.size() << '\n';

    BaseUnit& checked = healer;

    if (auto* typed = dynamic_cast<Healer*>(&checked))
    {
        std::cout << "dynamic_cast: " << typed->GetName() << '\n';
    }

    std::unique_ptr<IAbilityStrategy> strategy =
        std::make_unique<PoisonStrategy>();

    std::cout << strategy->Apply(warrior, healer) << '\n';

    strategy = std::make_unique<RegenerationStrategy>();

    std::cout << strategy->Apply(healer, warrior) << '\n';

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
    std::cout << "===== POLYMORPHISM AND CONSTRUCTORS =====\n";

    std::vector<std::unique_ptr<BaseUnit>> squad;

    squad.push_back(std::make_unique<Warrior>(1, "Arthas", 120, 0, 0));
    squad.push_back(std::make_unique<Archer>(2, "Legolas", 80, 1, 0));
    squad.push_back(std::make_unique<Mage>(3, "Merlin", 65, 2, 0));
    squad.push_back(std::make_unique<Healer>(4, "Mercy", 75, 3, 0));

    for (const auto& unit : squad)
    {
        Inspect(*unit);

        std::cout << "Attack: " << unit->Attack() << "\n\n";
    }

    std::cout << "===== VIRTUAL DESTRUCTOR =====\n";

    {
        std::unique_ptr<BaseUnit> temporary =
            std::make_unique<Warrior>(5, "Temporary", 90, 0, 1);
    }

    std::cout << "\n===== SHALLOW COPY =====\n";

    auto original = std::make_shared<Warrior>(6, "Guard", 100, 0, 2);
    auto shallow = std::make_shared<Warrior>(*original);

    std::cout << "Same profile: " << std::boolalpha
              << (original->ShareProfile() == shallow->ShareProfile())
              << '\n';

    shallow->ChangeSpecialization("shared specialization");

    std::cout << "Original specialization: "
              << original->GetProfile().specialization << '\n';

    std::cout << "\n===== DEEP COPY =====\n";

    auto deep = original->Clone();

    std::cout << "Same profile: "
              << (original->ShareProfile() == deep->ShareProfile()) << '\n';

    deep->ChangeSpecialization("independent specialization");

    std::cout << "Original: "
              << original->GetProfile().specialization << '\n';

    std::cout << "Clone: "
              << deep->GetProfile().specialization << '\n';

    std::cout << "\n===== COPY ASSIGNMENT AND this =====\n";

    Warrior target(8, "Copy target", 90, 0, 0);

    target = target;
    target.SetName("Renamed target");

    std::cout << "\n===== STRINGS AND this =====\n";

    std::string label = original->GetName() + " the defender";
    auto position = label.find("defender");

    std::cout << "Label: " << label << '\n';
    std::cout << "Substring: " << label.substr(position) << '\n';
    std::cout << "Name comparison: "
              << (original->GetName() == std::string("Guard")) << '\n';

    original->SetName("Veteran").SetName("Veteran Guard");

    RegisterUnit(*original);

    std::cout << "\n===== STATIC MEMBER =====\n";
    std::cout << "Alive objects: "
              << BaseUnit::GetAliveObjectCount() << '\n';

    std::cout << "\n===== BATTLEFIELD =====\n";

    Battlefield field(4, 2);
    auto archer = std::make_shared<Archer>(7, "Ranger", 70, 1, 1);

    field.PlaceUnit(archer, 1, 1);
    field.Print();

    if (auto placed = field.GetCell(1, 1).GetUnit())
    {
        std::cout << placed->Attack() << '\n';
    }

    DemonstrateLab05();

    return 0;
}
