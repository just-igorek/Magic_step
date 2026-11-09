namespace Battle;

/// Журнал боя. Держит «ресурс» и закрывает его в Dispose(): после выхода из блока using
/// вызов гарантирован, в отличие от сборки мусора, момент которой неизвестен.
public sealed class BattleLog : IDisposable
{
    private readonly string _title;

    public BattleLog(string title)
    {
        _title = title;
        Console.WriteLine($"[+] log opened: {_title}");
    }

    public void Write(string line) => Console.WriteLine($"    {line}");

    public void Dispose() => Console.WriteLine($"[-] log closed: {_title}");
}
