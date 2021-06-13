#include "../lib/list.hpp"

auto main() -> int {
  List_<int> nums(1, 2, 3, 4, 5, 5, 1, 2, 3);

  //nums.pop_duplicates();
  nums.pop_value(2);
  nums.print(true, '\n');
  //
  List_<int> list1(1, 2, 3, 4, 5, 5, 1, 2, 3);
  List_<int> list2(2, 2, 2, 2, 2, 2, 2, 2, 2);
  if ( list1.size() == list2.size() ) {
    for ( auto it = list1.begin(), it2 = list2.begin();
              it != list1.end(); ++it, ++it2 )
    {
      MYSWAP(*it, *it2);
    }
  }
  list1.print(true, '\n');
  list2.print(true, '\n');
  //
  std::cin.get();
}
