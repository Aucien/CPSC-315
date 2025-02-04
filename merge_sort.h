//Gordon Dan
#ifndef merge_sort_h
#define merge_sort_h

#include <cassert>
#include "utils.h"
#include "insertion_sort.h"

template <typename T>
class merge_sort
{
public:
  static void sort(T *arr, size_t n, const comparator<T> &comp = fwd_comparator<T>())
  {
    T *aux = new T[n];
    sort(arr, aux, 0, n - 1, comp);
    delete[] aux;
  }

private:
  static const int CUTOFF = 7;
  static void sort(T *arr, T *aux, size_t low, size_t high, const comparator<T> &comp)
  {
    insertion_sort<T> insertion;
    if (high <= low)
      return;
    if (high <= low + CUTOFF - 1)
    {
      insertion.sort(arr, low, high, comp);
      return;
    }
    size_t mid = low + (high - low) / 2;
    sort(arr, aux, low, mid, comp);
    sort(arr, aux, mid + 1, high, comp);
    merge(arr, aux, low, mid, high, comp);
  }
  static void merge(T *arr, T *aux, size_t low, size_t mid, size_t high, const comparator<T> &comp)
  {
    assert(is_sorted(arr, low, mid, comp));
    assert(is_sorted(arr, mid + 1, high, comp));
    size_t i = low, j = mid + 1;
    for (size_t k = low; k <= high; ++k)
    {
      aux[k] = arr[k];
    }
    for (size_t k = low; k <= high; ++k)
    {
      if (i > mid)
        arr[k] = aux[j++];
      else if (j > high)
        arr[k] = aux[i++];
      else if (less(aux[j], aux[i]))
        arr[k] = aux[j++];
      else
        arr[k] = aux[i++];
    }
    assert(is_sorted(arr, low, high, comp));
  }
};
template <typename T>
class merge_bu_sort
{
public:
  // merge_bu_sort() = delete;
  static void sort(T *arr, size_t n, const comparator<T> &comp = fwd_comparator<T>())
  {
    T *aux = new T[n];
    for (size_t sz = 1; sz < n; sz = sz + sz)
    {
      for (size_t low = 0; low < n - sz; low += sz + sz)
      {
        merge(arr, aux, low, low + sz - 1, std::min(low + sz + sz - 1, n - 1), comp);
      }
    }
  }

private:
  static void merge(T *arr, T *aux, size_t low, size_t mid, size_t high, const comparator<T> &comp)
  {
    size_t i = low, j = mid + 1;
    for (size_t k = low; k <= high; k++)
    {
      aux[k] = arr[k];
    }
    for (size_t k = low; k <= high; k++)
    {
      if (i > mid)
        arr[k] = aux[j++];
      else if (j > high)
        arr[k] = aux[i++];
      else if (less(aux[i], aux[j]))
        arr[k] = aux[j++];
      else
        arr[k] = aux[i++];
    }
  }
};

#endif