#include "Logger.h"

SimpleLogger::SimpleLogger()
{
	mLastMessage = "";
	mLastWarning = "";
	mLastError = "";

	mLogCounter = 0;
	mMessageCounter = 0;
	mErrorCounter = 0;
	mWarningCounter = 0;

	mPrintLog = true;

	// Clear any old log
	fstream tFile(DEF_DEFAULT_FILE, fstream::out | fstream::trunc);
}

SimpleLogger::~SimpleLogger()
{
	mInstanceFlag = false;
}

void SimpleLogger::logMessage(string iMessage)
{
	mLastMessage = iMessage;

	// Print message if log printing is enabled (on by default)
	if (mPrintLog)
	{
		cout << iMessage << endl;
	}

	// Log to file
	mFile.open(DEF_DEFAULT_FILE, fstream::out | fstream::app);
	mFile << "Log type: Message" << endl;
	mFile << ">>>" << iMessage << endl << endl;
	mFile.close();

	// Increase log counter
	mLogCounter++;
	mMessageCounter++;
}

void SimpleLogger::logError(string iError, int iErrorNum)
{
	mLastError = iError;

	// Print error if log printing is enabled (on by default)
	if (mPrintLog)
	{
		if (iErrorNum != -1)
		{
			cout << "Error #" << iErrorNum << ": " << iError << endl;
		}
		else
		{
			cout << "Error: " << iError << endl;
		}
	}

	// Log to file
	mFile.open(DEF_DEFAULT_FILE, fstream::out | fstream::app);
	mFile << "Log type: Error" << endl;
	mFile << "Error number: " << iErrorNum << endl;
	mFile << ">>>" << iError << endl << endl;
	mFile.close();

	// Increase log counter
	mLogCounter++;
	mErrorCounter++;
}

void SimpleLogger::logWarning(string iWarning, int iWarningNum)
{
	mLastWarning = iWarning;

	// Print warning if log printing is enabled (on by default)
	if (mPrintLog)
	{
		if (iWarningNum != -1)
		{
			cout << "Warning #" << iWarningNum << ": " << iWarning << endl;
		}
		else
		{
			cout << "Warning: " << iWarning << endl;
		}
	}

	// Log to file
	mFile.open(DEF_DEFAULT_FILE, fstream::out | fstream::app);
	mFile << "Log type: Warning" << endl;
	mFile << "Warning number: " << iWarningNum << endl;
	mFile << ">>>" << iWarning << endl << endl;
	mFile.close();

	// Increase log counter
	mLogCounter++;
	mWarningCounter++;
}

string SimpleLogger::getLastMessage(void)
{
	return mLastMessage;
}

string SimpleLogger::getLastError(void)
{
	return mLastError;
}

string SimpleLogger::getLastWarning(void)
{
	return mLastWarning;
}

void SimpleLogger::printLogToDebug(bool iToggle)
{
	mPrintLog = iToggle;
}

unsigned int SimpleLogger::getNumberTotal(void)
{
	return mLogCounter;
}

unsigned int SimpleLogger::getNumberMessages(void)
{
	return mMessageCounter;
}

unsigned int SimpleLogger::getNumberErrors(void)
{
	return mErrorCounter;
}

unsigned int SimpleLogger::getNumberWarnings(void)
{
	return mWarningCounter;
}

SimpleLogger* SimpleLogger::getInstance(void)
{
	if(!mInstanceFlag)
    {
        mSingleton = new SimpleLogger();
        mInstanceFlag = true;
    }
    
	return mSingleton;
}

// Initialize the global logger variable
bool SimpleLogger::mInstanceFlag = false;
SimpleLogger* SimpleLogger::mSingleton = NULL;