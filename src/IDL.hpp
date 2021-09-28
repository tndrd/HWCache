#ifndef __IDL_H__
#define __IDL_H__

#include "caches.hpp"

namespace Caches
{ 
  template <typename T, typename KeyT = int>
  struct Ideal_cache_t
  {
    private:
    // Cache size should be const to prevent the cache to be resized. It will stay this way until we define cache resizing principles
    const size_t sz_;
    
    struct cache_item_t
    {
      T item_;
      cache_item_t(T item): item_(item) {};
    };

    std::list<cache_item_t> cache_;
    
    using ListIt    = ListIt_t<cache_item_t>;
    using cListIt   = cListIt_t<cache_item_t>;
    using VectorIt  = VectorIt_t<KeyT>;
    using cVectorIt = cVectorIt_t<KeyT>;

    std::unordered_map<KeyT, ListIt> hash_;

    public:

    Ideal_cache_t (const size_t sz) : sz_(sz) {}

    template<typename F>
    int predict_hits(const std::vector<KeyT>& datastream, F get_function)
    {
      
      assert(sz_ < datastream.size());

      auto databegin = datastream.cbegin(); 
      auto dataend   = datastream.cend();
      
      auto data_it = databegin;
      
      size_t hits = 0;

      for (; data_it != dataend && cache_.size() < sz_; data_it++)
      {
        if (hash_.find(*data_it) != hash_.end()) { hits++; continue; }
  
        cache_.push_front({get_function(*data_it)});
        hash_[*data_it] = cache_.begin(); 
      }

      for (; data_it != dataend; data_it++)
      {
        auto found = hash_.find(*data_it);

        if (found != hash_.end()) { hits++; continue; }

        auto least_useful_it = find_least_useful(data_it, dataend); 
        cache_.erase(least_useful_it);
        hash_. erase(least_useful_it->item_.id_);
        cache_.push_front({get_function(*data_it)});
        hash_[*data_it] = cache_.begin(); 
      }

      return hits;
    }

    void print() const 
    {
      for (auto i = cache_.cbegin(); i != cache_.cend(); ++i)
      {
        std::cout << i->item_ << " ";
      }
      std::cout << std::endl;
    }

    private:

    cListIt find_least_useful(cVectorIt data_it, cVectorIt data_end)
    {
      auto cache_begin = cache_.cbegin();
      auto cache_end   = cache_.cend();

      auto luelt_it  = cache_begin; // least useful cache element iterator
      auto luelt_foi = data_it;  // iterator to its first occurency in datastream (foi)

      for (auto chelt_it = cache_begin; chelt_it != cache_end; chelt_it++)
      {

        for (;data_it != data_end; data_it++)
        {
          if (*data_it == chelt_it->item_.id_) break;
        }

        fflush(stdout);
        if (data_it == data_end) return chelt_it; // in this case we've found an element that wont appear anyway, its definetly useless to store it in cache

        if (std::distance(luelt_foi, data_it) > 0)
        {
          luelt_it  = chelt_it;
          luelt_foi = data_it;
        }
      }

      return luelt_it;
    }

  };

  #include "page.hpp"

  template<>
  size_t count_hits<Ideal_cache_t, page_t, int, page_t (&)(int)>(page_t (&get_function)(int))
  {
      size_t hits = 0;
      size_t nelements_in;
      size_t cache_size;

      std::cin >> cache_size >> nelements_in;
      assert(std::cin.good());
      
      Ideal_cache_t<page_t> cache {cache_size};
      std::vector<int> datastream;
      
      for (int i = 0; i < nelements_in; ++i)
      {
        int key;
        std::cin >> key;
        assert(std::cin.good());
        datastream.push_back(key);
      }
      
      hits = cache.predict_hits(datastream, get_function);

      return hits;
  }


}

#endif