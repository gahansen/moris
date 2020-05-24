#ifndef MORIS_IOS_CL_LOGGER_HPP_
#define MORIS_IOS_CL_LOGGER_HPP_
#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <cstring>

#include "typedefs.hpp"
#include "IO_Tools.hpp"

// for the global clock
#include "cl_GlobalClock.hpp" // MRS/IOS/src
#include "cl_Tracer_Enums.hpp"
#include "fn_stringify.hpp"
#include "Log_Constants.hpp"

namespace moris
{

// class forward declaration
//class GlobalClock;
//enum class EntityBase;
//enum class EntityType;
//enum class EntityAction;
//enum class OutputSpecifier;

    class Logger
    {
    public:

    // Output File
    std::ofstream mStream;
    bool mWriteToAscii = false;

    // decide which outputs get written
    moris::sint mSeverityLevel = LOGGER_DEFAULT_SEVERITY_LEVEL;

    /**
    * Output formating mode for console output:
    * 1 - legacy mode, everything is written to screen as handed to log macros/functions
    * 2 - output is written in a clean tree structure, general MORIS_LOG and MORIS_LOG_INFO is suppressed. Good for live tracing.
    * 3 - all output is written in a tree structure, no filtering
    */
    uint mDirectOutputFormat = LOGGER_DEFAULT_DIRECT_OUTPUT;

    // Clock for tracing and timing
    GlobalClock  mGlobalClock;




    public:
        Logger(){}

        ~Logger()
        {

            // report error if prematurely stopped
            if (mGlobalClock.mIndentationLevel != 0)
            {
                // set indentation level to zero
                mGlobalClock.mIndentationLevel = 0;

                // report error
                std::cout << "Global clock & logger prematurely stopped.";

                if( mWriteToAscii )
                {
                    // log current position in code
                    this->log_to_file_error("Global clock & logger prematurely stopped.");
                }

            }


            if( mWriteToAscii )
            {

                // log runtime of clock
                this->log_to_file(OutputSpecifier::ElapsedTime,
                        ( (moris::real) std::clock() - mGlobalClock.mTimeStamps(mGlobalClock.mIndentationLevel) ) / CLOCKS_PER_SEC );

                //close file
                mStream.close();
            }
        };

        /**
         * Initialize MORIS_LOGGER
         *
         * Severity Levels
         * 1 ... all outputs
         * 2 ... all outputs except info
         * 3 ... all outputs except info and warning
         *
         * @include "IOS/src/cl_Logger/log.inc"
         */

        void initialize( const moris::sint aSeverityLevel )
        {
            mSeverityLevel = aSeverityLevel;

        };


        void initialize( int  & argc, char * argv[] );


        void initialize( const std::string aPath,
                         const moris::sint aSverityLevel = LOGGER_DEFAULT_SEVERITY_LEVEL,
                         const moris::uint aDirectOutputFormat = LOGGER_DEFAULT_DIRECT_OUTPUT)
        {
            mDirectOutputFormat = aDirectOutputFormat;
            mSeverityLevel = aSverityLevel;

            mStream.open(aPath,std::ofstream::out);

            mWriteToAscii = true;

            // print header
            this->print_header();

            // log start of Global Clock to file
            if( mWriteToAscii )
            {
                // formated output to log file
                this->log_to_file( OutputSpecifier::SignIn, 1.0);
            }
       };

        void set_severity_level( const moris::sint aSverityLevel )
        {
            mSeverityLevel = aSverityLevel;
        };

        moris::sint get_severity_level()
        {
            return mSeverityLevel;
        };

        template< typename ... Args >
        void log_section( const Args ... aArgs )
        {
            // MORIS_ASSERT(mStream.is_open(),"Logger error, the output file stream ofstream is not open);
            std::string tString = print_log( aArgs ... );

            if (mDirectOutputFormat == 1)
            {
                char tTempString[1000];
                std::strcpy( tTempString, "===============================================================================\n" );
                std::strcat( tTempString, "\n" );
                std::strcat( tTempString, tString.c_str() );
                std::strcat( tTempString, "\n" );
                std::strcat( tTempString, "===============================================================================" );

                std::cout << tTempString << "\n";
            }

            if( mWriteToAscii )
            {
                this->log_to_file(tString);
            }
        }

