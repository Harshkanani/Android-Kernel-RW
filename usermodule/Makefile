CC := /home/harsh/project/android_kernel/toolchain/gcc-arm-10.3-2021.07-x86_64-aarch64-none-linux-gnu/bin/aarch64-none-linux-gnu-g++
CFLAGS := -g
TARGET := main
SRCS := $(wildcard *.cpp)
OBJS := $(patsubst %cpp,%o,$(SRCS))
all:$(TARGET)
%.o:%.cpp
	$(CC) $(CFLAGS) -static -c $<
$(TARGET):$(OBJS)
	$(CC) $(CFLAGS) -static -o $@ $^
clean:
	rm -rf $(TARGET) *.o