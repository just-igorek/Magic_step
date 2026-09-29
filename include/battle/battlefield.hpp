#pragma once

#include "cell.hpp"
#include "unit.hpp"

#include <cstdint>

namespace battle
{

class Battlefield
{
private:
    static constexpr std::int32_t MIN_SIZE = 1;

protected:
    std::int32_t m_width{ 0 };
    std::int32_t m_height{ 0 };
    Cell*** m_cells{ nullptr }; 

public:
    Battlefield() = default;
    Battlefield(std::int32_t width, std::int32_t height);
    ~Battlefield();

    Battlefield(const Battlefield&)            = delete;
    Battlefield(Battlefield&&)                 = delete;
    Battlefield& operator=(const Battlefield&) = delete;
    Battlefield& operator=(Battlefield&&)      = delete;

    [[nodiscard]] bool IsValidPosition(std::int32_t x, std::int32_t y) const;

    bool PlaceUnit(Unit* unit, std::int32_t x, std::int32_t y);

    void RemoveUnit(std::int32_t x, std::int32_t y);

    [[nodiscard]] Cell* GetCell(std::int32_t x, std::int32_t y) const;

    [[nodiscard]] auto GetWidth() const
    {
        return m_width;
    }

    [[nodiscard]] auto GetHeight() const
    {
        return m_height;
    }

    void Print() const;
};

} 