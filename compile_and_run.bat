g++ -std=c++11 -O3 -Wall ./src/*.cpp -o ./bin/saa.exe
cd bin
saa.exe 100 my_data_n100_N2000 -l my_comms_n100
pause