#pragma once 
#include <bits/stdc++.h>
#include <ctime>
using namespace std ;

#include "clsString.h"

string taps = "\t\t\t\t\t" ;

class clsStudent
{

public :

    struct stTime
    {
        short _hour ;
        short _min ;
    };


    struct stLog
    {
        string _Name ;
        string _From ;
        string _To ;
        double _Price ;
    };

private :
    
    enum enMode { EmptyObject = 0 , UpdateObject = 1 , AddNewObject = 2 } ;

    enMode _Mode ;

    bool _MarkedForDelete = false ;

    string _Name ;
    short _Hour ;
    short _min ; 
    double _Addons ;
    bool _WithTeacher ;



    double _GetminPrice()
    {

        if( !WithTeacher() )
            return 50 ;
        else
            return 60 ; 

    }
    
    static string _ConvertObjectToLogLine( clsStudent Student , string seperator = "#//#" )
    {

        stTime Now = GetNowTime() ;

        string Line = "" ;

        Line += Student.Name() + seperator ;
        Line += Student.StartTime() + seperator ;
        Line += FormatTime( Now._hour , Now._min ) + seperator ;
        Line += to_string( Student.getToTalPrice( Now ) ) ; 

        return Line ;

    }

    static stLog _ConvertLineToLog( string Line )
    {
        vector<string> vData = clsString::Split( Line , "#//#" ) ;

        stLog Log ;
        Log._Name  = vData[0] ;
        Log._From  = vData[1] ;
        Log._To    = vData[2] ;
        Log._Price = stod( vData[3] ) ;

        return Log ;
    }

    static vector<stLog> _LoadLogFromFile()
    {
        fstream MyFile ;
        MyFile.open( "Log.txt" , ios::in ) ;
        vector<stLog> vLog ;

        if( MyFile.is_open() )
        {
            string Line ;
            while( getline( MyFile , Line ) )
            {
                if( Line.empty() ) continue ;
                vLog.push_back( _ConvertLineToLog( Line ) ) ;
            }
            MyFile.close() ;
        }

        return vLog ;
    }

    static clsStudent _ConvertLineToObject( string Line )
    {
        
        vector<string>vData = clsString::Split( Line , "#//#" ) ;
        bool withteacher ;
        if( vData[4] == "0" )
            withteacher = false ;
        else
            withteacher = true ;


        clsStudent student( enMode::UpdateObject , vData[0] , stoi(vData[1]) , stoi(vData[2]) , stod(vData[3]) , withteacher );

        return student ;
        
    }

    static string _ConvertObjectToLine( clsStudent Student , string seperator = "#//#" )
    {

        string Line = "" ;

        Line += Student.Name() + seperator ;
        Line += to_string(Student.Hour()) + seperator ;
        Line += to_string(Student.Min()) + seperator ;
        Line += to_string(Student.Addons()) + seperator ;
        Line += to_string( Student.WithTeacher() );
        return Line ;

    }

    static vector<clsStudent> _LoadDataFromFile( )
    {

        fstream MyFile ;
        MyFile.open( "Student.txt" , ios::in );
        vector<clsStudent> vStudent ;
        if( MyFile.is_open() )
        {
            string Line ;
            while ( getline( MyFile , Line ) )
            {
                if( Line.empty() ) continue ;
                
                clsStudent Student = _ConvertLineToObject( Line ) ;
                vStudent.push_back( Student ) ; 

            }
            
            MyFile.close();
        }

        return vStudent ;

    }

    static void _SaveDataToFile( vector<clsStudent>vData )
    {

        fstream myfile ;
        myfile.open( "Student.txt" , ios::out );

        if( myfile.is_open() )
        {

            for( clsStudent& C :vData )
            {
                
                if( !C._MarkedForDelete )   
                {
                    string Line = _ConvertObjectToLine( C );
                    myfile << Line << endl ;
                }
            }

            myfile.close() ;

        } 

    }

    static clsStudent _GetEmptyObject()
    {
        return clsStudent ( enMode ::EmptyObject , "" , 0 , 0 , 0 , 0 ) ;
    }
    
    void _Update()
    {
        vector<clsStudent>vData = _LoadDataFromFile() ;  
        for( clsStudent& C : vData )
        {
            if( C.Name() == _Name )
            {
                C = *this ;
                break;
            }
        }

        _SaveDataToFile( vData ) ;

    }

    void _AddDataLinetoFile( string File  , string Line )
    {
        fstream MyFile;
        MyFile.open(File, ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << Line << endl;

            MyFile.close();
        }

    }


