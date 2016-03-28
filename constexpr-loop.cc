template <class ...T>
constexpr int sum(T ...num)
{                                                                         
  int s = 0;                          
  using noop = int[];                                                     
  (void) noop { (s+=num, 0)... };
  return s;                            
}                                                                          

int main()
{

  return sum(1, 2, 3);

}
