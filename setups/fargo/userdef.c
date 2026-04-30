#include "fargo3d.h"

void UserDef() {

  static int initialized = 0;
  static double final_mass[10];

  double tgrow = 20.0 * 2.0 * M_PI;  // 20 orbits at r=1, in code time units
  double f_min = 0.05;                // start at 5% of final mass

  double t = PhysicalTime;

  // Capture final masses from planets.cfg on the first call (before any tapering)
  if (!initialized) {
    for (int i = 0; i < Sys->nb; i++) {
      final_mass[i] = Sys->mass[i];
    }
    initialized = 1;
  }

  double f;

  if (t < tgrow) {
    f = sin(0.5*M_PI*t/tgrow);
    f = f*f;
    f = f_min + (1.0 - f_min) * f;
  } else {
    f = 1.0;
  }

  for (int i = 0; i < Sys->nb; i++) {
    Sys->mass[i] = final_mass[i] * f;
  }
}
