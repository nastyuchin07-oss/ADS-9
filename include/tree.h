// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>
#include <memory>

class Node {
 public:
  explicit Node(char val);
  char value;
  std::vector<std::shared_ptr<Node>> children;
};

class Tree {
 public:
  explicit Tree(const std::vector<char>& elements);
  ~Tree() = default;

  std::shared_ptr<Node> getRoot() const;
  std::vector<char> getOriginalElements() const;

 private:
  std::shared_ptr<Node> root_;
  std::vector<char> original_elements_;

  void buildTree(std::shared_ptr<Node> node,
                 std::vector<char> remaining_elements);
  void getAllPermutationsDFS(std::shared_ptr<Node> node,
                             std::vector<char>& current,
                             std::vector<std::vector<char>>& result);
};

std::vector<std::vector<char>> getAllPerms(Tree& tree);

std::vector<char> getPerm1(Tree& tree, int num);

std::vector<char> getPerm2(Tree& tree, int num);

#endif  // INCLUDE_TREE_H_
