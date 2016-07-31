################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Behaviors/Behavior.cpp \
../Behaviors/MoveForward.cpp \
../Behaviors/TurnRight.cpp 

OBJS += \
./Behaviors/Behavior.o \
./Behaviors/MoveForward.o \
./Behaviors/TurnRight.o 

CPP_DEPS += \
./Behaviors/Behavior.d \
./Behaviors/MoveForward.d \
./Behaviors/TurnRight.d 


# Each subdirectory must supply rules for building sources it contributes
Behaviors/%.o: ../Behaviors/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


