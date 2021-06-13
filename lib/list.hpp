/**
* @file list.hpp
* @author yahya mohammed ( goldroger.1993@outlook.com )
* @brief a double linked list with modern c++
* @date 2021-06-02 ("date started")
*/

#ifndef LIST_HPP
#define LIST_HPP

#define XORSWAP(a, b) ((a) ^= (b), (b) ^= (a), (a) ^= (b))
#define MYSWAP(a, b) (&(a) == &b) ? a : XORSWAP(a, b)

#include <initializer_list>
#include <iostream>
#include <memory>


constexpr auto empty_list = []() -> void {
  std::cerr << "- list is empty...";
};

template <typename T>
class List_
{
  class Node {
  public:
    T m_data = {};
    std::shared_ptr<Node> m_next = {nullptr};
    std::shared_ptr<Node> m_prev = {nullptr};
  }; // end of class Node

private:

  using sh_ptr = std::shared_ptr<Node>;
  constexpr sh_ptr allocate_node() const noexcept { return std::make_shared<Node>(); }

  sh_ptr      m_head = {nullptr};
  sh_ptr      m_tail = {nullptr};
  std::size_t m_size = {};

protected:
  T _failed_ = {};

private:

  class iterator {
  private:
    sh_ptr node_ptr {nullptr};
  public:
    constexpr iterator(const sh_ptr& newPtr)  : node_ptr(newPtr) {}
    constexpr iterator(sh_ptr&& newPtr)  : node_ptr(newPtr) {}
    constexpr iterator(const std::nullptr_t newPtr) : node_ptr(newPtr) {}
    //
    constexpr bool operator!=(const iterator& itr) const {
      return node_ptr != itr.node_ptr;
    }
    //
    constexpr T& operator*() const {
      return node_ptr->m_data;
    }
    // pre increment
    constexpr iterator operator++() {
      node_ptr = node_ptr->m_next;
      return *this;
    }
    // pre increment
    constexpr iterator operator--() {
      node_ptr = node_ptr->m_prev;
      return *this;
    }
    // post increment
    constexpr iterator operator++(int) {
      node_ptr = node_ptr->m_next;
      return *this;
    }
  }; // end of class iterator

public:

  [[nodiscard]] constexpr auto begin()  const noexcept -> iterator { return iterator(m_head); }
  [[nodiscard]] constexpr auto end()    const noexcept -> iterator { return iterator(nullptr); }
  [[nodiscard]] constexpr auto begin() noexcept -> iterator { return iterator(m_head); }
  [[nodiscard]] constexpr auto end()   noexcept -> iterator { return iterator(nullptr); }
  //
  [[nodiscard]] constexpr auto rbegin()  const noexcept -> iterator { return iterator(m_tail); }
  [[nodiscard]] constexpr auto rend()    const noexcept -> iterator { return iterator(m_head->m_prev); }
  [[nodiscard]] constexpr auto rbegin()  noexcept -> iterator { return iterator(m_tail); }
  [[nodiscard]] constexpr auto rend()    noexcept -> iterator { return iterator(m_head->m_prev); }
  /* constructors */
  List_() noexcept = default;
  //
  explicit constexpr List_(List_<T> && lh) noexcept
    : m_head(nullptr), m_tail(nullptr), m_size(0) {
    m_head = lh.m_head;
    m_tail = lh.m_tail;
    m_size = lh.m_size;
    //
    lh.m_tail.reset();
    lh.m_head.reset();
    lh.m_size = {};
  }
  //
  explicit constexpr List_(const List_<T>& lh) noexcept {
    m_head = lh.m_head;
    m_tail = lh.m_tail;
    m_size = lh.m_size;
  }

  //
  template<typename ...args>
  explicit constexpr List_(const args& ...arg) {
    (push_back(arg),...);
  }

  //
  template<typename ...args>
  explicit constexpr List_(args&& ...arg) {
    (push_back(arg),...);
  }

  //
  explicit constexpr List_(std::initializer_list<T> &&arg) {
    for (auto &&i : arg) { push_back(i); }
  }

