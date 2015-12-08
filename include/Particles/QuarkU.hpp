#pragma once

#ifndef QUARK_U_HPP_INCLUDED
#define QUARK_U_HPP_INCLUDED

#include "StdInclude.hpp"

class QuarkU;

#include "Particles/Quark.hpp"

class QuarkU : public Quark
{
	public:
		QuarkU(const Coord, const QUARK_COLOR);
		QuarkU(const Coord, const QUARK_COLOR, const Speed);

		//Color getColor () const;
		ld    getCharge() const;
		ld    getMass  () const;
};

#endif // QUARK_U_HPP_INCLUDED
