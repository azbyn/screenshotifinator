CXX := clang++
SRC_DIR := .
BUILD_DIR := build
TARGET := screenshotifinator

run: main
	./$(TARGET)
main:
	$(CXX) main.cpp -o  $(TARGET) -lX11
