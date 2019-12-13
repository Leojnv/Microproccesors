################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/conversion.c \
../Core/Src/main.c \
../Core/Src/retarget.c \
../Core/Src/stm32f7xx_hal_msp.c \
../Core/Src/stm32f7xx_it.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f7xx.c 

OBJS += \
./Core/Src/conversion.o \
./Core/Src/main.o \
./Core/Src/retarget.o \
./Core/Src/stm32f7xx_hal_msp.o \
./Core/Src/stm32f7xx_it.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f7xx.o 

C_DEPS += \
./Core/Src/conversion.d \
./Core/Src/main.d \
./Core/Src/retarget.d \
./Core/Src/stm32f7xx_hal_msp.d \
./Core/Src/stm32f7xx_it.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f7xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/conversion.o: ../Core/Src/conversion.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F767xx -DDEBUG -c -IC:/Users/leojn/STM32Cube/Repository/STM32Cube_FW_F7_V1.15.0/Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Core/Inc -IC:/Users/leojn/STM32Cube/Repository/STM32Cube_FW_F7_V1.15.0/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -IC:/Users/leojn/STM32Cube/Repository/STM32Cube_FW_F7_V1.15.0/Drivers/CMSIS/Include -IC:/Users/leojn/STM32Cube/Repository/STM32Cube_FW_F7_V1.15.0/Drivers/STM32F7xx_HAL_Driver/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/conversion.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/main.o: ../Core/Src/main.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F767xx -DDEBUG -c -IC:/Users/leojn/STM32Cube/Repository/STM32Cube_FW_F7_V1.15.0/Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Core/Inc -IC:/Users/leojn/STM32Cube/Repository/STM32Cube_FW_F7_V1.15.0/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -IC:/Users/leojn/STM32Cube/Repository/STM32Cube_FW_F7_V1.15.0/Drivers/CMSIS/Include -IC:/Users/leojn/STM32Cube/Repository/STM32Cube_FW_F7_V1.15.0/Drivers/STM32F7xx_HAL_Driver/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/main.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/retarget.o: ../Core/Src/retarget.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F767xx -DDEBUG -c -IC:/Users/leojn/STM32Cube/Repository/STM32Cube_FW_F7_V1.15.0/Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Core/Inc -IC:/Users/leojn/STM32Cube/Repository/STM32Cube_FW_F7_V1.15.0/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -IC:/Users/leojn/STM32Cube/Repository/STM32Cube_FW_F7_V1.15.0/Drivers/CMSIS/Include -IC:/Users/leojn/STM32Cube/Repository/STM32Cube_FW_F7_V1.15.0/Drivers/STM32F7xx_HAL_Driver/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/retarget.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/stm32f7xx_hal_msp.o: ../Core/Src/stm32f7xx_hal_msp.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F767xx -DDEBUG -c -IC:/Users/leojn/STM32Cube/Repository/STM32Cube_FW_F7_V1.15.0/Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Core/Inc -IC:/Users/leojn/STM32Cube/Repository/STM32Cube_FW_F7_V1.15.0/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -IC:/Users/leojn/STM32Cube/Repository/STM32Cube_FW_F7_V1.15.0/Drivers/CMSIS/Include -IC:/Users/leojn/STM32Cube/Repository/STM32Cube_FW_F7_V1.15.0/Drivers/STM32F7xx_HAL_Driver/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/stm32f7xx_hal_msp.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/stm32f7xx_it.o: ../Core/Src/stm32f7xx_it.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F767xx -DDEBUG -c -IC:/Users/leojn/STM32Cube/Repository/STM32Cube_FW_F7_V1.15.0/Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Core/Inc -IC:/Users/leojn/STM32Cube/Repository/STM32Cube_FW_F7_V1.15.0/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -IC:/Users/leojn/STM32Cube/Repository/STM32Cube_FW_F7_V1.15.0/Drivers/CMSIS/Include -IC:/Users/leojn/STM32Cube/Repository/STM32Cube_FW_F7_V1.15.0/Drivers/STM32F7xx_HAL_Driver/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/stm32f7xx_it.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/sysmem.o: ../Core/Src/sysmem.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F767xx -DDEBUG -c -IC:/Users/leojn/STM32Cube/Repository/STM32Cube_FW_F7_V1.15.0/Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Core/Inc -IC:/Users/leojn/STM32Cube/Repository/STM32Cube_FW_F7_V1.15.0/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -IC:/Users/leojn/STM32Cube/Repository/STM32Cube_FW_F7_V1.15.0/Drivers/CMSIS/Include -IC:/Users/leojn/STM32Cube/Repository/STM32Cube_FW_F7_V1.15.0/Drivers/STM32F7xx_HAL_Driver/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/sysmem.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/system_stm32f7xx.o: ../Core/Src/system_stm32f7xx.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F767xx -DDEBUG -c -IC:/Users/leojn/STM32Cube/Repository/STM32Cube_FW_F7_V1.15.0/Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Core/Inc -IC:/Users/leojn/STM32Cube/Repository/STM32Cube_FW_F7_V1.15.0/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -IC:/Users/leojn/STM32Cube/Repository/STM32Cube_FW_F7_V1.15.0/Drivers/CMSIS/Include -IC:/Users/leojn/STM32Cube/Repository/STM32Cube_FW_F7_V1.15.0/Drivers/STM32F7xx_HAL_Driver/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/system_stm32f7xx.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
