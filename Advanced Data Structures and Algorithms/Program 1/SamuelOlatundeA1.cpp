//*****************************************************************
//                   Assignment #1
//                    Names: Samuel Olatunde  
//                    Advanced Data Structures and Algorithms
//*****************************************************************
//   This Program uses recursive functions to calculate the   
//   summation, exponentiation, and product of numbers. The logic 
//   applied to these mathematical operations slightly differ 
//   from ideality (see individual definitions for futher 
//   explanation). Lastly input and output are made to the screen. 
//*****************************************************************    
#include<iostream>
#include <cctype>

using namespace std;

// Function Prototypes 
void menu(int& choice);
long long Summation(int n1);
long long BaseExponent(int base, int exponent);
long long Product(int n1);

int main()
{
    // variable declarations/initializations
    int n1 = 0, choice = 0, base = 0, exponent = 0;
    char keepRunning;

    do
    {
        // Displays Program Menu
        menu(choice);

        cout << endl;

        // Conditionals to perform diferent operations based on
        // the user's input
        if (choice == 1)
        {
            cout << "Enter a positive integer: ";
            cin >> n1;

            cout << "The sum of all the odd integers from 1 to " << n1
                << " is " << Summation(n1) << endl;
        }
        else if (choice == 2)
        {
            cout << "Enter an integer(base): ";
            cin >> base;

            cout << "Enter an integer(exponent): ";
            cin >> exponent;

            cout << "The result, when " << base << " is raised to the "
                << "power of " << exponent << " is "
                << BaseExponent(base, exponent) << endl;
        }
        else if (choice == 3)
        {
            cout << "Enter a positive integer: ";
            cin >> n1;

            cout << "The Product of all even integers from 1 to "
                << n1 << " is " << Product(n1) << endl;
        }

        // the operations can be run multiple times depending on the 
        // preference of the user 
        cout << endl
            << "Do you want to perform another Operation? "
            << "Enter Y for yes and N for no: " << endl;
        cin >> keepRunning;
        keepRunning = toupper(keepRunning);

    } while (keepRunning == 'Y');

    return 0;
}

//********************************************************************
//                      Name:: menu 
//                    Parameters: 1 int passed by reference 
//   This fucntion displays the menu for the program, reads in the 
//   menu choice, and performs input validation for the menu choice.
//   The function returns the value of choice via reference paramter
//   passing to main.      
//********************************************************************
void menu(int& choice)
{
    // Displays Menu
    cout << "1. Summation: Sum of odd integers between 1 and an "
        << "integer of your choice " << endl;
    cout << "2. Exponent: performs exponentiation between 2 "
        << "integers " << endl;
    cout << "3. Product: Product of even integers between 1 and an "
        << " integer of you choice " << endl;

    cout << "Make a choice: ";
    cin >> choice;

    // Input Validation Loop 
    while (choice < 1 || choice > 3)
    {
        cout << "Make a choice: ";
        cin >> choice;
    }
}

//*******************************************************************
//                      Name:: Summation 
//                    Parameters: 1 int 
//   In slight deviation, this recursive function adds all the odd 
//   integers between an integer and 1. The function returns a long 
//   long integer. This function doesn't put values of n1 less 
//   than or equal to zero into consideration. Of course passing 
//   in a negative integer would crash the program but we are 
//   assuming that all user input is correct.
//********************************************************************
long long Summation(int n1)
{
    // base case, values of n1 greater than zero approach 1
    if (n1 == 1)
    {
        return 1;
    }

    // if n1 is not even then add n1 to the next odd integer,
    // greater than 1 and less than n1; else, subtract one
    // from n1 (to give you the next odd integer),
    // then perform the summation
    if (n1 % 2 != 0)
    {
        // summation and recursive call
        return n1 + Summation(n1 - 2);
    }
    else
    {
        // summation and recursive call
        return Summation(n1 - 1);
    }
}

//*******************************************************************
//                      Name:: BaseExponent
//                    Parameters: 2 ints
//   This recursive function performs a typical exponentiation
//   operation, it rasies the base to the power of the exponent. It 
//   returns a long long integer. This function assumes that all 
//   values entered for the exponent are positive. It also doesn't 
//   take care of the unique scenario where the base and exponent 
//   are both zero
//********************************************************************
long long BaseExponent(int base, int exponent)
{
    if (base == 0)
    {
        return 0;
    }
    if (base == 1)
    {
        return 1;
    }

    if (exponent == 0)
    {
        return 1;
    }
    else
    {
        // exponentiation/recursive call 
        return base * BaseExponent(base, exponent - 1);
    }
}

//*******************************************************************
//                      Name:: Product
//                    Parameters: 1 int 
//   In slight deviation, this recursive function multiplies all 
//   even integers between 1 and integer ("n1"). It returns 
//   a long long integer. The function is made with the assumption
//   that all input are greater than 0;
//********************************************************************
long long Product(int n1)
{
    if (n1 == 2)
    {
        return 2;
    }

    if (n1 == 1)
    {
        return 0;
    }
    
    // if n1 is even then add n1 to the next even integer,
    // greater than 1 and less than n1; else, subtract one
    // from n1 (to give you the next even integer),
    // then perform the summation
    if (n1 % 2 == 0)
    {
        // multiplication/recurssive call 
        return n1 * Product(n1 - 2);
    }
    else
    {
        // recurssive call 
        return Product(n1 - 1);
    }
}
