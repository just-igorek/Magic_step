#pragma once

#include "unit.hpp"

#include <cstdint>

namespace battle
{

class Cell
{
protected:
    std::int32_t m_x{ 0 };
    std::int32_t m_y{ 0 };
    Unit* m_unit{ nullptr };  

public:
    Cell() = default;
    Cell(std::int32_t x, std::int32_t y);
    ~Cell();


    Cell(const Cell&)            = default;
    Cell(Cell&&)                 = default;
    Cell& operator=(const Cell&) = default;
    Cell& operator=(Cell&&)      = default;

    bool SetUnit(Unit* unit);

    void RemoveUnit();

    [[nodiscard]] bool IsEmpty() const
    {
        return m_unit == nullptr;
    }

    [[nodiscard]] Unit* GetUnit() const
    {
        return m_unit;
    }

    [[nodiscard]] auto GetX() const
    {
        return m_x;
    }

    [[nodiscard]] auto GetY() const
    {
        return m_y;
    }

    void Print() const;
};

} 