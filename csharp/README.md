# Magic Step — версия на C#

Перенос трёх классов ЛР 2 (`Unit`, `Cell`, `Battlefield`) на язык с управляемой памятью.
Память освобождает сборщик мусора, `delete` и деструкторов нет.

| Файл | Что внутри |
|---|---|
| `Unit.cs` | юнит: свойства `Health`, `Position`, `IsAlive`, методы `TakeDamage`, `Heal`, `MoveTo`, `ToString()` |
| `Cell.cs` | клетка (внутренний класс, создаётся только полем) |
| `Battlefield.cs` | поле; клетки создаёт в конструкторе и наружу не отдаёт (композиция) |
| `Position.cs` | структура (`struct`) для демонстрации типа-значения |
| `UnitClass.cs` | перечисление классов юнитов |
| `BattleLog.cs` | журнал, `IDisposable` (освобождение ресурса через `using`) |
| `Program.cs` | демонстрация: композиция, агрегация, правило, ссылки/копии, struct, `using`, сборщик мусора |

## Сборка и запуск

Нужен [.NET SDK](https://dotnet.microsoft.com/download) 8.0 или новее. Из корня репозитория:

```bash
dotnet build csharp
dotnet run --project csharp
```

Если в консоли Windows вместо текста вопросительные знаки: `chcp 65001`.

Если установлена другая версия SDK и сборка жалуется на `net8.0`, поменяйте `TargetFramework`
в `csharp/MagicStep.csproj` на свою версию (например, `net9.0`).
Папки `bin/` и `obj/` в репозиторий не попадают (`.gitignore`).
