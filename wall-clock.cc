#include <ctime>
#include <iomanip>
#include <chrono>
#include <iostream>
#include <locale>

int main()
{

  using std::cout;

  cout.imbue(std::locale());

  auto now = time(0);
  auto now_tm = std::localtime(&now);

  cout << std::put_time(now_tm, "%Ec") << '\n';

  return 0;
}
