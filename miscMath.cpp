#include "miscMath.h"

MiscMath::MiscMath()
{
}

MiscMath::~MiscMath()
{
	mInstanceFlag = false;
}

MiscMath* MiscMath::getInstance(void)
{
	if(!mInstanceFlag)
	{
		mSingleton = new MiscMath();
		mInstanceFlag = true;
		return mSingleton;
	}
	else
	{
		return mSingleton;
	}
}

template<typename T> void MiscMath::swap(T& iValue1, T& iValue2)
{
	T temp = iValue1;
	iValue1 = iValue2;
	iValue2 = temp;
}

// Initialize the global singleton variable
bool MiscMath::mInstanceFlag = false;
MiscMath* MiscMath::mSingleton = 0;