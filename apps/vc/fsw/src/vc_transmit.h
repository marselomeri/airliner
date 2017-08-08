
#ifndef VC_TRANSMIT_H
#define VC_TRANSMIT_H

/************************************************************************
** Pragmas
*************************************************************************/

/************************************************************************
** Includes
*************************************************************************/

/************************************************************************
** Defines
*************************************************************************/

/************************************************************************
** Structure Definitions
*************************************************************************/

/************************************************************************
** External Global Variables
*************************************************************************/

/************************************************************************
** Function Prototypes
*************************************************************************/

/************************************************************************/
/** \brief Custom function to initialize all output channels.
**
**  \par Description
**       This function is called once at initialization and allows the
**       custom layer to provide specific functionality to initialize
**       internal objects.
**
**  \par Assumptions, External Events, and Notes:
**       This function must be defined, but not all custom
**       layers will do anything in this function.
**
**  \returns
**  TRUE if successful, FALSE otherwise.
**  \endreturns
**
*************************************************************************/
boolean VC_Transmit_Init(void);


/************************************************************************/
/** \brief Custom function to uninitialize all output channels.
**
**  \par Description
**       This function is called in preparation for loading a new
**       configuration, allowing the custom layer to do whatever it
**       needs with the current configuration before reconfiguration,
**       if anything. Also, called in cleanup to close and uninitialize
**       transmit resources.
**
**  \par Assumptions, External Events, and Notes:
**       This function must be defined, but not all custom
**       layers will do anything in this function.
**
**  \returns
**  TRUE if successful, FALSE otherwise.
**  \endreturns
**
*************************************************************************/
boolean VC_Transmit_Uninit(void);


/************************************************************************/
/** \brief Custom function to verify a transmit address.
**
**  \par Description
**       This function is called to validate an address.
**
**  \par Assumptions, External Events, and Notes:
**       This function must be defined, but not all custom
**       layers will do anything in this function.
**
**  \returns
**  TRUE if successful, FALSE otherwise.
**  \endreturns
**
*************************************************************************/
boolean VC_Address_Verification(const char *Address);


/************************************************************************/
/** \brief Custom function to update the transmit destination.
**
**  \par Description
**       This function is called to validate an address.
**
**  \par Assumptions, External Events, and Notes:
**       Uninit must be called before the destination can be updated.
**
**  \param [in] Address the pointer to the address to verify.
**
**  \returns
**  TRUE if successful, FALSE otherwise.
**  \endreturns
**
*************************************************************************/
boolean VC_Update_Destination(const char *Address, uint16 Port);


/************************************************************************/
/** \brief Transmit data using a previously initialized channel.
**
**  \par Description
**       This function transmits data using a custom transmit resource.
**
**  \par Assumptions, External Events, and Notes:
**       None.
**
**  \param [in] Buffer points to a buffer containing the data to be sent.
**
**  \param [in] Size specifies the size of the data in bytes.
**
**  \returns
**  On success, returns the number of bytes sent. On error, -1 is
 *  returned
**  \endreturns
**
*************************************************************************/
int32 VC_SendData(uint32 ChannelID, const char* Buffer, uint32 Size);

#endif

/************************/
/*  End of File Comment */
/************************/
