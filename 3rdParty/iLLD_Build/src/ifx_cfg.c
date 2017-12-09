
#include <Ifx_Cfg.h>

#if (AURIX_ILLD_IFX_ASSERT != 0)
    
    //! this global array is used by IFX_ASSERT of iLLDs
const char* verboseLevelStr[6] = {
    "OFF",
    "FAILURE",
    "ERROR",
    "WARNING",
    "INFO",
    "DEBUG"
};

#endif /* (AURIX_ILLD_IFX_ASSERT != 0) */

