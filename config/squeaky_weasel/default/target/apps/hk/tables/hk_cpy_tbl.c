/************************************************************************
** Includes
*************************************************************************/
#include "cfe.h"
#include "hk_utils.h"
#include "hk_app.h"
#include "hk_msgids.h"
#include "hk_tbldefs.h"
#include "cfe_tbl_filedef.h"

hk_copy_table_entry_t      HK_CopyTable[HK_COPY_TABLE_ENTRIES] =
{
/*         inputMid        inputOffset     outputMid    outputOffset  numBytes*/
          /* Timestamp */
/*   0 */ { PX4_SENSOR_ACCEL_MID,   16, HK_COMBINED_PKT1_MID,    16,   8, },
          /* ErrorCount */
/*   1 */ { PX4_SENSOR_ACCEL_MID,   32, HK_COMBINED_PKT1_MID,    24,   8, },
          /* Temperature */
/*   2 */ { PX4_SENSOR_ACCEL_MID,   64, HK_COMBINED_PKT1_MID,    32,   4, },
          /* XRaw */
/*   3 */ { PX4_SENSOR_ACCEL_MID,   80, HK_COMBINED_PKT1_MID,    36,   2, },
          /* YRaw */
/*   4 */ { PX4_SENSOR_ACCEL_MID,   82, HK_COMBINED_PKT1_MID,    38,   2, },
          /* ZRaw */
/*   5 */ { PX4_SENSOR_ACCEL_MID,   84, HK_COMBINED_PKT1_MID,    40,   2, },
          /* TemperatureRaw */
/*   6 */ { PX4_SENSOR_ACCEL_MID,   86, HK_COMBINED_PKT1_MID,    42,   2, },
          /* Timestamp */
/*   7 */ { PX4_SENSOR_GYRO_MID,    16, HK_COMBINED_PKT1_MID,    44,   8, },
          /* ErrorCount */
/*   8 */ { PX4_SENSOR_GYRO_MID,    32, HK_COMBINED_PKT1_MID,    52,   8, },
          /* Temperature */
/*   9 */ { PX4_SENSOR_GYRO_MID,    64, HK_COMBINED_PKT1_MID,    60,   4, },
          /* XRaw */
/*  10 */ { PX4_SENSOR_GYRO_MID,    80, HK_COMBINED_PKT1_MID,    64,   2, },
          /* YRaw */
/*  11 */ { PX4_SENSOR_GYRO_MID,    82, HK_COMBINED_PKT1_MID,    66,   2, },
          /* ZRaw */
/*  12 */ { PX4_SENSOR_GYRO_MID,    84, HK_COMBINED_PKT1_MID,    68,   2, },
          /* Timestamp */
/*  13 */ { PX4_SENSOR_MAG_MID,     16, HK_COMBINED_PKT1_MID,    70,   8, },
          /* ErrorCount */
/*  14 */ { PX4_SENSOR_MAG_MID,     24, HK_COMBINED_PKT1_MID,    78,   8, },
          /* Temperature */
/*  15 */ { PX4_SENSOR_MAG_MID,     52, HK_COMBINED_PKT1_MID,    86,   4, },
          /* XRaw */
/*  16 */ { PX4_SENSOR_MAG_MID,     60, HK_COMBINED_PKT1_MID,    90,   2, },
          /* YRaw */
/*  17 */ { PX4_SENSOR_MAG_MID,     62, HK_COMBINED_PKT1_MID,    92,   2, },
          /* ZRaw */
/*  18 */ { PX4_SENSOR_MAG_MID,     64, HK_COMBINED_PKT1_MID,    94,   2, },
          /* Timestamp */
/*  19 */ { PX4_SENSOR_BARO_MID,    16, HK_COMBINED_PKT2_MID,    16,   8, },
          /* ErrorCount */
/*  20 */ { PX4_SENSOR_BARO_MID,    24, HK_COMBINED_PKT2_MID,    24,   4, },
          /* Pressure */
/*  21 */ { PX4_SENSOR_BARO_MID,    28, HK_COMBINED_PKT2_MID,    28,   4, },
          /* Temperature */
/*  22 */ { PX4_SENSOR_BARO_MID,    36, HK_COMBINED_PKT2_MID,    32,   4, },
/*  23 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/*  24 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/*  25 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },                                                                                                        
/*  26 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/*  27 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/*  28 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/*  29 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/*  30 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/*  31 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/*  32 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },                                                                                                        
/*  33 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/*  34 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/*  35 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/*  36 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/*  37 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/*  38 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/*  39 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/*  40 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/*  41 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/*  42 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/*  43 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/*  44 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/*  45 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/*  46 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/*  47 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/*  48 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/*  49 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/*  50 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/*  51 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/*  52 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/*  53 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/*  54 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/*  55 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/*  56 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/*  57 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/*  58 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/*  59 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/*  60 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/*  61 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/*  62 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/*  63 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/*  64 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/*  65 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/*  66 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/*  67 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/*  68 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/*  69 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/*  70 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/*  71 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/*  72 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/*  73 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/*  74 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/*  75 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/*  76 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/*  77 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/*  78 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/*  79 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/*  80 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/*  81 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/*  82 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/*  83 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/*  84 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/*  85 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/*  86 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/*  87 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/*  88 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/*  89 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/*  90 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/*  91 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/*  92 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/*  93 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/*  94 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/*  95 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/*  96 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/*  97 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/*  98 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/*  99 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/* 100 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/* 101 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/* 102 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/* 103 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/* 104 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/* 105 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/* 106 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/* 107 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/* 108 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/* 109 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/* 110 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/* 111 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/* 112 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/* 113 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/* 114 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/* 115 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/* 116 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/* 117 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/* 118 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/* 119 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/* 120 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/* 121 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/* 122 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/* 123 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/* 124 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/* 125 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/* 126 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },
/* 127 */ { HK_UNDEFINED_ENTRY,    0,   HK_UNDEFINED_ENTRY,       0,   0, },

};

/*
** Table file header
*/
CFE_TBL_FILEDEF(HK_CopyTable, HK.CopyTable, HK Copy Tbl, hk_cpy_tbl.tbl)

/************************/
/*  End of File Comment */
/************************/
