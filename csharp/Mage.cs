namespace Battle;

public class Mage : BaseUnit
{
    public Mage(uint id, string name, int hp, int x, int y)
        : base(id, name, hp, x, y, "magic", "uses elemental energy") { }

    private Mage(Mage other)
        : base(other.Id, other.Name, other.MaxHealth, other.X, other.Y,
               other.Profile.Specialization, other.Profile.Description)
    {
        CurrentHealth = other.Health;
        if (!other.IsAlive) TakeDamage(MaxHealth);
    }

    public override string ClassName => "Mage";
    public override string Attack() => $"{Name} casts a fireball";
    public override BaseUnit Clone() => new Mage(this);
}
