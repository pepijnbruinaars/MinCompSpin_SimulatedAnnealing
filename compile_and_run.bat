g++ -std=c++11 -O3 -Wall ./src/*.cpp -o ./bin/saa.exe
cd bin
saa.exe 20 -i my_data_n20_N1000 -p my_comms_n20 --max 26354 --stop 1736
pause