CC := gcc
CFLAGS := -ggdb -std=c++17 -Wall -Werror -Wextra -lstdc++
C_LIBS :=
TST_LIBS := -lgtest -lgmock -pthread

all: rebuild

rebuild: clean build

build:
	qmake -o QMakefile && make -f QMakefile

install: build
	mv maze.app ../build

uninstall:
	rm -rf ../build/maze.app

gcov_test: s21_test.cc
	$(CC) $(CFLAGS) --coverage s21_test.cc model/cave/model_cave.cc \
	model/helpers/parser.cc model/maze/model_maze.cc model/helpers/matrix.cc $(TST_LIBS) -o gcov_test

gcov_test.gcda: gcov_test
	chmod +x *
	./gcov_test

gcov_test.info: gcov_test gcov_test.gcda
	lcov -t "gcov_test" -o gcov_test.info --no-external -c -d .

gcov_report: clean gcov_test.info
	genhtml -o report/ gcov_test.info
	open report/index.html

dist: install
	cd ../build && tar -zcf maze.tar.gz maze.app

dvi:
	./texi2dvi.sh

clean: clean_o clean_build clean_test
	rm -rf QMakefile

clean_test:
	rm -rf report/ gcov_test exe *.gcda *.gcno *.info test.out *.dSYM

clean_o:
	rm -rf *.o

clean_build:
	rm -rf maze.app
	rm -rf ../build/maze.app
	rm -rf *.a
	rm -rf gcov_tests/*.a
	rm -rf docs/*.aux
	rm -rf docs/*.dvi
	rm -rf docs/*.log
	rm -rf docs/*.out
	rm -rf docs/*.pdf
	rm -rf moc_*
	rm -rf .qmake.stash
	rm -rf s21_test
	rm -rf ui_*.h

tests: clean
	$(CC) s21_test.cc model/cave/model_cave.cc \
    model/helpers/parser.cc model/maze/model_maze.cc \
    model/helpers/matrix.cc -I../ -o s21_test  $(TST_LIBS) $(CFLAGS)
	./s21_test

check:
	cp ../materials/linters/.clang-format ./
	clang-format -n ./*.cc ./*/*.cc ./*/*.h ./*/*/*.cc ./*/*/*.h
#./*/*/*/*.c ./*/*/*/*.h
