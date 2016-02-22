################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/HDConfigView.cpp \
../src/ParseCommand.cpp \
../src/main.cpp 

OBJS += \
./src/HDConfigView.o \
./src/ParseCommand.o \
./src/main.o 

CPP_DEPS += \
./src/HDConfigView.d \
./src/ParseCommand.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-linux-gnueabihf-g++ -std=c++11 -I/usr/include/libxml2 -I/usr/local/include/cppcms -I"/home/ian/work/cgi/include" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


