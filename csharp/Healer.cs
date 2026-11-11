namespace Battle;

public class Healer : BaseUnit
{
    public Healer(uint id, string name, int hp, int x, int y)
        : base(id, name, hp, x, y, "support", "restores allies' health") { }

    private Healer(Healer other)
        : base(other.Id, other.Name, other.MaxHealth, other.X, other.Y,
               other.Profile.Specialization, other.Profile.Description)
    {
        CurrentHealth = other.Health;
        if (!other.IsAlive) TakeDamage(MaxHealth);
    }

    public override string ClassName => "Healer";
    public override string Attack() => $"{Name} uses a staff strike";
    public override BaseUnit Clone() => new Healer(this);
}
