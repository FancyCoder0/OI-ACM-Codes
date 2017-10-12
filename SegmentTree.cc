#include <bits/stdc++.h>

/* -------------------------------------------------------------------------- */

// The interval in segment tree.
// The interval [L, R] contains the points whose index is between L and R.
struct Interval {
  int left_index, right_index;
};

// Help function for interval.
const int LengthOfInterval(const Interval& interval) {
  return interval.right_index - interval.left_index + 1;
}

const bool IntervalIsSinglePoint(const Interval& interval) {
  return interval.left_index == interval.right_index;
}

const int MidIndexOfInterval(const Interval& interval) {
  return (interval.left_index + interval.right_index) / 2;
}

const Interval LeftHalfOfInterval(const Interval& interval) {
  return (Interval) { interval.left_index , MidIndexOfInterval(interval) };
}

const Interval RightHalfOfInterval(const Interval& interval) {
  return (Interval) { MidIndexOfInterval(interval) + 1, interval.right_index };
}

const bool IntervalSeparate(const Interval& interval_a,
                            const Interval& interval_b) {
  return interval_a.right_index < interval_b.left_index ||
         interval_b.right_index < interval_a.left_index;
}

const bool IntervalContain(const Interval& interval_a,
                           const Interval& interval_b) {
  return interval_a.left_index <= interval_b.left_index &&
         interval_b.right_index <= interval_a.right_index;
}

/* -------------------------------------------------------------------------- */
/*        You need to re-write this part to meet different problems.          */

// The mark for node in segment tree.
struct NodeMark {
  int add;
};

const NodeMark MarkMerge(const NodeMark& mark, const NodeMark& new_mark) {
  return (NodeMark) { mark.add + new_mark.add };
}

// The information of the nodes in segment tree.
struct NodeInfo {
  long long sum;
};

const NodeInfo InfoMerge(const NodeInfo& info_a, const NodeInfo& info_b) {
  return (NodeInfo) { info_a.sum + info_b.sum };
}

const NodeInfo InfoUpdate(const NodeInfo& info,
                          const Interval& interval,
                          const NodeMark& mark) {
  return (NodeInfo) {
  	info.sum + static_cast<long long> (mark.add) * LengthOfInterval(interval)
  };
}

/* -------------------------------------------------------------------------- */

// This class is the node for segment which contains interval's left index &
// right index, interval's mark, interval's information.
class SegmentTreeNode {
 public:
  SegmentTreeNode(const Interval& interval, const NodeInfo& info):
    interval_(interval), info_(info), mark_(empty_mark_) { };

  SegmentTreeNode(const Interval& interval,
                  std::unique_ptr<SegmentTreeNode> left_child,
                  std::unique_ptr<SegmentTreeNode> right_child):
    interval_(interval), info_(empty_info_), mark_(empty_mark_) {
        left_child_ = std::move(left_child);
        right_child_ = std::move(right_child);
    };

  void MarkUpdate(const NodeMark& new_mark) {
    mark_ = MarkMerge(mark_, new_mark);
    info_ = InfoUpdate(info_, interval_, new_mark);
  }

  void PushDown() {
    left_child_->MarkUpdate(mark_);
    right_child_->MarkUpdate(mark_);
    mark_ = empty_mark_;
  }

  void Maintain() {
    info_ = InfoMerge(left_child_->GetInfo(), right_child_->GetInfo());
  }

  SegmentTreeNode* GetLeftChild() {
    return left_child_.get();
  }

  SegmentTreeNode* GetRightChild() {
    return right_child_.get();
  }

  const NodeInfo GetInfo() {
    return info_;
  }

  const Interval GetInterval() {
    return interval_;
  }

 private:
  static const NodeInfo empty_info_;
  static const NodeMark empty_mark_;

  Interval interval_;
  NodeInfo info_;
  NodeMark mark_;
  std::unique_ptr<SegmentTreeNode> left_child_;
  std::unique_ptr<SegmentTreeNode> right_child_;
};

