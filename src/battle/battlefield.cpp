#include "battle/battlefield.hpp"

#include <iostream>
#include <stdexcept>

namespace battle
{

Battlefield::Battlefield(std::int32_t width, std::int32_t height)
    : m_width{ width }
    , m_height{ height }
{
    if (width < MIN_SIZE || height < MIN_SIZE)
    {
        std::cout << "[Battlefield] Error: Field dimensions must be >= " << MIN_SIZE
                  << ". Field not created.\n";
        m_width  = 0;
        m_height = 0;
        return;
    }

    m_cells = std::make_unique<CellRow[]>(static_cast<std::size_t>(m_height));
    for (std::int32_t y = 0; y < m_height; ++y)
    {
        m_cells[y] = std::make_unique<std::unique_ptr<Cell>[]>(static_cast<std::size_t>(m_width));
        for (std::int32_t x = 0; x < m_width; ++x)
        {
            m_cells[y][x] = std::make_unique<Cell>(x, y);
        }
    }

    std::cout << "[Battlefield] Field created " << m_width << "x" << m_height << "\n";
}

Battlefield::~Battlefield()
{
    // Ячейки высвобождаются членами класса типа unique_ptr; здесь выводится только сообщение.
    std::cout << "[Battlefield] Destructor: field " << m_width << "x" << m_height << " destroyed\n";
}

bool Battlefield::IsValidPosition(std::int32_t x, std::int32_t y) const
{
    return x >= 0 && x < m_width && y >= 0 && y < m_height;
}

bool Battlefield::PlaceUnit(const std::shared_ptr<Unit>& unit, std::int32_t x, std::int32_t y)
{
    if (!unit)
    {
        std::cout << "[Battlefield] Error: null pointer to unit.\n";
        return false;
    }

    if (!IsValidPosition(x, y))
    {
        std::cout << "[Battlefield] Error: position (" << x << "," << y
                  << ") off the field " << m_width << "x" << m_height << ".\n";
        return false;
    }

    return m_cells[y][x]->SetUnit(unit);
}

void Battlefield::RemoveUnit(std::int32_t x, std::int32_t y)
{
    if (!IsValidPosition(x, y))
    {
        std::cout << "[Battlefield] Error: position (" << x << "," << y << ") off the field.\n";
        return;
    }
    m_cells[y][x]->RemoveUnit();
}

Cell& Battlefield::GetCell(std::int32_t x, std::int32_t y) const
{
    if (!IsValidPosition(x, y))
    {
        throw std::out_of_range("Battlefield::GetCell: position is off the field");
    }
    return *m_cells[y][x];
}

void Battlefield::Print() const
{
    std::cout << "Field " << m_width << "x" << m_height << ":\n";
    for (std::int32_t y = 0; y < m_height; ++y)
    {
        for (std::int32_t x = 0; x < m_width; ++x)
        {
            m_cells[y][x]->Print();
            std::cout << ' ';
        }
        std::cout << '\n';
    }
}

} 