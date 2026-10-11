#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "clsScreen.h"
#include "clsStudent.h"
#include "clsInputValidate.h"
#include "clsListScreen.h"

class clsEndStuScreen : protected clsScreen
{

private:

    static void _PrintInvoice( clsStudent& Stu , clsStudent::stTime Now )
    {

        int Minutes = Stu.getMinutes( Now ) ;
        double Rate = Stu.PricePerMin() ;

        string Line = "" ;
        for( int i = 0 ; i < 34 ; i++ )
            Line += "─" ;

        cout << taps << clr::Gray << Line << clr::Reset << "\n" ;
        cout << taps << clr::Gray << "Name     " << clr::Reset << clr::White << clr::Bold << Stu.Name() << clr::Reset << "\n" ;
        cout << taps << clr::Gray << "From     " << clr::Reset << Stu.StartTime() << "\n" ;
        cout << taps << clr::Gray << "To       " << clr::Reset << clsStudent::FormatTime( Now._hour , Now._min ) << "\n" ;
        cout << taps << clr::Gray << "Time     " << clr::Reset << Minutes << " min x " << (long long)Rate << " = " << (long long)( Minutes * Rate ) << "\n" ;
        cout << taps << clr::Gray << "Addons   " << clr::Reset << (long long)llround( Stu.Addons() ) << "\n" ;
        cout << taps << clr::Gray << Line << clr::Reset << "\n" ;
        cout << taps << clr::White << clr::Bold << "TOTAL    " << clr::Yellow << (long long)llround( Stu.getToTalPrice( Now ) ) << clr::Reset << "\n" ;
        cout << taps << clr::Gray << Line << clr::Reset << "\n\n" ;

    }

public:

    static void ShowEndStuScreen()
    {

        Clear() ;
        PrintHeader("End Student");

        vector<clsStudent> vData = clsListScreen::ShowStudents() ;

        if( vData.empty() )
        {
            Pause() ;
            return ;
        }

        cout << taps << clr::Cyan << clr::Bold << "> " << clr::Reset << clr::White << "Student number  [0 = Back] : " << clr::Reset ;
        int Num = clsInputValidate::ReadnumBetwen( 0 , vData.size() ) ;

        if( Num == 0 )
            return ;

        clsStudent Stu = vData[ Num - 1 ] ;
        clsStudent::stTime Now = clsStudent::GetNowTime() ;

        _PrintInvoice( Stu , Now ) ;

        cout << taps << clr::Cyan << clr::Bold << "> " << clr::Reset << clr::White << "End this student ? y/n : " << clr::Reset ;
        char c = clsInputValidate::ReadChar() ;

        if( c != 'y' && c != 'Y' )
            return ;

        if( Stu.Delete() )
        {
            Success( "Student ended and saved to the log" ) ;
        }
        else
        {
            Error( "Error while saving" ) ;
        }

        Pause() ;
    }
};
