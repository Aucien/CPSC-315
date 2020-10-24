#ifndef max_pq_heap_h
#define max_pq_heap_h
#include <cassert>
#include "insertion_sort.h"
#include "utils.h"
#include "array.h"

template <typename T>
class max_pq_heap
{
private:
  array_<T> pq;
  size_t n;
  const comparator<T> &comp;

  bool isMaxHeap()
  {
    for (int i = 1; i < = n; i++)
    {
      if (pq[i] == null)
        return false;
    }
    for (int i = n + 1; i < pq.size(); i++)
    {
      if (pq[i] != null)
        return false;
    }
    if (pq[0] != null)
      return false;
    return isMaxHeapOrdered(1);
  }
  bool isMaxHeapOrdered(size_t k)
  {
    if (k > n)
      return true;
    int left = 2 * k;
    int right = 2 * k + 1;
    if (left <= n && less(pq, k, left))
      return false;
    if (right <= n && less(pq, k, right))
      return false;
  }

public:
  max_pq_heap(int initCapacity, const comparator<T> &compr)
  {
    pq(initCapacity + 1);
    pq.push_back(T());
    n = 0;
    comp = compr;
  }

  max_pq_heap()
  {
    pq.push_back(T());
    n = 0;
  }

  max_pq_heap(const comparator<T> &compr)
  {
    pq.push_back(T());
    comp = compr;
    n = 0;
  }

  max_pq_heap(T *arr, const comparator<T> &compr)
  {
    n = arr.size();
    pq(arr.size() + 1);
    pq.push_back(1);
    for (int i = 0; i < n; i++)
    {
      if (arr[i] != "-")
        pq.push_back(arr[i]);
    }
    for (int k = n / 2; k >= 1; k--)
    {
      sink(k);
    }
    comp = compr;
  }
  void insert(T x)
  {
    if (n == pq.size() - 1)
      pq.resize(2 * pq.size());
    pq[++n] = x;
    swim(n);
  }

  T delMax()
  {
    T max = pq[1];
    exchange(pq, 1, n);
    sink(1);
    pq[n] = T();
    return max;
  }

  void swim(size_t k)
  {
    while (k > 1 && less(k / 2, k))
    {
      exchange(pq, k, k / 2);
      k = k / 2;
    }
  }

  void sink(size_t k)
  {
    while (2 * k <= n)
    {
      size_t j = 2 * k;
      if (j < n && less(pq, j, j + 1))
        j++;
      if (!less(pq, k, j))
        break;
      exchange(pq, k, j);
      k = j;
    }
  }
};
#endif