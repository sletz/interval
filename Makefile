ANALYSIS="-*,cert-*,clang-analyzer-*,modernize-*,performance-*,cppcoreguidelines-*,google-*,bugprone-*,misc-*,-google-runtime-references,-cppcoreguidelines-avoid-magic-numbers"


testinterval : *.cpp *.hh
	${CXX} -Wall -Wshadow -O1 -g --std=c++11 *.cpp -o testinterval


test: testinterval
	./testinterval

help:
	@echo "make [testinterval] : compile testinterval"
	@echo "make test           : compile and run testdigraph"
	@echo "make format         : compile and run testdigraph"
	@echo "make analyze        : clang-tidy code analysis"

format :
	clang-format -i -style=file *.cpp *.hh

clean :
	rm -f testinterval *.orig *.plist

analyze :
	clang-tidy-8 --extra-arg="--std=c++11" -checks=${ANALYSIS} -header-filter=.* *.cpp

fix :
	clang-tidy-8 --extra-arg="--std=c++11" -checks=${ANALYSIS} -header-filter=.* *.cpp -fix
