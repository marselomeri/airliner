#ifndef TO_APP_STUBS_H
#define TO_APP_STUBS_H

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************
** Includes
*************************************************************************/
#include "cfe.h"
#include "to_custom_test_utils.h"

/************************************************************************
** Structure Declarations
*************************************************************************/
typedef struct
{
    int32 TO_Channel_OpenChannel_Return; 
    uint8 TO_Channel_State_Return;
    uint8 TO_Channel_State_Return1;
    uint8 TO_Channel_State_CallCount;
} TO_App_Returns_t;

/************************************************************************
** External Global Variables
*************************************************************************/
extern TO_App_Returns_t TO_App_Return;

/************************************************************************
** Function Prototypes (Stubs)
*************************************************************************/
int32 TO_Channel_OpenChannel(uint32 index, char *ChannelName,
        char *ConfigTableName, char *ConfigTableFileName,
        char *DumpTableName);

void  TO_Channel_LockByIndex(uint32 index);

void  TO_Channel_UnlockByIndex(uint32 index);

uint8 TO_Channel_State(uint32 index);

#ifdef __cplusplus
}
#endif

#endif /* TO_APP_STUBS_H */
