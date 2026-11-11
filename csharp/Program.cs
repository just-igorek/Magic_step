using System.Text;

namespace Battle;

internal static class Program
{
    private static void Main()
    {
        Console.OutputEncoding = Encoding.UTF8;

        Console.WriteLine("===== POLYMORPHISM =====");
        BaseUnit[] squad =
        {
            new Warrior(1, "Arthas", 120, 0, 0),
            new Archer(2, "Legolas", 80, 1, 0),
            new Mage(3, "Merlin", 65, 2, 0),
            new Healer(4, "Mercy", 75, 3, 0)
        };

        foreach (BaseUnit unit in squad)
        {
            Console.WriteLine(unit.Describe());
            Console.WriteLine(unit.Attack());
        }

        Console.WriteLine("\n===== SHALLOW AND DEEP COPY =====");
        var source = new Warrior(5, "Guard", 100, 0, 1);
        // MemberwiseClone создаёт поверхностную копию: вложенный Profile остаётся общей ссылкой.
        var shallow = (Warrior)source.ShallowCopyForDemo();
        shallow.ChangeSpecialization("shared specialization");
        Console.WriteLine($"Source profile after shallow copy change: {source.GetSpecializationForDemo()}");

        var deep = source.Clone();
        deep.ChangeSpecialization("independent specialization");
        Console.WriteLine($"Source profile after Clone(): {source.GetSpecializationForDemo()}");
        Console.WriteLine($"Clone profile: {deep.GetSpecializationForDemo()}");

        Console.WriteLine("\n===== STRINGS, this, EQUALITY =====");
        string label = source.Name + " the defender";
        int index = label.IndexOf("defender", StringComparison.Ordinal);
        Console.WriteLine($"Substring: {label.Substring(index)}");
        Console.WriteLine($"Name comparison: {source.Name == "Guard"}");
        source.RenameAndReturn("Veteran").Rename("Veteran Guard");
        Console.WriteLine($"Renamed: {source.Name}");
        var same = new Warrior(5, "Veteran Guard", 100, 0, 1);
        Console.WriteLine($"Equals by content: {source.Equals(same)}");
        Console.WriteLine($"Hash codes equal: {source.GetHashCode() == same.GetHashCode()}");

        Console.WriteLine("\n===== STATIC MEMBERS =====");
        Console.WriteLine($"Created objects: {BaseUnit.CreatedCount}");

        Console.WriteLine("\n===== USING =====");
        using var log = new BattleLog();
        log.Write("The demonstration is running.");

        Console.WriteLine("\n===== BATTLEFIELD =====");
        var field = new Battlefield(4, 2);
        field.PlaceUnit(source, 0, 0);
        field.PlaceUnit(new Archer(6, "Ranger", 70, 1, 1), 1, 1);
        Console.WriteLine(field);
    }
}
