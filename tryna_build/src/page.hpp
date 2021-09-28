#pragma once

struct page_t
{
  int id_;

  page_t (int id): id_(id) {}
  page_t ():       id_(-1) {}
};

page_t slow_get_page(int id) // Maybe the return value should be page_t&, but idk how to properly implement dynamically created structs (also refs to stack values shouldn't be returned) 
{
    return { id };
}

std::ostream& operator<< (std::ostream& out, const page_t& page)
{
  out << page.id_;
  return out;
}

std::istream& operator>> (std::istream &in,  page_t& page)
{
    in >> page.id_;
    return in;
}