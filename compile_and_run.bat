g++ -std=c++11 -O3 -Wall ./src/*.cpp -o ./bin/saa.exe
cd bin
saa.exe 100 -i my_data_n100_N2000 -p my_comms_n100 --max 26354 --stop 1736
pause