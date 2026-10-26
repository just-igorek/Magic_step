#include "battle/cell.hpp"

#include <iostream>

namespace battle
{

Cell::Cell(std::int32_t x, std::int32_t y)
    : m_x{ x }
    , m_y{ y }
{
    std::cout << "[Cell] Constructor: cell (" << x << "," << y << ")\n";
}

Cell::~Cell()
{
    std::cout << "[Cell] Destructor: cell (" << m_x << "," << m_y << ")\n";
}

bool Cell::SetUnit(const std::shared_ptr<Unit>& unit)
{
    if (!unit)
    {
        std::cout << "[Cell] Error: null pointer to unit passed.\n";
        return false;
    }

    if (!IsEmpty())
    {
        std::cout << "[Cell] Error: cell (" << m_x << "," << m_y
                  << ") already occupied by a unit '" << m_unit.lock()->GetName() << "'.\n";
        return false;
    }

    m_unit = unit;
    return true;
}

void Cell::RemoveUnit()
{
    m_unit.reset();
}

void Cell::Print() const
{
    const std::shared_ptr<Unit> unit = m_unit.lock();
    if (!unit)
    {
        std::cout << '.';
    }
    else
    {
        std::cout << (unit->IsAlive() ? 'U' : 'x');
    }
}

}