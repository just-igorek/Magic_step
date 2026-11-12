# Лабораторная работа 4 — C++

Скопируйте содержимое `include/`, `src/`, `main.cpp` в соответствующие места C++-проекта.
Добавьте новые `.cpp` в список исходников вашей системы сборки.

Пример сборки из папки `cpp`:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic -Iinclude main.cpp src/battle/unit.cpp src/battle/warrior.cpp src/battle/archer.cpp src/battle/mage.cpp src/battle/healer.cpp src/battle/cell.cpp src/battle/battlefield.cpp -o lab04
./lab04
```

`BaseUnit` — абстрактный класс. `Warrior`, `Archer`, `Mage`, `Healer` реализуют `Attack()`.
Обычный конструктор копирования разделяет `UnitProfile` через `shared_ptr`, а `Clone()`
создаёт отдельный профиль. `Warrior` помечен `final`. Базовый деструктор виртуальный.