  //
  explicit constexpr List_(const std::initializer_list<T> &arg) {
    for (const auto &i : arg) { push_back(i); }
  }

  //
  constexpr List_<T>& operator=(const List_<T>& lh) noexcept {
    if (this != &lh) {
      m_head = lh.m_head;
      m_tail = lh.m_tail;
      m_size = lh.m_size;
    }
    return *this;
  }

  //
  constexpr List_<T>& operator=(List_<T>&& lh) noexcept {
    if (this != &lh) {
      m_head = lh.m_head;
      m_tail = lh.m_tail;
      m_size = lh.m_size;
      //
      lh.m_tail = {nullptr};
      lh.m_head = {nullptr};
      lh.m_size = {};
    }
    return *this;
  }

  /*@ methods: */
  /**
  * @brief check if list is empty
  * @complexity O(1)
  * @return true
  * @return false
  */
  [[nodiscard]] constexpr inline auto is_empty()
      const noexcept -> bool
  {
    return m_head == nullptr ? true : false;
  }

  /**
  * @brief returns size of the list
  * @complexity O(1)
  * @return std::size_t
  */
  [[nodiscard]]
  constexpr inline
  auto size() const noexcept 
      -> std::size_t { return m_size; }

  /**
  * @brief returns first element
  * @complexity O(1)
  * @return T&
  */
  [[nodiscard]]
  constexpr inline
  auto front()
      -> T &
  {
    if (is_empty()) [[unlikely]] { empty_list(); return _failed_; }
    return m_head->m_data;
  }

  /**
  * @brief return last element&
  * @complexity O(1)
  * @return T&
  */
  [[nodiscard]]
  constexpr inline
  auto back()
      -> T &
  {
    if (is_empty()) [[unlikely]] { empty_list(); return _failed_;}
    return m_tail->m_data;
  }

  /**
  * @brief return last element&
  * @complexity O(1)
  * @return T&
  */
  [[nodiscard]]
  constexpr inline
  auto back() const
      -> T
  {
    if (is_empty()) [[unlikely]] { empty_list(); return _failed_;}
    return m_tail->m_data;
  }

  //
  constexpr
  auto print(const bool order = true, const char delimiter = ' ')
      const -> void
  {
    if (is_empty()) [[unlikely]]  { empty_list(); return; }
    if ( order ) {
      for ( auto&& i : *this ) { std::cout << i << ' '; }
      std::cout << delimiter;
      return;
    }
    for ( auto i = rbegin(); i != rend(); --i ) {
      std::cout << *i << ' ';
    }
    std::cout << delimiter;
  }

  /**
  * @brief return element at given position&
  * @complexity O(n)
  * @param times
  * @return auto&
  */
  [[nodiscard]]
  constexpr 
  auto at(const T& times)
      -> auto &
  {
    if (is_empty()) [[unlikely]]      { empty_list(); return _failed_;}
    if (times < 0 || times >= size()) { empty_list(); return _failed_;}
    auto it = begin();
    for (T i = 0; i < times; ++i) { ++it; }
    return (*it);
  }

  [[nodiscard]]
  constexpr 
  auto at(const T& times) const
      -> auto
  {
    if (is_empty()) [[unlikely]]      { empty_list(); return _failed_;}
    if (times < 0 || times >= size()) { empty_list(); return _failed_;}
    auto it = begin();
    for (T i = 0; i < times; ++i) { ++it; }
    return (*it);
  }

  [[nodiscard]]
  constexpr inline
  auto at(const sh_ptr& ptr)
      const -> auto &
  {
    return ptr->m_data;
  }

