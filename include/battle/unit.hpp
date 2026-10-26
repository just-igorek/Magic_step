#pragma once

#include <cstdint>
#include <string>
#include <string_view>

namespace battle{
    class Unit
    {
        public:
        using IdType = std::uint32_t;
        enum class ClassType{
            eWarrior,
            eArcher,
            eMage,
            eHealer
        };
    private:
        static constexpr auto BASE_NAME = "noname";
    protected:
        IdType m_id{} ;
        std::string m_name{BASE_NAME};
        ClassType m_class{ClassType::eWarrior};
        std::int32_t m_health{ 0 };
        std::int32_t m_maxHealth { 0 };

        std::int32_t m_x {0};
        std::int32_t m_y {0};

        bool m_isAlive {true};

    public:
        Unit() = default;
        Unit(IdType id, std::string_view name, ClassType classType, std::int32_t maxhealth,
             std::int32_t x, std::int32_t y);
        ~Unit();
        Unit(const Unit&) = default;
        Unit(Unit&&) = default;
        Unit& operator=(const Unit&) = default;
        Unit& operator=(Unit&&) = default;

        void TakeDamage(std::int32_t amount);

        void Heal(std::int32_t amount);

        void MoveTo(std::int32_t nevX, std::int32_t nevY);

        [[nodiscard]] bool IsAlive() const
    {
        return m_isAlive;
    }

    [[nodiscard]] auto GetId() const
    {
        return m_id;
    }

    [[nodiscard]] std::string_view GetName() const
    {
        return m_name;
    }

    [[nodiscard]] auto GetClass() const
    {
        return m_class;
    }

    [[nodiscard]] auto GetHealth() const
    {
        return m_health;
    }

    [[nodiscard]] auto GetMaxHealth() const
    {
        return m_maxHealth;
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