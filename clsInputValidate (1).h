#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "clsScreen.h"

class clsInputValidate
{

public:

    static int ReadnumBetwen(int left, int right)
    {

        int x;

        while (true)
        {
            if (cin >> x && x >= min(left, right) && x <= max(left, right))
            {
                cin.ignore(10000, '\n');        // remove the rest of the line
                return x;
            }

            cin.clear();                        // remove fail state
            cin.ignore(10000, '\n');            // throw away the wrong input

            cout << "\t\t\t\t\t" << clr::Red << "Error Please Try Again betwen [" << min(left, right) << "," << max(left, right) << "] :  " << clr::Reset;
        }
    }

    // Reads a whole line (spaces allowed) and never returns an empty string
    static string ReadString()
    {

        string S;

        while (true)
        {
            if (getline(cin >> ws, S))
            {
                while (!S.empty() && isspace((unsigned char)S.back()))
                    S.pop_back();

                if (!S.empty())
                    return S;
            }

            cin.clear();
            cin.ignore(10000, '\n');

            cout << "\t\t\t\t\t" << clr::Red << "Invalid input, Try Again : " << clr::Reset;
        }
    }

    // Reads a line and returns its first character
    static char ReadChar()
    {
        string S = ReadString();
        return S[0];
    }

    static bool IsNumber(const string& S)
    {
        if (S.empty() || S.size() > 6)
            return false;

        for (char c : S)
            if (!isdigit((unsigned char)c))
                return false;

        return true;
    }

};
