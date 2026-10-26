using System.Runtime.CompilerServices;
using System.Text;
 
namespace Battle;
 
internal static class Program
{
    private static void Main()
    {
        Console.OutputEncoding = Encoding.UTF8;
 
        Console.WriteLine("===== 1. COMPOSITION: field of sparse cells =====");
        {
            var field = new Battlefield(3, 3);
            Console.WriteLine(field);
        }
 
        Console.WriteLine();
        Console.WriteLine("===== 2. AGGREGATION: the unit exists independently of the field =====");
        var hero = new Unit(1, "Warrior", UnitClass.Warrior, 100, 0, 0);
        Console.WriteLine(hero);
 
        {
            var field = new Battlefield(3, 3);
            field.PlaceUnit(hero, 0, 0);
            Console.WriteLine(field);
        }
 
        Console.WriteLine($"Unit after the field is gone: {hero}");
 
        Console.WriteLine();
        Console.WriteLine("===== 3. RULE CHECK: cell is occupied =====");
        var board = new Battlefield(3, 3);
        var enemy = new Unit(2, "Archer", UnitClass.Archer, 80, 1, 1);
 
        Console.WriteLine("Correct action: place the Warrior at (0,0).");
        board.PlaceUnit(hero, 0, 0);
 
        Console.WriteLine("Violation: placing the Archer on the same square (0,0).");
        board.PlaceUnit(enemy, 0, 0);
        Console.WriteLine(board);
 
        Console.WriteLine();
        Console.WriteLine("===== 4. MEMORY MANAGEMENT =====");
 
        Console.WriteLine("-- references and copies --");
        var first = new Unit(3, "Mage", UnitClass.Mage, 60, 2, 2);
        Unit second = first;
        Console.WriteLine("second = first; second.TakeDamage(20);");
        second.TakeDamage(20);
        Console.WriteLine($"first:  {first}");
        Console.WriteLine($"second: {second}");
        Console.WriteLine($"first == second: {first == second}  (one object, two references)");
 
        Console.WriteLine("-- struct: assignment copies the value --");
        var pointA = new Position(1, 1);
        Position pointB = pointA;
        Console.WriteLine("pointB = pointA; pointB.X = 10;");
        pointB.X = 10;
        Console.WriteLine($"pointA: {pointA}");
        Console.WriteLine($"pointB: {pointB}  (a copy, pointA did not change)");
 
        Console.WriteLine("-- releasing a resource without a destructor: IDisposable + using --");
        using (var log = new BattleLog("Turn 1"))
        {
            log.Write($"hero: {hero}");
            log.Write($"enemy: {enemy}");
            Console.WriteLine("    leaving the using block...");
        }
 
        Console.WriteLine("using block left: Dispose() has already run");
 
        Console.WriteLine("-- garbage collector --");
        WeakReference<Unit> watcher = CreateTemporaryUnit();
        Console.WriteLine($"no references left, GC has not run yet, object alive: {IsAlive(watcher)}");
        GC.Collect();
        GC.WaitForPendingFinalizers();
        Console.WriteLine($"after GC.Collect(), object alive: {IsAlive(watcher)}");
 
        Console.WriteLine();
        Console.WriteLine("===== 5. UNIT RULE CHECK =====");
        hero.TakeDamage(30);
        Console.WriteLine(hero);
        hero.Heal(10);
        Console.WriteLine(hero);
        hero.TakeDamage(1000);
        Console.WriteLine(hero);
        hero.Heal(50);
        hero.MoveTo(1, 1);
 
        Console.WriteLine();
        Console.WriteLine("===== END =====");
    }
 
    // Проверяется в отдельном методе: использование `out _` в методе Main привело бы к созданию скрытой локальной переменной,
    // которая в отладочной сборке (Debug build) удерживала бы объект в памяти, тем самым нарушая чистоту демонстрации.
    [MethodImpl(MethodImplOptions.NoInlining)]
    private static bool IsAlive(WeakReference<Unit> reference) => reference.TryGetTarget(out _);
 
    // Отдельный метод: после возврата из него ничто не удерживает сильную ссылку на объект (unit),
    // даже в отладочной сборке (локальная переменная могла бы поддерживать его существование вплоть до завершения функции Main).
    [MethodImpl(MethodImplOptions.NoInlining)]
    private static WeakReference<Unit> CreateTemporaryUnit()
    {
        var temp = new Unit(4, "Temporary", UnitClass.Healer, 30, 2, 0);
        Console.WriteLine($"created: {temp}");
        return new WeakReference<Unit>(temp);
    }
}