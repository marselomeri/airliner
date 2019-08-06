#include "cfe.h"
#include "mpu9250_custom.h"
#include "mpu9250_app.h"
#include "simlib.h"
#include <time.h>
#include "px4lib.h"


extern MPU9250 oMPU9250;

void MPU9250_Custom_InitData(void)
{

}


boolean MPU9250_Custom_Init(void)
{
	return TRUE;
}


boolean MPU9250_Custom_Uninit(void)
{
	return TRUE;
}


int32 MPU9250_Custom_Init_EventFilters(int32 ind, CFE_EVS_BinFilter_t *EventTbl)
{
	return 0;
}


boolean MPU9250_SetAccScale(uint8 Scale, float *AccDivider)
{
    boolean returnBool = TRUE;
    uint8 value = 0;

    /* Null pointer check */
    if(0 == AccDivider)
    {
        returnBool = FALSE;
        goto end_of_function;
    }

    switch (Scale)
    {
        case 2:
            *AccDivider = 16384;
            break;

        case 4:
            *AccDivider = 8192;
            break;

        case 8:
            *AccDivider = 4096;
            break;

        case 16:
            *AccDivider = 2048;
            break;

        default:
            returnBool = FALSE;
            goto end_of_function;
    }

end_of_function:
    return returnBool;
}


boolean MPU9250_SetGyroScale(uint32 Scale, float *GyroDivider)
{
    boolean returnBool = TRUE;

    /* Null pointer check */
    if(0 == GyroDivider)
    {
        returnBool = FALSE;
        goto end_of_function;
    }

    switch (Scale)
    {
        case 250:
            *GyroDivider = 131;
            break;

        case 500:
            *GyroDivider = 65.5;
            break;

        case 1000:
            *GyroDivider = 32.8;
            break;

        case 2000:
            *GyroDivider = 16.4;
            break;

        default:
            returnBool = FALSE;
            goto end_of_function;
    }

end_of_function:
    return returnBool;
}


boolean MPU9250_Measure(MPU9250_SampleQueue_t *SampleQueue)
{
    float calX_f = 0.0f;
    float calY_f = 0.0f;
    float calZ_f = 0.0f;
    float calTemp = 0.0f;

    SIMLIB_GetAccel(&calX_f, &calY_f, &calZ_f);
    /* Apply inverse rotation */
    MPU9250_Apply_Platform_Rotation(&calX_f, &calY_f, &calZ_f);
    SampleQueue->Samples[0].AX   = ((calX_f / oMPU9250.Diag.Calibration.AccXScale) + oMPU9250.Diag.Calibration.AccXOffset) / (oMPU9250.Diag.Conversion.AccUnit / oMPU9250.Diag.Conversion.AccDivider);
    SampleQueue->Samples[0].AY   = ((calY_f / oMPU9250.Diag.Calibration.AccYScale) + oMPU9250.Diag.Calibration.AccYOffset) / (oMPU9250.Diag.Conversion.AccUnit / oMPU9250.Diag.Conversion.AccDivider);
    SampleQueue->Samples[0].AZ   = ((calZ_f / oMPU9250.Diag.Calibration.AccZScale) + oMPU9250.Diag.Calibration.AccZOffset) / (oMPU9250.Diag.Conversion.AccUnit / oMPU9250.Diag.Conversion.AccDivider);

    SIMLIB_GetGyro(&calX_f, &calY_f, &calZ_f);
    /* Apply inverse rotation */
    MPU9250_Apply_Platform_Rotation(&calX_f, &calY_f, &calZ_f);
    SampleQueue->Samples[0].GX   = ((calX_f / oMPU9250.Diag.Calibration.GyroXScale) + oMPU9250.Diag.Calibration.GyroXOffset) / (oMPU9250.Diag.Conversion.GyroUnit / oMPU9250.Diag.Conversion.GyroDivider);
    SampleQueue->Samples[0].GY   = ((calY_f / oMPU9250.Diag.Calibration.GyroYScale) + oMPU9250.Diag.Calibration.GyroYOffset) / (oMPU9250.Diag.Conversion.GyroUnit / oMPU9250.Diag.Conversion.GyroDivider);
    SampleQueue->Samples[0].GZ   = ((calZ_f / oMPU9250.Diag.Calibration.GyroZScale) + oMPU9250.Diag.Calibration.GyroZOffset) / (oMPU9250.Diag.Conversion.GyroUnit / oMPU9250.Diag.Conversion.GyroDivider);

    SIMLIB_GetMag(&calX_f, &calY_f, &calZ_f);
    /* No rotation */
    SampleQueue->Samples[0].MX   = ((calX_f / oMPU9250.Diag.Calibration.MagXScale) + oMPU9250.Diag.Calibration.MagXOffset) / (oMPU9250.Diag.Conversion.MagXAdj / AK8963_RAW_TO_GAUSS);
    SampleQueue->Samples[0].MY   = ((calY_f / oMPU9250.Diag.Calibration.MagYScale) + oMPU9250.Diag.Calibration.MagYOffset) / (oMPU9250.Diag.Conversion.MagYAdj / AK8963_RAW_TO_GAUSS);
    SampleQueue->Samples[0].MZ   = ((calY_f / oMPU9250.Diag.Calibration.MagZScale) + oMPU9250.Diag.Calibration.MagZOffset) / (oMPU9250.Diag.Conversion.MagZAdj / AK8963_RAW_TO_GAUSS);

    SIMLIB_GetTemp(&calTemp);
    if(0 == calTemp)
    {
        SampleQueue->Samples[0].Temp = -1083;
    }
    else
    {
        SampleQueue->Samples[0].Temp = ((calTemp + oMPU9250.Diag.Conversion.RoomTempOffset) - 21.0f) * oMPU9250.Diag.Conversion.TempSensitivity;
    }

    SampleQueue->SampleCount = 1;

    return TRUE;

}


