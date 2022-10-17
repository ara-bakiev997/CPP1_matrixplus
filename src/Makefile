GCC = g++ -g -Wall -Werror -Wextra
SOURCE = s21_*.cc

all: clean test

clean:
	rm -rf *.o *.a *.so *.cfg *a.out *.dSYM test *.txt

test:
	clear
	@$(GCC) s21_matrix_oop.cc -o test
	@./test

git:
	make clean
	git add Makefile s21_matrix_oop.cc s21_matrix_oop.h
	git commit -m "transpose"
	git push origin tysaneno

check:
	cppcheck --enable=all --suppress=missingIncludeSystem --inconclusive --check-config $(SOURCE) *.h
	cp ../materials/linters/.clang-format .clang-format
	#clang-format -style=file exp.cc # как должно быть
	clang-format -n s21_matrix_oop.cc s21_matrix_oop.h
	rm -rf .clang-format
ifeq ($(OS), Darwin)
	leaks --atExit -- test
else
	CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=RESULT_VALGRIND.txt ./test
endif


