#include <iostream>
#include"head.h"

#include <stdlib.h>
#include<stdio.h>

using namespace std;

void sort(int arr[], bool n)
{
int i, j;
if (n == 0)
{

for (i = 0; i < 10; i++)
{


for (j = 0; j < 9; j++)
{
if (arr[j] > arr[j + 1])
swap(arr[j], arr[j + 1]);
}
}
}
else
{
for (i = 0; i < 10; i++)
{


for (j = 0; j < 9; j++)
{
if (arr[j] < arr[j + 1])
swap(arr[j], arr[j + 1]);
}
}
}
}
void findHighest(int array[], int position)
{
if (array[0] < array[9])
{

int pos = 10 - position;
cout << array[pos];
}
else
{
cout << array[position];
}


}
void print(int array[])
{

for (int i = 0; i < 10; i++)
cout << array[i] << " ";
cout << endl;
}


