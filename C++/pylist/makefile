# This is a simple makefile for C++ projects.
TARGET = main

# 目录设置
SRC_DIR = src
BUILD_DIR = build

# 查找所有 .cpp 文件并转换为 .o 文件存入 build/
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

# 编译器和编译选项
CXX = g++
CXXFLAGS = -Wall -g

# 生成最终可执行文件
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# 生成 .o 目标文件，确保 build/ 目录存在
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 创建 build 目录（仅当不存在时）
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# 运行程序
.PHONY: run
run: $(TARGET)
	./$(TARGET)

# 清理
.PHONY: clean
clean:
	rm -rf $(TARGET) $(BUILD_DIR)