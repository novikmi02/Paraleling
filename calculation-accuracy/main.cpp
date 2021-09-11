#include <iostream>
#include <thread>
#include <mutex>
#include <cmath>
#include <vector>

using namespace std;

const long double EPSILON = 1.0 / pow(10.0, 10.0);

long double sin2x(long double x) {
  return sin(x * x);
}

static long double trapezoidalIntegral(
    function<long double (long double)> func,
    long double a,
    long double b,
    int n
  ) {
  long double result = (func(a) + func(b)) / 2;
  long double h = (b - a) / n;

  for (int i = 1; i < n; i += 1) {
    result += func(a + i * h);
  }

  return result * h;
}

static long double getElementIntegralIncrement(long double a, long double i) {
  if (i == 0) {
    return pow(a, 3) / 3;
  }

  return -pow(a, 4) * (4 * i - 1) / (2 * i * (2 * i + 1) * (4 * i + 3));
}

static long double seriesIntegral(long double x) {
  long double i = 0.0;
  long double currentElement = getElementIntegralIncrement(x, i);
  long double previousElement = 0.0;
  long double sum = currentElement;

  while (abs(currentElement - previousElement) > EPSILON) {
    i += 1;
    previousElement = currentElement;
    currentElement *= getElementIntegralIncrement(x, i);
    sum += currentElement;
  }

  return sum;
}

static void runTrapezoidalIntegral(vector<long double> upperBoundOfIntegrationValues) {
  mutex mtx;
  unique_lock<mutex> ul(mtx, defer_lock);

  const long double lowerBoundOfIntegration = 0.0;
  const long double n = 10000;

  cout << "Trapezoidal formula integral:" << endl;
  ul.lock();
  for (long double a: upperBoundOfIntegrationValues) {
    cout << "A = " << a << ": " << trapezoidalIntegral(sin2x, lowerBoundOfIntegration, a, n) << endl; 
  }
  ul.unlock();
}

static void runSeriesIntegral(vector<long double> upperBoundOfIntegrationValues) {
  mutex mtx;
  unique_lock<mutex> ul(mtx, defer_lock);

  cout << "Series formula integral:" << endl;
  ul.lock();
  for (long double a: upperBoundOfIntegrationValues) {
    cout << "A = " << a << ": " << seriesIntegral(a) << endl; 
  }
  ul.unlock();
}

static void singleThreadIntegrals(vector<long double> upperBoundOfIntegrationValues) {
  cout << "Single thread:" << endl;
  runTrapezoidalIntegral(upperBoundOfIntegrationValues);
  runSeriesIntegral(upperBoundOfIntegrationValues);
}

static void multiThreadIntegrals(vector<long double> upperBoundOfIntegrationValues) {
  const int THREADS_COUNT = 2;
  thread t[THREADS_COUNT];

  cout << "Multithread:" << endl;
  t[0] = thread(runTrapezoidalIntegral, upperBoundOfIntegrationValues);
  t[1] = thread(runSeriesIntegral, upperBoundOfIntegrationValues);

  for (int i = 0; i < THREADS_COUNT; i += 1) {
    t[i].join();
  }
}

int main() {
  vector<long double> upperBoundOfIntegrationValues {1, 2, 3, 4, 5, 6};

  singleThreadIntegrals(upperBoundOfIntegrationValues);
  multiThreadIntegrals(upperBoundOfIntegrationValues);

  return 0;
}
