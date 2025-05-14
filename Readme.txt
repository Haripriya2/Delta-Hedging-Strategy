The following project comprises of the following header files:
1. NAIR_HARIPRIYA_Underlying.h
2. NAIR_HARIPRIYA_Option.h
3. NAIR_HARIPRIYA_Hedging.h

and their corresponding implementations:
1. NAIR_HARIPRIYA_Underlying.cpp
2. NAIR_HARIPRIYA_Option.cpp
3. NAIR_HARIPRIYA_Hedging.cpp

The main program would be : NAIR_HARIPRIYA_main.cpp and it comprises of task 1 and task 2 implementation using the above components.

To compile the code, please do the following pre-checks:
1. Have the op_GOOG.csv, sec_GOOG.csv and interest.csv files in the same folder as the code. I have already zipped it in.
2. The boost library must be placed within a folder boost_1_67_0. This would be the downloaded format of folders. Otherwise, please redirect
   the path of it to location of boost library on your system.

To compile the code:
1. Please type the following on the command line terminal:
g++ NAIR_HARIPRIYA_Underlying.cpp NAIR_HARIPRIYA_Option.cpp NAIR_HARIPRIYA_Hedging.cpp NAIR_HARIPRIYA_main.cpp -lboost_date_time
./a.out
