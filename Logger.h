/*! 
* \file Logger.h
*
* \breif A basic, yet useful logger class
*
* This class is used for simple logging purposes, and handles messages, errors and warnings. All these are user defined.
* Anything sent to this class is stored in an external text file(.txt). The text file is overwritten when the class is initialized, to remove any old log.
*
* Changelog
* =========
*
* 2014-01-28 (0.1.3)
*  - Added "Log" define to simplify usage
*
* 2014-01-23 (0.1.2)
*  - Return functions for message counters added (messages, warnings, errors and total)
*  - More readable log file formatting
*  - Switched design pattern to singleton, for modularity and ease-of-use
*
* 2014-01-22 (0.1.1)
*  - Initial release
*
* \author Dennis Fredriksson
* \date 2014-01-22
*/

#pragma once

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/*!
* \def DEF_DEFAULT_FILE
* \brief Sets the default log filename, for easy changing
*/
#define DEF_DEFAULT_FILE "project_log.txt"

/*!
* \def Log
* \brief Used to access the logger class singleton in an easier fashion. Default usage is still valid
*/
#define Log SimpleLogger::getInstance()

/*!
* \class SimpleLogger
*
* \brief A basic, yet useful logger class
*
* This class is used for simple logging purposes, and handles messages, errors and warnings. All these are user defined.
* Anything sent to this class is stored in an external .txt file. The text file is overwritten when the class is initialized, to remove any old log.
* Complete version history in the file description, see \ref logger.h "here"
*
* Changelog
* =========
*
* 2014-01-28 (0.1.3)
*  - Added "Log" define to simplify usage
*
* 2014-01-23 (0.1.2)
*  - Return functions for message counters added (messages, warnings, errors and total)
*  - More readable log file formatting
*  - Switched design pattern to singleton, for modularity and ease-of-use
*
* \version 0.1.3
*
* \author Dennis Fredriksson
*/
class SimpleLogger
{
private:
	/*! 
	* \var string mLastMessage
    * \brief Stores the last message recorded
	* \private
	*/
	string mLastMessage;

	/*! 
	* \var string mLastWarning
    * \brief Stores the last warning message recorded
	* \private
	*/
	string mLastWarning;

	/*! 
	* \var string mLastWarning
    * \brief Stores the last error message recorded
	* \private
	*/
	string mLastError;

	/*! 
	* \var unsigned int mLogCounter
    * \brief Counts the total amount of logs 
	* \private
	*/
	unsigned int mLogCounter;

	/*! 
	* \var unsigned int mMessageCounter
    * \brief Counts the total amount of message logs 
	* \private
	*/
	unsigned int mMessageCounter;

	/*! 
	* \var unsigned int mErrorCounter
    * \brief Counts the total amount of error logs 
	* \private
	*/
	unsigned int mErrorCounter;

	/*! 
	* \var unsigned int mWarningCounter
    * \brief Counts the total amount of warning logs 
	* \private
	*/
	unsigned int mWarningCounter;

	/*! 
	* \var bool mPrintLog
    * \brief Determines if the class should print to console debug or not
	* \private
	*/
	bool mPrintLog;

	/*! 
	* \var fstream mFile
    * \brief Used for saving the log to a text file
	* \private
	*/
	fstream mFile;

	/*! 
	* \var static bool mInstanceFlag
    * \brief Singleton instance flag
	* \private
	*/
	static bool mInstanceFlag;

	/*! 
	* \var static SimpleLogger* mSingleton
    * \brief Singleton class pointer
	* \private
	*/
	static SimpleLogger* mSingleton;

	/*!
	* \fn SimpleLogger()
	* \brief Class constructor
	* \private
	*/
	SimpleLogger();

public:
	/*!
	* \fn static SimpleLogger* getInstance(void)
	* \brief Returns an instance of the class singleton
	*
	* \retval static SimpleLogger*
	*/
	static SimpleLogger* getInstance(void);

	/*!
	* \fn ~SimpleLogger()
	* \brief Class deconstructor
	*/
	~SimpleLogger();

	/*!
	* \fn void logMessage(string iMessage)
	* \brief Send a new message to the log
	*
	* You only need to send the acctual message you want to log, formatting is done by the class internally. \n
	* Message formatting in log file: \n
	* Log type: Message \n
	* [Message]
	*
	* \param[in] iMessage The message
	*/
	void logMessage(string iMessage);

	/*!
	* \fn void logError(string iError, int iErrorNum = -1)
	* \brief Send a new error message to the log
	*
	* You only need to send the acctual error message you want to log, formatting is done by the class internally. \n
	* Message formatting to debug: \n
	* Error [Number]: [Error message]
	*
	* Message formatting in log file: \n
	* Log type: Error \n
	* Error number: [Number] \n
	* [Error message]
	*
	* \param[in] iError The error message
	* \param[in] iErrorNum The error number
	*/
	void logError(string iError, int iErrorNum = -1);

	/*!
	* \fn void logWarning(string iWarning, int iWarningNum = -1)
	* \brief Send a new warning message to the log
	*
	* You only need to send the acctual warning message you want to log, formatting is done by the class internally. \n
	* Message formatting to debug: \n
	* Warning [Number]: [Warning message]
	*
	* Message formatting in log file: \n
	* Log type: Warning \n
	* Error number: [Number] \n
	* [Warning message]
	*
	* \param[in] iError The warning message
	* \param[in] iErrorNum The warning number
	*/
	void logWarning(string iWarning, int iWarningNum = -1);

	/*!
	* \fn string getLastMessage(void)
	* \brief Returns the last message recorded
	*
	* This is NOT formatted, this is only the message the user sent.
	*
	* \retval string
	*/
	string getLastMessage(void);

	/*!
	* \fn string getLastError(void)
	* \brief Returns the last error message recorded
	*
	* This is NOT formatted, this is only the message the user sent.
	*
	* \retval string
	*/
	string getLastError(void);

	/*!
	* \fn string getLastWarning(void)
	* \brief Returns the last warning message recorded
	*
	* This is NOT formatted, this is only the message the user sent.
	*
	* \retval string
	*/
	string getLastWarning(void);

	/*!
	* \fn unsigned int getNumberMessages(void)
	* \brief Returns the amount of messages sent to the logger
	*
	* \retval unsigned int
	*/
	unsigned int getNumberMessages(void);

	/*!
	* \fn unsigned int getNumberWarnings(void)
	* \brief Returns the amount of warnings sent to the logger
	*
	* \retval unsigned int
	*/
	unsigned int getNumberWarnings(void);

	/*!
	* \fn unsigned int getNumberErrors(void)
	* \brief Returns the amount of errors sent to the logger
	*
	* \retval unsigned int
	*/
	unsigned int getNumberErrors(void);

	/*!
	* \fn unsigned int getNumberTotal(void)
	* \brief Returns the total amount of messages sent to the logger
	*
	* This includes normal messages, errors and warnings
	*
	* \retval unsigned int
	*/
	unsigned int getNumberTotal(void);

	/*!
	* \fn void printLogToDebug(bool iToggle)
	* \brief Tells the class if it should enable or disable debug printing to the console
	*
	* \see DEF_DEFAULT_FILE for filename and save path
	*
	* \param[in] iToggle The true/false toggle
	*/
	void printLogToDebug(bool iToggle);
};