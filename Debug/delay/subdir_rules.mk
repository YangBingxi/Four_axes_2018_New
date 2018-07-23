################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
delay/delay.obj: ../delay/delay.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"D:/Project_Program/Ccs/ccsv8/tools/compiler/ti-cgt-arm_18.1.2.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="F:/ProjectFile/ccs/Four_axes_2018_New" --include_path="F:/ProjectFile/ccs/Four_axes_2018_New/0.96'OLED" --include_path="F:/ProjectFile/ccs/Four_axes_2018/colorful_LED" --include_path="F:/ProjectFile/ccs/Four_axes_2018_New/delay" --include_path="F:/ProjectFile/ccs/Four_axes_2018_New/key" --include_path="F:/ProjectFile/ccs/Four_axes_2018_New/Pid" --include_path="F:/ProjectFile/ccs/Four_axes_2018_New/targetConfigs" --include_path="F:/ProjectFile/ccs/Four_axes_2018_New/Timer" --include_path="F:/ProjectFile/ccs/Four_axes_2018_New/uart" --include_path="D:/ti/TivaWare_C_Series-2.1.4.178" --include_path="D:/Project_Program/Ccs/ccsv8/tools/compiler/ti-cgt-arm_18.1.2.LTS/include" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="delay/delay.d_raw" --obj_directory="delay" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


