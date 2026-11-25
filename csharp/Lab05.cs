namespace Battle;

public interface ICombatant : IComparable<ICombatant>
{
    string CombatAction();
    void Support(BaseUnit target);
}
public sealed class InvalidCombatActionException(string message) : Exception(message);

public interface IAbilityStrategy
{
    string Apply(BaseUnit user, BaseUnit target);
}
public sealed class PoisonStrategy : IAbilityStrategy
{
    public string Apply(BaseUnit user, BaseUnit target)
    {
        if (!user.IsAlive || !target.IsAlive) throw new InvalidCombatActionException("Poison requires living units");
        target.TakeDamage(10);
        return $"{user.Name} applies poison to {target.Name}";
    }
}
public sealed class RegenerationStrategy : IAbilityStrategy
{
    public string Apply(BaseUnit user, BaseUnit target)
    {
        if (!user.IsAlive || !target.IsAlive) throw new InvalidCombatActionException("Regeneration requires living units");
        target.Heal(10);
        return $"{user.Name} restores {target.Name}";
    }
}
public static class Lab05
{
    public static void Run()
    {
        Console.WriteLine("\n===== LAB 05: INTERFACES AND POLYMORPHISM =====");
        var warrior = new Warrior(20, "Sentinel", 100, 0, 0);
        var healer = new Healer(21, "Medic", 80, 1, 0);
        BaseUnit baseReference = warrior;
        Console.WriteLine($"Late binding (override): {baseReference.Attack()}");
        Console.WriteLine($"Early binding (hidden new): {baseReference.BindingLabel()} / {warrior.BindingLabel()}");
        ICombatant throughInterface = healer;
        Console.WriteLine($"Interface call: {throughInterface.CombatAction()}");
        throughInterface.Support(warrior);

        var combatants = new List<ICombatant> { warrior, healer };
        combatants.Sort();
        Console.WriteLine($"IComparable sort: {string.Join(", ", combatants.Select(x => x.CombatAction()))}");

        BaseUnit inspected = healer;
        if (inspected is Healer healerType)
            Console.WriteLine($"is check succeeded: {healerType.Name}");
        var maybeHealer = inspected as Healer;
        Console.WriteLine($"as check: {maybeHealer?.ClassName}");

        IAbilityStrategy strategy = new PoisonStrategy();
        Console.WriteLine(strategy.Apply(warrior, healer));
        strategy = new RegenerationStrategy();
        Console.WriteLine(strategy.Apply(healer, warrior));
        try
        {
            strategy.Apply(healer, warrior);
            throw new InvalidCombatActionException("Example rule violation: action already used");
        }
        catch (InvalidCombatActionException ex)
        {
            Console.WriteLine($"Handled rule violation: {ex.Message}");
        }
        finally
        {
            Console.WriteLine("finally: action-processing resources/state finalized");
        }
    }
}
