#include "Particles/QuarkU.hpp"

QuarkU :: QuarkU(Coord c1, QUARK_COLOR c2)           : Quark(c1, c2){}
QuarkU :: QuarkU(Coord c1, QUARK_COLOR c2, Speed s1) : Quark(c1, c2, s1){}

//Color QuarkU :: getColor () const {return Color(1, 0, 0);}
ld    QuarkU :: getCharge() const {return PHY_QUARK_U_Q;}
ld    QuarkU :: getMass  () const {return PHY_QUARK_U_M;}
