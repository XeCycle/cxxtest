int main(){ using p_t=void(*)(int*); auto l = [&](int*){ }; p_t p = l; }