/* -------------------------------------------------------------------------- */
/*        You need to re-write this part to meet different problems.          */

const NodeInfo SegmentTreeNode::empty_info_ = (NodeInfo) { 0 };
const NodeMark SegmentTreeNode::empty_mark_ = (NodeMark) { 0 };

/* -------------------------------------------------------------------------- */

// This class is the segment tree.
// Now it supports query for the sum of numbers in a given interval
// and add some given number to each number in a given interval.
class SegmentTree {
 public:
  explicit SegmentTree(const std::vector<int>& elements) {
    std::vector<NodeInfo> temp_elements_vet;
    for (auto ele : elements) {
      temp_elements_vet.push_back((NodeInfo) { static_cast<long long> (ele) });
    }
    tree_root_ = Build(temp_elements_vet,
                       (Interval) { 1, static_cast<int> (elements.size()) });
  }

  const long long Sum(const int left_of_interval, const int right_of_interval) {
    query_flag_ = true;
    query_ans_ = (NodeInfo) { 0 };
    FindOnTree(tree_root_.get(),
              (Interval) { left_of_interval, right_of_interval });
    return query_ans_.sum;
  }

  void Add(const int left_of_interval,
           const int right_of_interval,
           const int add_value) {
    query_flag_ = false;
    operation_mark_ = (NodeMark){ add_value };
    FindOnTree(tree_root_.get(),
               (Interval) { left_of_interval, right_of_interval });
  }

 private:
  std::unique_ptr<SegmentTreeNode>
    Build(const std::vector<NodeInfo>& elements,
          const Interval& interval) {
    if (IntervalIsSinglePoint(interval)) {
      std::unique_ptr<SegmentTreeNode> node(
        new SegmentTreeNode(interval, elements[interval.left_index - 1]));
      return std::move(node);
    } else {
      auto left_child = Build(elements, LeftHalfOfInterval(interval));
      auto right_child = Build(elements, RightHalfOfInterval(interval));
      std::unique_ptr<SegmentTreeNode> node(
        new SegmentTreeNode(interval,
                            std::move(left_child),
                            std::move(right_child)));
      node->Maintain();
      return std::move(node);
    }
  }

  void FindOnTree(SegmentTreeNode* node, const Interval& query_interval) {
    if (IntervalSeparate(query_interval, node->GetInterval())) {
      return;
    } else if (IntervalContain(query_interval, node->GetInterval())) {
      if (query_flag_) {
        query_ans_ = InfoMerge(query_ans_, node->GetInfo());
      } else {
        node->MarkUpdate(operation_mark_);
      }
    } else {
      node->PushDown();
      FindOnTree(node->GetLeftChild(), query_interval);
      FindOnTree(node->GetRightChild(), query_interval);
      node->Maintain();
    }
  }

  std::unique_ptr<SegmentTreeNode> tree_root_;
  bool query_flag_;
  NodeMark operation_mark_;
  NodeInfo query_ans_;
};

/* -------------------------------------------------------------------------- */

void TestForSegmentTree() {
  int num_elements, num_query;
  scanf("%d%d", &num_elements, &num_query);

  std::vector<int> elements;
  for (int i = 0; i < num_elements; ++i) {
    int x;
    scanf("%d", &x);
    elements.push_back(x);
  }

  SegmentTree Tree(elements);
  for (int i = 0; i < num_query; ++i) {
    char type_of_query[3];
    int left_of_interval, right_of_interval;
    scanf("%s%d%d", type_of_query, &left_of_interval, &right_of_interval);
    if (type_of_query[0] == 'C') {
      int add_value;
      scanf("%d", &add_value);
      Tree.Add(left_of_interval, right_of_interval, add_value);
    } else {
      printf("%lld\n", Tree.Sum(left_of_interval, right_of_interval));
    }
  }
};

/* -------------------------------------------------------------------------- */

int main() {
  TestForSegmentTree();
  return 0;
}
