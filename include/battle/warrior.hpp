#pragma once
#include "unit.hpp"

namespace battle
{
class Warrior final : public BaseUnit
{
public:
    Warrior();
    Warrior(IdType id, std::string_view name, std::int32_t maxHealth,
            std::int32_t x, std::int32_t y);
    Warrior(const Warrior& other);
    std::string Attack() const override;
    std::string Describe() const override; // С вызовом базового метода.
    std::string GetClassName() const override { return "Warrior"; }
    std::unique_ptr<BaseUnit> Clone() const override;
};
}
