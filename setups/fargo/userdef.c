#include "fargo3d.h"

void UserDef() {

  double tgrow = 20.0 * 2.0 * M_PI;  // 20 orbits at r=1, in code time units
  double final_mass = FINALMASS;    // set via FinalMass in the .par file
  double f_min = 0.05;              // start at 5% of final mass

  double t = PhysicalTime;

  double f;

  if (t < tgrow) {
    f = sin(0.5*M_PI*t/tgrow);
    f = f*f;
    f = f_min + (1.0 - f_min) * f;
  } else {
    f = 1.0;
  }

  for (int i = 0; i < Sys->nb; i++) {
    Sys->mass[i] = final_mass * f;
  }
}
