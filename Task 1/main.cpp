#include<iostream>
#include<thread>
#include<future>
#include<fstream>
#include<cstdlib>
#include<algorithm>

using namespace std;

double average(int b[], int n);
double median(int b[], int n);

int main()
{
    fstream data;
    data.open("/1/data.txt", ios::in);

    // check if file exists
    if (data.good() == false)
    {
        cout << "Data not found!";
        exit(0);
    }

    const int size = 10000;
    int box[size];
    int number;
    int i = 0;

    // get data to array
    while (data >> number)
    {
        box[i++] = number;
    }

    data.close();

    future<double> ave = async(launch::async, average, box, size);
    future<double> med = async(launch::async, median, box, size);

    cout << "Waiting..." << endl;

    // waiting to get data from threads
    double a = ave.get();
    double m = med.get();

    cout << "Finished!" << endl;

    cout << "Average is: " << a << endl;
    cout << "Median is: " <<m << endl;

    if (a > m)
        cout << "Average is bigger" << endl;

    else if (a < m)
        cout << "Median is bigger" << endl;

    else
        cout << "Both are the same" << endl;

    cout << "Main ThreadID " << std::this_thread::get_id() << endl;

    return 0;
}

double average(int b[], int n)
{
    int sum = 0;
    double ave;

    for (int i = 0; i < n; i++)
    {
        sum += b[i];
    }

    ave = (double)sum / n;

    cout << "Average ThreadID " << std::this_thread::get_id() << endl;

    return ave;
}

double median(int b[], int n)
{
    double med;

    // sorting array
    sort(b, b + n);

    // check for odd case
    if (n % 2 != 0)
        med = (double)b[n/2];

    // even case
    med = (double)(b[(n-1)/2] + b[n/2]) / 2.0;

    cout << "Median ThreadID " << std::this_thread::get_id() << endl;

    return med;
}
