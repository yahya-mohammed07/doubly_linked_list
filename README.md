# Doubly-linked list

==============

## Introduction

- Doubly-linked list data-structure written in c++ modern with hybrid `smart-pointers and iterators`

## Requirement

- c++20 or later

  - Tested on:
    - g++10 -std=c++2a
    - g++-11 -std=c++2a
    - clang++-11 -std=c++2a
    - clang++-10 `under testing`

### Everything inside `list.hpp`

![Screenshot-20210710172453-551x339](https://user-images.githubusercontent.com/62993724/125166373-12ba0880-e1a4-11eb-8c13-e3d34840db35.png)

![Screenshot-20210710172527-554x338](https://user-images.githubusercontent.com/62993724/125166393-1ea5ca80-e1a4-11eb-8635-9433893cd66b.png)

![Screenshot-20210710172550-478x137](https://user-images.githubusercontent.com/62993724/125166408-26fe0580-e1a4-11eb-8e21-0fe6ab503e18.png)

## Usage

- simply download this library then copy `lib` folder to your working directory then include it like this: `#include "lib/list.hpp"`!

- if you're on ubuntu you can do this:

  - open terminal then do `sudo apt install nautilus-admin` then when it's done do `nautilus -q`
  - open `usr/include` folder as administrator
  - add `lib` folder into `usr/include`, you may rename library into `d_list` after you're done!, this is how you include it without copying it every time into your directory!

  - ```cpp
    #include <lib/list.hpp>
    #include <iostream>

    auto main()
        -> int
    {
      List_<int> nums(1, 2, 3, 5);
      nums.push_at(3, 99);
      nums.print(true, '\n');
    }
    ```
