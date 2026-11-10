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

bool Cell::SetUnit(Unit* unit)
{
    if (unit == nullptr)
    {
        std::cout << "[Cell] Error: null pointer to unit passed.\n";
        return false;
    }

    if (!IsEmpty())
    {
        std::cout << "[Cell] Error: cell (" << m_x << "," << m_y
                  << ") already occupied by a unit '" << m_unit->GetName() << "'.\n";
        return false;
    }

    m_unit = unit;
    return true;
}

void Cell::RemoveUnit()
{
    m_unit = nullptr;
}

void Cell::Print() const
{
    if (IsEmpty())
    {
        std::cout << '.';
    }
    else
    {
        std::cout << (m_unit->IsAlive() ? 'U' : 'x');
    }
}

}