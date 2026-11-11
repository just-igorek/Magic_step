#pragma once
#include "unit.hpp"
#include <cstdint>
#include <memory>

namespace battle
{
class Cell
{
protected:
    std::int32_t m_x{0}, m_y{0};
    std::weak_ptr<BaseUnit> m_unit;
public:
    Cell() = default;
    Cell(std::int32_t x, std::int32_t y);
    bool SetUnit(const std::shared_ptr<BaseUnit>& unit);
    void RemoveUnit();
    bool IsEmpty() const { return m_unit.expired(); }
    std::shared_ptr<BaseUnit> GetUnit() const { return m_unit.lock(); }
    std::int32_t GetX() const { return m_x; }
    std::int32_t GetY() const { return m_y; }
    void Print() const;
};
}
