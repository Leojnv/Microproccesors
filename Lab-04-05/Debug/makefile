################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32F7xx_HAL_Driver/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
Lab-04-05.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Lab-04-05.list \


# All Target
all: Lab-04-05.elf secondary-outputs

# Tool invocations
Lab-04-05.elf: $(OBJS) $(USER_OBJS) C:\Users\leojn\STM32CubeIDE\workspace_1.0.2\Lab-04-05\STM32F767ZITX_FLASH.ld
	arm-none-eabi-gcc -o "Lab-04-05.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m7 -T"C:\Users\leojn\STM32CubeIDE\workspace_1.0.2\Lab-04-05\STM32F767ZITX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Lab-04-05.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -u _printf_float -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Lab-04-05.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Lab-04-05.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
