#pragma once
#include <bits/stdc++.h>
using namespace std ;

#include "clsScreen.h"
#include "clsStudent.h"
#include "clsInputValidate.h"
#include "clsListScreen.h"


class clsUpdateScreen : protected clsScreen
{

public :

    // Adds products to a student, the user can add many products until he presses 0
    static void ShowUpdateScreen( clsStudent& Stu )
    {

        vector<pair<string,int>>Products ;

        Products.push_back( {"Kinza" , 5000} ) ;
        Products.push_back( {"XXl" , 8000} ) ;
        Products.push_back( {"DarkBlue" , 8000} ) ;

        vector<int> W = { 5 , 18 , 10 } ;

        string Msg = "" ;

        while( true )
        {

            Clear() ;
            PrintHeader( "Add Products" );
            clsListScreen::ShowStudents() ;

            cout << taps << clr::Gray << "Student " << clr::Reset << clr::White << clr::Bold << Stu.Name() << clr::Reset
                 << clr::Gray << "     Addons " << clr::Reset << clr::Yellow << clr::Bold << (long long)llround( Stu.Addons() ) << clr::Reset << "\n\n" ;

            if( Msg != "" )
            {
                cout << taps << clr::Green << Msg << clr::Reset << "\n\n" ;
                Msg = "" ;
            }

            // products table
            Border( 't' , W ) ;

            RowStart() ;
            Cell( "#"       , W[0] , clr::Cyan + clr::Bold ) ;
            Cell( "Product" , W[1] , clr::Cyan + clr::Bold ) ;
            Cell( "Price"   , W[2] , clr::Cyan + clr::Bold ) ;
            RowEnd() ;

            Border( 'm' , W ) ;

            for( int i = 0 ; i < (int)Products.size() ; i++ )
            {
                RowStart() ;
                Cell( "[" + to_string( i + 1 ) + "]" , W[0] , clr::Cyan + clr::Bold ) ;
                Cell( Products[i].first              , W[1] , clr::White + clr::Bold ) ;
                Cell( to_string( Products[i].second ) , W[2] , clr::Yellow ) ;
                RowEnd() ;
            }

            Border( 'b' , W ) ;

            cout << taps << clr::Gray << "[0] Back" << clr::Reset << "\n\n" ;
            cout << taps << clr::Cyan << clr::Bold << "> " << clr::Reset << clr::White << "Choice : " << clr::Reset ;

            int Choise = clsInputValidate ::ReadnumBetwen( 0 , Products.size() ) ;

            if( Choise == 0 )
                return ;

            Stu.set_Addons( Stu.Addons() + Products[Choise-1].second );

            if( Stu.Save() != clsStudent ::enSaveResault ::SvSuccfuly )
            {
                Error( "Saving failed" ) ;
                Pause() ;
                return ;
            }

            Msg = "+ " + Products[Choise-1].first + " added" ;
        }

    }

};
