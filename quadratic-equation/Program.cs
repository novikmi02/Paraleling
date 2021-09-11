using System;
using System.Diagnostics;
using System.Threading.Tasks;

namespace quadratic_equation
{
    class Program
    {
        static void Main(string[] args)
        {
            ConsecutiveExecution();
            MultiThreadingExecution();
        }

        static void MultiThreadingExecution()
        {
            int[][] numbers = NumberGenerator.GenerateNumbersArray();
            
            Stopwatch stopwatch = new Stopwatch();
            
            stopwatch.Start();
            Parallel.For(
                0, 
                numbers.Length, 
                i =>
                {
                    QuadraticEquationSolver quadraticEquationSolver = new QuadraticEquationSolver(
                        numbers[i][0], 
                        numbers[i][1], 
                        numbers[i][2]
                    );
                    quadraticEquationSolver.Solve();
                });
            TimeSpan timeTaken = stopwatch.Elapsed;
            Console.WriteLine("Time taken: " + timeTaken.ToString(@"m\:ss\.fff"));
        }

        static void ConsecutiveExecution()
        {
            int[][] numbers = NumberGenerator.GenerateNumbersArray();
            
            Stopwatch stopwatch = new Stopwatch();
            
            stopwatch.Start();
            for (int i = 0; i < numbers.Length; i += 1)
            {
                QuadraticEquationSolver quadraticEquationSolver = new QuadraticEquationSolver(
                    numbers[i][0], 
                    numbers[i][1], 
                    numbers[i][2]
                );
                quadraticEquationSolver.Solve();
            }
            stopwatch.Stop();

            TimeSpan timeTaken = stopwatch.Elapsed;
            Console.WriteLine("Time taken: " + timeTaken.ToString(@"m\:ss\.fff"));
        }
    }
}