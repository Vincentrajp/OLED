################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/SSD1322_OLED_lib/SSD1322_API.c \
../Core/Src/SSD1322_OLED_lib/SSD1322_GFX.c \
../Core/Src/SSD1322_OLED_lib/SSD1322_HW_Driver.c 

OBJS += \
./Core/Src/SSD1322_OLED_lib/SSD1322_API.o \
./Core/Src/SSD1322_OLED_lib/SSD1322_GFX.o \
./Core/Src/SSD1322_OLED_lib/SSD1322_HW_Driver.o 

C_DEPS += \
./Core/Src/SSD1322_OLED_lib/SSD1322_API.d \
./Core/Src/SSD1322_OLED_lib/SSD1322_GFX.d \
./Core/Src/SSD1322_OLED_lib/SSD1322_HW_Driver.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/SSD1322_OLED_lib/%.o Core/Src/SSD1322_OLED_lib/%.su Core/Src/SSD1322_OLED_lib/%.cyclo: ../Core/Src/SSD1322_OLED_lib/%.c Core/Src/SSD1322_OLED_lib/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../USB_HOST/App -I../USB_HOST/Target -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/sghute/STM32CubeIDE/driverDevelopment/oled1/Core/Src/SSD1322_OLED_lib" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-SSD1322_OLED_lib

clean-Core-2f-Src-2f-SSD1322_OLED_lib:
	-$(RM) ./Core/Src/SSD1322_OLED_lib/SSD1322_API.cyclo ./Core/Src/SSD1322_OLED_lib/SSD1322_API.d ./Core/Src/SSD1322_OLED_lib/SSD1322_API.o ./Core/Src/SSD1322_OLED_lib/SSD1322_API.su ./Core/Src/SSD1322_OLED_lib/SSD1322_GFX.cyclo ./Core/Src/SSD1322_OLED_lib/SSD1322_GFX.d ./Core/Src/SSD1322_OLED_lib/SSD1322_GFX.o ./Core/Src/SSD1322_OLED_lib/SSD1322_GFX.su ./Core/Src/SSD1322_OLED_lib/SSD1322_HW_Driver.cyclo ./Core/Src/SSD1322_OLED_lib/SSD1322_HW_Driver.d ./Core/Src/SSD1322_OLED_lib/SSD1322_HW_Driver.o ./Core/Src/SSD1322_OLED_lib/SSD1322_HW_Driver.su

.PHONY: clean-Core-2f-Src-2f-SSD1322_OLED_lib

