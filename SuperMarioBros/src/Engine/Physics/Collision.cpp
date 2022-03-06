#include "Collision.h"

bool Collision::RectCheck(Rect bounds1, Rect bounds2)
{
    return (bounds1.x < bounds2.x + bounds2.width &&
        bounds1.x + bounds1.width > bounds2.x &&
        bounds1.y < bounds2.y + bounds2.height &&
        bounds1.y + bounds1.height > bounds2.y);
}

bool Collision::TilemapCheck(Rect tileBounds, Rect characterBounds, CheckSide side)
{
    switch (side)
    {
    case CheckSide::Bottom:
        return BottomTileCheck(tileBounds, characterBounds);
        break;

    case CheckSide::Top:
        return TopTileCheck(tileBounds, characterBounds);
        break;

    case CheckSide::Left:
        return LeftTileCheck(tileBounds, characterBounds);
        break;

    case CheckSide::Right:
        return RightTileCheck(tileBounds, characterBounds);
        break;
    }

    return false;
}

bool Collision::BottomTileCheck(Rect tileBounds, Rect characterBounds)
{
    return (tileBounds.y + tileBounds.height > characterBounds.y);
}

bool Collision::TopTileCheck(Rect tileBounds, Rect characterBounds)
{
    return (tileBounds.y < characterBounds.y + characterBounds.height);
}

bool Collision::LeftTileCheck(Rect tileBounds, Rect characterBounds)
{
    return (tileBounds.x + tileBounds.width > characterBounds.x);
}

bool Collision::RightTileCheck(Rect tileBounds, Rect characterBounds)
{
    return (tileBounds.x < characterBounds.x + characterBounds.width);
}
