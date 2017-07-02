################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/featureManager.cpp \
../src/input.cpp \
../src/main.cpp 

OBJS += \
./src/featureManager.o \
./src/input.o \
./src/main.o 

CPP_DEPS += \
./src/featureManager.d \
./src/input.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std="c++11" -I/usr/local/include/vtk-5.10 -I/home/xwong/Downloads/eigen-eigen-67e894c6cd8f -I/home/xwong/Downloads/gnuIoStream/gnuplot-iostream -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


