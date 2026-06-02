// Copyright 2022 NNTU-CS
#include "../include/tree.h"

#include <algorithm>
#include <cmath>
#include <functional>

Node::Node(char val) : value(val) {}

Tree::Tree(const std::vector<char>& elements)
    : original_elements_(elements) {
  if (elements.empty()) {
    root_ = nullptr;
    return;
  }

  std::vector<char> sorted_elements = elements;
  std::sort(sorted_elements.begin(), sorted_elements.end());

  root_ = std::make_shared<Node>('\0');

  buildTree(root_, sorted_elements);
}

void Tree::buildTree(std::shared_ptr<Node> node,
                     std::vector<char> remaining_elements) {
  for (char element : remaining_elements) {
    auto child = std::make_shared<Node>(element);
    node->children.push_back(child);

    std::vector<char> new_remaining;
    for (char el : remaining_elements) {
      if (el != element) {
        new_remaining.push_back(el);
      }
    }

    if (!new_remaining.empty()) {
      buildTree(child, new_remaining);
    }
  }
}

std::shared_ptr<Node> Tree::getRoot() const {
  return root_;
}

std::vector<char> Tree::getOriginalElements() const {
  return original_elements_;
}

std::vector<std::vector<char>> getAllPerms(Tree& tree) {
  std::vector<std::vector<char>> result;

  auto root = tree.getRoot();
  if (!root) {
    return result;
  }

  std::vector<char> current;

  std::function<void(std::shared_ptr<Node>, std::vector<char>&)> dfs =
      [&](std::shared_ptr<Node> node, std::vector<char>& curr) {
        if (node->value != '\0') {
          curr.push_back(node->value);
        }

        if (node->children.empty() && node->value != '\0') {
          result.push_back(curr);
        } else {
          for (auto& child : node->children) {
            dfs(child, curr);
          }
        }

        if (node->value != '\0') {
          curr.pop_back();
        }
      };

  dfs(root, current);

  return result;
}

std::vector<char> getPerm1(Tree& tree, int num) {
  std::vector<std::vector<char>> all_permutations = getAllPerms(tree);

  if (num < 1 || num > static_cast<int>(all_permutations.size())) {
    return {};
  }

  return all_permutations[num - 1];
}

std::vector<char> getPerm2(Tree& tree, int num) {
  auto root = tree.getRoot();
  if (!root || num < 1) {
    return {};
  }

  auto original_elements = tree.getOriginalElements();
  int n = static_cast<int>(original_elements.size());

  auto factorial = [](int x) {
    int result = 1;
    for (int i = 2; i <= x; ++i) {
      result *= i;
    }
    return result;
  };

  std::vector<char> result;
  std::shared_ptr<Node> current_node = root;
  int remaining_positions = n;
  int current_num = num;

  while (current_node && remaining_positions > 0) {
    int block_size = factorial(remaining_positions - 1);

    int child_index = (current_num - 1) / block_size;

    if (child_index >= static_cast<int>(current_node->children.size())) {
      return {};
    }

    current_node = current_node->children[child_index];
    result.push_back(current_node->value);

    current_num = (current_num - 1) % block_size + 1;
    remaining_positions--;
  }

  return result;
}
