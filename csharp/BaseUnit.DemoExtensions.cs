namespace Battle;

public abstract partial class BaseUnit
{
    // MemberwiseClone доступен только внутри класса; метод оставлен для демонстрации ЛР.
    public BaseUnit ShallowCopyForDemo() => (BaseUnit)MemberwiseClone();

    public string GetSpecializationForDemo() => Profile.Specialization;
}
