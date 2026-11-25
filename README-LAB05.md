# Лабораторная работа 5 — C++17

## Что добавлено
- `ICombatant` — интерфейс без полей с виртуальным noexcept-деструктором; его реализуют `Warrior` и `Healer` наряду с наследованием от `BaseUnit`.
- `PerformSupport(const ICombatant&, BaseUnit&)` показывает работу через интерфейс.
- Виртуальный `Attack()` демонстрирует позднее связывание; `Warrior::BindingLabel()` доступен через конкретный тип (раннее связывание при обращении через тип класса).
- `dynamic_cast` проверяет фактический тип.
- `IAbilityStrategy`, `PoisonStrategy`, `RegenerationStrategy` и `unique_ptr<IAbilityStrategy>` демонстрируют смену поведения во время выполнения.
- `InvalidCombatAction` и try/catch демонстрируют обработку нарушения правила.
- Сортировка указателей на интерфейс использует CompareCombatants.

## Сборка и запуск
Из корня репозитория:
```bash
g++ -std=c++17 -Wall -Wextra -pedantic -Iinclude main.cpp src/battle/*.cpp -o build-lab05
./build-lab05
```
