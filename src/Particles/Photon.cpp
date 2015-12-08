#include "Particles/Photon.hpp"

Photon :: Photon(const Coord c1, const Vector3 v1) : Particle(c1)
{
	;
}

Color Photon :: getColor() const
{
	return Color(1, 1, 0.5);
}

ld Photon :: getCharge() const
{
	return 0;
}

ld Photon :: getMass() const
{
    return PHY_H / (PHY_C * vaweLength);
}
