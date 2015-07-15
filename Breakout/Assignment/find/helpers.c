/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{   
    int first = 0, last = n-1;
    int i = 0;
    while ( first <= last)
    {
        i = (first + last)/2;
        if (value == values[i])
        {
            return true;
        }
        else if (value > values[i])
        {
            first = i + 1;
        }
        else if (value < values[i])
        {
            last = i - 1;
        }
        
    }
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    int temp = 0;
    
    for ( int i = 1; i < n; i++)
    {
        for (int j = 0; j < n - 1; j++)
        {
            if (values[j] > values[j+1])
            {
                temp = values[j];
                values[j] = values[j+1];
                values[j+1] = temp;
            }
        }
    }
    
    return;
}
