struct name {
  int value1, value2, value3;
  int name::* ptr;
};

int main(int argc, char** argv)
{
  name foo { 1, 2, 3, &name::value2 };
  return foo.*(foo.ptr);
}
