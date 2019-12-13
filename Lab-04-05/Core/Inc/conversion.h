#include <math.h>
#include <stdbool.h>

// RT -10K RT vs Temperature Table

#define RT_TABLE_SIZE  39			// Number of elements in RT s Temp Table


float calculateVin(int n);
float calculateRt(float Vin);
float calculateTemp(float Rt);
int search_item(float arr[], float Rt);
int findNeighbours(float Rt);
float convert_C_F(float C);