  /**
  * @brief add element at end of list
  * @complexity O(1)
  * @param arg
  */
  constexpr
  auto push_back(T &&arg)
      -> void
  {
    sh_ptr new_node   = allocate_node();
    new_node->m_data  = arg;
    new_node->m_next  = nullptr;
    //
    if ( is_empty() ) [[unlikely]] {
      m_head = new_node; // |null,arg, null|
      m_tail = new_node; // |null,arg, null|
    }
    m_tail->m_next = new_node; // changes head-> next too, then it changes
    // the previous temps next
    // head ->|null,0, 0x1| <-> |0x77,1, 0x3| <-> |0x88,2, null|
    new_node->m_prev = m_tail;
    m_tail = new_node; // now tail points to temp
    //
    if ( m_head->m_prev != nullptr ) {
      m_head->m_prev = nullptr;
    }
    //
    ++m_size;
  }

  /**
  * @brief add element at end of list
  * @complexity O(1)
  * @param arg
  */
  constexpr
  auto push_back(const T &arg)
      -> void
  {
    sh_ptr new_node   = allocate_node();
    new_node->m_data  = arg;
    new_node->m_next  = nullptr;
    //
    if ( is_empty() ) [[unlikely]] {
      m_head = new_node; // |null,arg, null|
      m_tail = new_node; // |null,arg, null|
    }
    m_tail->m_next = new_node; // changes head-> next too, then it changes
    // the previous temps next
    // head ->|null,0, 0x1| <-> |0x77,1, 0x3| <-> |0x88,2, null|
    new_node->m_prev = m_tail;
    m_tail = new_node; // now tail points to temp
    //
    if ( m_head->m_prev != nullptr ) {
      m_head->m_prev = nullptr;
    }
    //
    ++m_size;
  }

  //
  template<typename ...args>
  inline constexpr auto push_back(const args&...arg)
      -> void
  {
    (push_back(arg),...);
  }

  /**
  * @brief add element at the beginning of list
  * @complexity O(1)
  * @param arg
  */
  inline constexpr 
  auto push_front(const T &arg) 
      -> void
  {
    sh_ptr old_head   = allocate_node();
    m_head->m_prev    = old_head; // linking head to old head // head -> |old head, arg, next|
    //
    old_head->m_data  = arg;
    old_head->m_next  = m_head;
    m_head = old_head; // m_head is new_head now
    m_head->m_prev    = nullptr;
    //
    ++m_size;
  }

  /**
  * @brief add element at the beginning of list
  * @complexity O(1)
  * @param arg
  */
  inline constexpr
  auto push_front(T &&arg)
      -> void
  {
    sh_ptr old_head   = allocate_node();
    m_head->m_prev    = old_head; // linking head to old head // head -> |old head, arg, next|
    //
    old_head->m_data  = arg;
    old_head->m_next  = m_head;
    m_head = old_head; // m_head is new_head now
    m_head->m_prev    = nullptr;
    //
    ++m_size;
  }

  //
  inline constexpr
  auto push_front(const auto& ...arg)
      -> void
  {
    (push_front(arg), ...);
  }

  /**
  * @brief add element at given position
  * @complexity O(n)
  * @param pos
  * @param arg
  */
  constexpr
  auto push_at(const std::size_t pos, const T &arg)
      -> void
  {
    if (is_empty())  [[unlikely]]     { empty_list(); return; }
    if (pos == 0)                     { push_front(arg); }
    if (pos == size()-1)              { push_back(arg); }
    /* adding nodes between previous and next */
    sh_ptr prev_node  = allocate_node(); // hold previous node
    sh_ptr new_node   = allocate_node(); // hold new node
    sh_ptr next_node  = m_head; // points to next node
    //
    for (std::size_t i = 0; i < pos; ++i) {
      prev_node = next_node;
      next_node = next_node->m_next;
    }
    new_node->m_data  = arg;
    /// @link:
    prev_node->m_next = new_node;
    new_node->m_next  = next_node;

    new_node->m_prev  = prev_node;
    next_node->m_prev = new_node;
    //
    ++m_size;
  }

