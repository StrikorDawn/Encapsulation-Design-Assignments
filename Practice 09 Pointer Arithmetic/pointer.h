/*************************************************************
 * 1. Name:
 *      Mark Van Horn & Taden Marston
 * 2. Assignment Name:
 *      Practice 09: Pointer Arithmetic
 * 3. Assignment Description:
 *      Traverse a string using pointer notation
 * 4. What was the hardest part? Be as specific as possible.
 *      -a paragraph or two about how the assignment went for you-
 * 5. How long did it take for you to complete the assignment?
 *      -total time in hours: reading the assignment, submitting, etc.
 **************************************************************/


/**************************************
 * COUNT - ARRAY
 **************************************/
int countArray(char text[], char letter)
{
	int letterCount = 0;

	for (int i = 0; i < strlen(text); i++)
	{
		if (text[i] == letter)
		{
			letterCount++;
		}
	}
	return letterCount;
}

/**************************************
 * COUNT - POINTER
 **************************************/
int countPointer(char text[], char letter)
{
   int count = 0;
   for (char * p = text; *p; p++)
   {
      if (*p == letter)
         count++;
   }
   return count;
}
