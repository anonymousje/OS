#include <iostream>
#include "head.h"

using namespace std;


int main()
{
int arr[12];
for (int i = 0; i < 12; i++)
{
cin >> arr[i];
}

print(arr);
sort(arr, arr[10]);
print(arr);
if(arr[11] < 11)
{
cout << "Highest: " << endl;
findHighest(arr, arr[11]);
}
else 
{
  cout << "Index doesnt exist";
  }


system("PAUSE");

return 0;
}
