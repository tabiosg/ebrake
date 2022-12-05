################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/adc_sensor.c \
../Core/Src/battery_sensor.c \
../Core/Src/brake_wireless.c \
../Core/Src/force_sensor.c \
../Core/Src/i2c_mux.c \
../Core/Src/imu.c \
../Core/Src/interrupt_timer.c \
../Core/Src/joint.c \
../Core/Src/main.c \
../Core/Src/motor.c \
../Core/Src/pin_data.c \
../Core/Src/skater.c \
../Core/Src/speed_sensor.c \
../Core/Src/stm32g0xx_hal_msp.c \
../Core/Src/stm32g0xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32g0xx.c 

OBJS += \
./Core/Src/adc_sensor.o \
./Core/Src/battery_sensor.o \
./Core/Src/brake_wireless.o \
./Core/Src/force_sensor.o \
./Core/Src/i2c_mux.o \
./Core/Src/imu.o \
./Core/Src/interrupt_timer.o \
./Core/Src/joint.o \
./Core/Src/main.o \
./Core/Src/motor.o \
./Core/Src/pin_data.o \
./Core/Src/skater.o \
./Core/Src/speed_sensor.o \
./Core/Src/stm32g0xx_hal_msp.o \
./Core/Src/stm32g0xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32g0xx.o 

C_DEPS += \
./Core/Src/adc_sensor.d \
./Core/Src/battery_sensor.d \
./Core/Src/brake_wireless.d \
./Core/Src/force_sensor.d \
./Core/Src/i2c_mux.d \
./Core/Src/imu.d \
./Core/Src/interrupt_timer.d \
./Core/Src/joint.d \
./Core/Src/main.d \
./Core/Src/motor.d \
./Core/Src/pin_data.d \
./Core/Src/skater.d \
./Core/Src/speed_sensor.d \
./Core/Src/stm32g0xx_hal_msp.d \
./Core/Src/stm32g0xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32g0xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G031xx -c -I../Core/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -O3 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/adc_sensor.d ./Core/Src/adc_sensor.o ./Core/Src/adc_sensor.su ./Core/Src/battery_sensor.d ./Core/Src/battery_sensor.o ./Core/Src/battery_sensor.su ./Core/Src/brake_wireless.d ./Core/Src/brake_wireless.o ./Core/Src/brake_wireless.su ./Core/Src/force_sensor.d ./Core/Src/force_sensor.o ./Core/Src/force_sensor.su ./Core/Src/i2c_mux.d ./Core/Src/i2c_mux.o ./Core/Src/i2c_mux.su ./Core/Src/imu.d ./Core/Src/imu.o ./Core/Src/imu.su ./Core/Src/interrupt_timer.d ./Core/Src/interrupt_timer.o ./Core/Src/interrupt_timer.su ./Core/Src/joint.d ./Core/Src/joint.o ./Core/Src/joint.su ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/motor.d ./Core/Src/motor.o ./Core/Src/motor.su ./Core/Src/pin_data.d ./Core/Src/pin_data.o ./Core/Src/pin_data.su ./Core/Src/skater.d ./Core/Src/skater.o ./Core/Src/skater.su ./Core/Src/speed_sensor.d ./Core/Src/speed_sensor.o ./Core/Src/speed_sensor.su ./Core/Src/stm32g0xx_hal_msp.d ./Core/Src/stm32g0xx_hal_msp.o ./Core/Src/stm32g0xx_hal_msp.su ./Core/Src/stm32g0xx_it.d ./Core/Src/stm32g0xx_it.o ./Core/Src/stm32g0xx_it.su ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32g0xx.d ./Core/Src/system_stm32g0xx.o ./Core/Src/system_stm32g0xx.su

.PHONY: clean-Core-2f-Src

