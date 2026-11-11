namespace Battle;

/// Демонстрация using var и IDisposable для ресурса.
internal sealed class BattleLog : IDisposable
{
    private bool _disposed;

    public void Write(string message)
    {
        if (_disposed) throw new ObjectDisposedException(nameof(BattleLog));
        Console.WriteLine($"[BattleLog] {message}");
    }

    public void Dispose()
    {
        if (_disposed) return;
        _disposed = true;
        Console.WriteLine("[BattleLog] resource released by using");
    }
}
