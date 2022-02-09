#include "Collision.h"

bool Collision::Check(RECT bounds1, RECT bounds2)
{
    return (bounds1.left < bounds2.left + bounds2.right &&
        bounds1.left + bounds1.right > bounds2.left &&
        bounds1.bottom < bounds2.bottom + bounds2.top &&
        bounds1.top + bounds1.bottom > bounds2.bottom);
}
