/************************************************************************
** File:
**   $Id: hs_amt_tbl.c 1.3 2015/03/03 12:16:12EST sstrege Exp  $
**
**   Copyright � 2007-2014 United States Government as represented by the 
**   Administrator of the National Aeronautics and Space Administration. 
**   All Other Rights Reserved.  
**
**   This software was created at NASA's Goddard Space Flight Center.
**   This software is governed by the NASA Open Source Agreement and may be 
**   used, distributed and modified only pursuant to the terms of that 
**   agreement.
**
** Purpose:
**  The CFS Health and Safety (HS) Applications Monitor Table Definition
**
** Notes:
**
** $Log: hs_amt_tbl.c  $
** Revision 1.3 2015/03/03 12:16:12EST sstrege 
** Added copyright information
** Revision 1.2 2011/08/15 15:43:17EDT aschoeni 
** Updated so application name is configurable
** Revision 1.1 2009/05/04 11:50:07EDT aschoeni 
** Initial revision
** Member added to project c:/MKSDATA/MKS-REPOSITORY/CFS-REPOSITORY/hs/fsw/project.pj
**
*************************************************************************/


/************************************************************************
** Includes
*************************************************************************/
#include "cfe.h"
#include "hs_tbl.h"
#include "hs_tbldefs.h"
#include "cfe_tbl_filedef.h"


static CFE_TBL_FileDef_t CFE_TBL_FileDef =
{
    "HS_Default_AppMon_Tbl", HS_APP_NAME ".AppMon_Tbl", "HS AppMon Table",
    "hs_amt.tbl", (sizeof(HS_AMTEntry_t) * HS_MAX_CRITICAL_APPS)
};



HS_AMTEntry_t      HS_Default_AppMon_Tbl[HS_MAX_CRITICAL_APPS] =
{
/*          AppName                    NullTerm CycleCount     ActionType */
                                                
/*   0 */ { "CFE_ES",                  0,       10,            HS_AMT_ACT_NOACT },
/*   1 */ { "CFE_EVS",                 0,       10,            HS_AMT_ACT_NOACT },
/*   2 */ { "CFE_TIME",                0,       10,            HS_AMT_ACT_NOACT },
/*   3 */ { "TIME_TONE_TASK",          0,       10,            HS_AMT_ACT_NOACT },
/*   4 */ { "TIME_1HZ_TASK",           0,       10,            HS_AMT_ACT_NOACT },
/*   5 */ { "CFE_TBL",                 0,       10,            HS_AMT_ACT_NOACT },
/*   6 */ { "CFE_SB",                  0,       10,            HS_AMT_ACT_NOACT },
/*   7 */ { "CF",                      0,       10,            HS_AMT_ACT_NOACT },
/*   8 */ { "CI",                      0,       10,            HS_AMT_ACT_NOACT },
/*   9 */ { "CS",                      0,       10,            HS_AMT_ACT_NOACT },
/*  10 */ { "DS",                      0,       10,            HS_AMT_ACT_NOACT },
/*  11 */ { "ETA",                     0,       10,            HS_AMT_ACT_NOACT },
/*  12 */ { "FM",                      0,       10,            HS_AMT_ACT_NOACT },
/*  13 */ { "HK",                      0,       10,            HS_AMT_ACT_NOACT },
/*  14 */ { "HS",                      0,       10,            HS_AMT_ACT_NOACT },
/*  15 */ { "LC",                      0,       10,            HS_AMT_ACT_NOACT },
/*  16 */ { "MD",                      0,       10,            HS_AMT_ACT_NOACT },
/*  17 */ { "MM",                      0,       10,            HS_AMT_ACT_NOACT },
/*  18 */ { "PX4BR",                   0,       10,            HS_AMT_ACT_NOACT },
/*  19 */ { "SC",                      0,       10,            HS_AMT_ACT_NOACT },
/*  20 */ { "SCH",                     0,       10,            HS_AMT_ACT_NOACT },
/*  21 */ { "TO",                      0,       10,            HS_AMT_ACT_NOACT },
/*  22 */ { "",                        0,       10,            HS_AMT_ACT_NOACT },
/*  23 */ { "",                        0,       10,            HS_AMT_ACT_NOACT },
/*  24 */ { "",                        0,       10,            HS_AMT_ACT_NOACT },
/*  25 */ { "",                        0,       10,            HS_AMT_ACT_NOACT },
/*  26 */ { "",                        0,       10,            HS_AMT_ACT_NOACT },
/*  27 */ { "",                        0,       10,            HS_AMT_ACT_NOACT },
/*  28 */ { "",                        0,       10,            HS_AMT_ACT_NOACT },
/*  29 */ { "",                        0,       10,            HS_AMT_ACT_NOACT },
/*  30 */ { "",                        0,       10,            HS_AMT_ACT_NOACT },
/*  31 */ { "",                        0,       10,            HS_AMT_ACT_NOACT },

};

/************************/
/*  End of File Comment */
/************************/
