namespace Battle;

public sealed class Warrior : BaseUnit, ICombatant
{
    public Warrior(uint id, string name, int hp, int x, int y)
        : base(id, name, hp, x, y, "front line", "close combat specialist")
    {
        Console.WriteLine("[Warrior] constructor");
    }

    private Warrior(Warrior other)
        : base(
            other.Id,
            other.Name,
            other.MaxHealth,
            other.X,
            other.Y,
            other.Profile.Specialization,
            other.Profile.Description)
    {
        CurrentHealth = other.CurrentHealth;

        if (!other.IsAlive)
        {
            TakeDamage(MaxHealth);
        }
    }

    public override string ClassName => "Warrior";

    public override string Attack()
    {
        return $"{Name} strikes with a sword";
    }

    public override string Describe()
    {
        var builder = new System.Text.StringBuilder(base.Describe());

        AppendProfile(builder);

        return builder.ToString();
    }

    public override BaseUnit Clone()
    {
        return new Warrior(this);
    }

    public Warrior RenameAndReturn(string name)
    {
        this.Rename(name);

        return this;
    }

    public string CombatAction()
    {
        return Attack();
    }

    public void Support(BaseUnit target)
    {
        if (!IsAlive || !target.IsAlive)
        {
            throw new InvalidCombatActionException("Support requires living units");
        }

        target.Heal(5);
    }

    public int CompareTo(ICombatant? other)
    {
        if (other is null)
        {
            return 1;
        }

        return string.Compare(
            CombatAction(),
            other.CombatAction(),
            StringComparison.Ordinal);
    }

    public new string BindingLabel()
    {
        return "Warrior binding";
    }
}
