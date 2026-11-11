#pragma once
#include "unit.hpp"

namespace battle
{
class Healer : public BaseUnit
{
public:
    Healer(IdType id, std::string_view name, std::int32_t hp, std::int32_t x, std::int32_t y);
    std::string Attack() const override;
    std::string GetClassName() const override { return "Healer"; }
    std::unique_ptr<BaseUnit> Clone() const override;
};
}
