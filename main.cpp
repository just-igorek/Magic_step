#include "battle/archer.hpp"
#include "battle/battlefield.hpp"
#include "battle/healer.hpp"
#include "battle/mage.hpp"
#include "battle/warrior.hpp"

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
        std::unique_ptr<BaseUnit> temporary = std::make_unique<Warrior>(5, "Temporary", 90, 0, 1);
    }

    std::cout << "\n===== SHALLOW COPY: shared_ptr =====\n";
    auto original = std::make_shared<Warrior>(6, "Guard", 100, 0, 2);
    auto shallow = std::make_shared<Warrior>(*original);
    std::cout << "Same profile: " << std::boolalpha
              << (original->ShareProfile() == shallow->ShareProfile()) << '\n';
    shallow->ChangeSpecialization("shared specialization");
    std::cout << "Original specialization: " << original->GetProfile().specialization << '\n';

    std::cout << "\n===== DEEP COPY: Clone() =====\n";
    auto deep = original->Clone();
    std::cout << "Same profile: " << (original->ShareProfile() == deep->ShareProfile()) << '\n';
    deep->ChangeSpecialization("independent specialization");
    std::cout << "Original: " << original->GetProfile().specialization << '\n';
    std::cout << "Clone: " << deep->GetProfile().specialization << '\n';

    std::cout << "\n===== COPY ASSIGNMENT AND this =====\n";
    Warrior assignmentTarget(8, "Copy target", 90, 0, 0);
    assignmentTarget = assignmentTarget; // Проверка самоприсваивания через this != &other.
    assignmentTarget.SetName("Renamed target");

    std::cout << "\n===== STRINGS AND this =====\n";
    std::string label = original->GetName() + " the defender"; // concatenation
    auto position = label.find("defender");
    std::cout << "Label: " << label << '\n';
    std::cout << "Substring: " << label.substr(position) << '\n';
    std::cout << "Name comparison: " << (original->GetName() == std::string("Guard")) << '\n';
    original->SetName("Veteran").SetName("Veteran Guard");
    RegisterUnit(*original); // Передача текущего объекта по ссылке.

    std::cout << "\n===== STATIC MEMBER =====\n";
    std::cout << "Currently alive BaseUnit objects: " << BaseUnit::GetAliveObjectCount() << '\n';

    std::cout << "\n===== BATTLEFIELD USES BASE CLASS =====\n";
    Battlefield field(4, 2);
    auto archer = std::make_shared<Archer>(7, "Ranger", 70, 1, 1);
    field.PlaceUnit(archer, 1, 1);
    field.Print();
    if (auto placed = field.GetCell(1, 1).GetUnit())
        std::cout << placed->Attack() << '\n';

    std::cout << "\n===== END OF DEMONSTRATION =====\n";
    return 0;
}
