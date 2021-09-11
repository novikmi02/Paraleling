using System;
using System.Collections.Generic;

namespace quadratic_equation
{
    public class NumberGenerator
    {
        private const int MinValue = 1;
        private const int MaxValue = 100;
        private const int ArrayCount = 10000000;
        private const int NumbersInArrayCount = 3;
        
        public static int[][] GenerateNumbersArray()
        {
            Random randNum = new Random();
            List<int[]> result = new List<int[]>();
            
            for (int i = 0; i < ArrayCount; i += 1)
            {
                List<int> numbersList = new List<int>();
                for (int j = 0; j < NumbersInArrayCount; j += 1)
                {
                    numbersList.Add(randNum.Next(MinValue, MaxValue));
                }
                result.Add(numbersList.ToArray());
            }

            return result.ToArray();
        }
    }
}