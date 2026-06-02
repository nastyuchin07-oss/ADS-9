// Copyright 2022 NNTU-CS
#ifndef TREE_H
#define TREE_H

#include <vector>
#include <memory>

class Node {
public:
    char value;
    std::vector<std::shared_ptr<Node>> children;
    
    Node(char val);
};

class Tree {
private:
    std::shared_ptr<Node> root;
    std::vector<char> originalElements;
    
    void buildTree(std::shared_ptr<Node> node, std::vector<char> remainingElements);
    void getAllPermutationsDFS(std::shared_ptr<Node> node, 
                               std::vector<char>& current,
                               std::vector<std::vector<char>>& result);
    
public:
    Tree(const std::vector<char>& elements);
    
    ~Tree() = default;
    
    std::shared_ptr<Node> getRoot() const;
    
    std::vector<char> getOriginalElements() const;
};

std::vector<std::vector<char>> getAllPerms(Tree& tree);

std::vector<char> getPerm1(Tree& tree, int num);

std::vector<char> getPerm2(Tree& tree, int num);

#endif
