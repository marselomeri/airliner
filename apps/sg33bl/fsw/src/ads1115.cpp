/************************************************************************
** Includes
*************************************************************************/

#include "ads1115.h"


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Default constructor.                                            */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
ADS1115::ADS1115()
{
    /* Set default values as initial values. */
    mConfig.mux = ADS1115_MUX_BITS_P0_N1;
    mConfig.pga = ADS1115_PGA_BITS_2P048;
    mConfig.mode = ADS1115_MODE_BITS_SINGLE;
    mConfig.rate = ADS1115_DATA_RATE_BITS_128;
    mConfig.compMode = ADS1115_COMP_MODE_BITS_HYSTERESIS;
    mConfig.compPolarity = ADS1115_COMP_POL_ACTIVE_LOW;
    mConfig.compLatching = ADS1115_COMP_LAT_BITS_NON_LATCHING;
    mConfig.compQueueMode = ADS1115_COMP_QUE_BITS_DISABLE;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Destructor constructor.                                         */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
ADS1115::~ADS1115()
{

}


/* Configuration setters. */
boolean ADS1115::setMux(ADS1115_Bits_Mux_t mux)
{
    return FALSE;
}


boolean ADS1115::setGain(ADS1115_Bits_Pga_t pga)
{
    return FALSE;
}


boolean ADS1115::setMode(ADS1115_Bits_Mode_t mode)
{
    return FALSE;
}


boolean ADS1115::setRate(ADS1115_Bits_Data_Rate_t rate)
{
    return FALSE;
}


boolean ADS1115::setComparatorMode(ADS1115_Bits_Comp_Mode_t compMode)
{
    return FALSE;
}


boolean ADS1115::setComparatorPolarity(ADS1115_Bits_Comp_Polarity_t compPolarity)
{
    return FALSE;
}


boolean ADS1115::setComparatorLatchEnabled(ADS1115_Bits_Comp_Latching_t compLatching)
{
    return FALSE;
}


boolean ADS1115::setComparatorQueueMode(ADS1115_Bits_Comp_Queue_t compQueueMode)
{
    return FALSE;
}


/* Configuration getters. */
boolean ADS1115::getMux(ADS1115_Bits_Mux_t *mux)
{
    return FALSE;
}


boolean ADS1115::getGain(ADS1115_Bits_Pga_t *pga)
{
    return FALSE;
}


boolean ADS1115::getMode(ADS1115_Bits_Mode_t *mode)
{
    return FALSE;
}


boolean ADS1115::getRate(ADS1115_Bits_Data_Rate_t *rate)
{
    return FALSE;
}


boolean ADS1115::getComparatorMode(ADS1115_Bits_Comp_Mode_t *compMode)
{
    return FALSE;
}


boolean ADS1115::getComparatorPolarity(ADS1115_Bits_Comp_Polarity_t *compPolarity)
{
    return FALSE;
}


boolean ADS1115::getComparatorLatchEnabled(ADS1115_Bits_Comp_Latching_t *compLatching)
{
    return FALSE;
}


boolean ADS1115::getComparatorQueueMode(ADS1115_Bits_Comp_Queue_t *compQueueMode)
{
    return FALSE;
}


/************************/
/*  End of File Comment */
/************************/
