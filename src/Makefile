GCC = g++ -Wall -Werror -Wextra -g
SOURCE = s21_*.cpp

all: clean test

clean:
	rm -rf *.o *.a *.so *.cfg *a.out *.dSYM test

test:
	clear
	@$(GCC) s21_matrix_oop.cpp -o test
	@./test

git:
	make clean
	git add Makefile s21_matrix_oop.cpp s21_matrix_oop.h
	git commit -m "start"
	git push origin tysaneno

check:
	cppcheck --enable=all --suppress=missingIncludeSystem --inconclusive --check-config $(SOURCE) *.h
	cp ../materials/linters/.clang-format .clang-format
#    clang-format -n src/$(SOURCE) *.h
	rm -rf .clang-format

