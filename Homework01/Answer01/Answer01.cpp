// Homework01.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <algorithm>


//
// BubbleSort
//
void BubbleSort(std::vector<int>& list)
{
    int arraySize = list.size();

    // loop through all numbers 
    for (int i = 0; i < arraySize - 1; i++)
    {
        bool swapped = false;

        // loop through numbers falling ahead 
        for (int j = 0; j < arraySize - 1 - i; j++)
        {
            // check if next number is lesser than current no
            //   swap the numbers. 
            //  (Bubble up the highest number)
            if (list[j] > list[j + 1])
            {
                std::swap(list[j], list[j + 1]);
                swapped = true;
            }
        }

        // if no number was swapped that means 
        //   array is sorted now, break the loop. 
        if (!swapped) {
            break;
        }
    }
}


//
// InsertionSort
//
void InsertionSort(std::vector<int>& list)
{
    int arraySize = list.size();

    // loop through all numbers 
    for (int i = 1; i < arraySize; i++)
    {
        // select a value to be inserted. 
        int valueToInsert = list[i];

        // select the hole position where number is to be inserted 
        int holePosition = i;

        // check if previous no. is larger than value to be inserted 
        while (holePosition > 0 && list[holePosition - 1] > valueToInsert)
        {
            list[holePosition] = list[holePosition - 1];
            holePosition--;
        }

        if (holePosition != i)
        {
            // insert the number at hole position 
            list[holePosition] = valueToInsert;
        }
    }
}

void Sort(void(*funcSort)(std::vector<int>&), std::vector<int>& list)
{
    funcSort(list);
}

int _tmain(int argc, _TCHAR* argv[])
{
    int list[] = { 1, 8, 4, 6, 0, 3, 5, 2, 7, 9 };

    std::vector<int> a(list, list + _countof(list));
    Sort(BubbleSort, a);

    std::vector<int> b(list, list + _countof(list));
    Sort(InsertionSort, b);

	return 0;
}

