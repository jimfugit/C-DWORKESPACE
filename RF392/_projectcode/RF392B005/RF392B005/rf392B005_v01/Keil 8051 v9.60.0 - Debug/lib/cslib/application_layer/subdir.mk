################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib/cslib/application_layer/cslib_config.c 

OBJS += \
./lib/cslib/application_layer/cslib_config.OBJ 


# Each subdirectory must supply rules for building sources it contributes
lib/cslib/application_layer/%.OBJ: ../lib/cslib/application_layer/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Keil 8051 Compiler'
	C51 "@$(patsubst %.OBJ,%.__i,$@)" || $(RC)
	@echo 'Finished building: $<'
	@echo ' '

lib/cslib/application_layer/cslib_config.OBJ: E:/jim/project/A2021/CDWorkingroom1/RF392/_projectcode/RF392B005/RF392B005/rf392B005_v01/inc/config/cslib_config.h E:/jim/project/A2021/CDWorkingroom1/RF392/_projectcode/RF392B005/RF392B005/rf392B005_v01/inc/config/cslib_hwconfig.h D:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.0/Lib/efm8_capsense/cslib.h D:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.0/Device/shared/si8051Base/si_toolchain.h D:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.0/Lib/efm8_capsense/si_toolchain_select.h D:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.0/Device/shared/si8051Base/stdint.h D:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.0/Device/shared/si8051Base/stdbool.h


