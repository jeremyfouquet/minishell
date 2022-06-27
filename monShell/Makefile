C=gcc
EXEC=monshell
LDFLAGS=
CXXFLAGS= -Wall
SRC= monshell.c cn-decouper.c cl-monsystem.c moncd.c monexec.c redirection.c monpipe.c pipe.c autocompletion.c

OBJ=$(SRC:.c=.o)

all: $(EXEC)

$(EXEC): $(OBJ)
	$(C) -o $@ $^ $(LDFLAGS)

monshell.o: monshell.c sys.h
	$(C) -o $@ -c $< $(CXXFLAGS)

cn-decouper.o: cn-decouper.c sys.h
	$(C) -o $@ -c $< $(CXXFLAGS)

cl-system.o: cl-system.c sys.h
	$(C) -o $@ -c $< $(CXXFLAGS)

moncd.o: moncd.c sys.h
	$(C) -o $@ -c $< $(CXXFLAGS)

monexec.o: monexec.c sys.h
	$(C) -o $@ -c $< $(CXXFLAGS)

redirection.o: redirection.c sys.h
	$(C) -o $@ -c $< $(CXXFLAGS)

monpipe.o: monpipe.c sys.h
	$(C) -o $@ -c $< $(CXXFLAGS)

pipe.o: pipe.c sys.h
	$(C) -o $@ -c $< $(CXXFLAGS)

autocompletion.o: autocompletion.c sys.h
	$(C) -o $@ -c $< $(CXXFLAGS)

# pour forcer clean/cleanall même s'il existe un fichier de même nom
.PHONY: clean cleanall

clean:
	rm -rf *.o

cleanall: clean
	rm -rf $(EXEC)
