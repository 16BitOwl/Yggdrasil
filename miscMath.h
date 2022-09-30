/*! 
* \file miscMath.h
*
* \brief Header file for the MiscMath class
*
* The MiscMath class is mostly used for useful functions that don't fit with the other classes, such as min/max, clamp....
*
* \author Dennis Fredriksson
* \date 2014-09-01
*/
#pragma once

/*!
* \def miscMath
* \brief Used to access the MiscMath class singleton in an easier fashion. Default usage is still valid
*/
#define miscMath MiscMath::getInstance()

/*!
* \def M_PI
* \brief Definition of the number PI
*/
#define M_PI 3.14159265359

/*!
* \def M_EPSILON
* \brief Definition of a floating point epsilon
*/
#define M_EPSILON 0.00001f

/*!
* \def M_EPSILONSQUARED
* \brief Definition of a squared floating point epsilon
*/
#define M_EPSILONSQUARED 0.00001f * 0.00001f

/*!
* \class MiscMath
*
* \brief MiscMath class, contains useful math functions that won't fit any other class
*
* \author Dennis Fredriksson
*/
class MiscMath
{
private:
	/*! 
	* \var static bool mInstanceFlag
    * \brief Singleton instance flag
	* \private
	*/
	static bool mInstanceFlag;

	/*! 
	* \var static MiscMath* mSingleton
    * \brief Singleton class pointer
	* \private
	*/
	static MiscMath* mSingleton;

	/*!
	* \brief MiscMath class constructor
	* \private
	*/
	MiscMath();

public:
	/*!
	* \fn static MiscMath* getInstance(void)
	* \brief Returns an instance of the class singleton
	*
	* \retval static MiscMath*
	*/
	static MiscMath* getInstance(void);

	/*!
	* \brief MiscMath class deconstructor
	*/
	~MiscMath();

	/*!
	* \brief Clips a value if it is outside a defined range
	*
	* \param[const T&] The value to clamp
	* \param[const T&] Lowest allowed value
	* \param[const T&] Highest allowed value
	*/
	template<typename T> T clamp(const T& iValue, const T& iLow, const T& iHigh) { return iValue < iLow ? iLow : (iValue > iHigh ? iHigh : iValue); }

	/*!
	* \brief Wraps a value if it is outside a defined range
	*
	* \param[const T&] The value to clamp
	* \param[const T&] Lowest allowed value
	* \param[const T&] Highest allowed value
	*/
	template<typename T> T wrap(const T& iValue, const T& iLow, const T& iHigh) { return iValue < iLow ? iHigh : (iValue > iHigh ? iLow : iValue); }

	/*!
	* \brief Checks if a value is smaller than another value
	*
	* \param[const T&] The value to clamp
	* \param[const T&] Lowest allowed value
	*/
	template<typename T> T minimum(const T& iValue, const T& iLow) { return iValue < iLow ? iLow : iValue; }

	/*!
	* \brief Checks if a value is larger than another value
	*
	* \param[const T&] The value to clamp
	* \param[const T&] Highest allowed value
	*/
	template<typename T> T maximum(const T& iValue, const T& iHigh) { return iValue > iHigh ? iHigh : iValue; }

	template<typename T> void swap(T& iValue1, T& iValue2);
};