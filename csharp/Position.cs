namespace Battle;

/// Позиция на поле. Структура: маленькое значение без собственной «личности»,
/// присваивание копирует её целиком.
public struct Position
{
    public Position(int x, int y)
    {
        X = x;
        Y = y;
    }

    public int X { get; set; }

    public int Y { get; set; }

    public override string ToString() => $"({X},{Y})";
}
