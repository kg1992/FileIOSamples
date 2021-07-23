#include <iostream>
#include <algorithm>

int main()
{
    std::cout << "press ctrl+z to stop." << std::endl;
    std::copy(
        std::istreambuf_iterator<char>(std::cin), 
        std::istreambuf_iterator<char>(),
        std::ostreambuf_iterator<char>(std::cout)
        );
    return 0;
}