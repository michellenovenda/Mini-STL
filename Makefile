all:
	g++ I2P2_main.cpp src/*.cpp -DTEST_LIST -DDOUBLE -std=c++11 -g -fsanitize=address,undefined -Wall -Wextra
