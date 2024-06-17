################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/jsonconfig/abstract_json_config_getter.cpp \
../src/jsonconfig/json_config.cpp 

CPP_DEPS += \
./src/jsonconfig/abstract_json_config_getter.d \
./src/jsonconfig/json_config.d 

OBJS += \
./src/jsonconfig/abstract_json_config_getter.o \
./src/jsonconfig/json_config.o 


# Each subdirectory must supply rules for building sources it contributes
src/jsonconfig/%.o: ../src/jsonconfig/%.cpp src/jsonconfig/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -D__DEBUG=1 -DUSE_OS_TZDB=1 -D__SUPLA_SERVER=1 -DUSE_DEPRECATED_EMEV_V1 -D__TEST=1 -D__OPENSSL_TOOLS=1 -D__BCRYPT=1 -I../src -I../src/asynctask -I../src/mqtt -I$(INCMYSQL) -I../src/user -I../src/device -I../src/client -I$(SSLDIR)/include -I../src/test -O2 -g3 -Wall -fsigned-char -c -fmessage-length=0 -fstack-protector-all -D_FORTIFY_SOURCE=2 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-jsonconfig

clean-src-2f-jsonconfig:
	-$(RM) ./src/jsonconfig/abstract_json_config_getter.d ./src/jsonconfig/abstract_json_config_getter.o ./src/jsonconfig/json_config.d ./src/jsonconfig/json_config.o

.PHONY: clean-src-2f-jsonconfig

