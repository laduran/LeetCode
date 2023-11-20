from typing import List 

class Solution:
  def merge(self, nums1: List[int], m: int, nums2: List[int], n: int) -> None:
    i = m - 1      # nums1's index (actual nums)
    j = n - 1      # nums2's index
    k = m + n - 1  # nums1's index (next filled position)

    while j >= 0:
      if i >= 0 and nums1[i] > nums2[j]:
        nums1[k] = nums1[i]
        i -= 1
      else:
        nums1[k] = nums2[j]
        j -= 1
      k -= 1


def main():
  solution = Solution()

  nums1 = [1,2,3,0,0,0]
  nums2 = [2,5,6]
  solution.merge(nums1, 3, nums2, 3)
  print(nums1)


main()