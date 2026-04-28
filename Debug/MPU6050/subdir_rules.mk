################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
MPU6050/%.o: ../MPU6050/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Arm Compiler - building file: "$<"'
	"D:/Study/DianSai/M0_software_info/CCS Theia/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"D:/Study/DianSai/TTSourceCode/M0G3507_TB6612_TT2/MPU6050" -I"D:/Study/DianSai/TTSourceCode/M0G3507_TB6612_TT2/clock" -I"D:/Study/DianSai/TTSourceCode/M0G3507_TB6612_TT2/Motor" -I"D:/Study/DianSai/TTSourceCode/M0G3507_TB6612_TT2/GRAPH" -I"D:/Study/DianSai/TTSourceCode/M0G3507_TB6612_TT2" -I"D:/Study/DianSai/TTSourceCode/M0G3507_TB6612_TT2/Debug" -I"C:/ti/mspm0_sdk_2_10_00_04/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_10_00_04/source" -DMPU6050 -DMOTION_DRIVER_TARGET_MSPM0 -gdwarf-3 -MMD -MP -MF"MPU6050/$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


