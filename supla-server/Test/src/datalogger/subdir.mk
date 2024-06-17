################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/datalogger/abstract_electricity_logger.cpp \
../src/datalogger/abstract_electricity_logger_dao.cpp \
../src/datalogger/current_logger.cpp \
../src/datalogger/current_logger_dao.cpp \
../src/datalogger/general_purpose_measurement_logger.cpp \
../src/datalogger/general_purpose_measurement_logger_dao.cpp \
../src/datalogger/general_purpose_meter_logger.cpp \
../src/datalogger/general_purpose_meter_logger_dao.cpp \
../src/datalogger/hp_thermostat_logger.cpp \
../src/datalogger/hp_thermostat_logger_dao.cpp \
../src/datalogger/impulse_logger.cpp \
../src/datalogger/impulse_logger_dao.cpp \
../src/datalogger/power_active_logger.cpp \
../src/datalogger/power_active_logger_dao.cpp \
../src/datalogger/temperature_logger.cpp \
../src/datalogger/temperature_logger_dao.cpp \
../src/datalogger/total_energy_logger.cpp \
../src/datalogger/total_energy_logger_dao.cpp \
../src/datalogger/voltage_aberration_logger.cpp \
../src/datalogger/voltage_aberration_logger_dao.cpp \
../src/datalogger/voltage_logger.cpp \
../src/datalogger/voltage_logger_dao.cpp 

CPP_DEPS += \
./src/datalogger/abstract_electricity_logger.d \
./src/datalogger/abstract_electricity_logger_dao.d \
./src/datalogger/current_logger.d \
./src/datalogger/current_logger_dao.d \
./src/datalogger/general_purpose_measurement_logger.d \
./src/datalogger/general_purpose_measurement_logger_dao.d \
./src/datalogger/general_purpose_meter_logger.d \
./src/datalogger/general_purpose_meter_logger_dao.d \
./src/datalogger/hp_thermostat_logger.d \
./src/datalogger/hp_thermostat_logger_dao.d \
./src/datalogger/impulse_logger.d \
./src/datalogger/impulse_logger_dao.d \
./src/datalogger/power_active_logger.d \
./src/datalogger/power_active_logger_dao.d \
./src/datalogger/temperature_logger.d \
./src/datalogger/temperature_logger_dao.d \
./src/datalogger/total_energy_logger.d \
./src/datalogger/total_energy_logger_dao.d \
./src/datalogger/voltage_aberration_logger.d \
./src/datalogger/voltage_aberration_logger_dao.d \
./src/datalogger/voltage_logger.d \
./src/datalogger/voltage_logger_dao.d 

OBJS += \
./src/datalogger/abstract_electricity_logger.o \
./src/datalogger/abstract_electricity_logger_dao.o \
./src/datalogger/current_logger.o \
./src/datalogger/current_logger_dao.o \
./src/datalogger/general_purpose_measurement_logger.o \
./src/datalogger/general_purpose_measurement_logger_dao.o \
./src/datalogger/general_purpose_meter_logger.o \
./src/datalogger/general_purpose_meter_logger_dao.o \
./src/datalogger/hp_thermostat_logger.o \
./src/datalogger/hp_thermostat_logger_dao.o \
./src/datalogger/impulse_logger.o \
./src/datalogger/impulse_logger_dao.o \
./src/datalogger/power_active_logger.o \
./src/datalogger/power_active_logger_dao.o \
./src/datalogger/temperature_logger.o \
./src/datalogger/temperature_logger_dao.o \
./src/datalogger/total_energy_logger.o \
./src/datalogger/total_energy_logger_dao.o \
./src/datalogger/voltage_aberration_logger.o \
./src/datalogger/voltage_aberration_logger_dao.o \
./src/datalogger/voltage_logger.o \
./src/datalogger/voltage_logger_dao.o 


# Each subdirectory must supply rules for building sources it contributes
src/datalogger/%.o: ../src/datalogger/%.cpp src/datalogger/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -D__DEBUG=1 -DUSE_OS_TZDB=1 -D__SUPLA_SERVER=1 -DUSE_DEPRECATED_EMEV_V1 -D__TEST=1 -D__OPENSSL_TOOLS=1 -D__BCRYPT=1 -I../src -I../src/asynctask -I../src/mqtt -I$(INCMYSQL) -I../src/user -I../src/device -I../src/client -I$(SSLDIR)/include -I../src/test -O2 -g3 -Wall -fsigned-char -c -fmessage-length=0 -fstack-protector-all -D_FORTIFY_SOURCE=2 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-datalogger

clean-src-2f-datalogger:
	-$(RM) ./src/datalogger/abstract_electricity_logger.d ./src/datalogger/abstract_electricity_logger.o ./src/datalogger/abstract_electricity_logger_dao.d ./src/datalogger/abstract_electricity_logger_dao.o ./src/datalogger/current_logger.d ./src/datalogger/current_logger.o ./src/datalogger/current_logger_dao.d ./src/datalogger/current_logger_dao.o ./src/datalogger/general_purpose_measurement_logger.d ./src/datalogger/general_purpose_measurement_logger.o ./src/datalogger/general_purpose_measurement_logger_dao.d ./src/datalogger/general_purpose_measurement_logger_dao.o ./src/datalogger/general_purpose_meter_logger.d ./src/datalogger/general_purpose_meter_logger.o ./src/datalogger/general_purpose_meter_logger_dao.d ./src/datalogger/general_purpose_meter_logger_dao.o ./src/datalogger/hp_thermostat_logger.d ./src/datalogger/hp_thermostat_logger.o ./src/datalogger/hp_thermostat_logger_dao.d ./src/datalogger/hp_thermostat_logger_dao.o ./src/datalogger/impulse_logger.d ./src/datalogger/impulse_logger.o ./src/datalogger/impulse_logger_dao.d ./src/datalogger/impulse_logger_dao.o ./src/datalogger/power_active_logger.d ./src/datalogger/power_active_logger.o ./src/datalogger/power_active_logger_dao.d ./src/datalogger/power_active_logger_dao.o ./src/datalogger/temperature_logger.d ./src/datalogger/temperature_logger.o ./src/datalogger/temperature_logger_dao.d ./src/datalogger/temperature_logger_dao.o ./src/datalogger/total_energy_logger.d ./src/datalogger/total_energy_logger.o ./src/datalogger/total_energy_logger_dao.d ./src/datalogger/total_energy_logger_dao.o ./src/datalogger/voltage_aberration_logger.d ./src/datalogger/voltage_aberration_logger.o ./src/datalogger/voltage_aberration_logger_dao.d ./src/datalogger/voltage_aberration_logger_dao.o ./src/datalogger/voltage_logger.d ./src/datalogger/voltage_logger.o ./src/datalogger/voltage_logger_dao.d ./src/datalogger/voltage_logger_dao.o

.PHONY: clean-src-2f-datalogger

