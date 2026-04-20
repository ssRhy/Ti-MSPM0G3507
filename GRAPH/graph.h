#ifndef __GRAPH_H__
#define __GRAPH_H__

#include "ti_msp_dl_config.h"


#define READ_HW_OUT_1   (DL_GPIO_readPins(GRAPH_SENSOR_HW_OUT_1_PORT, GRAPH_SENSOR_HW_OUT_1_PIN) ? 1 : 0)
#define READ_HW_OUT_2   (DL_GPIO_readPins(GRAPH_SENSOR_HW_OUT_2_PORT, GRAPH_SENSOR_HW_OUT_2_PIN) ? 1 : 0)
#define READ_HW_OUT_3   (DL_GPIO_readPins(GRAPH_SENSOR_HW_OUT_3_PORT, GRAPH_SENSOR_HW_OUT_3_PIN) ? 1 : 0)
#define READ_HW_OUT_4   (DL_GPIO_readPins(GRAPH_SENSOR_HW_OUT_4_PORT, GRAPH_SENSOR_HW_OUT_4_PIN) ? 1 : 0)

void GRAPH_SENSOR_Init(void);

#endif