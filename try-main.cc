int main(int argc, char *argv[]) try
{
  throw 1;
  return 0;
} catch(...) {
  throw;
}
