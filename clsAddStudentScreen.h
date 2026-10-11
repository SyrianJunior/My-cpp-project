#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "clsScreen.h"
#include "clsStudent.h"
#include "clsInputValidate.h"
#include "clsListScreen.h"

class clsAddStudentScreen : protected clsScreen
{

private :

    // returns false if the user pressed 0 (Back)
    static bool _GetInfo( clsStudent& Stu )
    {

        cout << taps << clr::Cyan << clr::Bold << "> " << clr::Reset << clr::White << "Student name  [0 = Back] : " << clr::Reset ;
        string Name = clsInputValidate::ReadString() ;

        while ( Name != "0" && clsStudent::is_StudentExsist( Name ) )
        {
            cout << taps << clr::Red << "There is a student with the same name ! Retry [0 = Back] : " << clr::Reset ;
            Name = clsInputValidate::ReadString() ;
        }

        if( Name == "0" )
            return false ;

        Stu.set_Name( Name ) ;

        clsStudent::stTime Now = clsStudent::GetNowTime() ;
        Stu.set_Hour( Now._hour );
        Stu.set_Min( Now._min );

        cout << taps << clr::Cyan << clr::Bold << "> " << clr::Reset << clr::White << "With teacher ? y/n  [0 = Back] : " << clr::Reset ;
        char chois = clsInputValidate::ReadChar() ;

        if( chois == '0' )
            return false ;

        Stu.set_WithTeacher( chois == 'Y' || chois == 'y' ) ;

        return true ;

    }

public :


    static void ShowAddStudentScreen()
    {

        Clear() ;
        PrintHeader( "Add Student" );
        clsListScreen::ShowStudents() ;

        clsStudent NewStu = clsStudent ::GetAddNewSudent() ;

        if( !_GetInfo( NewStu ) )
            return ;

        clsStudent::enSaveResault SaveRes = NewStu.Save() ;

        if( SaveRes == clsStudent::enSaveResault::SvSuccfuly )
        {
            Success( "Student added successfully" ) ;
        }
        else
        {
            Error( "Student was not saved" ) ;
        }

        Pause() ;
    }


};