    void _AddNewStu()
    {

        _AddDataLinetoFile( "Student.txt" , _ConvertObjectToLine( *this )) ;  

    }


    void _AddObjectToLog( )
    {
        _AddDataLinetoFile( "Log.txt" , _ConvertObjectToLogLine(  *this )) ;  
    }

public :

    static vector<stLog> GetLogList()
    {
        return _LoadLogFromFile() ;
    }

    static stTime GetNowTime()
    {
        time_t now = time(0) ;
        tm *local = localtime(&now) ;

        stTime T ;
        T._hour = local->tm_hour ;
        T._min  = local->tm_min ;
        return T ;
    }

    static string FormatTime( short Hour , short Min )
    {
        char Buf[16] ;
        snprintf( Buf , sizeof(Buf) , "%02d:%02d" , Hour , Min ) ;
        return string( Buf ) ;
    }

    string StartTime()
    {
        return FormatTime( _Hour , _min ) ;
    }

    // minutes between the start of the student and currtime (handles midnight)
    int getMinutes( stTime currtime )
    {
        int Diff = ( currtime._hour * 60 + currtime._min ) - ( Hour() * 60 + Min() ) ;

        if( Diff < 0 )
            Diff += 24 * 60 ;

        return Diff ;
    }

    double PricePerMin()
    {
        return _GetminPrice() ;
    }

    clsStudent( enMode Mode ,  string Name , short Hour , short Min , double Addons , bool WithTeacher )
    {
        _Mode = Mode ;
        _Name = Name ;
        _Hour = Hour ;
        _min = Min ;
        _Addons = Addons ;
        _WithTeacher = WithTeacher ;
    }

    /////////////
    short Hour()
    {
        return _Hour ;
    }
    void set_Hour( short hour )
    {
        _Hour = hour ;
    }

    short Min()
    {
        return _min ;
    }
    void set_Min( short Min )
    {
        _min = Min ;
    }

    double Addons( )
    {
        return _Addons ;
    }

    void set_Addons( double Addons )
    {
        _Addons = Addons ;
    }

    bool WithTeacher()
    {
        return _WithTeacher ;
    }

    void set_WithTeacher( bool WithTeacher )
    {
        _WithTeacher = WithTeacher ;
    }

    string Name()
    {
        return _Name ;
    }
    void set_Name( string name )
    {
        _Name = name ;
    }


    double getToTalPrice( stTime currtime )
    {

        return Addons() + getMinutes( currtime ) * _GetminPrice() ;

    }

    static bool is_StudentExsist( string name )
    {

        vector<clsStudent>vData = _LoadDataFromFile() ;

        for( auto C : vData )
        {
            if( name == C.Name() )
            {
                return true ;
            }
        } 

        return false ;

    }

    enum enSaveResault { FailedEmptyObj = 0 , SvSuccfuly = 1 , FailedAccountNumberIsUsed = 2 } ;

    enSaveResault Save()
    {
        
        if( _Mode == enMode ::EmptyObject )
        {
            return enSaveResault :: FailedEmptyObj ;
        }
        else if( _Mode == enMode ::UpdateObject )
        {

            _Update() ;
            return enSaveResault ::SvSuccfuly ;
        }   
        else if( _Mode == enMode ::AddNewObject )
        {
            _AddNewStu();
            return enSaveResault ::SvSuccfuly ;
        }   

        return enSaveResault :: FailedEmptyObj ;
    }

    static vector<clsStudent>GetListStudent(  )
    {

        return _LoadDataFromFile() ;

    }
    
    static clsStudent Find( string Name )
    {

        vector<clsStudent> vData = clsStudent::_LoadDataFromFile() ;

        for( clsStudent& C : vData )
        {

            if( C.Name() == Name )
            {

                //cout << C.Name() << endl ;

                return C ;
            }
            
        }

        return _GetEmptyObject() ;
    }

    bool Delete( )
    {
        
        vector<clsStudent>vData = clsStudent ::_LoadDataFromFile() ;

        for( clsStudent& C : vData )
        {

            if( C.Name() == _Name )
            {
                C._MarkedForDelete = true ;
                break;
            }

        }

        _SaveDataToFile( vData ) ;

        _AddObjectToLog() ;

        *this = _GetEmptyObject() ;

        return true ;

    }

    static clsStudent GetAddNewSudent()
    {
        return clsStudent( enMode ::AddNewObject , "" , 0 , 0 , 0 , false );
    }

};
