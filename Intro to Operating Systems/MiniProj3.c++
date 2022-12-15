// Name: Samuel Olatunde, Bao Tang
// Course: Introduction To Operating Systems - Fall 2022 
// Instructor: Nelson Passos
// Description: This program simply counts the number of different 
// pages and segments in a table of addresses
#include<iostream>
#include<fstream>

using namespace std;

int main()
{
    //variable declarations
    int pageCounter = 0, segCounter = 0, code = 0;
    uint32_t input = 0, sieve = 0;

    //arrays to keep track of our different segments/pages
    bool pageFound[2048];
    bool segFound[1024];

    // initialize the arrays
    for (int i = 0; i < 1024; i++)
    {
        pageFound[i] = false;
        segFound[i] = false;
    }

    ifstream infile("spice.txt");
    ofstream outfile("shortreport.txt");

    if (!infile)
    {
        cout << "File Open Failed" << endl;
        return 0;
    }

    // read input from the file and process
    while (infile >> code)
    {
        infile >> hex >> input;

        //extract segment number
        sieve = input;
        sieve = sieve >> 22;

        if (segFound[sieve] == false)
        {
            segCounter++;
            segFound[sieve] = true;
        }

        sieve = input;

        //extract page number
        sieve = sieve << 10;
        sieve = sieve >> 21;

        if (pageFound[sieve] == false)
        {
            pageCounter++;
            pageFound[sieve] = true;
        }
    }

    outfile << "The number of different Segments are: " 
            << segCounter << endl;
    outfile << "The number of different Pages are: " 
            << pageCounter << endl;

    infile.close();
    outfile.close();
    return 0;
}