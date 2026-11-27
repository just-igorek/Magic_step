using System.Text;

namespace Battle;

internal static class Program
{
    private static void Main()
    {
        Console.OutputEncoding = Encoding.UTF8;
        Console.WriteLine("===== LAB 05 =====");

        var warrior = new Warrior(20, "Sentinel", 100, 0, 0);
        var healer = new Healer(21, "Medic", 80, 1, 0);

        // Раннее связывание: невиртуальный метод выбирается на основе типа ссылки.
        BaseUnit baseRef = warrior;

        Console.WriteLine(
            $"Early binding: {baseRef.BindingLabel()} / {warrior.BindingLabel()}");

        // Позднее связывание: виртуальный метод выбирается в зависимости от фактического типа объекта.
        Console.WriteLine($"Late binding: {baseRef.Attack()}");

        // Полиморфизм на основе интерфейсов.
        ICombatant actor = healer;

        Console.WriteLine($"Interface dispatch: {actor.CombatAction()}");
        actor.Support(warrior);

        // Реализация IComparable и сортировка.
        var combatants = new List<ICombatant>
        {
            warrior,
            healer
        };

        combatants.Sort();

        Console.WriteLine(
            $"Sorted combatants: {string.Join(", ", combatants.Select(unit => unit.CombatAction()))}");

        // Проверка типов во время выполнения и безопасное приведение типов.
        BaseUnit inspected = healer;

        if (inspected is Healer typed)
        {
            Console.WriteLine($"is: {typed.Name}");
        }

        var cast = inspected as Healer;
        Console.WriteLine($"as: {cast?.ClassName}");

        // изменение функциональности во время выполнения программы.
        IAbilityStrategy strategy = new PoisonStrategy();
        Console.WriteLine(strategy.Apply(warrior, healer));

        strategy = new RegenerationStrategy();
        Console.WriteLine(strategy.Apply(healer, warrior));

        // Пользовательские исключения и обработка исключений.
        healer.TakeDamage(healer.MaxHealth);

        try
        {
            strategy.Apply(healer, warrior);
        }
        catch (InvalidCombatActionException error)
        {
            Console.WriteLine($"Custom exception: {error.Message}");
        }
        catch (Exception error)
        {
            Console.WriteLine($"General exception: {error.Message}");
        }
        finally
        {
            Console.WriteLine("finally: завершение обработки действия");
        }
    }

    
        
}
