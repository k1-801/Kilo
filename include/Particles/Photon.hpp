#pragma once

#ifndef PHOTON_HPP_INCLUDED
#define PHOTON_HPP_INCLUDED

#include "StdInclude.hpp"

class Photon;

#include "Particle.hpp"

// Note that Photon always moves with light-speed (PHY_C), so second constructor parameter will only be used to calculate direction

class Photon : public Particle
{
	private:
		ld vaweLength;

	public:
		Photon(const Coord, const Vector3);

		Color getColor () const;
		ld    getCharge() const;
		ld    getMass  () const;
};

#endif // PHOTON_HPP_INCLUDED
