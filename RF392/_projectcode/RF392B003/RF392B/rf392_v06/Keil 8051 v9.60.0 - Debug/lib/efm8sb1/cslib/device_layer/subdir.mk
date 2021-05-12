################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib/efm8sb1/cslib/device_layer/hardware_config.c \
../lib/efm8sb1/cslib/device_layer/hardware_routines.c \
../lib/efm8sb1/cslib/device_layer/low_power_config.c 

OBJS += \
./lib/efm8sb1/cslib/device_layer/hardware_config.OBJ \
./lib/efm8sb1/cslib/device_layer/hardware_routines.OBJ \
./lib/efm8sb1/cslib/device_layer/low_power_config.OBJ 


# Each subdirectory must supply rules for building sources it contributes
lib/efm8sb1/cslib/device_layer/%.OBJ: ../lib/efm8sb1/cslib/device_layer/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Keil 8051 Compiler'
	C51 "@$(patsubst %.OBJ,%.__i,$@)" || $(RC)
	@echo 'Finished building: $<'
	@echo ' '

lib/efm8sb1/cslib/device_layer/hardware_config.OBJ: E:/jim/project/A2021/RF392/_projectcode/RF392B003/RF392B/rf392_v06/inc/config/cslib_hwconfig.h E:/jim/project/A2021/RF392/_projectcode/RF392B003/RF392B/rf392_v06/lib/efm8sb1/cslib/device_layer/hardware_routines.h E:/jim/project/A2021/RF392/_projectcode/RF392B003/RF392B/rf392_v06/inc/config/cslib_config.h D:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.0/Device/shared/si8051Base/si_toolchain.h D:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.0/Device/shared/si8051Base/stdint.h D:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.0/Device/shared/si8051Base/stdbool.h

lib/efm8sb1/cslib/device_layer/hardware_routines.OBJ: E:/jim/project/A2021/RF392/_projectcode/RF392B003/RF392B/rf392_v06/inc/config/cslib_hwconfig.h E:/jim/project/A2021/RF392/_projectcode/RF392B003/RF392B/rf392_v06/inc/config/cslib_config.h E:/jim/project/A2021/RF392/_projectcode/RF392B003/RF392B/rf392_v06/lib/efm8sb1/cslib/device_layer/low_power_config.h D:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.0/Lib/efm8_capsense/cslib.h E:/jim/project/A2021/RF392/_projectcode/RF392B003/RF392B/rf392_v06/lib/efm8sb1/cslib/device_layer/hardware_routines.h D:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.0/Device/EFM8SB1/inc/SI_EFM8SB1_Defs.h D:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.0/Device/shared/si8051Base/si_toolchain.h D:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.0/Lib/efm8_capsense/si_toolchain_select.h D:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.0/Device/shared/si8051Base/stdint.h D:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.0/Device/shared/si8051Base/stdbool.h

lib/efm8sb1/cslib/device_layer/low_power_config.OBJ: D:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.0/Device/shared/si8051Base/si_toolchain.h E:/jim/project/A2021/RF392/_projectcode/RF392B003/RF392B/rf392_v06/inc/config/cslib_hwconfig.h E:/jim/project/A2021/RF392/_projectcode/RF392B003/RF392B/rf392_v06/inc/config/cslib_config.h D:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.0/Lib/efm8_capsense/cslib.h E:/jim/project/A2021/RF392/_projectcode/RF392B003/RF392B/rf392_v06/lib/efm8sb1/cslib/device_layer/low_power_hardware.h E:/jim/project/A2021/RF392/_projectcode/RF392B003/RF392B/rf392_v06/lib/efm8sb1/cslib/device_layer/hardware_routines.h D:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.0/Device/EFM8SB1/inc/SI_EFM8SB1_Defs.h E:/jim/project/A2021/RF392/_projectcode/RF392B003/RF392B/rf392_v06/lib/efm8sb1/cslib/device_layer/low_power_config.h D:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.0/Device/shared/si8051Base/stdint.h D:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.0/Device/shared/si8051Base/stdbool.h D:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.0/Lib/efm8_capsense/si_toolchain_select.h


