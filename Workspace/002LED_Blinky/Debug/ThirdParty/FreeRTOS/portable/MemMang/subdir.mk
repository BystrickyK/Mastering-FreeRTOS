################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ThirdParty/FreeRTOS/portable/MemMang/heap_4.c 

OBJS += \
./ThirdParty/FreeRTOS/portable/MemMang/heap_4.o 

C_DEPS += \
./ThirdParty/FreeRTOS/portable/MemMang/heap_4.d 


# Each subdirectory must supply rules for building sources it contributes
ThirdParty/FreeRTOS/portable/MemMang/%.o: ../ThirdParty/FreeRTOS/portable/MemMang/%.c ThirdParty/FreeRTOS/portable/MemMang/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L4R5xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/bystr/Embedded_FreeRTOS/Mastering-FreeRTOS/Workspace/002LED_Blinky/ThirdParty/FreeRTOS/include" -I"C:/Users/bystr/Embedded_FreeRTOS/Mastering-FreeRTOS/Workspace/002LED_Blinky/ThirdParty/FreeRTOS/portable" -I"C:/Users/bystr/Embedded_FreeRTOS/Mastering-FreeRTOS/Workspace/002LED_Blinky/ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F" -I"C:/Users/bystr/Embedded_FreeRTOS/Mastering-FreeRTOS/Workspace/002LED_Blinky/ThirdParty/SEGGER/SEGGER" -I"C:/Users/bystr/Embedded_FreeRTOS/Mastering-FreeRTOS/Workspace/002LED_Blinky/ThirdParty/SEGGER" -I"C:/Users/bystr/Embedded_FreeRTOS/Mastering-FreeRTOS/Workspace/002LED_Blinky/ThirdParty/SEGGER/OS" -I"C:/Users/bystr/Embedded_FreeRTOS/Mastering-FreeRTOS/Workspace/002LED_Blinky/ThirdParty/SEGGER/Config" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-ThirdParty-2f-FreeRTOS-2f-portable-2f-MemMang

clean-ThirdParty-2f-FreeRTOS-2f-portable-2f-MemMang:
	-$(RM) ./ThirdParty/FreeRTOS/portable/MemMang/heap_4.d ./ThirdParty/FreeRTOS/portable/MemMang/heap_4.o

.PHONY: clean-ThirdParty-2f-FreeRTOS-2f-portable-2f-MemMang

