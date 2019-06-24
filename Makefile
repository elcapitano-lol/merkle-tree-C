# This is a Makefile to compile and link the test app successfuly

# Define macros for general compiler and compiler flags i.e. path to header files
CC = gcc
CFLAGS = -g -I$(IDIR)

# Define macros for folder location
IDIR = ./include
ODIR = ./obj
SDIR = ./src

# Define macro for included libraries e.g. crypto
LIBS = -lm -lcrypto

# Define macros for the dependencies
_DEPS = mtree.h utils.h sha256.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

# Define macro for the object files
_OBJ = mtree.o utils.o sha256.o test_app.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

# Define a rule for compiling the object files 
# gcc -c -o <objects> <sources> <flags> <libs>
$(ODIR)/%.o : $(SDIR)/%.c $(DEPS)
	$(info Compiling $@...)
	@$(CC) -c -o $@ $< $(CFLAGS) $(LIBS)

# Define a rule for compiling the test_app executable using all object files
test_app: $(OBJ)
	$(info Compiling $@...)
	@$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
	
# Define a rule for cleaning all object files and executables
.PHONY: clean
clean:
	$(info Cleaning up...)
	@rm -f $(ODIR)/*.o test_app
	$(info Clean. Exiting...)

# Define a rule for make all, which should be to execute the rule of test_app
.PHONY: all
all: test_app
	$(info Exiting...)

