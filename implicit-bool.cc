bool implicit_bool(bool);

struct explicit_bool {
  explicit operator bool() const
  {
    return true;
  }
};

int main(int argc, char *argv[])
{
  decltype(implicit_bool(explicit_bool())) x;
  return 0;
}
