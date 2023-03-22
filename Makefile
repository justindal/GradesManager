objects = Grade.o Course.o GradeManager.o main.o

all: $(objects)
	g++ -o GradeManager $(objects)

Grade.o: Grade.cc
	g++ -c Grade.cc

Course.o: Course.cc
	g++ -c Course.cc

GradeManager.o: GradeManager.cc
	g++ -c GradeManager.cc

main.o: main.cc
	g++ -c main.cc

clean:
	rm GradeManager $(objects)