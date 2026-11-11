namespace Battle;

public class Archer : BaseUnit
{
    public Archer(uint id, string name, int hp, int x, int y)
        : base(id, name, hp, x, y, "ranged", "attacks from a distance")
    {
        Console.WriteLine("[Archer] constructor");
    }

    private Archer(Archer other)
        : base(other.Id, other.Name, other.MaxHealth, other.X, other.Y,
               other.Profile.Specialization, other.Profile.Description)
    {
        CurrentHealth = other.Health;
        if (!other.IsAlive) TakeDamage(MaxHealth);
    }

    public override string ClassName => "Archer";
    public override string Attack() => $"{Name} shoots an arrow";

    // Переопределение без вызова base.Describe().
    public override string Describe() => $"Archer '{Name}' HP={Health}/{MaxHealth}";

    public override BaseUnit Clone() => new Archer(this);
}
