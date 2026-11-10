#pragma once

#include "unit.hpp"

#include <cstdint>
#include <memory>

namespace battle
{

class Cell
{
protected:
    std::int32_t m_x{ 0 };
    std::int32_t m_y{ 0 };
    std::weak_ptr<Unit> m_unit;  // агрегация: объект (ячейка) наблюдает за другим объектом (элементом), но не владеет им

public:
    Cell() = default;
    Cell(std::int32_t x, std::int32_t y);
    ~Cell();

    Cell(const Cell&)            = default;
    Cell(Cell&&)                 = default;
    Cell& operator=(const Cell&) = default;
    Cell& operator=(Cell&&)      = default;

    bool SetUnit(const std::shared_ptr<Unit>& unit);

    void RemoveUnit();

    // Ячейка считается пустой, если в неё никто не был помещён или если находившийся в ней юнит был уничтожен.
    [[nodiscard]] bool IsEmpty() const
    {
        return m_unit.expired();
    }

    // Пустой указатель, если ячейка пуста или объект больше не существует.
    [[nodiscard]] std::shared_ptr<Unit> GetUnit() const
    {
        return m_unit.lock();
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
