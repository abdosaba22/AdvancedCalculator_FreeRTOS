################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/Diploma\ Advanced332023/STM32CUBEWORKSPACE/Common/ThirdParty/SEGGER/Rec/segger_uart.c 

OBJS += \
./Common/ThirdParty/SEGGER/Rec/segger_uart.o 

C_DEPS += \
./Common/ThirdParty/SEGGER/Rec/segger_uart.d 


# Each subdirectory must supply rules for building sources it contributes
Common/ThirdParty/SEGGER/Rec/segger_uart.o: D:/Diploma\ Advanced332023/STM32CUBEWORKSPACE/Common/ThirdParty/SEGGER/Rec/segger_uart.c Common/ThirdParty/SEGGER/Rec/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Diploma Advanced332023/STM32CUBEWORKSPACE/Common/ThirdParty/FreeRTOS/include" -I"D:/Diploma Advanced332023/STM32CUBEWORKSPACE/Common/ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F" -I"D:/Diploma Advanced332023/STM32CUBEWORKSPACE/Common/ThirdParty/SEGGER/Config" -I"D:/Diploma Advanced332023/STM32CUBEWORKSPACE/Common/ThirdParty/SEGGER/OS" -I"D:/Diploma Advanced332023/STM32CUBEWORKSPACE/Common/ThirdParty/SEGGER/SEGGER" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Common-2f-ThirdParty-2f-SEGGER-2f-Rec

clean-Common-2f-ThirdParty-2f-SEGGER-2f-Rec:
	-$(RM) ./Common/ThirdParty/SEGGER/Rec/segger_uart.cyclo ./Common/ThirdParty/SEGGER/Rec/segger_uart.d ./Common/ThirdParty/SEGGER/Rec/segger_uart.o ./Common/ThirdParty/SEGGER/Rec/segger_uart.su

.PHONY: clean-Common-2f-ThirdParty-2f-SEGGER-2f-Rec

