################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/client/call_handler/abstract_client_srpc_call_handler.cpp \
../src/client/call_handler/abstract_execute_action.cpp \
../src/client/call_handler/abstract_register_client.cpp \
../src/client/call_handler/calcfg_request.cpp \
../src/client/call_handler/calcfg_request_b.cpp \
../src/client/call_handler/call_handler_collection.cpp \
../src/client/call_handler/channel_set_value.cpp \
../src/client/call_handler/channel_set_value_b.cpp \
../src/client/call_handler/clients_reconnect_request.cpp \
../src/client/call_handler/device_reconnect_request.cpp \
../src/client/call_handler/execute_action.cpp \
../src/client/call_handler/execute_action_with_auth.cpp \
../src/client/call_handler/get_channel_basic_cfg.cpp \
../src/client/call_handler/get_channel_config.cpp \
../src/client/call_handler/get_channel_state.cpp \
../src/client/call_handler/get_channel_value_with_auth.cpp \
../src/client/call_handler/get_device_config.cpp \
../src/client/call_handler/get_next.cpp \
../src/client/call_handler/oauth_token_request.cpp \
../src/client/call_handler/register_client.cpp \
../src/client/call_handler/register_client_a.cpp \
../src/client/call_handler/register_client_b.cpp \
../src/client/call_handler/register_client_c.cpp \
../src/client/call_handler/register_client_d.cpp \
../src/client/call_handler/register_pn_client_token.cpp \
../src/client/call_handler/set_caption.cpp \
../src/client/call_handler/set_channel_config.cpp \
../src/client/call_handler/set_channel_function.cpp \
../src/client/call_handler/set_registration_enabled.cpp \
../src/client/call_handler/set_value.cpp \
../src/client/call_handler/superuser_authorization_request.cpp \
../src/client/call_handler/superuser_authorization_result.cpp \
../src/client/call_handler/timer_arm.cpp 

CPP_DEPS += \
./src/client/call_handler/abstract_client_srpc_call_handler.d \
./src/client/call_handler/abstract_execute_action.d \
./src/client/call_handler/abstract_register_client.d \
./src/client/call_handler/calcfg_request.d \
./src/client/call_handler/calcfg_request_b.d \
./src/client/call_handler/call_handler_collection.d \
./src/client/call_handler/channel_set_value.d \
./src/client/call_handler/channel_set_value_b.d \
./src/client/call_handler/clients_reconnect_request.d \
./src/client/call_handler/device_reconnect_request.d \
./src/client/call_handler/execute_action.d \
./src/client/call_handler/execute_action_with_auth.d \
./src/client/call_handler/get_channel_basic_cfg.d \
./src/client/call_handler/get_channel_config.d \
./src/client/call_handler/get_channel_state.d \
./src/client/call_handler/get_channel_value_with_auth.d \
./src/client/call_handler/get_device_config.d \
./src/client/call_handler/get_next.d \
./src/client/call_handler/oauth_token_request.d \
./src/client/call_handler/register_client.d \
./src/client/call_handler/register_client_a.d \
./src/client/call_handler/register_client_b.d \
./src/client/call_handler/register_client_c.d \
./src/client/call_handler/register_client_d.d \
./src/client/call_handler/register_pn_client_token.d \
./src/client/call_handler/set_caption.d \
./src/client/call_handler/set_channel_config.d \
./src/client/call_handler/set_channel_function.d \
./src/client/call_handler/set_registration_enabled.d \
./src/client/call_handler/set_value.d \
./src/client/call_handler/superuser_authorization_request.d \
./src/client/call_handler/superuser_authorization_result.d \
./src/client/call_handler/timer_arm.d 

OBJS += \
./src/client/call_handler/abstract_client_srpc_call_handler.o \
./src/client/call_handler/abstract_execute_action.o \
./src/client/call_handler/abstract_register_client.o \
./src/client/call_handler/calcfg_request.o \
./src/client/call_handler/calcfg_request_b.o \
./src/client/call_handler/call_handler_collection.o \
./src/client/call_handler/channel_set_value.o \
./src/client/call_handler/channel_set_value_b.o \
./src/client/call_handler/clients_reconnect_request.o \
./src/client/call_handler/device_reconnect_request.o \
./src/client/call_handler/execute_action.o \
./src/client/call_handler/execute_action_with_auth.o \
./src/client/call_handler/get_channel_basic_cfg.o \
./src/client/call_handler/get_channel_config.o \
./src/client/call_handler/get_channel_state.o \
./src/client/call_handler/get_channel_value_with_auth.o \
./src/client/call_handler/get_device_config.o \
./src/client/call_handler/get_next.o \
./src/client/call_handler/oauth_token_request.o \
./src/client/call_handler/register_client.o \
./src/client/call_handler/register_client_a.o \
./src/client/call_handler/register_client_b.o \
./src/client/call_handler/register_client_c.o \
./src/client/call_handler/register_client_d.o \
./src/client/call_handler/register_pn_client_token.o \
./src/client/call_handler/set_caption.o \
./src/client/call_handler/set_channel_config.o \
./src/client/call_handler/set_channel_function.o \
./src/client/call_handler/set_registration_enabled.o \
./src/client/call_handler/set_value.o \
./src/client/call_handler/superuser_authorization_request.o \
./src/client/call_handler/superuser_authorization_result.o \
./src/client/call_handler/timer_arm.o 


