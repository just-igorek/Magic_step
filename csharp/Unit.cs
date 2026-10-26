namespace Battle;

/// Боевая единица. Правила: урон и лечение положительные, мёртвый не двигается и не лечится.
public class Unit
{
    private const string BaseName = "noname";

    private int _health;

    public Unit(uint id, string name, UnitClass unitClass, int maxHealth, int x, int y)
    {
        Id = id;
        Name = string.IsNullOrEmpty(name) ? BaseName : name;
        Class = unitClass;
        MaxHealth = Math.Max(0, maxHealth);
        Health = MaxHealth;
        Position = new Position(x, y);
        IsAlive = maxHealth > 0;

        if (maxHealth <= 0)
        {
            Console.WriteLine($"[Unit] Error: maximum health must be greater than zero. Unit '{Name}' created dead.");
        }
    }

    public uint Id { get; }

    public string Name { get; }

    public UnitClass Class { get; }

    public int MaxHealth { get; }

    public int Health
    {
        get => _health;
        private set => _health = Math.Clamp(value, 0, MaxHealth);
    }

    public Position Position { get; private set; }

    public bool IsAlive { get; private set; }

    public void TakeDamage(int amount)
    {
        if (amount <= 0)
        {
            Console.WriteLine("[Unit] Error: damage must be positive.");
            return;
        }

        if (!IsAlive)
        {
            Console.WriteLine($"[Unit] Error: cannot attack a dead unit '{Name}'.");
            return;
        }

        Health -= amount;
        if (Health == 0)
        {
            IsAlive = false;
            Console.WriteLine($"[Unit] Unit '{Name}' died.");
        }
    }

    public void Heal(int amount)
    {
        if (amount <= 0)
        {
            Console.WriteLine("[Unit] Error: the treatment must be positive.");
            return;
        }

        if (!IsAlive)
        {
            Console.WriteLine($"[Unit] Error: Cannot heal a dead unit. '{Name}'.");
            return;
        }

        Health += amount;
    }

    public void MoveTo(int newX, int newY)
    {
        if (!IsAlive)
        {
            Console.WriteLine($"[Unit] Error: dead unit '{Name}' cannot move.");
            return;
        }

        Position = new Position(newX, newY);
    }

    public override string ToString() =>
        $"Unit{{id={Id}, name={Name}, hp={Health}/{MaxHealth}, pos={Position}, alive={(IsAlive ? "yes" : "no")}}}";
}
