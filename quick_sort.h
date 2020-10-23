#ifndef quick_sort_h
#define quick_sort_h

#include <cassert>
#include "utils.h"
#include "insertion_sort.h"
#include "random.h"

template <typename T>
class quick_sort
{
public:
  static void sort(T *arr, int n, const comparator<T> &comp = fwd_comparator<T>())
  {
    std_random<T>::shuffle(arr, n);
    sort(arr, 0, n - 1, comp);
    assert(is_sorted(arr, n, comp));
  }

private:
  static const int CUTOFF = 7;
  static void sort(T *arr, int low, int high, const comparator<T> &comp)
  {
    insertion_sort<T> insertion;
    if (high <= low)
      return;
    if (high <= low + CUTOFF - 1)
    {
      insertion.sort(arr, low, high, comp);
      return;
    }
    int j = partition(arr, low, high, comp);
    sort(arr, low, j - 1, comp);
    sort(arr, j + 1, high, comp);
  }
  static int partition(T *arr, int low, int high, const comparator<T> &comp)
  {
    int i = low;
    int j = high + 1;
    T v = arr[low];
    while (true)
    {
      while (less(arr[++i], v))
      {
        if (i == high)
          break;
      }
      while (less(v, arr[--j]))
      {
        if (j == low)
          break;
      }

      if (i >= j)
        break;
      exchange(arr, i, j);
    }
    exchange(arr, low, j);
    return j;
  }
};
template <typename T>
class quick_sort_3way
{
public:
  static void sort(T *arr, size_t n, const comparator<T> &comp = fwd_comparator<T>())
  {
    std_random<T>::shuffle(arr, n);
    sort(arr, 0, n - 1, comp);
    assert(is_sorted(arr, n, comp));
  }

private:
  static const int CUTOFF = 7;
  static void sort(T *arr, size_t low, size_t high, const comparator<T> &comp)
  {
    if (high <= low)
      return;
    int lt = low, i = low + 1, gt = high;
    T v = arr[low];
    while (i <= gt)
    {
      int cmp = compare(arr[i], v, comp);
      if (cmp < 0)
        exchange(arr, lt++, i++);
      else if (cmp > 0)
        exchange(arr, i, gt--);
      else
        i++;
      sort(arr, low, lt - 1, comp);
      sort(arr, gt + 1, high, comp);
    }
  }
};

#endif