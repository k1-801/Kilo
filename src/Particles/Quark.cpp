#include "Quark.hpp"

std :: vector <Quark*> Quark :: quarkList;

Quark :: Quark(Coord c1, QUARK_COLOR c2)           : Particle(c1){create(c2);}
Quark :: Quark(Coord c1, QUARK_COLOR c2, Speed s1) : Particle(c1, s1){create(c2);}
Quark :: ~Quark(){}

void Quark :: create(QUARK_COLOR c1)
{
	quarkList.push_back(this);
	qc = c1;
}

QUARK_COLOR Quark :: getQuarkColor() const {return qc;}

Color       Quark :: getColor() const
{
	class QuarkColorIsBrokenException : public std :: exception {};
	// Return color as QuarkColor
    switch(qc)
    {
    	// None
		case QC_NONE:
			return Color(0.1, 0.1, 0.1);

		// Straight
		case QC_RED:
			return Color(1, 0, 0);
		case QC_GREEN:
			return Color(0, 1, 0);
		case QC_BLUE:
			return Color(0, 0, 1);

		// Reverse
		case QC_ARED:
            return Color(0, 0.15, 0.15);
		case QC_AGREEN:
			return Color(0.15, 0, 0.15);
		case QC_ABLUE:
			return Color(0.15, 0.15, 0);
    }
    throw QuarkColorIsBrokenException();
}
