namespace Battle;

/// Клетка поля. Создаётся только самим полем (композиция) и наружу не отдаётся.
/// Юнит создаётся снаружи, клетка хранит лишь ссылку на него (агрегация).
internal sealed class Cell
{
    private Unit? _occupant;

    public Cell(int x, int y)
    {
        X = x;
        Y = y;
        Console.WriteLine($"[Cell] Constructor: cell ({x},{y})");
    }

    public int X { get; }

    public int Y { get; }

    public bool IsEmpty => _occupant is null;

    public Unit? Occupant => _occupant;

    public bool SetUnit(Unit unit)
    {
        if (unit is null)
        {
            Console.WriteLine("[Cell] Error: null reference to unit passed.");
            return false;
        }

        if (!IsEmpty)
        {
            Console.WriteLine($"[Cell] Error: cell ({X},{Y}) already occupied by a unit '{_occupant!.Name}'.");
            return false;
        }

        _occupant = unit;
        return true;
    }

    public void RemoveUnit() => _occupant = null;

    public override string ToString()
    {
        if (_occupant is null)
        {
            return ".";
        }

        return _occupant.IsAlive ? "U" : "x";
    }
}
