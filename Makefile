objects = Grade.o Course.o GradeManager.o test.o

all: $(objects)
	g++ -o GradeManager $(objects)

Grade.o: Grade.cc
	g++ -c Grade.cc

Course.o: Course.cc
	g++ -c Course.cc

GradeManager.o: GradeManager.cc
	g++ -c GradeManager.cc

test.o: test.cc
	g++ -c test.cc

clean:
	rm GradeManager $(objects)