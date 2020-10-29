CXX      = g++														# Name of compiler
CXX_FILE = $(wildcard *.cpp)										# File to compile. If you have multiple, will result in syntax error on input to compiler.
TARGET   = $(patsubst %.cpp,%,$(CXX_FILE))							# Take the filename minus cpp
CXXFLAGS = -g -Wall -Werror -pedantic-errors -fmessage-length=0		# -g: include debug info -Wall: enforce standards \
																	  -Werror: turn errors into warnings \
																	  -pedantic-errors: enforce more stringent standards \
																	  -fmessage-length=0: line length before new line. \
																	                      Makes errors go on separate lines.
																	                      
# Lines here need a TAB Character
# Some optional info stuff to print out as a string.
# For cleaning, just remove forcefully that target and exe crap, incase you build in cygwin (linux emulator in windows)
all:
	$(info CXX_FILE is $(CXX_FILE))
	$(info TARGET is $(TARGET))
	$(CXX) $(CXXFLAGS) $(CXX_FILE) -o $(TARGET)		#
clean:
	rm -f $(TARGET) $(TARGET).exe
	
# Makefile precedence:
# - makefile > Makefile
# - "make -f makefile": Specified file takes priority

# Note: Sometimes you might need to "make clean" or even "make clean && make"