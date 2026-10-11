#pragma once 
#include <bits/stdc++.h>
using namespace std ;

class clsString
{

private :

public :

    static vector<string> Split( string S , string seperator = "/" )
    {

        vector<string>Resault ;

        while (true)
        {
            
            int pos = S.find( seperator );

            if(  pos == -1 )
            {
                Resault.push_back( S ) ;
                break;
            }
            else
            {
                Resault.push_back( S.substr( 0 , pos ) ) ;
                S = S.substr( pos + seperator.length() ) ;

            }

        }
        
        return Resault ;
    }


};

