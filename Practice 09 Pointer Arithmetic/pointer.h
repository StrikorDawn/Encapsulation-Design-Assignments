/*************************************************************
 * 1. Name:
 *      Mark Van Horn & Taden Marston
 * 2. Assignment Name:
 *      Practice 09: Pointer Arithmetic
 * 3. Assignment Description:
 *      Traverse a string using pointer notation
 * 4. What was the hardest part? Be as specific as possible.
 *      The hardest part was figuring out exactly how to write
 *      the countPointer function, but a quick review of the reading
 *      solved that problem very easily.
 * 5. How long did it take for you to complete the assignment?
 *      30 minutes.
 **************************************************************/


/**************************************
 * COUNT - ARRAY
 **************************************/
int countArray(char text[], char letter)
{
   int count = 0;
   for (int i = 0; i < strlen(text); i++)
   {
      if (text[i] == letter)
         count++;
   }
   return count;
}

/**************************************
 * COUNT - POINTER
 **************************************/
int countPointer(char text[], char letter)
{
   int count = 0;
   for (char* p = text; *p; p++)
   {
      if (*p == letter)
         count++;
   }
   return count;
}
