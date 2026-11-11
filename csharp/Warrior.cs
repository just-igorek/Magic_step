namespace Battle;

public sealed class Warrior : BaseUnit
{
    public Warrior(uint id, string name, int hp, int x, int y)
        : base(id, name, hp, x, y, "front line", "close combat specialist")
    {
        Console.WriteLine("[Warrior] constructor");
    }

    private Warrior(Warrior other)
        : base(other.Id, other.Name, other.MaxHealth, other.X, other.Y,
               other.Profile.Specialization, other.Profile.Description)
    {
        CurrentHealth = other.CurrentHealth;
        if (!other.IsAlive) TakeDamage(MaxHealth);
    }

    public override string ClassName => "Warrior";
    public override string Attack() => $"{Name} strikes with a sword";

    public override string Describe()
    {
        var builder = new System.Text.StringBuilder(base.Describe());
        AppendProfile(builder);
        return builder.ToString();
    }

    public override BaseUnit Clone() => new Warrior(this);

    public Warrior RenameAndReturn(string name)
    {
        this.Rename(name);
        return this;
    }
}
