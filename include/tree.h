// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_
#include <vector>
struct Node {
    std::vector<Node*> rest;
    char number;
};
class Tree {
 private:
    Node* root;
    std::vector<std::vector<char>> permutations;
    std::vector<char> numsCatalogue;
    void addLeaves(Node* localRoot, std::vector<char> remains) {
        if (remains.empty()) {
            return;
        }
        int j = 0;
        for (int i = 0; i < remains.size(); i++) {
            Node* child = new Node;
            child->number = remains[i];
            localRoot->rest.push_back(child);
            std::vector<char> nextVec;
            for (char u : remains) {
                if (u == remains[i]) {
                    continue;
                }
                nextVec.push_back(u);
            }
            addLeaves(child, nextVec);
        }
    }
    void AssemblyPerms(Node* root, std::vector<char> current) {
        if (root->number) {
            current.push_back(root->number);
        }
        if (root->rest.empty()) {
            permutations.push_back(current);
            return;
        }
        for (int i = 0; i < root->rest.size(); i++) {
            AssemblyPerms(root->rest[i], current);
        }
    }

 public:
    explicit Tree(const std::vector<char>& numbers) {
        numsCatalogue = numbers;
        std::vector<char> StartVec;
        root = new Node;
        root->number = 0;
        addLeaves(root, numsCatalogue);
        AssemblyPerms(root, StartVec);
    }
    std::vector<char> getOrderedPerm(int n)const {
        if (n - 1 > permutations.size()) {
            return std::vector<char>();
        }
        return permutations[n - 1];
    }
};
#endif  // INCLUDE_TREE_H_
