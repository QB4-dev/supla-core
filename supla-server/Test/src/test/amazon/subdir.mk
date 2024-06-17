################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/test/amazon/AlexaChangeReportRequestTest.cpp \
../src/test/amazon/AlexaDeleteRequestTest.cpp \
../src/test/amazon/AlexaDiscoverRequestTest.cpp \
../src/test/amazon/AlexaResponseRequestTest.cpp \
../src/test/amazon/AlexaTokenRefreshTest.cpp 

CPP_DEPS += \
./src/test/amazon/AlexaChangeReportRequestTest.d \
./src/test/amazon/AlexaDeleteRequestTest.d \
./src/test/amazon/AlexaDiscoverRequestTest.d \
./src/test/amazon/AlexaResponseRequestTest.d \
./src/test/amazon/AlexaTokenRefreshTest.d 

OBJS += \
./src/test/amazon/AlexaChangeReportRequestTest.o \
./src/test/amazon/AlexaDeleteRequestTest.o \
./src/test/amazon/AlexaDiscoverRequestTest.o \
./src/test/amazon/AlexaResponseRequestTest.o \
./src/test/amazon/AlexaTokenRefreshTest.o 


# Each subdirectory must supply rules for building sources it contributes
src/test/amazon/%.o: ../src/test/amazon/%.cpp src/test/amazon/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -D__DEBUG=1 -DUSE_OS_TZDB=1 -D__SUPLA_SERVER=1 -DUSE_DEPRECATED_EMEV_V1 -D__TEST=1 -D__OPENSSL_TOOLS=1 -D__BCRYPT=1 -I../src -I../src/asynctask -I../src/mqtt -I$(INCMYSQL) -I../src/user -I../src/device -I../src/client -I$(SSLDIR)/include -I../src/test -O2 -g3 -Wall -fsigned-char -c -fmessage-length=0 -fstack-protector-all -D_FORTIFY_SOURCE=2 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-test-2f-amazon

clean-src-2f-test-2f-amazon:
	-$(RM) ./src/test/amazon/AlexaChangeReportRequestTest.d ./src/test/amazon/AlexaChangeReportRequestTest.o ./src/test/amazon/AlexaDeleteRequestTest.d ./src/test/amazon/AlexaDeleteRequestTest.o ./src/test/amazon/AlexaDiscoverRequestTest.d ./src/test/amazon/AlexaDiscoverRequestTest.o ./src/test/amazon/AlexaResponseRequestTest.d ./src/test/amazon/AlexaResponseRequestTest.o ./src/test/amazon/AlexaTokenRefreshTest.d ./src/test/amazon/AlexaTokenRefreshTest.o

.PHONY: clean-src-2f-test-2f-amazon

