using System.Text;
namespace Battle;
internal static class Program
{
    private static void Main()
    {
        Console.OutputEncoding=Encoding.UTF8;
        Console.WriteLine("===== POLYMORPHISM =====");
        BaseUnit[] squad={new Warrior(1,"Arthas",120,0,0),new Archer(2,"Legolas",80,1,0),new Mage(3,"Merlin",65,2,0),new Healer(4,"Mercy",75,3,0)};
        foreach(BaseUnit unit in squad){Console.WriteLine(unit.Describe());Console.WriteLine(unit.Attack());}
        Console.WriteLine("\n===== SHALLOW AND DEEP COPY =====");
        var source=new Warrior(5,"Guard",100,0,1);
        var shallow=(Warrior)source.ShallowCopyForDemo();
        shallow.ChangeSpecialization("shared specialization");
        Console.WriteLine($"Source profile after shallow copy change: {source.GetSpecializationForDemo()}");
        var deep=source.Clone(); deep.ChangeSpecialization("independent specialization");
        Console.WriteLine($"Source profile after Clone(): {source.GetSpecializationForDemo()}");
        Console.WriteLine($"Clone profile: {((Warrior)deep).GetSpecializationForDemo()}");
        Console.WriteLine("\n===== STRINGS, this, EQUALITY =====");
        string label=source.Name+" the defender";int index=label.IndexOf("defender",StringComparison.Ordinal);
        Console.WriteLine($"Substring: {label.Substring(index)}");
        source.RenameAndReturn("Veteran").Rename("Veteran Guard");
        Console.WriteLine($"Renamed: {source.Name}");
        Lab05.Run();
        Console.WriteLine($"Created objects: {BaseUnit.CreatedCount}");
        using var log=new BattleLog(); log.Write("The demonstration is running.");
    }
}
