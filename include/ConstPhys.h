#ifndef _CONSTPHYS_H_
#define _CONSTPHYS_H_

namespace PHYS {

/* The Boltzmann constant
 * in SI unit (J / degK) */
const double k_Boltzmann_ = 1.380649 * 1.0e-23;

/* The Planck constant
 * in SI unit (J sec) */
const double h_Planck_ = 6.62607015 * 1.0e-34;

/* The reduced Planck constant
 * in SI unit (J sec) */
const double hbar_Planck_ = 1.054571817 * 1.0e-34;

/* The Avogadro constant */
const double N_Avogadro_ = 6.02214076 * 1.0e+23;

/* The elementary charge
 * in SI unit (Coulomb; C) */
const double Q_element_ = 1.602176634 * 1.0e-19;

/* The Coulomb constant
 * in SI unit (N m^2 / C^2) */
const double k_Coulomb_ = 8.9875517862 * 1.0e+9;

/* The speed of light in vacuum
 * in SI unit (m / sec) */
const double c_light_vac_ = 299792458;

/* The Newtonian constant gravitation
 * in SI unit (N m^2 / kg^2 = J m / kg^2) */
const double G_Newton_ = 6.67430 * 1.0e-11;

/* mass of a proton
 * in SI unit (kg) */
const double mass_proton_ = 1.67262192595 * 1.0e-27;

/* mass of a neutron
 * in SI unit (kg) */
const double mass_neutron_ = 1.67492750056 * 1.0e-27;

} // end of namespace PHYS

#endif
