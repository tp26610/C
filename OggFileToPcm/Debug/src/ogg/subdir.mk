################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/ogg/bitwise.c \
../src/ogg/framing.c 

OBJS += \
./src/ogg/bitwise.o \
./src/ogg/framing.o 

C_DEPS += \
./src/ogg/bitwise.d \
./src/ogg/framing.d 


# Each subdirectory must supply rules for building sources it contributes
src/ogg/%.o: ../src/ogg/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -I/home/ntut/workspace/eclipse/OggFileToPcm/src -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


