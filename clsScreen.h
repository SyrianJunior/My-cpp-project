#pragma once
#include <bits/stdc++.h>
using namespace std ;

#ifdef _WIN32
    #define WIN32_LEAN_AND_MEAN
    #define NOMINMAX
    #include <windows.h>
#endif

// ---------- colors (ANSI) ----------
namespace clr
{
    const string Reset  = "\033[0m" ;
    const string Bold   = "\033[1m" ;
    const string Red    = "\033[91m" ;
    const string Green  = "\033[92m" ;
    const string Yellow = "\033[93m" ;
    const string Cyan   = "\033[96m" ;
    const string Gray   = "\033[90m" ;
    const string White  = "\033[97m" ;
    const string Bar    = "\033[46m\033[30m" ;   // cyan background + black text
}

class clsScreen
{

private :

    static const string _Tabs()
    {
        return "\t\t\t\t\t" ;
    }

    static string _Repeat( string S , int N )
    {
        string R = "" ;
        for( int i = 0 ; i < N ; i++ )
            R += S ;
        return R ;
    }

    // enables UTF-8 + colors on the Windows console (runs once)
    static void _InitConsole()
    {
        static bool Done = false ;
        if( Done ) return ;
        Done = true ;

        #ifdef _WIN32
            SetConsoleOutputCP( CP_UTF8 ) ;
            SetConsoleCP( CP_UTF8 ) ;

            HANDLE h = GetStdHandle( STD_OUTPUT_HANDLE ) ;
            DWORD Mode = 0 ;
            if( GetConsoleMode( h , &Mode ) )
                SetConsoleMode( h , Mode | 0x0004 ) ;   // ENABLE_VIRTUAL_TERMINAL_PROCESSING
        #endif
    }

public :

    static void Clear()
    {
        _InitConsole() ;

        #ifdef _WIN32
            system( "cls" ) ;
        #else
            cout << "\033[2J\033[H" ;
        #endif
    }

    // logo + screen title bar
    static void PrintHeader( string Title )
    {

        cout << "\n" ;
        cout << _Tabs() << clr::Cyan << clr::Bold << "▄▀█ █▀ ▄▀█ █▀   █▀█ █   █ █ █▀"   << clr::Reset << "\n" ;
        cout << _Tabs() << clr::Cyan << clr::Bold << "█▀█ ▄█ █▀█ ▄█   █▀▀ █▄▄ █▄█ ▄█"   << clr::Reset << "\n" ;
        cout << _Tabs() << clr::Gray << _Repeat( "─" , 74 ) << clr::Reset << "\n" ;
        cout << _Tabs() << clr::Bar << clr::Bold << "  " << Title << "  " << clr::Reset << "\n\n" ;

    }

    static void Pause()
    {
        cout << "\n" << _Tabs() << clr::Gray << "Press Enter to continue ... " << clr::Reset ;
        string S ;
        getline( cin , S ) ;
    }

    static void Success( string Msg )
    {
        cout << "\n" << _Tabs() << clr::Green << clr::Bold << "[ OK ] " << clr::Reset << clr::Green << Msg << clr::Reset << "\n" ;
    }

    static void Error( string Msg )
    {
        cout << "\n" << _Tabs() << clr::Red << clr::Bold << "[ !! ] " << clr::Reset << clr::Red << Msg << clr::Reset << "\n" ;
    }

    // ---------- table helpers ----------

    // Kind: 't' = top border , 'm' = middle border , 'b' = bottom border
    static void Border( char Kind , const vector<int>& W )
    {

        string L , M , R ;

        if( Kind == 't' )      { L = "┌" ; M = "┬" ; R = "┐" ; }
        else if( Kind == 'm' ) { L = "├" ; M = "┼" ; R = "┤" ; }
        else                   { L = "└" ; M = "┴" ; R = "┘" ; }

        cout << _Tabs() << clr::Gray << L ;

        for( int i = 0 ; i < (int)W.size() ; i++ )
            cout << _Repeat( "─" , W[i] ) << ( i + 1 < (int)W.size() ? M : R ) ;

        cout << clr::Reset << "\n" ;
    }

    static void RowStart()
    {
        cout << _Tabs() ;
    }

    static void RowEnd()
    {
        cout << clr::Gray << "│" << clr::Reset << "\n" ;
    }

    // cuts a text to N bytes without breaking a UTF-8 character
    static string Fit( string S , int N )
    {
        if( (int)S.size() <= N )
            return S ;

        while( N > 0 && ( (unsigned char)S[N] & 0xC0 ) == 0x80 )
            N-- ;

        return S.substr( 0 , N ) ;
    }

    // one cell : border + colored text padded to W
    static void Cell( string Text , int W , string Color = clr::White )
    {
        cout << clr::Gray << "│" << clr::Reset
             << Color << left << setw( W ) << Fit( Text , W - 1 ) << clr::Reset ;
    }

};
