
int yy = 0;

auto func(int x)->decltype(yy)
{
    auto y = x;
    return y;
}

int main()
{
    return 0;
}