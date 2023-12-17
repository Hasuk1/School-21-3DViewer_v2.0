CC := g++
CPPFLAGS := -lgtest -lgtest_main -std=c++17 -pthread
CHECKFLAGS := -Wall -Werror -Wextra
SRC := model/*.cc tests/*.cc
OS := $(shell uname)
ifeq ($(OS), Darwin)
	OPEN_CMD := open
else
	OPEN_CMD := xdg-open
endif
TARGET := SmartCalc_v2.0

all: tests gcov_report style install 

install: uninstall
	@echo "===>    Installation has started     <==="
	@mkdir -p ../build
	@cd ./view && qmake && make && make clean && rm -rf Makefile  && mv $(TARGET).app ../../build
	@cp -R ../build/$(TARGET).app ~/Desktop/$(TARGET).app
	@clear
	@echo "===> SmartCalc application installed <==="
	@echo "Do you want to open application? [yes/no]"
	@read -r ANSWER; \
	if [ "$ANSWER" != "yes" ] && [ "$$ANSWER" != "y" ]; then \
  	exit 0; \
	fi
	@make open

open:
	@echo "Opening application..."	
	@$(OPEN_CMD) ../build/$(TARGET).app

uninstall:
	@rm -rf ./../build ./out
	@rm -rf ~/Desktop/$(TARGET).app 

clean:
	@rm -f test *.gcda *.gcno *.info *.filtered gcov_report ./../*.log
	@rm -rf ./build-view-* ./report ../.vscode ../dist

tests: clean
	@$(CC) $(CHECKFLAGS) $(SRC) -o test $(CPPFLAGS) && ./test

dvi:
	@$(OPEN_CMD) ../misc/info.html

dist:
	@mkdir -p ../dist
	@cp -R ../build/$(TARGET).app ../dist && cp ../misc/info.html ../dist
	@cd ../dist && tar cvzf $(TARGET).tgz *
	@cd ../dist && rm -rf $(TARGET).app info.html

gcov_report: clean
	@$(CC) --coverage $(SRC) ${CPPFLAGS} ${CHECKFLAGS} ${LIBS} -o gcov_report
	@./gcov_report
	@lcov -c -d . -o coverage.info --rc lcov_branch_coverage=1 --ignore-errors mismatch -t "all_check"
	@lcov --rc lcov_branch_coverage=1 -e coverage.info 'model/*.cc' 'tests/test.cc' -o coverage.info.filtered
	@genhtml coverage.info.filtered --output-directory report
	@$(OPEN_CMD) report/index.html;

clang:
	@echo "===> Formatting your code for Google Style <==="
	@clang-format -i -style=GOOGLE $(SRC) model/*.h controller/*.h view/*.cc view/*.h view/*.ui

style:
	@echo "===> Checking your code for Google Style <==="
	@clang-format -n -style=GOOGLE $(SRC) model/*.h controller/*.h view/*.cc view/*.h view/*.ui

leaks: clean tests
	@leaks -atExit -- ./test

valgrind: clean tests
	@CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./test

docker:
	@docker build . -t smart_calc:2.0 -f ./Dockerfile
	@docker run --rm -it --name set_test smart_calc:2.0

.PHONY: install open uninstall clean tests dvi dist gcov_report clang style
