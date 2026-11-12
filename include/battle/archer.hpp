#pragma once
#include "unit.hpp"

namespace battle
{
class Archer : public BaseUnit
{
public:
    Archer();
    Archer(IdType id, std::string_view name, std::int32_t maxHealth,
           std::int32_t x, std::int32_t y);
    Archer(const Archer& other);
    std::string Attack() const override;
    std::string Describe() const override; // Без вызова базового метода.
    std::string GetClassName() const override { return "Archer"; }
    std::unique_ptr<BaseUnit> Clone() const override;
};
}
