using System;

namespace quadratic_equation
{
    public class QuadraticEquationSolver
    {
        private double a;
        private double b;
        private double c;
        
        public QuadraticEquationSolver(double a, double b, double c)
        {
            this.a = a;
            this.b = b;
            this.c = c;
        }

        public void Solve()
        {
            double discriminate = GetDescriminate();
            
            if (discriminate >= 0)
            {
                (double, double) realSolutions = GetRealSolutions(discriminate);
                // Console.WriteLine(realSolutions.Item1 + ", " + realSolutions.Item2);
            }
            else
            {
                (double, double, double) imaginarySolutions =  GetImaginarySolutions(discriminate);
                // Console.WriteLine(imaginarySolutions.Item1 + " + " + imaginarySolutions.Item2 + " * i, " + imaginarySolutions.Item1 + " + " + imaginarySolutions.Item3 + " * i ");
            }
        }

        private (double, double) GetRealSolutions(double discriminate)
        {
            double x1 = (-b + Math.Sqrt(discriminate)) / 2 * a;
            double x2 = (-b - Math.Sqrt(discriminate)) / 2 * a;

            return (x1, x2);
        }

        private (double, double, double) GetImaginarySolutions(double discriminate)
        {
            double x1 = -b / (2 * a);
            discriminate = -discriminate ;
            double x2 = Math.Sqrt(discriminate) / (2 * a);
            double x3 = -Math.Sqrt(discriminate) / (2 * a);

            return (x1, x2, x3);
        }

        private double GetDescriminate()
        {
            return Math.Pow(b, 2) - 4 * a * c;
        }
    }
}