//boolean MPU9250_Read_Gyro(int16 *rawX, int16 *rawY, int16 *rawZ)
//{
	//float calX_f = 0.0f;
	//float calY_f = 0.0f;
	//float calZ_f = 0.0f;

	//SIMLIB_GetGyro(&calX_f, &calY_f, &calZ_f);
    
    ///* Apply inverse rotation */
    //MPU9250_Apply_Platform_Rotation(&calX_f, &calY_f, &calZ_f);

    //*rawX = ((calX_f / oMPU9250.Diag.Calibration.GyroXScale) + oMPU9250.Diag.Calibration.GyroXOffset) / (oMPU9250.Diag.Conversion.GyroUnit / oMPU9250.Diag.Conversion.GyroDivider);
    //*rawY = ((calY_f / oMPU9250.Diag.Calibration.GyroYScale) + oMPU9250.Diag.Calibration.GyroYOffset) / (oMPU9250.Diag.Conversion.GyroUnit / oMPU9250.Diag.Conversion.GyroDivider);
    //*rawZ = ((calZ_f / oMPU9250.Diag.Calibration.GyroZScale) + oMPU9250.Diag.Calibration.GyroZOffset) / (oMPU9250.Diag.Conversion.GyroUnit / oMPU9250.Diag.Conversion.GyroDivider);



	//return TRUE;
//}


//boolean MPU9250_Read_Accel(int16 *rawX, int16 *rawY, int16 *rawZ)
//{
	//float calX_f = 0.0f;
	//float calY_f = 0.0f;
	//float calZ_f = 0.0f;

	//SIMLIB_GetAccel(&calX_f, &calY_f, &calZ_f);

    ///* Apply inverse rotation */
    //MPU9250_Apply_Platform_Rotation(&calX_f, &calY_f, &calZ_f);

    //*rawX = ((calX_f / oMPU9250.Diag.Calibration.AccXScale) + oMPU9250.Diag.Calibration.AccXOffset) / (oMPU9250.Diag.Conversion.AccUnit / oMPU9250.Diag.Conversion.AccDivider);
    //*rawY = ((calY_f / oMPU9250.Diag.Calibration.AccYScale) + oMPU9250.Diag.Calibration.AccYOffset) / (oMPU9250.Diag.Conversion.AccUnit / oMPU9250.Diag.Conversion.AccDivider);
    //*rawZ = ((calZ_f / oMPU9250.Diag.Calibration.AccZScale) + oMPU9250.Diag.Calibration.AccZOffset) / (oMPU9250.Diag.Conversion.AccUnit / oMPU9250.Diag.Conversion.AccDivider);

	//return TRUE;
