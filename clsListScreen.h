#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "clsScreen.h"
#include "clsStudent.h"


class clsListScreen : protected clsScreen
{

public:

    // Prints the table of the students who are inside now
    // and returns the same list (so the caller can choose a student by its number)
    static vector<clsStudent> ShowStudents()
    {

        vector<clsStudent> vData = clsStudent::GetListStudent();
        clsStudent::stTime Now = clsStudent::GetNowTime();

        vector<int> W = { 4, 18, 8, 7, 9, 9, 11 };

        cout << taps << clr::White << "Inside now : " << clr::Bold << clr::Green << vData.size() << clr::Reset
             << clr::Gray << "        Time : " << clr::Reset << clr::Bold << clr::Yellow
             << clsStudent::FormatTime(Now._hour, Now._min) << clr::Reset << "\n\n";

        Border('t', W);

        RowStart();
        Cell("#", W[0], clr::Cyan + clr::Bold);
        Cell("Name", W[1], clr::Cyan + clr::Bold);
        Cell("Since", W[2], clr::Cyan + clr::Bold);
        Cell("Min", W[3], clr::Cyan + clr::Bold);
        Cell("Addons", W[4], clr::Cyan + clr::Bold);
        Cell("Teacher", W[5], clr::Cyan + clr::Bold);
        Cell("Price Now", W[6], clr::Cyan + clr::Bold);
        RowEnd();

        Border('m', W);

        if (vData.empty())
        {
            RowStart();
            Cell("", W[0]);
            Cell("No students inside", W[1] + W[2] + W[3] + W[4] + W[5] + W[6] + 5, clr::Gray);
            RowEnd();
        }
        else
        {
            for (int i = 0; i < (int)vData.size(); i++)
            {
                clsStudent &C = vData[i];

                int Minutes = C.getMinutes(Now);

                // green < 1 hour , yellow < 2 hours , red after that
                string MinColor = Minutes < 60 ? clr::Green : (Minutes < 120 ? clr::Yellow : clr::Red);

                RowStart();
                Cell(to_string(i + 1), W[0], clr::Gray);
                Cell(C.Name(), W[1], clr::White + clr::Bold);
                Cell(C.StartTime(), W[2], clr::White);
                Cell(to_string(Minutes), W[3], MinColor);
                Cell(to_string((long long)llround(C.Addons())), W[4], clr::White);
                Cell(C.WithTeacher() ? "Yes" : "No", W[5], C.WithTeacher() ? clr::Green : clr::Gray);
                Cell(to_string((long long)llround(C.getToTalPrice(Now))), W[6], clr::Yellow + clr::Bold);
                RowEnd();
            }
        }

        Border('b', W);

        cout << "\n";

        return vData;
    }
};
