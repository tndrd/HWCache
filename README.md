# HWCache

First task of Ilab C++ course. Includes LRU, LFU and Bélády's algorithm-based (IDL) caches implementations.

# How to build

```bash
mkdir build
cd buld
cmake ..
cmake --build .
```

# How to run tests

After you've done the previous step, run

```bash
ctest .
```

# How to run

After you've build the project, ```e2e`` executable will appear. It counts the specified cache's hits that turn up when specified data array is recieved.
**Format**:
```bash
./e2e <LFU | LRU | IDL> <cache size> 
``
