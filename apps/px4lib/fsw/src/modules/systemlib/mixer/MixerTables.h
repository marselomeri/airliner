#ifndef MIXER_TABLES_H
#define MIXER_TABLES_H

#include "cfe.h"

#define MULTIROTOR_MIXER_MAX_ROTOR_COUNT 8

typedef enum
{
    MIXER_QUAD_X,
    MIXER_QUAD_H,
    MIXER_QUAD_PLUS,
    MIXER_QUAD_V,
    MIXER_QUAD_WIDE,
    MIXER_QUAD_S250AQ,
    MIXER_QUAD_DEADCAT,
    MIXER_HEX_X,
    MIXER_HEX_PLUS,
    MIXER_HEX_COX,
    MIXER_HEX_T,
    MIXER_OCTA_X,
    MIXER_OCTA_PLUS,
    MIXER_OCTA_COX,
    MIXER_OCTA_COX_WIDE,
    MIXER_TWIN_ENGINE,
    MIXER_TRI_Y,
    MIXER_MAX_GEOMETRY
} MultirotorGeometry_t;

typedef struct {
    float   RollScale; /**< scales roll for this rotor */
    float   PitchScale;/**< scales pitch for this rotor */
    float   YawScale;  /**< scales yaw for this rotor */
    float   OutScale;  /**< scales total out for this rotor */
} MultirotorMixer_RotorConfig_t;

typedef struct
{
    float  RollScale;
    float  PitchScale;
    float  YawScale;
    float  IdleSpeed;
    float  DeltaOutMax;
    uint32 RotorCount;
	MultirotorGeometry_t Geometry;
    MultirotorMixer_RotorConfig_t RotorConfig[MULTIROTOR_MIXER_MAX_ROTOR_COUNT];
} MultirotorMixer_ConfigTable_t;


typedef MultirotorMixer_ConfigTable_t *MultirotorMixer_ConfigTablePtr_t;


#endif
