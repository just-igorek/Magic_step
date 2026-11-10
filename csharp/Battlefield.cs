using System.Text;

namespace Battle;

/// Поле из клеток. Клетки создаёт само и никому не отдаёт (композиция).
public class Battlefield
{
    private const int MinSize = 1;

    private readonly Cell[,] _cells;

    public Battlefield(int width, int height)
    {
        if (width < MinSize || height < MinSize)
        {
            Console.WriteLine($"[Battlefield] Error: Field dimensions must be >= {MinSize}. Field not created.");
            Width = 0;
            Height = 0;
            _cells = new Cell[0, 0];
            return;
        }

        Width = width;
        Height = height;
        _cells = new Cell[height, width];
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                _cells[y, x] = new Cell(x, y);
            }
        }

        Console.WriteLine($"[Battlefield] Field created {Width}x{Height}");
    }

    public int Width { get; }

    public int Height { get; }

    public bool IsValidPosition(int x, int y) => x >= 0 && x < Width && y >= 0 && y < Height;

    public bool PlaceUnit(Unit unit, int x, int y)
    {
        if (unit is null)
        {
            Console.WriteLine("[Battlefield] Error: null reference to unit.");
            return false;
        }

        if (!IsValidPosition(x, y))
        {
            Console.WriteLine($"[Battlefield] Error: position ({x},{y}) off the field {Width}x{Height}.");
            return false;
        }

        return _cells[y, x].SetUnit(unit);
    }

    public void RemoveUnit(int x, int y)
    {
        if (!IsValidPosition(x, y))
        {
            Console.WriteLine($"[Battlefield] Error: position ({x},{y}) off the field.");
            return;
        }

        _cells[y, x].RemoveUnit();
    }

    public bool IsCellEmpty(int x, int y) => IsValidPosition(x, y) && _cells[y, x].IsEmpty;

    public Unit? GetUnitAt(int x, int y) => IsValidPosition(x, y) ? _cells[y, x].Occupant : null;

    public override string ToString()
    {
        var builder = new StringBuilder();
        builder.Append($"Field {Width}x{Height}:");
        for (int y = 0; y < Height; y++)
        {
            builder.AppendLine();
            for (int x = 0; x < Width; x++)
            {
                builder.Append(_cells[y, x]).Append(' ');
            }
        }

        return builder.ToString();
    }
}
