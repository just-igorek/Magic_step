namespace Battle;

/// Ячейка хранит ссылку на базовый тип, но не создаёт юнита.
internal sealed class Cell
{
    private BaseUnit? _occupant;
    public Cell(int x, int y) { X = x; Y = y; }
    public int X { get; }
    public int Y { get; }
    public bool IsEmpty => _occupant is null;
    public BaseUnit? Occupant => _occupant;

    public bool SetUnit(BaseUnit unit)
    {
        if (unit is null || !IsEmpty) return false;
        _occupant = unit;
        return true;
    }

    public void RemoveUnit() => _occupant = null;
    public override string ToString() => _occupant is null ? "." : (_occupant.IsAlive ? "U" : "x");
}
