objects = Grade.o Course.o

all: $(objects)
	g++ -o GradeManager $(objects)

Grade.o: Grade.cc Grade.h
	g++ -c Grade.cc

Course.o: Course.cc Course.h
	g++ -c Course.cc

clean:
	rm GradeManager $(objects)