//}


//boolean MPU9250_Read_Mag(int16 *rawX, int16 *rawY, int16 *rawZ)
//{
	//float calX_f = 0.0f;
	//float calY_f = 0.0f;
	//float calZ_f = 0.0f;
	//float rawX_f = 0.0f;
	//float rawY_f = 0.0f;
	//float rawZ_f = 0.0f;
	//float magXAdj_f = oMPU9250.Diag.Calibration.MagXAdj;
	//float magYAdj_f = oMPU9250.Diag.Calibration.MagYAdj;
	//float magZAdj_f = oMPU9250.Diag.Calibration.MagZAdj;

	//SIMLIB_GetMag(&calX_f, &calY_f, &calZ_f);

	//rawX_f = ((calX_f * 1000.0f) - oMPU9250.Diag.Calibration.MagXOffset) / (((((magXAdj_f - 128.0f) * 0.5f) / 128.0f) + 1.0) * oMPU9250.Diag.Calibration.MagXScale);
	//rawY_f = ((calY_f * 1000.0f) - oMPU9250.Diag.Calibration.MagYOffset) / (((((magYAdj_f - 128.0f) * 0.5f) / 128.0f) + 1.0) * oMPU9250.Diag.Calibration.MagYScale);
	//rawZ_f = ((calZ_f * 1000.0f) - oMPU9250.Diag.Calibration.MagZOffset) / (((((magZAdj_f - 128.0f) * 0.5f) / 128.0f) + 1.0) * oMPU9250.Diag.Calibration.MagZScale);

	//*rawX = rawX_f;
	//*rawY = rawY_f;
	//*rawZ = rawZ_f;

	//return TRUE;
//}


//boolean MPU9250_Read_Temp(uint16 *rawTemp)
//{
	//float calTemp = 0.0f;

	//SIMLIB_GetTemp(&calTemp);

    //if(0 == calTemp)
    //{
        //*rawTemp = -1083;
    //}
    //else
    //{
        //*rawTemp = ((calTemp + oMPU9250.Diag.Conversion.RoomTempOffset) - 21.0f) * oMPU9250.Diag.Conversion.TempSensitivity;
    //}

	//return TRUE;
//}


boolean MPU9250_Read_MagAdj(uint8 *X, uint8 *Y, uint8 *Z)
{
    *X = 170;
    *Y = 170;
    *Z = 170;

    return TRUE;
}


boolean MPU9250_Apply_Platform_Rotation(float *X, float *Y, float *Z)
{
    boolean returnBool = TRUE;
    float temp;

    /* Null pointer check */
    if(0 == X || 0 == Y || 0 == Z)
    {
        returnBool = FALSE;
        goto end_of_function;
    }
    /* TODO move to a table */
    /* ROTATION_ROLL_180_YAW_90 */
    temp = *X; 
    *X = *Y; 
    *Y = temp; 
    *Z = -*Z;

end_of_function:

    return returnBool;
}


boolean MPU9250_Apply_Mag_Platform_Rotation(float *X, float *Y, float *Z)
{
    boolean returnBool = TRUE;
    float temp;

    /* Null pointer check */
    if(0 == X || 0 == Y || 0 == Z)
    {
        returnBool = FALSE;
        goto end_of_function;
    }

    /* No Rotation */

end_of_function:

    return returnBool;
}


void MPU9250_Get_Rotation(uint8 *Rotation)
{
    
    /* Null pointer check */
    if(0 == Rotation)
    {
        goto end_of_function;
    }
    
    /* TODO move to a table */
    *Rotation = ROTATION_ROLL_180_YAW_90;

end_of_function:
    return;
}

void MPU9250_Get_Mag_Rotation(uint8 *Rotation)
{
    
    /* Null pointer check */
    if(0 == Rotation)
    {
        goto end_of_function;
    }
    
    /* TODO move to a table */
    *Rotation = ROTATION_NONE;

end_of_function:
    return;
}