        template< typename ... Args >
        void log( const Args ... aArgs )
        {
           // MORIS_ASSERT(mStream.is_open(),"Logger error, the output file stream ofstream is not open);

            std::string tString = print_log( aArgs ... );

            // switch based on OutputFormat provided
            if (mDirectOutputFormat == 3)
            {
                std::cout << print_empty_line(mGlobalClock.mIndentationLevel) << "_" << "Log: " << tString << " \n";
            }
            else if (mDirectOutputFormat == 1)
                std::cout << tString << "\n";

            if( mWriteToAscii )
            {
                this->log_to_file(tString);
            }
        }

        template< typename ... Args >
        void log_info( const Args ... aArgs )
        {
           // MORIS_ASSERT(mStream.is_open(),"Logger error, the output file stream ofstream is not open);

            std::string tString = print_log( aArgs ... );

            // switch based on OutputFormat provided
//            if ((mDirectOutputFormat == 3) || (mDirectOutputFormat == 2))
            if (mDirectOutputFormat == 3)
            {
                std::cout << print_empty_line(mGlobalClock.mIndentationLevel) << "_" << "Info: " << tString << " \n";
            }
            else if (mDirectOutputFormat == 1)
                std::cout << tString << "\n";

            // write to file if requested
            if( mWriteToAscii )
            {
                this->log_to_file_info(tString);
            }
        }

        template< typename ... Args >
        void log_debug( const Args ... aArgs )
        {
           // MORIS_ASSERT(mStream.is_open(),"Logger error, the output file stream ofstream is not open);

            std::string tString = print_log( aArgs ... );

            // switch based on OutputFormat provided
            if ((mDirectOutputFormat == 3) || (mDirectOutputFormat == 2))
            {
                std::cout << print_empty_line(mGlobalClock.mIndentationLevel) << "_" << "Debug: " << tString << " \n";
            }
            else
                std::cout << tString << "\n";

            // write to file if requested
            if( mWriteToAscii )
            {
                this->log_to_file_debug(tString);
            }
        }

        template< typename ... Args >
        void log_warning( const Args ... aArgs )
        {
           // MORIS_ASSERT(mStream.is_open(),"Logger error, the output file stream ofstream is not open);

            std::string tString = print_log( aArgs ... );

            // switch based on OutputFormat provided
            if ((mDirectOutputFormat == 3) || (mDirectOutputFormat == 2))
            {
                std::cout << print_empty_line(mGlobalClock.mIndentationLevel) << "_" << "WARNING: " << tString << " \n";
            }
            else
                std::cout << tString << "\n";

            // write to file if requested
            if( mWriteToAscii )
            {
                this->log_to_file_warning(tString);
            }
        }

        template< typename ... Args >
        void log_error( const Args ... aArgs )
        {
           // MORIS_ASSERT(mStream.is_open(),"Logger error, the output file stream ofstream is not open);

            std::string tString = print_log( aArgs ... );

            // switch based on OutputFormat provided
            if ((mDirectOutputFormat == 3) || (mDirectOutputFormat == 2))
            {
//                std::cout << print_empty_line(mGlobalClock.mIndentationLevel) << "_" << "ERROR: " << tString << " \n";
                std::cout << tString << "\n";
            }
            else
                std::cout << tString << "\n";

            // write to file if requested
            if( mWriteToAscii )
            {
                this->log_to_file_error(tString);
            }
        }


        // ---------------------------------------------------------------------------------------------- //
        // FUNCTIONS ENABLING TRACING AND CLOCK LOGGING ------------------------------------------------- //
        // ---------------------------------------------------------------------------------------------- //

        // log with specified output type
        template <class T>
        void log_specific(enum OutputSpecifier aOutputSpecifier, T aOutputValue)
        {

            // switch based on OutputFormat provided
            if ((mDirectOutputFormat == 3) || (mDirectOutputFormat == 2))
            {
                std::cout << print_empty_line(mGlobalClock.mIndentationLevel) << "_"
                          << get_enum_str(aOutputSpecifier) << ": "
                          << ios::stringify(aOutputValue) << " \n";
            }
            else
                std::cout << get_enum_str(aOutputSpecifier) << ": " << ios::stringify(aOutputValue) << " \n";

            // write to file if requested
            if( mWriteToAscii )
            {
                this->log_to_file(aOutputSpecifier, aOutputValue);
            }
        }

        // sign in
        void sign_in( enum EntityBase aEntityBase, enum EntityType aEntityType, enum EntityAction aEntityAction );

        // signing out
        void sign_out();


