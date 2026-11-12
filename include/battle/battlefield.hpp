#pragma once
#include "cell.hpp"
#include <cstdint>
#include <memory>

namespace battle
{
class Battlefield
{
    using CellRow = std::unique_ptr<std::unique_ptr<Cell>[]>;
    std::int32_t m_width{0}, m_height{0};
    std::unique_ptr<CellRow[]> m_cells;
public:
    Battlefield(std::int32_t width, std::int32_t height);
    bool IsValidPosition(std::int32_t x, std::int32_t y) const;
    bool PlaceUnit(const std::shared_ptr<BaseUnit>& unit, std::int32_t x, std::int32_t y);
    void RemoveUnit(std::int32_t x, std::int32_t y);
    Cell& GetCell(std::int32_t x, std::int32_t y) const;
    void Print() const;
};
}
