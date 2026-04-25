#include "ti_msp_dl_config.h"
#include "graph.h"

void GRAPH_SENSOR_Init(void)
{
    DL_GPIO_initDigitalInput(GRAPH_SENSOR_HW_OUT_1_IOMUX);
    DL_GPIO_initDigitalInput(GRAPH_SENSOR_HW_OUT_2_IOMUX);
    DL_GPIO_initDigitalInput(GRAPH_SENSOR_HW_OUT_3_IOMUX);
    DL_GPIO_initDigitalInput(GRAPH_SENSOR_HW_OUT_4_IOMUX);
    DL_GPIO_initDigitalInput(GRAPH_SENSOR_HW_OUT_5_IOMUX);
    DL_GPIO_initDigitalInput(GRAPH_SENSOR_HW_OUT_6_IOMUX);
    DL_GPIO_initDigitalInput(GRAPH_SENSOR_HW_OUT_7_IOMUX);
    DL_GPIO_initDigitalInput(GRAPH_SENSOR_HW_OUT_8_IOMUX);
}