#ifndef IFX_CFG_H
#define IFX_CFG_H

//#include <aurix_illd_cfg.h>

#define AURIX_ILLD_IFX_ASSERT 	0
#define AURIX_ILLD_PLL_FREQ		(200000000)
#define AURIX_ILLD_XTAL_FREQ	(20000000)
#if (AURIX_ILLD_IFX_ASSERT != 0)
#include <stdio.h>	/* for printf used in IFX_ASSERT below */
#endif


// XTAL/PLL frequency
#define IFX_CFG_SCU_XTAL_FREQUENCY    (AURIX_ILLD_XTAL_FREQ)
#define IFX_CFG_SCU_PLL_FREQUENCY    (AURIX_ILLD_PLL_FREQ)


#ifdef  __cplusplus
extern "C" {
#endif

// Assertions
#if (AURIX_ILLD_IFX_ASSERT != 0)
extern const char* verboseLevelStr[6];
#  define IFX_ASSERT(level, expr) (((expr) || (level > IFX_VERBOSE_LEVEL_ERROR)) ? ((void)0) : (void)printf("[ASSERT:%s] '%s' in %s:%d (function '%s')\n", verboseLevelStr[level], #expr, __FILE__, __LINE__, __func__))
#else
#  define IFX_ASSERT(level, expr)
#endif


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* IFX_CFG_H */

