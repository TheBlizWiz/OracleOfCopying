#ifndef M_RNG_H
#define M_RNG_H

#include "defs/d_common.h"

/** Get next random int from table.
 * This is the "global" version, for RNG calls that *don't* affect gameplay.
 * In other words, if you call RNG and you're *not* in game, use rng_gnext().
 * Otherwise, use rng_lnext().
 *
 * \param  void - None
 * \return u16  - Random u16 value from RNG_TABLE
 */
DLLINCLUDE u16 rng_gnext(void);

/**
 * Get next random int from table.
 * This is the "local" version, for RNG calls that *do* affect gameplay.
 * In other words, if you call RNG and you *are* in game, use rng_lnext().
 * Otherwise, use rng_gnext().
 *
 * \param  void - None
 * \return u16  - random u16 value from RNG_TABLE
 */
DLLINCLUDE u16 rng_lnext(void);

/**
 * Resets rng table.
 * Sets rng_gnext() and rng_lnext() back to the start of the table
 * by setting grindx and lrindx back to zero.
 *
 * \param  void - None
 * \return void - None
 */
DLLINCLUDE void rng_reset(void);

#endif