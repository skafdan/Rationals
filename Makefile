asgn:
		@g++ -g -o calc *.cpp
clean:
		@rm -rf calc
valgrind:
		@valgrind --leak-check=full ./calc