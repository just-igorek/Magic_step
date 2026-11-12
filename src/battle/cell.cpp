#include "battle/cell.hpp"
#include <iostream>
namespace battle
{
Cell::Cell(std::int32_t x, std::int32_t y) : m_x(x), m_y(y) {}
bool Cell::SetUnit(const std::shared_ptr<BaseUnit>& unit)
{
    if (!unit || !IsEmpty()) return false;
    m_unit = unit;
    return true;
}
void Cell::RemoveUnit() { m_unit.reset(); }
void Cell::Print() const
{
    auto unit = m_unit.lock();
    std::cout << (!unit ? '.' : (unit->IsAlive() ? 'U' : 'x'));
}
}
