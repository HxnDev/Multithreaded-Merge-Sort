#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <pthread.h>
#include <sys/wait.h>
#include <algorithm>
using namespace std;

pthread_t tid1, tid2, tid3, tid4, tid5;
int *arr, *res;

void* sortQuarter1(void* arg) 
{

    int n = *((int *)arg); 

    cout << "\nQuarter number 1 = ";

    for (int i = 0; i < n/4; i++)
        cout << arr[i] << " ";
    cout<<endl;

    for (int i = 0; i < n/4; i++) 
    {
        for (int j = 0; j < n/4; j++) 
        {
            if (arr[i] < arr[j])
                swap(arr[i], arr[j]);
        }
    }
    
    cout << "\nQuarter 1 sorted : ";

    for (int i = 0; i < n/4; i++)
        cout << arr[i] << " ";
    
    cout << endl;
    
    return NULL;
}

void* sortQuarter2(void* arg) 
{

    int n = *((int*)arg); 

    cout << "\nQuarter number 2 = ";

    for (int i = n/4; i < n/2; i++)
        cout << arr[i] << " ";
    cout<<endl;

    for (int i = n/4; i < n/2; i++) 
    {
        for (int j = n/4; j < n/2; j++) 
        {
            if (arr[i] < arr[j])
                swap(arr[i], arr[j]);
        }
    }

    cout << "\nQuarter 2 sorted : ";

    for (int i = n/4; i < n/2; i++)
        cout << arr[i] << " ";
    
    cout << endl;

    return NULL;
}

void* sortQuarter3(void* arg) 
{

    int n = *((int*)arg); 

    cout << "\nQuarter number 3 = ";

    for (int i = n/2; i < n-n/4; i++)
        cout << arr[i] << " ";

    cout<<endl;
    for (int i = n/2; i < n-n/4; i++) 
    {
        for (int j = n/2; j < n-n/4; j++) 
        {
            if (arr[i] < arr[j])
                swap(arr[i], arr[j]);
        }
    }
    
    cout << "\nQuarter 3 sorted : ";

    for (int i = n/2; i < n-n/4; i++)
        cout << arr[i] << " ";
    
    cout << endl;

    return NULL;
}

void* sortQuarter4(void* arg) 
{

    int n = *((int*)arg); 

    cout << "\nQuarter number 4 = ";

    for (int i = n-n/4; i < n; i++)
        cout << arr[i] << " ";
        
    cout<<endl;

    for (int i = n-n/4; i < n; i++) 
    {
        for (int j = n-n/4; j < n; j++) 
        {
            if (arr[i] < arr[j])
                swap(arr[i], arr[j]);
        }
    }
    
    cout << "\nQuarter 4 sorted : ";

    for (int i = n-n/4; i < n; i++)
        cout << arr[i] << " ";
    
    cout << endl;

    return NULL;
}


void* mergeArray(void* arg) 
{

    int size_ = *((int *)arg);
    
    int* q1 = arr;
    int* q2 = arr + size_/4;
    int* q3 = arr + size_/2;
    int* q4 = arr + size_ - size_/4;
    
    int* first_half = new int[size_/2];

    // merging first two quarters (copying and sorting)

    for (int i = 0; i < size_/4; i++)
        first_half[i] = q1[i];

    for (int i = size_/4, j = 0; i < size_/2; i++, j++)
        first_half[i] = q2[j];

    for (int i = 0; i < size_/2; i++) {
        for (int j = 0; j < size_/2; j++) {
            if (first_half[i] < first_half[j]) {
                int temp = first_half[i];
                first_half[i] = first_half[j];
                first_half[j] = temp;
            }
        }
    }
    
    cout << "First half = ";
    for (int i = 0; i < size_/2; i++)
        cout << first_half[i] << " ";

    cout << endl;
    
    int* second_half = new int[size_/2];
    
    // merging second two quarters (copying and sorting)

    for (int i = 0; i < size_/4; i++)
    	second_half[i] = q3[i];
    	
    for (int i = size_/4, j = 0; i < size_/2; i++, j++)
    	second_half[i] = q4[j];

    for (int i = size_/2; i < size_; i++) {
        for (int j = size_/2; j < size_; j++) {
            if (second_half[i] < second_half[j]) {
                int temp = second_half[i];
                second_half[i] = second_half[j];
                second_half[j] = temp;
            }
        }
    }
    
    cout << "Second half = ";
    for (int i = 0; i < size_/2; i++)
        cout << second_half[i] << " ";

    cout << endl;
    
    // merging the two halves
    
    for (int i = 0, j = 0; i < size_/2; i++, j++)
        res[i] = first_half[j];

    for (int i = size_/2, j = 0; i < size_; i++, j++) {
        res[i] = second_half[j];
     }

    for (int i = 0; i < size_; i++) {
        for (int j = 0; j < size_; j++) {
            if (res[i] < res[j]) {
                int temp = res[i];
                res[i] = res[j];
                res[j] = temp;
            }
        }
    }
    

    cout << "Array after merging = ";
    for (int i = 0; i < size_; i++)
        cout << res[i] << " ";

    cout << endl;


    return NULL; 
}

int main() {

    int size_;

    cout << "Enter size of the array: ";
    cin >> size_;

    arr = new int[size_];
    res = new int[size_];

    
    for (int i = 0; i < size_; i++)
    {
        cout << "Enter value "<<i<<" = ";
        cin >> arr[i];
    }

    pthread_create(&tid1, NULL, sortQuarter1, (void*) &size_);
    pthread_create(&tid2, NULL, sortQuarter2, (void*) &size_);
    pthread_create(&tid3, NULL, sortQuarter3, (void*) &size_);
    pthread_create(&tid4, NULL, sortQuarter4, (void*) &size_);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);
    pthread_join(tid4, NULL);

    pthread_create(&tid5, NULL, mergeArray, (void*) &size_);

	pthread_exit(NULL);
}

