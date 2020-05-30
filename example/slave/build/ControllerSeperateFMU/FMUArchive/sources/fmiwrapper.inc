#include "Controller_Seperate.h"
#include "Controller_Seperate_private.h"

typedef struct {
	BuiltInDTypeId dtypeID;
	size_t size;
	void* address;
} ModelVariable;

#ifndef NO_FMI_FUNCTION_PREFIX
#define FMI2_FUNCTION_PREFIX Controller_Seperate_
#endif

#define MODEL_GUID       "{6a6ba1b4-0ba0-493f-b239-1b5b64224ebd}"
#define MODEL            Controller_Seperate
#define MODEL_INITIALIZE Controller_Seperate_initialize
#define MODEL_STEP       Controller_Seperate_step
#define MODEL_TERMINATE  Controller_Seperate_terminate
#define RT_MDL_TYPE      RT_MODEL_Controller_Seperate_T
#define STEP_SIZE        0.01

/* R2019a defines the block parameters as extern */
#ifndef rtmGetDefaultParam
#define rtmGetDefaultParam(S) (&Controller_Seperate_P)
#endif

#define REUSABLE_FUNCTION

static void initializeModelVariables(RT_MDL_TYPE* S, ModelVariable modelVariables[]) {
    modelVariables[0].dtypeID = 0;
    modelVariables[0].size    = 0;
    modelVariables[0].address = &(rtmGetDefaultParam(S)->Integrator_gainval);
    modelVariables[1].dtypeID = 0;
    modelVariables[1].size    = 0;
    modelVariables[1].address = &(rtmGetDefaultParam(S)->Filter_gainval);
    modelVariables[2].dtypeID = 0;
    modelVariables[2].size    = 0;
    modelVariables[2].address = &(rtmGetDefaultParam(S)->Saturation_UpperSat);
    modelVariables[3].dtypeID = 0;
    modelVariables[3].size    = 0;
    modelVariables[3].address = &(rtmGetDefaultParam(S)->Saturation_LowerSat);
    modelVariables[4].dtypeID = 0;
    modelVariables[4].size    = 0;
    modelVariables[4].address = &(rtmGetU(S)->Velocity);
    modelVariables[5].dtypeID = 0;
    modelVariables[5].size    = 0;
    modelVariables[5].address = &(rtmGetY(S)->Throttle);
    modelVariables[6].dtypeID = 0;
    modelVariables[6].size    = 0;
    modelVariables[6].address = &(rtmGetBlockIO(S)->Sum);
}

#define N_MODEL_VARIABLES 8
