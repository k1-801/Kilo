#pragma once

#ifndef QUARK_D_HPP_INCLUDED
#define QUARK_D_HPP_INCLUDED

#include "StdInclude.hpp"

class QuarkD;

#include "Particles/Quark.hpp"

class QuarkD : public Quark
{
	public:
		QuarkD(const Coord, const QUARK_COLOR);
		QuarkD(const Coord, const QUARK_COLOR, const Speed);

		//Color getColor () const;
		ld    getCharge() const;
		ld    getMass  () const;
};

#endif // QUARK_D_HPP_INCLUDED
