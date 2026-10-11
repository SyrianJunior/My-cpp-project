#pragma once
#include <bits/stdc++.h>
using namespace std ;

#include "clsScreen.h"
#include "clsInputValidate.h"

#include "clsListScreen.h"
#include "clsEndStuScreen.h"
#include "clsUpdateScreen.h"
#include "clsAddStudentScreen.h"
#include "clsLogScreen.h"

class clsMainScreen : protected clsScreen
{

private :

    static void _PrintKey( string Key , string Text , string Color )
    {
        cout << Color << clr::Bold << "[" << Key << "]" << clr::Reset << clr::White << " " << Text << clr::Reset << "     " ;
    }

public :

    // Shows the main screen once and runs one command.
    // returns false when the user chose Exit.
    static bool ShowMainScreen()
    {

        Clear() ;

        PrintHeader( "Main Screen" ) ;

        vector<clsStudent> vData = clsListScreen::ShowStudents() ;

        cout << taps ;
        _PrintKey( "E" , "End"  , clr::Red ) ;
        _PrintKey( "A" , "Add"  , clr::Green ) ;
        _PrintKey( "L" , "Log"  , clr::Cyan ) ;
        _PrintKey( "0" , "Exit" , clr::Gray ) ;
        cout << "\n" ;

        if( !vData.empty() )
            cout << taps << clr::Gray << "type a student number to add products" << clr::Reset << "\n" ;

        cout << "\n" << taps << clr::Cyan << clr::Bold << "> " << clr::Reset ;

        while( true )
        {

            string In = clsInputValidate::ReadString() ;

            if( In == "0" )
                return false ;

            if( In.size() == 1 )
            {
                char C = toupper( In[0] ) ;

                if( C == 'E' )
                {
                    clsEndStuScreen::ShowEndStuScreen() ;
                    return true ;
                }
                if( C == 'A' )
                {
                    clsAddStudentScreen::ShowAddStudentScreen() ;
                    return true ;
                }
                if( C == 'L' )
                {
                    clsLogScreen::ShowLogScreen() ;
                    return true ;
                }
            }

            if( clsInputValidate::IsNumber( In ) )
            {
                int Num = stoi( In ) ;

                if( Num >= 1 && Num <= (int)vData.size() )
                {
                    clsUpdateScreen::ShowUpdateScreen( vData[ Num - 1 ] ) ;
                    return true ;
                }
            }

            cout << taps << clr::Red << "Invalid choice, Try Again : " << clr::Reset ;
        }

    }


};