# Each subdirectory must supply rules for building sources it contributes
src/client/call_handler/%.o: ../src/client/call_handler/%.cpp src/client/call_handler/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -D__DEBUG=1 -DUSE_OS_TZDB=1 -D__SUPLA_SERVER=1 -DUSE_DEPRECATED_EMEV_V1 -D__TEST=1 -D__OPENSSL_TOOLS=1 -D__BCRYPT=1 -I../src -I../src/asynctask -I../src/mqtt -I$(INCMYSQL) -I../src/user -I../src/device -I../src/client -I$(SSLDIR)/include -I../src/test -O2 -g3 -Wall -fsigned-char -c -fmessage-length=0 -fstack-protector-all -D_FORTIFY_SOURCE=2 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-client-2f-call_handler

clean-src-2f-client-2f-call_handler:
	-$(RM) ./src/client/call_handler/abstract_client_srpc_call_handler.d ./src/client/call_handler/abstract_client_srpc_call_handler.o ./src/client/call_handler/abstract_execute_action.d ./src/client/call_handler/abstract_execute_action.o ./src/client/call_handler/abstract_register_client.d ./src/client/call_handler/abstract_register_client.o ./src/client/call_handler/calcfg_request.d ./src/client/call_handler/calcfg_request.o ./src/client/call_handler/calcfg_request_b.d ./src/client/call_handler/calcfg_request_b.o ./src/client/call_handler/call_handler_collection.d ./src/client/call_handler/call_handler_collection.o ./src/client/call_handler/channel_set_value.d ./src/client/call_handler/channel_set_value.o ./src/client/call_handler/channel_set_value_b.d ./src/client/call_handler/channel_set_value_b.o ./src/client/call_handler/clients_reconnect_request.d ./src/client/call_handler/clients_reconnect_request.o ./src/client/call_handler/device_reconnect_request.d ./src/client/call_handler/device_reconnect_request.o ./src/client/call_handler/execute_action.d ./src/client/call_handler/execute_action.o ./src/client/call_handler/execute_action_with_auth.d ./src/client/call_handler/execute_action_with_auth.o ./src/client/call_handler/get_channel_basic_cfg.d ./src/client/call_handler/get_channel_basic_cfg.o ./src/client/call_handler/get_channel_config.d ./src/client/call_handler/get_channel_config.o ./src/client/call_handler/get_channel_state.d ./src/client/call_handler/get_channel_state.o ./src/client/call_handler/get_channel_value_with_auth.d ./src/client/call_handler/get_channel_value_with_auth.o ./src/client/call_handler/get_device_config.d ./src/client/call_handler/get_device_config.o ./src/client/call_handler/get_next.d ./src/client/call_handler/get_next.o ./src/client/call_handler/oauth_token_request.d ./src/client/call_handler/oauth_token_request.o ./src/client/call_handler/register_client.d ./src/client/call_handler/register_client.o ./src/client/call_handler/register_client_a.d ./src/client/call_handler/register_client_a.o ./src/client/call_handler/register_client_b.d ./src/client/call_handler/register_client_b.o ./src/client/call_handler/register_client_c.d ./src/client/call_handler/register_client_c.o ./src/client/call_handler/register_client_d.d ./src/client/call_handler/register_client_d.o ./src/client/call_handler/register_pn_client_token.d ./src/client/call_handler/register_pn_client_token.o ./src/client/call_handler/set_caption.d ./src/client/call_handler/set_caption.o ./src/client/call_handler/set_channel_config.d ./src/client/call_handler/set_channel_config.o ./src/client/call_handler/set_channel_function.d ./src/client/call_handler/set_channel_function.o ./src/client/call_handler/set_registration_enabled.d ./src/client/call_handler/set_registration_enabled.o ./src/client/call_handler/set_value.d ./src/client/call_handler/set_value.o ./src/client/call_handler/superuser_authorization_request.d ./src/client/call_handler/superuser_authorization_request.o ./src/client/call_handler/superuser_authorization_result.d ./src/client/call_handler/superuser_authorization_result.o ./src/client/call_handler/timer_arm.d ./src/client/call_handler/timer_arm.o

.PHONY: clean-src-2f-client-2f-call_handler