  constexpr
  auto push_at(const std::size_t pos, T &&arg)
      -> void
  {
    if (is_empty()) [[unlikely]]  { empty_list(); return; }
    if (pos == 0)                 { push_front(arg); }
    if (pos == size()-1)          { push_back(arg); }
    /* adding nodes between previous and next */
    sh_ptr prev_node  = allocate_node(); // hold previous node
    sh_ptr new_node   = allocate_node(); // hold new node
    sh_ptr next_node  = m_head; // points to next node
    //
    for (std::size_t i = 0; i < pos; ++i) {
      prev_node = next_node;
      next_node = next_node->m_next;
    }
    new_node->m_data    = arg;
    /// @link:
    prev_node->m_next = new_node;
    new_node->m_next  = next_node;

    new_node->m_prev  = prev_node;
    next_node->m_prev = new_node;
    //
    ++m_size;
  }

  /**
  * @brief add element at after given position
  * @complexity O(n)
  * @param pos
  * @param arg
  */
  constexpr 
  auto push_after_node(const std::size_t pos, const T &arg)
      -> void
  {
    if (is_empty())  [[unlikely]]     { empty_list(); return; }
    if (pos == 0)                     { push_front(arg); }
    if (pos == size()-1)              { push_back(arg); }
    /* adding nodes between previous and next */
    sh_ptr prev_node  = allocate_node(); // hold previous node
    sh_ptr new_node   = allocate_node(); // hold new node
    sh_ptr next_node  = m_head; // points to next node
    //
    for (std::size_t i = 0; i < pos+1; ++i) {
      prev_node = next_node;
      next_node = next_node->m_next;
    }
    new_node->m_data  = arg;
    /// @link:
    prev_node->m_next = new_node;
    new_node->m_next  = next_node;

    new_node->m_prev  = prev_node;
    next_node->m_prev = new_node;
    //
    ++m_size;
  }

  /**
  * @brief add element at after given position
  * @complexity O(n)
  * @param pos
  * @param arg
  */
  constexpr
  auto push_after_node(const std::size_t pos,  T &&arg)
      -> void
  {
    if (is_empty())  [[unlikely]]     { empty_list(); return; }
    if (pos == 0)                     { push_front(arg); }
    if (pos == size()-1)              { push_back(arg); }
    /* adding nodes between previous and next */
    sh_ptr prev_node  = allocate_node(); // hold previous node
    sh_ptr new_node   = allocate_node(); // hold new node
    sh_ptr next_node  = m_head; // points to next node
    //
    for (std::size_t i = 0; i < pos+1; ++i) {
      prev_node = next_node;
      next_node = next_node->m_next;
    }
    new_node->m_data  = arg;
    /// @link:
    prev_node->m_next = new_node;
    new_node->m_next  = next_node;

    new_node->m_prev  = prev_node;
    next_node->m_prev = new_node;
    //
    ++m_size;
  }

  /**
  * @brief adds value after specific location
  * @param after : the value you want add value after it
  * @param val : the value
  */
  [[deprecated]]
  constexpr
  auto push_after(const T& after, const T& val) 
      -> void
  {
    if (is_empty()) { empty_list(); return;}
    if (after == at(m_tail)) { push_back(val); }
    sh_ptr it = {m_head};
    for(; at(it) != after; it = it->m_next) {}
    if (!it->m_next) { std::cerr << "- `pos` not found..."; return;}
    //
    sh_ptr new_node = allocate_node();
    new_node->m_data = val; // add data to new_node
    /// @link:
    new_node->m_next = it->m_next; // new_node's next now points at what it's next it
    it->m_next = new_node; // it's next points to new_node
    //
    ++m_size;
  }

  constexpr
  auto pop_value(T&& val)
      -> void
  {
    if ( is_empty() ) { empty_list(); return; }
    //
    auto it = begin();
    std::size_t count {0};
    //
    while ( it != end() ) {
      if ( *it == val ) {
        pop_at(count);
        count = 0;
      }
      ++count;
      ++it;
    }
  }


  [[deprecated]]
  constexpr auto 
  push_after(T&& after, T&& val)
      -> void
  {
    if (is_empty()) [[unlikely]] { empty_list(); return;}
    if (after == at(m_tail)) { push_back(val); }
    sh_ptr it = {m_head};
    for(; it->m_next != nullptr && at(it) != after; it = it->m_next) {}
    if (!it->m_next) { std::cerr << "- `pos` not found..."; return;}
    //
    sh_ptr new_node = allocate_node();
    new_node->m_data = val; // add data to new_node
    new_node->m_next = it->m_next; // new_node's next now points at what it's next it
    it->m_next = new_node; // it's next points to new_node
    //
    ++m_size;
  }

