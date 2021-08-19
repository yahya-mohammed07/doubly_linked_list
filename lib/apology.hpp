#ifndef APOLOGY_HPP
#define APOLOGY_HPP

#include <unordered_map>
#include <string_view>
#include <cassert>
#include <iostream>


enum class Apology {
  empty = 1,
  not_found = 2,
  invalid_position = 3,
};

inline
const std::unordered_map<Apology, std::string_view>
  Apologies =
{
  { Apology::empty, "- Apology: List is empty...\n" },
  { Apology::not_found, "- Apology: Node not found...\n" },
  { Apology::invalid_position, " -Apology: Invalid position...\n"}
};

inline
auto get_apology(const Apology& apology)
    -> void
{
  if ( apology == Apology::empty ) {
    std::cerr << Apologies.at( Apology::empty );
    assert(false);
  } else if (apology == Apology::invalid_position) {
    std::cerr << Apologies.at( Apology::invalid_position );
    assert(false);
  }
  std::cerr << Apologies.at( Apology::not_found );
  assert(false);
}

#endif // APOLOGY_HPP
