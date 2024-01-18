CC := g++
CPPFLAGS := -lgtest -lgtest_main -std=c++17 -pthread
CHECKFLAGS := -Wall -Werror -Wextra
LIBS := -fprofile-arcs -ftest-coverage
SRC := model/parser/file_parser.cc model/transform/transform.cc tests/tests.cc
OS := $(shell uname)
ifeq ($(OS), Darwin)
	OPEN_CMD := open
else
	OPEN_CMD := xdg-open
endif
TARGET := 3DViewer_v2.0
PWD := $(shell pwd)

all: tests gcov_report style install 

install: uninstall
	@echo "===>    Installation has started     <==="
	@mkdir -p ../build
	@cd ./view && qmake && make && make clean && rm -rf Makefile  && mv $(TARGET).app ../../build
	@cp -R ../build/$(TARGET).app ~/Desktop/$(TARGET).app
	@clear
	@echo "===> 3DViewer_v2.0 application installed <==="
	@echo "Do you want to open application? [yes/no]"
	@read -r ANSWER; \
	if [ "$ANSWER" == "yes" ] || [ "$$ANSWER" == "y" ]; then \
  	make open; \
	fi

open:
	@echo "Opening application..."	
	@$(OPEN_CMD) ~/Desktop/$(TARGET).app

uninstall:
	@rm -rf ./../build
	@rm -rf ~/Desktop/$(TARGET).app 

clean:
	@rm -f test *.gcda *.gcno *.info *.filtered gcov_report ./../*.log ../.DS_Store
	@rm -rf ./build-view-* ./report ../.vscode ../dist view/.qmake.stash

tests: clean
	@$(CC) $(CHECKFLAGS) $(SRC) -o test $(CPPFLAGS) && ./test

dvi:
	@$(OPEN_CMD) ../dvi/dvi.html

dist:
	@mkdir -p ../dist
	@cp -R ../build/$(TARGET).app ../dist && cp ../dvi/dvi.html ../dist
	@cd ../dist && tar cvzf $(TARGET).tgz *
	@cd ../dist && rm -rf $(TARGET).app dvi.html

gcov_report: clean
	@$(CC) --coverage $(SRC) ${CPPFLAGS} ${CHECKFLAGS} ${LIBS} -o gcov_report
	@./gcov_report
	@lcov -c -d . -o coverage.info --rc lcov_branch_coverage=1 --ignore-errors mismatch -t "all_check"
	@lcov --rc lcov_branch_coverage=1 -e coverage.info 'model/*.cc' -o coverage.info.filtered
	@genhtml coverage.info.filtered --output-directory report
	@$(OPEN_CMD) report/index.html;

clang:
	@echo "===> Formatting your code for Google Style <==="
	@clang-format -i -style=GOOGLE model/parser/* model/transform/* model/*.h view/*.cc view/*.h view/*.ui controller/*.h tests/*.cc

style:
	@echo "===> Checking your code for Google Style <==="
	@clang-format -n -style=GOOGLE model/parser/* model/transform/* model/*.h view/*.cc view/*.h view/*.ui controller/*.h tests/*.cc

leaks:
	@if [ "$(OS)" = "Darwin" ]; then \
		make clean && make tests; \
		leaks -atExit -- ./test; \
	else \
		echo "===> Use "make valgrind" to check for leaks <==="; \
	fi

valgrind:
	@if [ "$(OS)" = "Darwin" ]; then \
		docker build . -t 3d_viewer:2.0 -f ./Dockerfile; \
		docker run --rm -it --entrypoint "" --name 3d_viewer_test 3d_viewer:2.0 make valgrind; \
	elif [ "$(OS)" = "Linux" ]; then \
		make clean && make tests; \
		CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all -s --track-origins=yes --verbose ./test; \
	fi
	
docker:
	@docker build . -t 3d_viewer:2.0 -f ./Dockerfile
	@docker run --rm -it --name 3d_viewer_test -v $(PWD):/home/3d_viewer 3d_viewer:2.0

download_obj:
	@git clone https://github.com/Hasuk1/obj_files.git
	@mv obj_files ~/Downloads

.PHONY: install open uninstall clean tests dvi dist gcov_report clang style
