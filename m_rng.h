#ifndef M_RNG_H
#define M_RNG_H

#include "d_common.h"

/** Get next random int from table
  * This is the "global" version, for RNG calls that *don't* affect gameplay
  * In other words, if you call RNG and you're *not* in game, use rng_gnext()
  * Otherwise, use rng_lnext()
  */
u16  rng_gnext (void);

/** Get next random int from table
  * This is the "local" version, for RNG calls that *do* affect gameplay
  * In other words, if you call RNG and you *are* in game, use rng_lnext();
  * Otherwise, use rng_gnext();
  */
u16  rng_lnext (void);

/** Reset rng table
  * Sets rng_gnext() and rng_lnext() back to the start of the table
  * by setting grindx and lrindx back to zero
  */
void rng_reset (void);

#endif