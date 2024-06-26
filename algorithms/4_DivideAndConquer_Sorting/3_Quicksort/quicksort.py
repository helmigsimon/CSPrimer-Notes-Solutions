"""
- Not as clearly a divide and conquer algorithm as merge sort
- He will do it inplace
- Why have another algorithm in nlogn?
    - Quicksort is faster for sorting in memory
    - Far easier to implement inplace with no extra space usage
    - Constant factor is faster for quicksort
- Merge sort is useful still when merging database tables for example
    - When we want to preserve the sequential access of these tables that aligns with the merge sort implementation

Idea:
- Bunch of values: 4 3 6 2 5
- Pick a value in there: 4 (pivot value)
- Perform an operation where:
    - Everything less than pivot value on the LHS
    - Everything higher than the pivot value on the RHS
- We can recursively apply the same approach to the sub arrays we have created on the LHS and RHS
    - You are halving the array with each split, so takes log n splits
    - Takes n operations to do the partitioning

- Can you come up with your own partitioning scheme?
    - Function that figures out how to move the pivot value to the middle of the array

Example:
4 3 6 2 5
3 2 4 6 5
2 3 4 6 5
2 3 4 5 6
"""

import random

def quicksort(n: list[int], l: int | None = None, r: int | None = None) -> None:
    """
    Plan:
    - if len(n) == 1:
        return n
    - if len(n) == 2:
        if n[0] > n[1]:
            return [n[0], n[1]]
        return n
    - (
        lhs,pivot, rhs
      ) = partition(n)
    - return quicksort(lhs) + pivot + quicksort(rhs)

    def partition(n) -> list[int], list[int], list[int]:
        Lomuto Scheme
        - Take the first value as the pivot
        - Iterate over your array, setting your midpoint pointer to the first value and search pointer as the second value
            - Perform a swap if the value at the index is strictly smaller than the pivot value
        - To perform a swap:
            - Swap the ith value with the m+1th value
        - Pointer advancement
            - If you make a swap, then both m and i advance
            - If you don't make a swap, then only i advances
        - Continue iterating until end of array
        return n[:m] + n[m] + n[m+1:]
    """
    l = l if l is not None else 0
    r = r if r is not None else len(n)-1
    if l >= r:
        return
    midpoint = partition(n, l, r)
    quicksort(n, l, midpoint)
    quicksort(n, midpoint+1, r)


def partition(n: list[int], l: int, r: int) -> int:
    pivot = n[l]
    midpoint = l
    idx = l+1
    while idx != r+1:
        if n[idx] < pivot:
            midpoint += 1
            swap(n, idx, midpoint)
        idx += 1
    swap(n, l, midpoint)
    return midpoint


def swap(n: list[int], l: int, r: int) -> None:
    n[l], n[r] = n[r], n[l]


random_ints = [random.randint(0, 10) for _ in range(10000)]
TEST_CASES = [
    ([2], [2]),
    ([2, 1], [1, 2]),
    ([1, 2], [1, 2]),
    ([3, 1, 2], [1, 2, 3]),
    ([3, 1, 4, 2], [1, 2, 3, 4]),
    (random_ints, sorted(random_ints)),
]


if __name__ == "__main__":
    for case, expected_result in TEST_CASES:
        quicksort(case)
        try:
            assert case == expected_result
        except AssertionError:
            print(f"Case: {case}")
            print(f"Expected Result: {expected_result}")
            raise
    print("done")
