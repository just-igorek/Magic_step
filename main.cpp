#include "include/battle/battlefield.hpp"
#include "include/battle/unit.hpp"

#include <iostream>
using namespace battle;

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

int main()
{

    std::cout << "===== 1. COMPOSITION: field of sparse cells =====\n";
    {
        Battlefield field(3, 3);
        field.Print();
    } 

    std::cout << "\n===== 2. AGGREGATION: the unit exists independently of the field =====\n";
    Unit* hero = new Unit(1, "Warrior", Unit::ClassType::eWarrior, 100, 0, 0);
    hero->Print();

    {
        Battlefield field(3, 3);
        field.PlaceUnit(hero, 0, 0);
        field.Print();
    } 

    std::cout << "Unit after the field is destroyed:";
    hero->Print();

    std::cout << "\n===== 3. RULE CHECK: cell is occupied =====\n";
    Battlefield field(3, 3);
    Unit* enemy = new Unit(2, "Archer", Unit::ClassType::eArcher, 80, 1, 1);

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
    Unit* dynamicUnit = new Unit(4, "Medic", Unit::ClassType::eHealer, 70, 1, 2);
    PrintUnitByPtr(dynamicUnit);
    delete dynamicUnit;

    std::cout << "-- dynamic array of objects --\n";
    Unit* squad = new Unit[2];
    squad[0] = Unit(5, "Warrior2", Unit::ClassType::eWarrior, 100, 0, 1);
    squad[1] = Unit(6, "Archer2", Unit::ClassType::eArcher, 80, 1, 1);
    for (int i = 0; i < 2; ++i)
    {
        PrintUnitByRef(squad[i]);
    }
    delete[] squad;

    std::cout << "-- array of dynamic objects --\n";
    Unit** squadPtr = new Unit*[2];
    squadPtr[0] = new Unit(7, "Mage2", Unit::ClassType::eMage, 60, 2, 0);
    squadPtr[1] = new Unit(8, "Medic2", Unit::ClassType::eHealer, 70, 2, 1);
    for (int i = 0; i < 2; ++i)
    {
        PrintUnitByPtr(squadPtr[i]);
    }
    for (int i = 0; i < 2; ++i)
    {
        delete squadPtr[i];
    }
    delete[] squadPtr;

    std::cout << "\n===== 5. UNIT RULE CHECK =====\n";
    hero->TakeDamage(30);
    hero->Print();
    hero->Heal(10);
    hero->Print();
    hero->TakeDamage(1000);  
    hero->Print();
    hero->Heal(50);         
    hero->MoveTo(1, 1);      

    delete hero;
    delete enemy;

    std::cout << "\n===== END =====\n";
    return 0;
}