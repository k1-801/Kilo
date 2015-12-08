#pragma once

#ifndef PHY_HPP_INCLUDED
#define PHY_HPP_INCLUDED

// Dynamic constants
#define PHY_C            299792458.0
#define PHY_K           8987551787.997911
#define PHY_E                    0.000000000008854187817
#define PHY_G                    0.0000000000667545
#define PHY_H                    0.000000000000000000000000000000000663

// Pre-calculated frequently used constant products
#define PHY_C_SQ 89875517873681764.0

// Conversion constants
#define PHY_EV                   0.000000000000000000000000000000000001782661845

// Particle characteristics
// Electron
#define PHY_ELECTRON_M           0.000000000000000000000000000000910938291
#define PHY_ELECTRON_Q          -0.00000000000000000016021765653

// Quarks
#define PHY_QUARK_D_M            0.00000000000000000000000000000853895023755
#define PHY_QUARK_U_M            0.00000000000000000000000000000358315030845
#define PHY_QUARK_D_Q           -0.00000000000000000005340588433
#define PHY_QUARK_U_Q            0.00000000000000000010681176866

// Stars and planets?!
#define PHY_EARTH_M

#endif // PHY_HPP_INCLUDED
