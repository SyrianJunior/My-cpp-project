#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "clsScreen.h"
#include "clsStudent.h"

class clsLogScreen : protected clsScreen
{

public :

    static void ShowLogScreen()
    {

        Clear() ;
        PrintHeader( "Log Screen" ) ;

        vector<clsStudent::stLog> vLog = clsStudent::GetLogList() ;

        vector<int> W = { 20 , 12 , 12 , 14 } ;

        Border( 't' , W ) ;

        RowStart() ;
        Cell( "Name"  , W[0] , clr::Cyan + clr::Bold ) ;
        Cell( "From"  , W[1] , clr::Cyan + clr::Bold ) ;
        Cell( "To"    , W[2] , clr::Cyan + clr::Bold ) ;
        Cell( "Price" , W[3] , clr::Cyan + clr::Bold ) ;
        RowEnd() ;

        Border( 'm' , W ) ;

        double Total = 0 ;

        if( vLog.empty() )
        {
            RowStart() ;
            Cell( "No log yet" , W[0] + W[1] + W[2] + W[3] + 3 , clr::Gray ) ;
            RowEnd() ;
        }
        else
        {
            // newest first
            for( int i = (int)vLog.size() - 1 ; i >= 0 ; i-- )
            {
                clsStudent::stLog& L = vLog[i] ;

                RowStart() ;
                Cell( L._Name , W[0] , clr::White + clr::Bold ) ;
                Cell( L._From , W[1] , clr::White ) ;
                Cell( L._To   , W[2] , clr::White ) ;
                Cell( to_string( (long long)llround( L._Price ) ) , W[3] , clr::Yellow + clr::Bold ) ;
                RowEnd() ;

                Total += L._Price ;
            }
        }

        Border( 'b' , W ) ;

        cout << "\n" << taps << clr::White << "Sessions : " << clr::Bold << vLog.size() << clr::Reset
             << clr::Gray << "      " << clr::White << "Total : " << clr::Bold << clr::Yellow
             << (long long)llround( Total ) << clr::Reset << "\n" ;

        Pause() ;

    }

};
