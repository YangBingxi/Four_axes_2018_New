################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := D:/Project_Program/Ccs/ccsv8/tools/compiler/ti-cgt-arm_18.1.2.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./main.obj" \
"./tm4c123gh6pm_startup_ccs.obj" \
"./0.96'OLED/OLED.obj" \
"./Control/Control.obj" \
"./Pid/pid.obj" \
"./Timer/Timer.obj" \
"./Type_conversion/Type_conversion.obj" \
"./colorful_LED/colorful_LED.obj" \
"./delay/delay.obj" \
"./key/key.obj" \
"./uart/uart_echo.obj" \
"./uart/uartstdio.obj" \
"D:/ti/TivaWare_C_Series-2.1.4.178/driverlib/ccs/Debug/driverlib.lib" \
"../tm4c123gh6pm.cmd" \
$(GEN_CMDS__FLAG) \
-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include 0.96'OLED/subdir_vars.mk
-include Control/subdir_vars.mk
-include Pid/subdir_vars.mk
-include Timer/subdir_vars.mk
-include Type_conversion/subdir_vars.mk
-include colorful_LED/subdir_vars.mk
-include delay/subdir_vars.mk
-include key/subdir_vars.mk
-include uart/subdir_vars.mk
-include subdir_rules.mk
-include 0.96'OLED/subdir_rules.mk
-include Control/subdir_rules.mk
-include Pid/subdir_rules.mk
-include Timer/subdir_rules.mk
-include Type_conversion/subdir_rules.mk
-include colorful_LED/subdir_rules.mk
-include delay/subdir_rules.mk
-include key/subdir_rules.mk
-include uart/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
Four_axes_2018_New.out \

EXE_OUTPUTS__QUOTED += \
"Four_axes_2018_New.out" \

BIN_OUTPUTS += \
Four_axes_2018_New.hex \

BIN_OUTPUTS__QUOTED += \
"Four_axes_2018_New.hex" \


# All Target
all: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "Four_axes_2018_New.out"

# Tool invocations
Four_axes_2018_New.out: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: ARM Linker'
	"D:/Project_Program/Ccs/ccsv8/tools/compiler/ti-cgt-arm_18.1.2.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi -z -m"Four_axes_2018_New.map" --heap_size=0 --stack_size=512 -i"D:/Project_Program/Ccs/ccsv8/tools/compiler/ti-cgt-arm_18.1.2.LTS/lib" -i"D:/Project_Program/Ccs/ccsv8/tools/compiler/ti-cgt-arm_18.1.2.LTS/include" --reread_libs --diag_wrap=off --display_error_number --warn_sections --xml_link_info="Four_axes_2018_New_linkInfo.xml" --rom_model -o "Four_axes_2018_New.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

Four_axes_2018_New.hex: $(EXE_OUTPUTS)
	@echo 'Building files: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo 'Invoking: ARM Hex Utility'
	"D:/Project_Program/Ccs/ccsv8/tools/compiler/ti-cgt-arm_18.1.2.LTS/bin/armhex"  -o "Four_axes_2018_New.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "main.obj" "tm4c123gh6pm_startup_ccs.obj" "0.96'OLED\OLED.obj" "Control\Control.obj" "Pid\pid.obj" "Timer\Timer.obj" "Type_conversion\Type_conversion.obj" "colorful_LED\colorful_LED.obj" "delay\delay.obj" "key\key.obj" "uart\uart_echo.obj" "uart\uartstdio.obj" 
	-$(RM) "main.d" "tm4c123gh6pm_startup_ccs.d" "0.96'OLED\OLED.d" "Control\Control.d" "Pid\pid.d" "Timer\Timer.d" "Type_conversion\Type_conversion.d" "colorful_LED\colorful_LED.d" "delay\delay.d" "key\key.d" "uart\uart_echo.d" "uart\uartstdio.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

