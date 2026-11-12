#include "battle/battlefield.hpp"
#include <iostream>
#include <stdexcept>
namespace battle
{
Battlefield::Battlefield(std::int32_t width, std::int32_t height)
    : m_width(width), m_height(height)
{
    if (width <= 0 || height <= 0) throw std::invalid_argument("Field dimensions must be positive");
    m_cells = std::make_unique<CellRow[]>(static_cast<std::size_t>(height));
    for (int y = 0; y < height; ++y)
    {
        m_cells[y] = std::make_unique<std::unique_ptr<Cell>[]>(static_cast<std::size_t>(width));
        for (int x = 0; x < width; ++x) m_cells[y][x] = std::make_unique<Cell>(x, y);
    }
}
bool Battlefield::IsValidPosition(std::int32_t x, std::int32_t y) const
{ return x >= 0 && x < m_width && y >= 0 && y < m_height; }
bool Battlefield::PlaceUnit(const std::shared_ptr<BaseUnit>& unit, std::int32_t x, std::int32_t y)
{ return unit && IsValidPosition(x, y) && m_cells[y][x]->SetUnit(unit); }
void Battlefield::RemoveUnit(std::int32_t x, std::int32_t y)
{ if (IsValidPosition(x, y)) m_cells[y][x]->RemoveUnit(); }
Cell& Battlefield::GetCell(std::int32_t x, std::int32_t y) const
{
    if (!IsValidPosition(x, y)) throw std::out_of_range("Position is outside battlefield");
    return *m_cells[y][x];
}
void Battlefield::Print() const
{
    std::cout << "Field " << m_width << "x" << m_height << '\n';
    for (int y = 0; y < m_height; ++y)
    {
        for (int x = 0; x < m_width; ++x) { m_cells[y][x]->Print(); std::cout << ' '; }
        std::cout << '\n';
    }
}
}
