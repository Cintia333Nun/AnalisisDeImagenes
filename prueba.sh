clear
g++ -c main.cpp -o main.o
g++ -c procesamientoimagenes.cpp -o procesamientoimagenes.o
g++ procesamientoimagenes.o main.o
./a.out 
