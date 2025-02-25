/*************************************************************
 * 1. Name:
 *      Taden Marston & Mark Van Horn
 * 2. Assignment Name:
 *      Practice 08: Allocation
 * 3. Assignment Description:
 *      Allocate an array and then use it
 * 4. What was the hardest part? Be as specific as possible.
 *			The hardest part was remembering how that we needed to pass
 *			in the pointers as references for test cases deleteArrayDouble_1,
 *			deleteArrayDouble_4, and deleteOneFloat. We after racking 
 *			our brains for 15 minuets without understanding what was wrong
 *			we asked copilot to help us understand what we were missing
 *			and it told us we needed to pass the pointers by reference.
 *			That fixed our code and helped us pass all of the test cases.
 * 5. How long did it take for you to complete the assignment?
 *      This assignment took us 35 minuets.
 **************************************************************/

 /****************************
  * ALLOCATE ONE FLOAT
  ****************************/
inline float* allocateOneFloat(float pointer)
{
	float* p = new float(pointer);
	return p;
}


/****************************
 * ALLOCATE ARRAY of DOUBLEs
 ****************************/
inline double* allocateArrayDouble(int arraySize) 
{
	if (arraySize <= 0) 
	{
		return nullptr;
	}
	else
	{
		double* p = new double[arraySize];
		return p;
	}
}

/****************************
 * DELETE ONE FLOAT
 ****************************/
inline void deleteOneFloat(float*& p) 
{
	if (p != nullptr) 
	{
		delete p;
		p = nullptr;
	}
}

/****************************
 * DELETE ARRAY of DOUBLEs
 ****************************/
inline void deleteArrayDouble(double*& p)
{
	if (p != nullptr)
	{
		delete[] p;
		p = nullptr;
	}
}