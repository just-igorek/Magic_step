namespace Battle;

/// <summary>
/// Абстрактная боевая единица.
/// </summary>
public abstract partial class BaseUnit
{
    private static int _createdCount;

    protected int CurrentHealth;

    protected BaseUnit(
        uint id,
        string name,
        int maxHealth,
        int x,
        int y,
        string specialization,
        string description)
    {
        Id = id;
        Name = string.IsNullOrWhiteSpace(name) ? "noname" : name;
        MaxHealth = Math.Max(0, maxHealth);

        CurrentHealth = MaxHealth;
        X = x;
        Y = y;
        IsAlive = maxHealth > 0;

        Profile = new UnitProfile(specialization, description);

        _createdCount++;

        Console.WriteLine($"[BaseUnit] constructor: {Name}");
    }

    public uint Id { get; }

    public string Name { get; protected set; }

    public int MaxHealth { get; }

    public int Health => CurrentHealth;

    public int X { get; private set; }

    public int Y { get; private set; }

    public bool IsAlive { get; private set; }

    protected UnitProfile Profile { get; set; }

    public abstract string Attack();

    public abstract BaseUnit Clone();

    public abstract string ClassName { get; }

    public virtual string Describe()
    {
        return $"{ClassName} '{Name}' HP={Health}/{MaxHealth} at ({X},{Y})";
    }

    public string BindingLabel()
    {
        return "BaseUnit binding";
    }

    public void TakeDamage(int amount)
    {
        if (amount <= 0 || !IsAlive)
        {
            return;
        }

        CurrentHealth = Math.Max(0, CurrentHealth - amount);

        if (CurrentHealth == 0)
        {
            IsAlive = false;
        }
    }

    public void Heal(int amount)
    {
        if (amount > 0 && IsAlive)
        {
            CurrentHealth = Math.Min(MaxHealth, CurrentHealth + amount);
        }
    }

    public void MoveTo(int x, int y)
    {
        if (IsAlive)
        {
            X = x;
            Y = y;
        }
    }

    public static int CreatedCount => _createdCount;

    public void Rename(string name)
    {
        if (!string.IsNullOrWhiteSpace(name))
        {
            Name = name;
        }
    }

    public void ChangeSpecialization(string value)
    {
        Profile.Specialization = value;
    }

    public string GetSpecializationForDemo()
    {
        return Profile.Specialization;
    }

    public BaseUnit ShallowCopyForDemo()
    {
        return (BaseUnit)MemberwiseClone();
    }

    public override bool Equals(object? obj)
    {
        return obj is BaseUnit other
            && Id == other.Id
            && ClassName == other.ClassName
            && Name == other.Name;
    }

    public override int GetHashCode()
    {
        return HashCode.Combine(Id, ClassName, Name);
    }

    protected void AppendProfile(System.Text.StringBuilder builder)
    {
        builder.Append($" | {Profile.Specialization}: {Profile.Description}");
    }

    protected sealed class UnitProfile
    {
        public UnitProfile(string specialization, string description)
        {
            Specialization = specialization;
            Description = description;
        }

        public string Specialization { get; set; }

        public string Description { get; }
    }
}

public interface ICombatant : IComparable<ICombatant>
{
    string CombatAction();

    void Support(BaseUnit target);
}

public sealed class InvalidCombatActionException : Exception
{
    public InvalidCombatActionException(string message)
        : base(message)
    {
    }
}

public interface IAbilityStrategy
{
    string Apply(BaseUnit user, BaseUnit target);
}

public sealed class PoisonStrategy : IAbilityStrategy
{
    public string Apply(BaseUnit user, BaseUnit target)
    {
        if (!user.IsAlive || !target.IsAlive)
        {
            throw new InvalidCombatActionException("Poison requires living units");
        }

        target.TakeDamage(10);

        return $"{user.Name} applies poison to {target.Name}";
    }
}

public sealed class RegenerationStrategy : IAbilityStrategy
{
    public string Apply(BaseUnit user, BaseUnit target)
    {
        if (!user.IsAlive || !target.IsAlive)
        {
            throw new InvalidCombatActionException("Regeneration requires living units");
        }

        target.Heal(10);

        return $"{user.Name} restores {target.Name}";
    }
}
