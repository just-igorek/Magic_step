#pragma once
#include "unit.hpp"
#include <memory>
#include <stdexcept>
#include <string>

namespace battle {
class ICombatant {
public:
    virtual ~ICombatant() noexcept = default;
    virtual std::string CombatAction() const = 0;
    virtual void Support(BaseUnit& target) const = 0;
    virtual int CompareCombatants(const ICombatant& other) const noexcept = 0;
};
class InvalidCombatAction : public std::runtime_error {
public: explicit InvalidCombatAction(const std::string& message) : std::runtime_error(message) {}
};
class IAbilityStrategy {
public:
    virtual ~IAbilityStrategy() noexcept = default;
    virtual std::string Apply(BaseUnit& user, BaseUnit& target) const = 0;
};
class PoisonStrategy final : public IAbilityStrategy {
public: std::string Apply(BaseUnit& user, BaseUnit& target) const override;
};
class RegenerationStrategy final : public IAbilityStrategy {
public: std::string Apply(BaseUnit& user, BaseUnit& target) const override;
};
void PerformSupport(const ICombatant& actor, BaseUnit& target);
void DemonstrateLab05();
}
