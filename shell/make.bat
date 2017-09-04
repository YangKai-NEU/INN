echo program is running...
cd ../
cd code
g++ -o3 Main.cpp -o main

@echo off

if "%1"=="" goto end3
if "%1"=="D2" goto end1
if "%1"=="D3" goto end2

echo.

echo effect of query number_5:
for %%i in (100,500,1000,5000,10000) do main ../data/D1/XY_RSS_5AP_2_4.txt 5 ../data/D1/graph.txt 5 99.0 %%i 0.5

echo effect of query number_14:
for %%i in (100,500,1000,5000,10000) do main ../data/D1/XY_RSS_14AP_2_4.txt 14 ../data/D1/graph.txt 5 99.0 %%i 0.5

echo effect of query number_57:
for %%i in (100,500,1000,5000,10000) do main ../data/D1/XY_RSS_57AP_2_4.txt 57 ../data/D1/graph.txt 5 99.0 %%i 0.5

echo.
echo effect of object number_5:
for %%i in (1,2,3,4,5,6,7,8,9,10,11,12) do main ../data/D1/XY_RSS_5AP_2_4.txt 5 ../data/D1/graph.txt %%i 99.0 10000 0.5

echo effect of object number_14:
for %%i in (1,2,3,4,5,6,7,8,9,10,11,12) do main ../data/D1/XY_RSS_14AP_2_4.txt 14 ../data/D1/graph.txt %%i 99.0 10000 0.5

echo effect of object number_57:
for %%i in (1,2,3,4,5,6,7,8,9,10,11,12) do main ../data/D1/XY_RSS_57AP_2_4.txt 57 ../data/D1/graph.txt %%i 99.0 10000 0.5

:end1

if "%1"=="D1" goto end3

echo.
echo effect of query number:
for %%i in (100,500,1000,2000,5000,10000,20000) do main ../data/D2/omni_16dbm_5ap.txt 5 ../data/D2/graph.txt 5 95.0 %%i 0

echo.
echo effect of object number:
for %%i in (1,2,3,4,5,6,7,8,9,10,11,12) do main ../data/D2/omni_16dbm_5ap.txt 5 ../data/D2/graph.txt %%i 95.0 10000 0

:end2

if "%1"=="D2" goto end3

echo.
echo effect of query number:
for %%i in (100,500,1000,5000,10000) do main ../data/D3/Task_2_training_data.txt 99 ../data/D3/graph.txt 5 99.0 %%i 0

echo.
echo effect of object number:
for %%i in (1,2,3,4,5,6,7,8,9,10,11,12) do main ../data/D3/Task_2_training_data.txt 99 ../data/D3/graph.txt %%i 99.0 10000 0

:end3

del main.exe
cd ../
cd shell