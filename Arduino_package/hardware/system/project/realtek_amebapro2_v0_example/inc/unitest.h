#ifndef UNITEST_H
#define UNITEST_H

#ifndef CONFIG_UNITEST
#define CONFIG_UNITEST 0
#endif

#if CONFIG_UNITEST == 0

#define INIT_PASS_COND(condi, t, v, to)
#define test_add(fn, pass_condi)

#define testatcmd_start(seq)
#define testatcmd_end(seq)
#define testatcmd_add(seq, serial, cmd, ret)
#define testatcmd_add_with_range(seq, serial, cmd, ret, c_mi, c_ma, c_st)
#define testatcmd_add_with_same_range(seq, serial, cmd, ret, c_mi, c_ma, c_st)
#define testatcmd_add_with_dual_range(seq, serial, cmd, c_mi, c_ma, c_st, ret, r_mi, r_ma, r_st)

#else
#include "unitest_internal.h"
#endif

#endif