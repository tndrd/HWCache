#include <iostream>

struct page_t
{
  int id_;

  page_t (int id): id_(id) {}
  page_t ():       id_(-1) {}
};

page_t slow_get_page(int id);
std::ostream& operator<< (std::ostream& out, const page_t& page);
std::istream& operator>> (std::istream &in,  page_t& page);