################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/accept_loop.cpp \
../src/active_period.cpp \
../src/caller.cpp \
../src/dcpair.cpp \
../src/metrics.cpp \
../src/objcontainer.cpp \
../src/objcontaineritem.cpp \
../src/serverstatus.cpp \
../src/supla-server.cpp 

C_SRCS += \
../src/cfg.c \
../src/eh.c \
../src/ini.c \
../src/lck.c \
../src/log.c \
../src/proto.c \
../src/safearray.c \
../src/sthread.c \
../src/supla-socket.c \
../src/svrcfg.c \
../src/tools.c 

CPP_DEPS += \
./src/accept_loop.d \
./src/active_period.d \
./src/caller.d \
./src/dcpair.d \
./src/metrics.d \
./src/objcontainer.d \
./src/objcontaineritem.d \
./src/serverstatus.d \
./src/supla-server.d 

C_DEPS += \
./src/cfg.d \
./src/eh.d \
./src/ini.d \
./src/lck.d \
./src/log.d \
./src/proto.d \
./src/safearray.d \
./src/sthread.d \
./src/supla-socket.d \
./src/svrcfg.d \
./src/tools.d 

OBJS += \
./src/accept_loop.o \
./src/active_period.o \
./src/caller.o \
./src/cfg.o \
./src/dcpair.o \
./src/eh.o \
./src/ini.o \
./src/lck.o \
./src/log.o \
./src/metrics.o \
./src/objcontainer.o \
./src/objcontaineritem.o \
./src/proto.o \
./src/safearray.o \
./src/serverstatus.o \
./src/sthread.o \
./src/supla-server.o \
./src/supla-socket.o \
./src/svrcfg.o \
./src/tools.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	$(CXX) -D__DEBUG=1 -DUSE_OS_TZDB=1 -D__SUPLA_SERVER=1 -DSPROTO_WITHOUT_OUT_BUFFER -DSRPC_WITHOUT_OUT_QUEUE -DUSE_DEPRECATED_EMEV_V1 -D__OPENSSL_TOOLS=1 -D__SSOCKET_WRITE_TO_FILE=$(SSOCKET_WRITE_TO_FILE) -D__BCRYPT=1 -I$(INCMYSQL) -I../src/mqtt -I../src/device -I../src/user -I../src -I$(SSLDIR)/include -I../src/client -O2 -g3 -Wall -fsigned-char -c -fmessage-length=0 -fstack-protector-all -D_FORTIFY_SOURCE=2 -std=c++11 -fPIE -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	$(CC) -D__OPENSSL_TOOLS=1 -DUSE_OS_TZDB=1 -D__SUPLA_SERVER=1 -DSPROTO_WITHOUT_OUT_BUFFER -DSRPC_WITHOUT_OUT_QUEUE -DUSE_DEPRECATED_EMEV_V1 -D__DEBUG=1 -D__SSOCKET_WRITE_TO_FILE=$(SSOCKET_WRITE_TO_FILE) -D__BCRYPT=1 -I$(SSLDIR)/include -I../src/mqtt -I../src/user -I../src/device -I../src/client -I../src -O2 -g3 -Wall -fsigned-char -c -fmessage-length=0 -fstack-protector-all  -D_FORTIFY_SOURCE=2 -fPIE -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/accept_loop.d ./src/accept_loop.o ./src/active_period.d ./src/active_period.o ./src/caller.d ./src/caller.o ./src/cfg.d ./src/cfg.o ./src/dcpair.d ./src/dcpair.o ./src/eh.d ./src/eh.o ./src/ini.d ./src/ini.o ./src/lck.d ./src/lck.o ./src/log.d ./src/log.o ./src/metrics.d ./src/metrics.o ./src/objcontainer.d ./src/objcontainer.o ./src/objcontaineritem.d ./src/objcontaineritem.o ./src/proto.d ./src/proto.o ./src/safearray.d ./src/safearray.o ./src/serverstatus.d ./src/serverstatus.o ./src/sthread.d ./src/sthread.o ./src/supla-server.d ./src/supla-server.o ./src/supla-socket.d ./src/supla-socket.o ./src/svrcfg.d ./src/svrcfg.o ./src/tools.d ./src/tools.o

.PHONY: clean-src

