namespace Caches
{

template <typename T, typename KeyT = int>
struct LFU_cache_t
{
  private:
  
  // Cache size should be const to prevent the cache to be resized. It will stay this way until we define cache resizing principles
  const size_t sz_;
  
  struct cache_item_t
  {
    size_t frq_ = 0;
    T item_;
    cache_item_t(T item): item_(item) {};
  };

  std::list<cache_item_t> cache_;
  
  using ListIt  = ListIt_t<cache_item_t>;
  using cListIt = cListIt_t<cache_item_t>;

  std::unordered_map<KeyT, ListIt> hash_;

  cListIt get_lfu_item() const
  {
    auto lfu_item = cache_.cbegin();
    auto cache_end = cache_.cend();
    for (auto i = cache_.cbegin(); i != cache_end; i++)
    {
      if (i->frq_ < lfu_item->frq_)
      {
        lfu_item = i;
      }
    }

    return lfu_item;
  }

  public:

  LFU_cache_t(const size_t sz) : sz_(sz) {}

  template<typename F> bool lookup_update(KeyT key, F slow_get_page)
  {
      auto hit = hash_.find(key);
      if (hit == hash_.end())
      {
        if (full())
        {
          auto lfu_item = get_lfu_item();
          hash_.erase(lfu_item->item_.id_);
          cache_.erase(lfu_item);
        }
        
        cache_.push_front({slow_get_page(key)});
        hash_[key] = cache_.begin();
        return false;
      }

      hit->second->frq_ += 1;
      return true;
  }


  bool full() const
  {
      return cache_.size() == sz_;
  }


  void print() const 
  {
    for (auto i = cache_.cbegin(); i != cache_.cend(); ++i)
    {
      std::cout << i->item_ << "(" << i->frq_ << ")" << " ";
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