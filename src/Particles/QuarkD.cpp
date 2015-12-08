#include "Particles/QuarkD.hpp"

QuarkD :: QuarkD(Coord c1, QUARK_COLOR c2)           : Quark(c1, c2){}
QuarkD :: QuarkD(Coord c1, QUARK_COLOR c2, Speed s1) : Quark(c1, c2, s1){}

//Color QuarkD :: getColor () const {return Color(0, 0, 1);}
ld    QuarkD :: getCharge() const {return PHY_QUARK_D_Q;}
ld    QuarkD :: getMass  () const {return PHY_QUARK_D_M;}
