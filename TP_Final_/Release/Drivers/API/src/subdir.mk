################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/API/src/API_AHT10.c \
../Drivers/API/src/API_AHT10_MEF.c \
../Drivers/API/src/API_GPIO.c \
../Drivers/API/src/API_LCD_i2c.c \
../Drivers/API/src/API_LCD_port.c \
../Drivers/API/src/API_TempConfig.c \
../Drivers/API/src/API_debounce.c \
../Drivers/API/src/API_delay.c \
../Drivers/API/src/API_i2c.c \
../Drivers/API/src/API_uart.c 

OBJS += \
./Drivers/API/src/API_AHT10.o \
./Drivers/API/src/API_AHT10_MEF.o \
./Drivers/API/src/API_GPIO.o \
./Drivers/API/src/API_LCD_i2c.o \
./Drivers/API/src/API_LCD_port.o \
./Drivers/API/src/API_TempConfig.o \
./Drivers/API/src/API_debounce.o \
./Drivers/API/src/API_delay.o \
./Drivers/API/src/API_i2c.o \
./Drivers/API/src/API_uart.o 

C_DEPS += \
./Drivers/API/src/API_AHT10.d \
./Drivers/API/src/API_AHT10_MEF.d \
./Drivers/API/src/API_GPIO.d \
./Drivers/API/src/API_LCD_i2c.d \
./Drivers/API/src/API_LCD_port.d \
./Drivers/API/src/API_TempConfig.d \
./Drivers/API/src/API_debounce.d \
./Drivers/API/src/API_delay.d \
./Drivers/API/src/API_i2c.d \
./Drivers/API/src/API_uart.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/API/src/%.o Drivers/API/src/%.su Drivers/API/src/%.cyclo: ../Drivers/API/src/%.c Drivers/API/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DSTM32 -DSTM32F429ZITx -DSTM32F4 -DNUCLEO_F429ZI -c -I../Inc -I"/media/micael/Nuevo vol/ESPECIALIDAD EN SISTEMAS EMBEBIDOS/Programación de Microprocesadores/PdM_workspace_Micael/TP_Final_/Drivers/STM32F4xx_HAL_Driver/Inc" -I"/media/micael/Nuevo vol/ESPECIALIDAD EN SISTEMAS EMBEBIDOS/Programación de Microprocesadores/PdM_workspace_Micael/TP_Final_/Drivers/CMSIS/Include" -I"/media/micael/Nuevo vol/ESPECIALIDAD EN SISTEMAS EMBEBIDOS/Programación de Microprocesadores/PdM_workspace_Micael/TP_Final_/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"/media/micael/Nuevo vol/ESPECIALIDAD EN SISTEMAS EMBEBIDOS/Programación de Microprocesadores/PdM_workspace_Micael/TP_Final_/Drivers/BSP/STM32F4xx_Nucleo_144" -I"/media/micael/Nuevo vol/ESPECIALIDAD EN SISTEMAS EMBEBIDOS/Programación de Microprocesadores/PdM_workspace_Micael/TP_Final_/Drivers/Core/Inc" -I"/media/micael/Nuevo vol/ESPECIALIDAD EN SISTEMAS EMBEBIDOS/Programación de Microprocesadores/PdM_workspace_Micael/TP_Final_/Drivers/API/Inc" -I"/media/micael/Nuevo vol/ESPECIALIDAD EN SISTEMAS EMBEBIDOS/Programación de Microprocesadores/PdM_workspace_Micael/TP_Final_/Drivers/API/src" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-API-2f-src

clean-Drivers-2f-API-2f-src:
	-$(RM) ./Drivers/API/src/API_AHT10.cyclo ./Drivers/API/src/API_AHT10.d ./Drivers/API/src/API_AHT10.o ./Drivers/API/src/API_AHT10.su ./Drivers/API/src/API_AHT10_MEF.cyclo ./Drivers/API/src/API_AHT10_MEF.d ./Drivers/API/src/API_AHT10_MEF.o ./Drivers/API/src/API_AHT10_MEF.su ./Drivers/API/src/API_GPIO.cyclo ./Drivers/API/src/API_GPIO.d ./Drivers/API/src/API_GPIO.o ./Drivers/API/src/API_GPIO.su ./Drivers/API/src/API_LCD_i2c.cyclo ./Drivers/API/src/API_LCD_i2c.d ./Drivers/API/src/API_LCD_i2c.o ./Drivers/API/src/API_LCD_i2c.su ./Drivers/API/src/API_LCD_port.cyclo ./Drivers/API/src/API_LCD_port.d ./Drivers/API/src/API_LCD_port.o ./Drivers/API/src/API_LCD_port.su ./Drivers/API/src/API_TempConfig.cyclo ./Drivers/API/src/API_TempConfig.d ./Drivers/API/src/API_TempConfig.o ./Drivers/API/src/API_TempConfig.su ./Drivers/API/src/API_debounce.cyclo ./Drivers/API/src/API_debounce.d ./Drivers/API/src/API_debounce.o ./Drivers/API/src/API_debounce.su ./Drivers/API/src/API_delay.cyclo ./Drivers/API/src/API_delay.d ./Drivers/API/src/API_delay.o ./Drivers/API/src/API_delay.su ./Drivers/API/src/API_i2c.cyclo ./Drivers/API/src/API_i2c.d ./Drivers/API/src/API_i2c.o ./Drivers/API/src/API_i2c.su ./Drivers/API/src/API_uart.cyclo ./Drivers/API/src/API_uart.d ./Drivers/API/src/API_uart.o ./Drivers/API/src/API_uart.su

.PHONY: clean-Drivers-2f-API-2f-src

