#include "battle/archer.hpp"
#include "battle/battlefield.hpp"
#include "battle/healer.hpp"
#include "battle/mage.hpp"
#include "battle/warrior.hpp"
#include "battle/lab05.hpp"
#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace battle;
static void Inspect(const BaseUnit& unit) { std::cout << unit.Describe() << '\n'; }
static void RegisterUnit(const BaseUnit& unit) { std::cout << "[registry] registered: " << unit.GetName() << '\n'; }
int main() {
    std::cout << "===== POLYMORPHISM AND CONSTRUCTORS =====\n";
    std::vector<std::unique_ptr<BaseUnit>> squad;
    squad.push_back(std::make_unique<Warrior>(1,"Arthas",120,0,0));
    squad.push_back(std::make_unique<Archer>(2,"Legolas",80,1,0));
    squad.push_back(std::make_unique<Mage>(3,"Merlin",65,2,0));
    squad.push_back(std::make_unique<Healer>(4,"Mercy",75,3,0));
    for (const auto& unit : squad) { Inspect(*unit); std::cout << "Attack: " << unit->Attack() << "\n\n"; }
    std::cout << "\n===== SHALLOW COPY / CLONE =====\n";
    auto original=std::make_shared<Warrior>(6,"Guard",100,0,2);
    auto shallow=std::make_shared<Warrior>(*original);
    std::cout << "Shared profile: " << (original->ShareProfile()==shallow->ShareProfile()) << '\n';
    auto deep=original->Clone();
    std::cout << "Independent clone: " << (original->ShareProfile()!=deep->ShareProfile()) << '\n';
    RegisterUnit(*original);
    Battlefield field(4,2);
    field.PlaceUnit(std::make_shared<Archer>(7,"Ranger",70,1,1),1,1);
    field.Print();
    DemonstrateLab05();
    return 0;
}