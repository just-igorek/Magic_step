namespace Battle;

public class Healer : BaseUnit, ICombatant
{
    public Healer(uint id, string name, int hp, int x, int y)
        : base(id, name, hp, x, y, "support", "restores allies' health")
    {
    }

    private Healer(Healer other)
        : base(
            other.Id,
            other.Name,
            other.MaxHealth,
            other.X,
            other.Y,
            other.Profile.Specialization,
            other.Profile.Description)
    {
        CurrentHealth = other.Health;

        if (!other.IsAlive)
        {
            TakeDamage(MaxHealth);
        }
    }

    public override string ClassName => "Healer";

    public override string Attack()
    {
        return $"{Name} uses a staff strike";
    }

    public override BaseUnit Clone()
    {
        return new Healer(this);
    }

    public string CombatAction()
    {
        return Attack();
    }

    public void Support(BaseUnit target)
    {
        if (!IsAlive || !target.IsAlive)
        {
            throw new InvalidCombatActionException("Healing requires living units");
        }

        target.Heal(15);
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
}
