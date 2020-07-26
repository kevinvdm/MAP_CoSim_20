#include "Controller_Seperate_Step.h"
#include "Controller_Seperate_Step_private.h"

typedef struct {
	BuiltInDTypeId dtypeID;
	size_t size;
	void* address;
} ModelVariable;

#ifndef NO_FMI_FUNCTION_PREFIX
#define FMI2_FUNCTION_PREFIX Controller_Seperate_Step_
#endif

#define MODEL_GUID       "{b84dbf96-ecbb-4fe0-80de-8f2bdf768382}"
#define MODEL            Controller_Seperate_Step
#define MODEL_INITIALIZE Controller_Seperate_Step_initialize
#define MODEL_STEP       Controller_Seperate_Step_step
#define MODEL_TERMINATE  Controller_Seperate_Step_terminate
#define RT_MDL_TYPE      RT_MODEL_Controller_Seperate__T
#define STEP_SIZE        0.01

/* R2019a defines the block parameters as extern */
#ifndef rtmGetDefaultParam
#define rtmGetDefaultParam(S) (&Controller_Seperate_Step_P)
#endif

#define REUSABLE_FUNCTION

static void initializeModelVariables(RT_MDL_TYPE* S, ModelVariable modelVariables[]) {
    modelVariables[0].dtypeID = 0;
    modelVariables[0].size    = 0;
    modelVariables[0].address = &(rtmGetDefaultParam(S)->Step_Time);
    modelVariables[1].dtypeID = 0;
    modelVariables[1].size    = 0;
    modelVariables[1].address = &(rtmGetDefaultParam(S)->Step_Y0);
    modelVariables[2].dtypeID = 0;
    modelVariables[2].size    = 0;
    modelVariables[2].address = &(rtmGetDefaultParam(S)->Step_YFinal);
    modelVariables[3].dtypeID = 0;
    modelVariables[3].size    = 0;
    modelVariables[3].address = &(rtmGetDefaultParam(S)->Integrator_gainval);
    modelVariables[4].dtypeID = 0;
    modelVariables[4].size    = 0;
    modelVariables[4].address = &(rtmGetDefaultParam(S)->Filter_gainval);
    modelVariables[5].dtypeID = 0;
    modelVariables[5].size    = 0;
    modelVariables[5].address = &(rtmGetU(S)->Velocity);
    modelVariables[6].dtypeID = 0;
    modelVariables[6].size    = 0;
    modelVariables[6].address = &(rtmGetY(S)->Throttle);
    modelVariables[7].dtypeID = 0;
    modelVariables[7].size    = 0;
    modelVariables[7].address = &(rtmGetY(S)->Vdesired);
    modelVariables[8].dtypeID = 0;
    modelVariables[8].size    = 0;
    modelVariables[8].address = &(rtmGetBlockIO(S)->Sum);
}

#define N_MODEL_VARIABLES 10