        // write logged info to formated file
        template <class T>
        void log_to_file(enum OutputSpecifier aOutputSpecifier, T aOutputValue)
        {
            std::string tLine =   ios::stringify(mGlobalClock.mIndentationLevel) + ";"
                                + ios::stringify(mGlobalClock.mCurrentFunctionID(mGlobalClock.mIndentationLevel)) + ";"
                                +   get_enum_str(mGlobalClock.mCurrentEntity(mGlobalClock.mIndentationLevel)) + ";"
                                +   get_enum_str(mGlobalClock.mCurrentType(mGlobalClock.mIndentationLevel)) + ";"
                                +   get_enum_str(mGlobalClock.mCurrentAction(mGlobalClock.mIndentationLevel)) + ";"
                                +   get_enum_str(aOutputSpecifier) + ";"
                                + ios::stringify(aOutputValue) + "\n";

            mStream << tLine;
        }

        template <class T1, class T2>
        void log2_to_file(enum OutputSpecifier aOutputSpecifier1, T1 aOutputValue1,
                        enum OutputSpecifier aOutputSpecifier2, T2 aOutputValue2);

        template <class T1, class T2, class T3>
        void log3_to_file(enum OutputSpecifier aOutputSpecifier1, T1 aOutputValue1,
                        enum OutputSpecifier aOutputSpecifier2, T2 aOutputValue2,
                        enum OutputSpecifier aOutputSpecifier3, T3 aOutputValue3);

        // logging operation using Clock Info and string
        void log_to_file(std::string aOutputString);
        void log_to_file_info(std::string aOutputString);
        void log_to_file_debug(std::string aOutputString);
        void log_to_file_warning(std::string aOutputString);
        void log_to_file_error(std::string aOutputString);


        // ---------------------------------------------------------------------------------------------- //
        // FORMATTING TOOLS FOR OUTPUT ------------------------------------------------------------------ //
        // ---------------------------------------------------------------------------------------------- //

        // print header
        void print_header();

        // print empty line
        std::string print_empty_line(uint aIndentationLevel);

    }; // end class Logger

} // end namespace moris

// ---------------------------------------------------------------------------------------- //
// ---------------------------------------- MACROS ---------------------------------------- //
// ---------------------------------------------------------------------------------------- //

extern moris::Logger gLogger;

/**
 * Log an section severity message.
 *
 * @include "IOS/src/cl_Logger/log.inc"
 */
#define MORIS_SECTION( ... ) \
    do \
    { \
        gLogger.log_section( __VA_ARGS__ ); \
    } while (false)

/**
 * Log an informational severity message.
 *
 * @include "IOS/src/cl_Logger/log.inc"
 */
#define MORIS_LOG( ... ) \
    do \
    { \
        gLogger.log( __VA_ARGS__ ); \
    } while (false)

/**
 * Log an informational severity message.
 *
 * @include "IOS/src/cl_Logger/log.inc"
 */
#define MORIS_LOG_INFO( ... ) \
    do \
    { \
        if ( gLogger.get_severity_level() < 1 )\
        {\
           gLogger.log_info( __VA_ARGS__ ); \
        }\
    } while (false)

/**
 * Log single output value with specified type
 *
 * @include "IOS/src/cl_Logger/log.inc"
 */
#define MORIS_LOG_SPEC( ... ) \
    do \
    { \
        if ( gLogger.get_severity_level() < 1 )\
        {\
           gLogger.log_specific( __VA_ARGS__ ); \
        }\
    } while (false)

/**
 * Log a debug severity message.
 *
 * @include "IOS/src/cl_Logger/log_debug.inc"
 */
#if defined(DEBUG)
#define MORIS_LOG_DEBUG( ... ) \
    do \
    { \
        gLogger.log_debug( __VA_ARGS__ ); \
    } while (false)
#else
#define MORIS_LOG_DEBUG( ... )
#endif

/**
 * Log a warning severity message.
 *
 * @include "IOS/src/cl_Logger/log_warning.inc"
 */
#define MORIS_LOG_WARNING( ... ) \
    do \
    { \
        if ( gLogger.get_severity_level() < 2 ) \
        {\
            gLogger.log_warning( __VA_ARGS__ ); \
        }\
    } while (false)

/**
 * Log an error severity message.
 *
 * @include "IOS/src/cl_Logger/log_error.inc"
 */
#define MORIS_LOG_ERROR( ... ) \
    do \
    { \
        if ( gLogger.get_severity_level() < 2 ) \
        {\
            gLogger.log_warning( __VA_ARGS__ ); \
        }\
    } while (false)


#endif	/* MORIS_IOS_CL_LOGGER_HPP_ */
