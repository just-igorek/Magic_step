#include "battle/battlefield.hpp"
#include "battle/unit.hpp"

#include <iostream>
#include <memory>

using namespace battle;

// Функции, которые лишь обращаются к объекту, но никогда его не сохраняют, принимают обычную ссылку или указатель.
static void PrintUnitByRef(const Unit& unit)
{
    std::cout << "[by ref] ";
    unit.Print();
}

static void PrintUnitByPtr(const Unit* unit)
{
    if (unit == nullptr)
    {
        std::cout << "[by ptr] nullptr\n";
        return;
    }
    std::cout << "[by ptr] ";
    unit->Print();
}

// Принимает объект в собственность: вызывающий должен передать его с помощью std::move.
static void Garrison(std::unique_ptr<Unit> unit)
{
    std::cout << "[Garrison] took over '" << unit->GetName() << "'\n";
}   // Здесь обрывается параметр гарнизона — как, впрочем, и само подразделение.

int main()
{
    std::cout << "===== 1. COMPOSITION: field of sparse cells =====\n";
    {
        Battlefield field(3, 3);
        field.Print();
    }

    std::cout << "\n===== 2. AGGREGATION: the unit exists independently of the field =====\n";
    std::shared_ptr<Unit> hero = std::make_shared<Unit>(1, "Warrior", Unit::ClassType::eWarrior, 100, 0, 0);
    hero->Print();

    {
        Battlefield field(3, 3);
        field.PlaceUnit(hero, 0, 0);
        field.Print();
        std::cout << "use_count of the hero while placed on the field: " << hero.use_count()
                  << " (the cell only observes)\n";
    }

    std::cout << "Unit after the field is destroyed: ";
    hero->Print();

    std::cout << "\n===== 3. RULE CHECK: cell is occupied =====\n";
    Battlefield field(3, 3);
    std::shared_ptr<Unit> enemy = std::make_shared<Unit>(2, "Archer", Unit::ClassType::eArcher, 80, 1, 1);

    std::cout << "Correct action: place the Warrior at (0,0).\n";
    field.PlaceUnit(hero, 0, 0);

    std::cout << "Violation: placing the Archer on the same square (0,0).\n";
    field.PlaceUnit(enemy, 0, 0);
    field.Print();

    std::cout << "\n===== 4. MEMORY MANAGEMENT =====\n";

    std::cout << "-- static object --\n";
    Unit staticUnit(3, "Mage", Unit::ClassType::eMage, 60, 2, 2);
    PrintUnitByRef(staticUnit);
    PrintUnitByPtr(&staticUnit);

    std::cout << "-- dynamic object --\n";
    {
        std::unique_ptr<Unit> dynamicUnit =
            std::make_unique<Unit>(4, "Medic", Unit::ClassType::eHealer, 70, 1, 2);
        PrintUnitByPtr(dynamicUnit.get());
    }

    std::cout << "-- dynamic array of objects --\n";
    {
        std::unique_ptr<Unit[]> squad = std::make_unique<Unit[]>(2);
        squad[0] = Unit(5, "Warrior2", Unit::ClassType::eWarrior, 100, 0, 1);
        squad[1] = Unit(6, "Archer2", Unit::ClassType::eArcher, 80, 1, 1);
        for (int i = 0; i < 2; ++i)
        {
            PrintUnitByRef(squad[i]);
        }
    }

    std::cout << "-- array of dynamic objects --\n";
    {
        std::unique_ptr<Unit> squadPtr[2];
        squadPtr[0] = std::make_unique<Unit>(7, "Mage2", Unit::ClassType::eMage, 60, 2, 0);
        squadPtr[1] = std::make_unique<Unit>(8, "Medic2", Unit::ClassType::eHealer, 70, 2, 1);
        for (int i = 0; i < 2; ++i)
        {
            PrintUnitByPtr(squadPtr[i].get());
        }
    }

    std::cout << "\n===== 5. UNIT RULE CHECK =====\n";
    hero->TakeDamage(30);
    hero->Print();
    hero->Heal(10);
    hero->Print();
    hero->TakeDamage(1000);
    hero->Print();
    hero->Heal(50);
    hero->MoveTo(1, 1);

    std::cout << "\n===== 6. unique_ptr: single owner =====\n";
    {
        std::cout << "-- destroyed on leaving the block, nothing freed by hand --\n";
        std::unique_ptr<Unit> scout = std::make_unique<Unit>(9, "Scout", Unit::ClassType::eArcher, 50, 0, 2);
        scout->Print();
        std::cout << "leaving the block...\n";
    }
    std::cout << "block left\n";

    std::cout << "-- ownership transfer through std::move --\n";
    std::unique_ptr<Unit> guard = std::make_unique<Unit>(10, "Guard", Unit::ClassType::eWarrior, 90, 2, 2);
    std::cout << "guard is " << (guard ? "not empty" : "empty") << " before the transfer\n";
    Garrison(std::move(guard));
    std::cout << "guard is " << (guard ? "not empty" : "empty") << " after std::move\n";

    std::cout << "\n===== 7. shared_ptr: several owners =====\n";
    std::shared_ptr<Unit> banner = std::make_shared<Unit>(11, "Banner", Unit::ClassType::eHealer, 40, 1, 0);
    std::cout << "use_count after creation: " << banner.use_count() << "\n";
    {
        std::shared_ptr<Unit> copy1 = banner;
        std::cout << "use_count after the first copy: " << banner.use_count() << "\n";
        {
            std::shared_ptr<Unit> copy2 = banner;
            std::cout << "use_count after the second copy: " << banner.use_count() << "\n";
        }
        std::cout << "use_count after the second copy is gone: " << banner.use_count() << "\n";
    }
    std::cout << "use_count after the first copy is gone: " << banner.use_count() << "\n";

    std::shared_ptr<Unit> spare = banner;
    std::cout << "use_count with 'spare': " << banner.use_count() << "\n";
    banner.reset();
    std::cout << "original owner gave up the unit; the unit lives through 'spare': ";
    spare->Print();
    std::cout << "the last owner gives up the unit...\n";
    spare.reset();
    std::cout << "last owner released\n";

    std::cout << "\n===== 8. weak_ptr: observer =====\n";
    std::shared_ptr<Unit> pilot = std::make_shared<Unit>(12, "Pilot", Unit::ClassType::eMage, 55, 0, 1);
    std::weak_ptr<Unit> watcher = pilot;
    std::cout << "use_count with a weak_ptr attached: " << pilot.use_count() << " (weak does not count)\n";

    if (std::shared_ptr<Unit> alive = watcher.lock())
    {
        std::cout << "object is alive, reached through lock(): ";
        alive->Print();
    }

    field.PlaceUnit(pilot, 2, 2);
    std::cout << "cell (2,2) empty while the unit is alive: " << (field.GetCell(2, 2).IsEmpty() ? "yes" : "no") << "\n";

    std::cout << "the last owner gives up the unit...\n";
    pilot.reset();

    if (std::shared_ptr<Unit> alive = watcher.lock())
    {
        std::cout << "object is still alive\n";
    }
    else
    {
        std::cout << "lock() returned an empty pointer: the object no longer exists\n";
    }
    std::cout << "cell (2,2) empty after the unit is destroyed: " << (field.GetCell(2, 2).IsEmpty() ? "yes" : "no") << "\n";

    std::cout << "\n===== END =====\n";
    return 0;
}
