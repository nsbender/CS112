################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../Matrix.o \
../MatrixTester.o \
../runTimeTrials.o \
../tester.o 

CPP_SRCS += \
../Matrix.cpp \
../MatrixTester.cpp \
../runTimeTrials.cpp \
../tester.cpp 

OBJS += \
./Matrix.o \
./MatrixTester.o \
./runTimeTrials.o \
./tester.o 

CPP_DEPS += \
./Matrix.d \
./MatrixTester.d \
./runTimeTrials.d \
./tester.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -fopenmp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


