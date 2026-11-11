# Лабораторная работа 4 — C#

Скопируйте классы в существующую папку `csharp/`. Старый `Unit.cs` и `UnitClass.cs`
больше не нужны для новой иерархии. `Battlefield` и `Cell` работают с `BaseUnit`.

Проверьте, что `BaseUnit` объявлен как `partial`, поскольку демонстрационные методы
поверхностного копирования вынесены в `BaseUnit.DemoExtensions.cs`. В файле
`BaseUnit.cs` замените объявление `public abstract class BaseUnit` на
`public abstract partial class BaseUnit`.

Сборка и запуск из корня репозитория:

```bash
dotnet build csharp
dotnet run --project csharp
```
