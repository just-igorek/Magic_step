#pragma once

#include "unit_profile.hpp"

#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <stdexcept>

namespace battle
{
class BaseUnit
{
public:
    using IdType = std::uint32_t;

    BaseUnit();
    BaseUnit(IdType id, std::string_view name, std::int32_t maxHealth,
             std::int32_t x, std::int32_t y, std::string specialization,
             std::string description);
    BaseUnit(const BaseUnit& other);
    BaseUnit(BaseUnit&& other) noexcept;
    BaseUnit& operator=(const BaseUnit& other);
    BaseUnit& operator=(BaseUnit&& other) noexcept;
    virtual ~BaseUnit();

    virtual std::string Attack() const = 0;
    virtual std::unique_ptr<BaseUnit> Clone() const = 0;
    virtual std::string GetClassName() const = 0;

    virtual std::string Describe() const;
    void TakeDamage(std::int32_t amount);
    void Heal(std::int32_t amount);
    void MoveTo(std::int32_t newX, std::int32_t newY);

    [[nodiscard]] bool IsAlive() const noexcept { return m_isAlive; }
    [[nodiscard]] IdType GetId() const noexcept { return m_id; }
    [[nodiscard]] const std::string& GetName() const noexcept { return m_name; }
    [[nodiscard]] std::int32_t GetHealth() const noexcept { return m_health; }
    [[nodiscard]] std::int32_t GetMaxHealth() const noexcept { return m_maxHealth; }
    [[nodiscard]] std::int32_t GetX() const noexcept { return m_x; }
    [[nodiscard]] std::int32_t GetY() const noexcept { return m_y; }
    [[nodiscard]] const UnitProfile& GetProfile() const noexcept { return *m_profile; }

    BaseUnit& SetName(std::string name);
    void ChangeSpecialization(std::string specialization);
    [[nodiscard]] static std::size_t GetAliveObjectCount() noexcept;

    // Наглядно демонстрирует общую вложенную часть при обычном копировании.
    [[nodiscard]] std::shared_ptr<UnitProfile> ShareProfile() const noexcept { return m_profile; }
    std::string BindingLabel() const { return "BaseUnit binding"; }

protected:
    IdType m_id{0};
    std::string m_name{"noname"};
    std::int32_t m_health{0};
    std::int32_t m_maxHealth{0};
    std::int32_t m_x{0};
    std::int32_t m_y{0};
    bool m_isAlive{false};
    std::shared_ptr<UnitProfile> m_profile;

    void MakeProfileUnique();
    void PrintBaseDescription(std::string& result) const;

private:
    static std::size_t s_aliveObjects;
};
class ICombatant {
public:
    virtual ~ICombatant() noexcept = default;
    virtual std::string CombatAction() const = 0;
    virtual void Support(BaseUnit& target) const = 0;
    virtual int CompareCombatants(const ICombatant& other) const = 0;
};
class InvalidCombatAction : public std::runtime_error {
public:
    explicit InvalidCombatAction(const std::string& message) : std::runtime_error(message) {}
};
class IAbilityStrategy {
public:
    virtual ~IAbilityStrategy() noexcept = default;
    virtual std::string Apply(BaseUnit& user, BaseUnit& target) const = 0;
};
class PoisonStrategy final : public IAbilityStrategy {
public:
    std::string Apply(BaseUnit& user, BaseUnit& target) const override {
        if (!user.IsAlive() || !target.IsAlive()) throw InvalidCombatAction("Poison requires living units");
        target.TakeDamage(10); return user.GetName() + " applies poison to " + target.GetName();
    }
};
class RegenerationStrategy final : public IAbilityStrategy {
public:
    std::string Apply(BaseUnit& user, BaseUnit& target) const override {
        if (!user.IsAlive() || !target.IsAlive()) throw InvalidCombatAction("Regeneration requires living units");
        target.Heal(10); return user.GetName() + " restores " + target.GetName();
    }
};
}