  /**
  * @brief remove last element
  * @complexity O(n)
  */
  auto pop_back()
      -> void
  {
    if (is_empty()) [[unlikely]] { empty_list(); return; }
    if (size() == 1)             { m_head.reset(); return; } // if one node created
    //
    sh_ptr last   = m_tail;
    sh_ptr temp = last->m_prev->m_prev;
    //
    m_tail = m_tail->m_prev; // old tail = prev of tail
    m_tail->m_next = nullptr; // new tails next = null;
    m_tail->m_prev = temp; // new tails prev = last->prev->prev

    last.reset();
    --m_size;
  }

  /**
  * @brief remove first element
  * @complexity O(1)
  */
  auto pop_front() 
      -> void
  {
    if (is_empty()) [[unlikely]]  { empty_list(); return; }
    if (size() == 1)              { m_head.reset(); return; } // if one node created
    //
    sh_ptr first  = {m_head}; // first points to old head
    m_head        = m_head->m_next; // head points to one step ahead of old head
    m_head->m_prev = nullptr;
    //
    --m_size;
    first.reset();
  }

  /**
  * @brief remove element at given position
  * @complexity O(n)
  */
  auto pop_at(const std::size_t pos)
      -> void
  {
    const std::size_t s = size();
    if (pos < 0 || pos >= s)      { empty_list(); return; }
    if (is_empty()) [[unlikely]]  { empty_list(); return; }
    if (pos == 0)                 { pop_front(); return; }
    else if ( pos == s-1)         { pop_back(); return; }
    //
    sh_ptr prev = allocate_node();
    sh_ptr next = m_head;
    // ex: 0, 1, 2, 3, 4, 5 : pop_at(1) now:
    sh_ptr mid   = m_head;
    for (std::size_t i = 0; i < pos && next != nullptr; ++i) {
      prev  = mid;                 // 0
      next  = mid->m_next->m_next; // 2
      mid    = mid->m_next;         // 1
    }
    prev->m_next = next; // 0 -> 2 -> 3 -> 4 -> 5 and whatever was node 1, is now gone
    next->m_prev = prev;
    --m_size;
    //
    mid = nullptr; // 1 -> nullptr
  }

  /**
  * @brief remove element at given position
  * @complexity O(n)
  */
  auto pop_at(std::size_t&& pos)
      -> void
  {
    const std::size_t s = size();
    if (pos < 0 || pos >= s)      { empty_list(); return; }
    if (is_empty()) [[unlikely]]  { empty_list(); return; }
    if (pos == 0)                 { pop_front(); return; }
    else if ( pos == s-1)         { pop_back(); return; }
    //
    sh_ptr prev = allocate_node();
    sh_ptr next = m_head;
    // ex: 0, 1, 2, 3, 4, 5 : pop_at(1) now:
    sh_ptr mid   = m_head;
    for (std::size_t i = 0; i < pos && next != nullptr; ++i) {
      prev  = mid;                 // 0
      next  = mid->m_next->m_next; // 2
      mid    = mid->m_next;         // 1
    }
    prev->m_next = next; // 0 -> 2 -> 3 -> 4 -> 5 and whatever was node 1, is now gone
    next->m_prev = prev;
    --m_size;
    //
    mid = nullptr; // 1 -> nullptr
  }

  constexpr
  auto pop_duplicates()
      -> void
  {
    sort();
    if (is_empty()) { empty_list(); return; }
    //
    sh_ptr it = m_head;
    while( it->m_next != nullptr ) {
      if ( at(it) == at(it->m_next) ) {
        MYSWAP(at(it), back());
      }
      pop_back();
      it = it->m_next;
    }
  }

