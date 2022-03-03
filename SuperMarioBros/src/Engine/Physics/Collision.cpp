#include "Collision.h"

bool Collision::RectCheck(RECT bounds1, RECT bounds2)
{
    return (bounds1.left < bounds2.left + bounds2.right &&
        bounds1.left + bounds1.right > bounds2.left &&
        bounds1.bottom < bounds2.bottom + bounds2.top &&
        bounds1.top + bounds1.bottom > bounds2.bottom);
}

bool Collision::TileCheck(RECT tileBounds, RECT bounds, CheckSide& side)
{
    /*
    // Top collision
    if (tileBounds.bottom >= bounds.bottom + bounds.top)
    {
        side |= CheckSide::Top;
    }
    */

    // Bottom collision
    if (tileBounds.bottom + tileBounds.top >= bounds.bottom)
    {
        side |= CheckSide::Bottom;
    }

    /*
    // Left collision
    if (tileBounds.left + tileBounds.right >= bounds.left)
    {
        side |= CheckSide::Left;
    }

    // Right collision
    if (tileBounds.left <= bounds.left + bounds.right)
    {
        side |= CheckSide::Right;
    }
    */

    return side != CheckSide::None;
}
