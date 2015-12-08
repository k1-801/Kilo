#pragma once

#ifndef QUARK_HPP_INCLUDED
#define QUARK_HPP_INCLUDED

#include "StdInclude.hpp"

enum QUARK_COLOR
{
	QC_NONE   = 0,

    QC_RED    = 0x11,
    QC_GREEN  = 0x12,
    QC_BLUE   = 0x13,

    QC_ARED   = 0x21,
    QC_AGREEN = 0x22,
    QC_ABLUE  = 0x23
};

class Quark;

#include "Particle.hpp"

class Quark : public Particle
{
	protected:
		static std :: vector <Quark*> quarkList;
		QUARK_COLOR qc;

		void create(QUARK_COLOR);

	public:
		Quark(const Coord, const QUARK_COLOR);
		Quark(const Coord, const QUARK_COLOR, const Speed);
		virtual ~Quark();

		QUARK_COLOR   getQuarkColor() const;
		virtual Color getColor     () const;
};

#endif // QUARK_HPP_INCLUDED
