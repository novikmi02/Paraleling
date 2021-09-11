#include <iostream>
#include <thread>
#include <mutex>

#include "Timer.cpp"

using namespace std;

// There is a stadium for 60,000 people (30 sections for 2,000 people).
// At what number of entries (1, 2, 3, 5 or 6) will the stadium fill up the fastest?

static const int STADIUM_SECTIONS_COUNT = 30;
static const int STADIUM_SITTINGS_COUNT = 2000;
static const int MAX_STADIUM_ENTRIES_COUNT = 6;

int** InitStadium(int sectionsCount, int sittingsCount) {
  int** stadium = new int*[sectionsCount];

  for (int i = 0; i < sectionsCount; i += 1) {
    stadium[i] = new int[sittingsCount];
    for (int j = 0; j < sittingsCount; j += 1) {
      stadium[i][j] = 0;
    }
  }

  return stadium;
}

static void PrintStadium(int** stadium, int sectionsCount, int sittingsCount) {
  cout << "================================" << endl;

  for (int i = 0; i < sectionsCount; i += 1) {
    cout << "[" << endl;
    for (int j = 0; j < sittingsCount; j += 1) {
      cout << stadium[i][j] << " ";
    }
    cout << "]" << endl;
  } 

  cout << "================================" << endl;
}

static void FillSections(int** stadium, int sectionsCount, int sittingsCount, int stadiumEntriesCount, int entryIndex) {
  mutex mtx;
  unique_lock<mutex> ul(mtx, defer_lock);

  ul.lock();
  for (int i = entryIndex * (sectionsCount / stadiumEntriesCount); i < entryIndex * (sectionsCount / stadiumEntriesCount) + sectionsCount / stadiumEntriesCount; i += 1) {
    for (int j = 0; j < sittingsCount; j += 1) {
      stadium[i][j] = 1;
    } 
  }
  ul.unlock();
}

static void FillStadium(int** stadium, int sectionsCount, int sittingsCount, int stadiumEntriesCount) {
  thread t[stadiumEntriesCount];

  for (int i = 0; i < stadiumEntriesCount; i += 1) {
    t[i] = thread(FillSections, stadium, sectionsCount, sittingsCount, stadiumEntriesCount, i);
  }

  for (int i = 0; i < stadiumEntriesCount; i += 1) {
    t[i].join();
  }
}

int main() {
  for (int i = 1; i <= MAX_STADIUM_ENTRIES_COUNT; i += 1) {
    if (STADIUM_SECTIONS_COUNT % i != 0) {
      continue;
    }

    Timer timer;
    FillStadium(InitStadium(STADIUM_SECTIONS_COUNT, STADIUM_SITTINGS_COUNT), STADIUM_SECTIONS_COUNT, STADIUM_SITTINGS_COUNT, i);
    cout << "For " << i << " entries count:" << endl;
  }

  return 0;
}

