using System.Text;

namespace Battle;

internal static class Program
{
    private static void Main()
    {
        Console.OutputEncoding = Encoding.UTF8;
        RunLab05();
    }

    private static void RunLab05()
    {
        Console.WriteLine("===== LAB 05 =====");

        var warrior = new Warrior(20, "Sentinel", 100, 0, 0);
        var healer = new Healer(21, "Medic", 80, 1, 0);

        // Early binding: the non-virtual method is selected by the reference type.
        BaseUnit baseRef = warrior;

        Console.WriteLine(
            $"Early binding: {baseRef.BindingLabel()} / {warrior.BindingLabel()}");

        // Late binding: the virtual method is selected by the actual object type.
        Console.WriteLine($"Late binding: {baseRef.Attack()}");

        // Interface-based polymorphism.
        ICombatant actor = healer;

        Console.WriteLine($"Interface dispatch: {actor.CombatAction()}");
        actor.Support(warrior);

        // IComparable implementation and sorting.
        var combatants = new List<ICombatant>
        {
            warrior,
            healer
        };

        combatants.Sort();

        Console.WriteLine(
            $"Sorted combatants: {string.Join(", ", combatants.Select(unit => unit.CombatAction()))}");

        // Runtime type checking and safe casts.
        BaseUnit inspected = healer;

        if (inspected is Healer typed)
        {
            Console.WriteLine($"is: {typed.Name}");
        }

        var cast = inspected as Healer;
        Console.WriteLine($"as: {cast?.ClassName}");

        // Strategy pattern: change the ability at runtime.
        IAbilityStrategy strategy = new PoisonStrategy();
        Console.WriteLine(strategy.Apply(warrior, healer));

        strategy = new RegenerationStrategy();
        Console.WriteLine(strategy.Apply(healer, warrior));

        // Custom exception and exception handling.
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