  /**
  * @brief splitiing the current list into two lists
  * @complexity O(n)
  * @param l1
  * @param l2
  */
  auto split(List_<T> &l1, List_<T> &l2) -> void // note: not tes
  {
    if (is_empty()) [[unlikely]] { empty_list(); return; }
    const auto& s   = size();
    sh_ptr      it  = { m_head };
    for (std::size_t i = 0; i < (s/2); ++i, it = it->m_next) {
      l1.push_back( at(it) );
    }
    for ( std::size_t i = (s/2); i < s; ++i , it = it->m_next) {
      l2.push_back( at(it) );
    }
  }

  /**
  * @brief merges two lists into one
  * @complexity O(n)
  * @param l1
  * @param l2
  */
  auto merge( List_<T>& l1,  List_<T>& l2) -> void // note: not tested
  {
    if (l1.is_empty()) [[unlikely]] { empty_list(); return; }
    if (l2.is_empty()) [[unlikely]] { empty_list(); return; }
    for ( const auto& i : l1 ) { push_back(i); }
    for ( const auto& i : l2 ) { push_back(i); }
  }

  /**
  * @brief: sorts element in ASC order by default put `true` for DESC
  * @complexity  O(n^2)
  */
  constexpr
  auto sort(const bool desc = false) const 
      -> void
  {
    if (is_empty()) { empty_list(); return; }
    bool sorted   = true;
    sh_ptr curr   = {};
    sh_ptr next   = {};
    //
    if ( !desc ) [[likely]] {
      while ( sorted ) {
        sorted   = false;
        curr     = m_head;
        while ( curr->m_next != nullptr ) {
          next = curr->m_next;
          if ( at(curr) > at(next) ) {
            MYSWAP(at(next), at(curr));
            sorted = true;
          }
          curr = curr->m_next;
        }
      }
    } else {
      while ( sorted ) {
        sorted   = false;
        curr     = {m_head};
        while (curr->m_next != nullptr) {
          next = curr->m_next;
          if ( at(curr) < at(next) ) {
            MYSWAP(at(curr), at(next));
            sorted = true;
          }
          curr = curr->m_next;
        }
      }
    }
  }

  /**
  * @brief check if the list is sorted ASC
  * @complexity O(n)
  */
  [[nodiscard]]
  constexpr
  auto is_sorted() const 
      -> bool
  {
    if ( is_empty() ) [[unlikely]] { empty_list(); return -1; }
    bool check  = false;
    sh_ptr it   = {m_head};
    while ( it->m_next != nullptr ) {
      if ( at(it->m_next) >= at(it) ) { check = true; }
      else {
        check = false;
        break;
      }
      it = it->m_next;
    }
    return check;
  }

  /**
  * @brief search for a value
  * @complexity O(n)
  * @param target
  */
  [[nodiscard]]
  constexpr
  auto search(const T & target) const 
      -> bool
  {
    if (is_empty()) [[unlikely]] { empty_list(); return -1; }
    for (const auto& i : *this) {
      if ( i == target ) { return true; }
    }
    return false;
  }

  /**
  * @brief returns the location of that node containing target, count from the right to left
  * @complexity O(n)
  * @param target
  * @return std::int64_t
  */
  [[nodiscard]] 
  constexpr
  auto locate(const T& target) const 
      -> std::int64_t
  {
    if (is_empty()) [[unlikely]] { empty_list(); return -1; }
    for (std::size_t j = 0; const auto& i : *this ) {
      if ( i == target ) { return static_cast<std::int64_t>(j); }
      ++j;
    }
    return -1;
  }

  /**
  * @brief erases the list
  * @complexity O(n)
  */
  auto clear() -> void
  {
    if (is_empty()) [[unlikely]] { empty_list(); return; }
    sh_ptr it = m_head;
    sh_ptr temp     = {};
    while ( it != nullptr ) {
      temp = it->m_next;
      it = nullptr;
      it = temp;
    }
    m_head.reset();
    m_tail.reset();
    it.reset();
    m_size = {};
  }
}; // end of class List_<T>

#endif // LIST_HPP
