// Copyright 2022 NNTU-CS
#include "../include/tree.h"
#include <algorithm>
#include <cmath>

Node::Node(char val) : value(val) {}

Tree::Tree(const std::vector<char>& elements) : originalElements(elements) {
    if (elements.empty()) {
        root = nullptr;
        return;
    }
    
    std::vector<char> sortedElements = elements;
    std::sort(sortedElements.begin(), sortedElements.end());
    
    root = std::make_shared<Node>('\0');
    
    buildTree(root, sortedElements);
}

void Tree::buildTree(std::shared_ptr<Node> node, std::vector<char> remainingElements) {
    for (char element : remainingElements) {
        auto child = std::make_shared<Node>(element);
        node->children.push_back(child);
        
        std::vector<char> newRemaining;
        for (char el : remainingElements) {
            if (el != element) {
                newRemaining.push_back(el);
            }
        }
        
        if (!newRemaining.empty()) {
            buildTree(child, newRemaining);
        }
    }
}

std::shared_ptr<Node> Tree::getRoot() const {
    return root;
}

std::vector<char> Tree::getOriginalElements() const {
    return originalElements;
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
    std::vector<std::vector<char>> allPermutations = getAllPerms(tree);
    
    if (num < 1 || num > static_cast<int>(allPermutations.size())) {
        return {};
    }
    
    return allPermutations[num - 1];
}

std::vector<char> getPerm2(Tree& tree, int num) {
    auto root = tree.getRoot();
    if (!root || num < 1) {
        return {};
    }
    
    auto originalElements = tree.getOriginalElements();
    int n = originalElements.size();
    
    auto factorial = [](int x) {
        int result = 1;
        for (int i = 2; i <= x; ++i) {
            result *= i;
        }
        return result;
    };
    
    std::vector<char> result;
    std::shared_ptr<Node> currentNode = root;
    int remainingPositions = n;
    int currentNum = num;
    
    while (currentNode && remainingPositions > 0) {
        int blockSize = factorial(remainingPositions - 1);
        
        int childIndex = (currentNum - 1) / blockSize;
        
        if (childIndex >= static_cast<int>(currentNode->children.size())) {
            return {};
        }
        
        currentNode = currentNode->children[childIndex];
        result.push_back(currentNode->value);
        
        currentNum = (currentNum - 1) % blockSize + 1;
        remainingPositions--;
    }
    
    return result;
}
