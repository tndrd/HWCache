namespace Caches
{

template <typename T, typename KeyT = int>
struct LRU_cache_t
{
  private:
  
  // Cache size needs to be const to prevent the cache to be resized. It will stay this way until we define cache resizing principles
  const size_t sz_;
  std::list<T> cache_;
  
  using ListIt  = ListIt_t<T>;
  using cListIt = cListIt_t<T>;

  std::unordered_map<KeyT, ListIt> hash_;

  public:

  LRU_cache_t(const size_t sz) : sz_(sz) {}

  template <typename F>
  bool lookup_update(KeyT key, F slow_get_page)
  {
      auto hit = hash_.find(key);
      if (hit == hash_.end()) {
        if (full()) {
          hash_.erase(cache_.back().id_);
          cache_.pop_back();
        }
        cache_.push_front(slow_get_page(key));
        hash_[key] = cache_.begin();
        return false;
      }

      auto elem_it = hit->second;
      if (elem_it != cache_.begin())
        cache_.splice(cache_.begin(), cache_, elem_it/*, std::next(eltit)*/);
      return true;
  }


  bool full() const
  {
      return cache_.size() == sz_;
  }


  void print() const 
  {
    for (auto i = cache_.begin(); i != cache_.end(); ++i)
    {
      std::cout << *i << ' ';
    }
    std::cout << std::endl;
  }


  void clear()
  {
      hash_.clear();
      cache_.clear();
  }

  };
}