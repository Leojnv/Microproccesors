#include "conversion.h"

float rt_values[RT_TABLE_SIZE] = { 182.6, 205.5, 231.9, 262.4, 297.7,  338.7,  386.6,  442.6,  508.3,  585.7,
								   677.3,   786, 915.4,  1070,  1256,   1481,   1753,   2084,   2490,   2989,
								    3605,  4372,  5330,  6535,  8059,  10000,  12488,  15698,  19872,  25339,
								   32554, 42157, 55046, 72500, 96358, 129287, 175200, 239900, 332094 };

float rt_temp_values[RT_TABLE_SIZE] = { 150, 145, 140, 135, 130, 125, 120, 115, 110, 105,
										100,  95,  90,  85,  80,  75,  70,  65,  60,  55,
										 50,  45,  40,  35,  30,  25,  20,  15,  10,   5,
										  0,  -5, -10, -15, -20, -25, -30, -35, -40 };

float calculateVin(int n) {
    return ( n / (float)(2<<11) ) * 3.3;
};

float calculateRt(float Vin) {
    return ( 10000 * 3.3 ) / Vin - 10000;
};

float calculateTemp(float Rt) {

    int index = search_item(rt_values, Rt);

    if (index != -1)
        return rt_temp_values[index];
    else
    {
        int idx = findNeighbours(Rt);
        float x_1, x_2, y_1, y_2;
        x_1 = rt_values[idx-1];
        y_1 = rt_temp_values[idx-1];
        x_2 = rt_values[idx];
        y_2 = rt_temp_values[idx];

        return ( (Rt-x_1) / (x_2-x_1) ) * (y_2-y_1) + y_1;
    }
};
int search_item(float arr[], float Rt){
	for (int i = 0;  i < RT_TABLE_SIZE; i++) {
		if (arr[i] == Rt)
			return i;
	}
	return -1;
}
int findNeighbours(float Rt) {
    int idx = 0;
    for (int i = 0; i < RT_TABLE_SIZE; i++) {
        if (Rt < rt_values[i]) {
        	idx = i;
            break;
        }
    }
    return idx;
};

float convert_C_F(float C){
    return C * 9/5 + 32;
};
