#include "Particles/Electron.hpp"

Electron :: Electron(const Coord c1) : Particle(c1){}
Electron :: Electron(const Coord c1, const Speed s1) : Particle(c1, s1){}

Color Electron :: getColor () const {return Color(0, 1, 1);}
ld    Electron :: getCharge() const {return PHY_ELECTRON_Q;}
ld    Electron :: getMass  () const {return PHY_ELECTRON_M;}
