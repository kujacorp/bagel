#include <iostream>
#include <map>
#include <sstream>
#include <string>

using std::cerr;
using std::cin;
using std::cout;
using std::istringstream;
using std::map;
using std::ostringstream;
using std::string;


int to_seconds(const char* mmss) {
  istringstream iss{mmss};
  int mm;
  iss >> mm;
  char colon;
  iss >> colon;
  int ss;
  iss >> ss;
  return 60 * mm + ss;
}

double to_metres(const char* dist) {
  const map<string, double> metres_per_unit{
    {"m", 1},
    {"k", 1'000},
    {"mi", 1'609},
  };

  istringstream iss{dist};
  double number;
  iss >> number;
  string unit;
  iss >> unit;
  return metres_per_unit.at(unit) * number;
}

string lead_with_zero(int num) {
  ostringstream oss;
  if (num < 10) {
    oss << "0";
  }
  oss << num;
  return oss.str();
}

int main(int argc, char** argv) {
  if (argc < 3) {
    cerr << "Need two arguments. Usage: " << argv[0] << " <pace> <distance>\n";
    return 1;
  }

  // Read the pace from argv[1] and the distance from argv[2] and convert them
  // to times for common race distances: 5k, 10k, half marathon, marathon.
  const auto mmss = argv[1];
  const auto dist = argv[2];

  // Split the pace at the colon(:) and read the first value in as minutes and
  // second value as seconds.
  const int seconds = to_seconds(mmss);

  // Split the second value into a number and a unit: (ex: 400m -> 400, "m")
  // and get the number of metres in it.
  const double metres = to_metres(dist);

  // Combine the time and distance to create a pace.
  const double seconds_5k = seconds * (5'000 / metres);
  const int minutes_5k = seconds_5k / 60;
  const int remainder_5k = seconds_5k - (minutes_5k*60);
  cout << "5k:\t" << minutes_5k << ":" << lead_with_zero(remainder_5k) << '\n';

  const double seconds_10k = seconds * (10'000 / metres);
  const int minutes_10k = seconds_10k / 60;
  const int remainder_10k = seconds_10k - (minutes_10k*60);
  cout << "10k:\t" << minutes_10k << ":" << lead_with_zero(remainder_10k) << '\n';

  const double seconds_hm = seconds * (21'100 / metres);
  const int hours_hm = seconds_hm / (60 * 60);
  const int minutes_hm = (seconds_hm - (hours_hm*60*60)) / 60;
  cout << "HM:\t" << hours_hm << ":" << lead_with_zero(minutes_hm) << '\n';

  const double seconds_m = seconds * (42'195 / metres);
  const int hours_m = seconds_m / (60 * 60);
  const int minutes_m = (seconds_m - hours_m * 60 * 60) / 60;
  cout << "M:\t" << hours_m << ":" << lead_with_zero(minutes_m) << '\n';
}
