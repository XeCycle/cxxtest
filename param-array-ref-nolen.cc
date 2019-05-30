void f(int (&&)[])
{}
void f(int*)
{}
int x = (f(nullptr), 0);
using arr = int[];
int y = (f(arr{1, 2, 3}), 0);
