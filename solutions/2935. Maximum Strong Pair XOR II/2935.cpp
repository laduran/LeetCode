struct TrieNode {
  vector<shared_ptr<TrieNode>> children;
  TrieNode() : children(2) {}
  int min = INT_MAX;
  int max = INT_MIN;
};

class BitTrie {
 public:
  BitTrie(int maxBit) : maxBit(maxBit) {}

  void insert(int num) {
    shared_ptr<TrieNode> node = root;
    for (int i = maxBit; i >= 0; --i) {
      const int bit = num >> i & 1;
      if (node->children[bit] == nullptr)
        node->children[bit] = make_shared<TrieNode>();
      node = node->children[bit];
      node->min = min(node->min, num);
      node->max = max(node->max, num);
    }
  }

  // Returns max(x ^ y) where |x - y| <= min(x, y).
  //
  // If x <= y, |x - y| <= min(x, y) can be written as y - x <= x.
  // So, y <= 2 * x.
  int getMaxXor(int x) {
    int maxXor = 0;
    shared_ptr<TrieNode> node = root;
    for (int i = maxBit; i >= 0; --i) {
      const int bit = x >> i & 1;
      const int toggleBit = bit ^ 1;
      // If `node.children[toggleBit].max > x`, it means there's a number in the
      // node that satisfies the condition to ensure that x <= y among x and y.
      // If `node.children[toggleBit].min <= 2 * x`, it means there's a number
      // in the node that satisfies the condition for a valid y.
      if (node->children[toggleBit] != nullptr &&
          node->children[toggleBit]->max > x &&
          node->children[toggleBit]->min <= 2 * x) {
        maxXor = maxXor | 1 << i;
        node = node->children[toggleBit];
      } else if (node->children[bit] != nullptr) {
        node = node->children[bit];
      } else {  // Nothing in the Bit Trie.
        return 0;
      }
    }
    return maxXor;
  }

 private:
  const int maxBit;
  shared_ptr<TrieNode> root = make_shared<TrieNode>();
};

class Solution {
 public:
  // Same as 2932. Maximum Strong Pair XOR I
  int maximumStrongPairXor(vector<int>& nums) {
    const int maxNum = ranges::max(nums);
    const int maxBit = static_cast<int>(log2(maxNum));
    int ans = 0;
    BitTrie bitTrie(maxBit);

    for (const int num : nums)
      bitTrie.insert(num);

    for (const int num : nums)
      ans = max(ans, bitTrie.getMaxXor(num));

    return ans;
  }
};
