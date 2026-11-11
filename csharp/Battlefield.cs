using System.Text;

namespace Battle;

public class Battlefield
{
    private readonly Cell[,] _cells;

    public Battlefield(int width, int height)
    {
        if (width <= 0 || height <= 0) throw new ArgumentOutOfRangeException(nameof(width));
        Width = width;
        Height = height;
        _cells = new Cell[height, width];
        for (int y = 0; y < height; y++)
            for (int x = 0; x < width; x++)
                _cells[y, x] = new Cell(x, y);
    }

    public int Width { get; }
    public int Height { get; }
    public bool IsValidPosition(int x, int y) => x >= 0 && x < Width && y >= 0 && y < Height;

    public bool PlaceUnit(BaseUnit unit, int x, int y) =>
        unit is not null && IsValidPosition(x, y) && _cells[y, x].SetUnit(unit);

    public void RemoveUnit(int x, int y)
    {
        if (IsValidPosition(x, y)) _cells[y, x].RemoveUnit();
    }

    public BaseUnit? GetUnitAt(int x, int y) =>
        IsValidPosition(x, y) ? _cells[y, x].Occupant : null;

    public override string ToString()
    {
        var builder = new StringBuilder($"Field {Width}x{Height}:");
        for (int y = 0; y < Height; y++)
        {
            builder.AppendLine();
            for (int x = 0; x < Width; x++) builder.Append(_cells[y, x]).Append(' ');
        }
        return builder.ToString();
    }
}
