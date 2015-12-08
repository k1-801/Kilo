#pragma once

#ifndef ELECTRON_HPP_INCLUDED
#define ELECTRON_HPP_INCLUDED

#define PHY_ELECTRON_M 0.000000000000000000000000000000910938291

#include "StdInclude.hpp"

class Electron;

#include "Particle.hpp"

class Electron : public Particle
{
	public:
		Electron(const Coord);
		Electron(const Coord, const Speed);

		Color getColor () const;
        ld    getCharge() const;
        ld    getMass  () const;
};

#endif // ELECTRON_HPP_INCLUDED
