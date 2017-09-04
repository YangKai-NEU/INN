#! /bin/bash

cd /home/yangkai/INN/code

g++ Main.cpp -o main


dataFile="/home/yangkai/INN/data/XY_RSS_5AP_2_4.txt"
EP_size=5
graphPath="/home/yangkai/INN/data/graph.txt"
AIM_SIze=5
./main $dataFile $EP_size $graphPath $AIM_SIze
