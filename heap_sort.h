#ifndef heap_sort_h
#define heap_sort_h

#include <cassert>
#include "utils.h"
#include "insertion_sort.h"
#include <queue>

template <typename T>
class heap_sort
{
public:
  static void sort(T *arr, int n, const comparator<T> &comp = fwd_comparator<T>())
  {
    for (int k = n / 2; k >= 1; k--)
      sink(arr, k, n, comp);

    int k = n;
    while (k > 1)
    {
      exchange(arr, 0, k--);
      sink(arr, 1, k, comp);
    }
  }

private:
  static void sink(T *arr, int k, int n, const comparator<T> &comp)
  {
    while (2 * k <= n)
    {
      int j = 2 * k;
      if (j < n && less(arr[j - 1], arr[j], comp))
        j++;
      if (!less(arr[k - 1], arr[j - 1], comp))
        break;
      exchange(arr, k - 1, j - 1);
      k = j
    }
  }
};

template <typename t>
class MaxPQ
{
public:
  MaxPQ(int initCapacity)
  {
    pq = new key[initCapacity + 1];
    n = 0;
  }

  MaxPQ()
  {
    std::priority_queue<t> queue;
  }

  MaxPq(int initCapacity, const comparator<T> &comp)
  {
    this = comp;
    pq = new key[initCapacity + 1];
    n = 0;
  }

  MaxPQ(const comparator<T> &comp)
  {
  }

private:
  T pq;
  int n;
};
#endif