/**
 * @file bst.hpp
 * @brief Implementação genérica de uma Árvore Binária de Busca (BST).
 * 
 * A BST funciona com qualquer tipo T que defina o operador < para comparação.
 * Operações básicas: inserção, busca, remoção e travessias (in-order, pre-order, post-order).
 */

#pragma once

#include <vector>

template <typename T>
class BST {
private:
    struct TreeNode {
        T value;
        TreeNode* left;
        TreeNode* right;
        TreeNode(const T& val) : value(val), left(nullptr), right(nullptr) {}
    };

    TreeNode* root;

    // Função auxiliar para deletar recursivamente a árvore
    void clear(TreeNode* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

    // Função auxiliar para inserir valor
    bool insert(TreeNode*& node, const T& val) {
        if (!node) {
            node = new TreeNode(val);
            return true;
        }
        if (val < node->value) {
            return insert(node->left, val);
        }
        if (node->value < val) {
            return insert(node->right, val);
        }
        // valor já existe (não insere duplicata)
        return false;
    }

    // Função auxiliar para buscar valor
    bool contain(TreeNode* node, const T& val) const {
        if (!node) return false;
        if (val < node->value) return contain(node->left, val);
        if (node->value < val) return contain(node->right, val);
        return true;  // iguais (nem val < node->value nem node->value < val)
    }

    // Função auxiliar para encontrar o nó com o menor valor na subárvore
    TreeNode* findMin(TreeNode* node) const {
        while (node && node->left)
            node = node->left;
        return node;
    }

    // Função auxiliar para remover um valor
    bool remove(TreeNode*& node, const T& val) {
        if (!node) return false;

        if (val < node->value) {
            return remove(node->left, val);
        }
        if (node->value < val) {
            return remove(node->right, val);
        }
        // Achou o nó para remover
        if (!node->left && !node->right) {
            delete node;
            node = nullptr;
        } else if (!node->left) {
            TreeNode* temp = node;
            node = node->right;
            delete temp;
        } else if (!node->right) {
            TreeNode* temp = node;
            node = node->left;
            delete temp;
        } else {
            // Dois filhos: substitui pelo menor da subárvore direita
            TreeNode* minNode = findMin(node->right);
            node->value = minNode->value;
            remove(node->right, minNode->value);
        }
        return true;
    }

    // Travessias recursivas
    void inOrder(TreeNode* node, std::vector<T>& out) const {
        if (!node) return;
        inOrder(node->left, out);
        out.push_back(node->value);
        inOrder(node->right, out);
    }

    void preOrder(TreeNode* node, std::vector<T>& out) const {
        if (!node) return;
        out.push_back(node->value);
        preOrder(node->left, out);
        preOrder(node->right, out);
    }

    void postOrder(TreeNode* node, std::vector<T>& out) const {
        if (!node) return;
        postOrder(node->left, out);
        postOrder(node->right, out);
        out.push_back(node->value);
    }

public:
    BST() : root(nullptr) {}
    ~BST() { clear(root); }

    bool insert(const T& val) {
        return insert(root, val);
    }

    bool contain(const T& val) const {
        return contain(root, val);
    }

    bool remove(const T& val) {
        return remove(root, val);
    }

    std::vector<T> in_order() const {
        std::vector<T> result;
        inOrder(root, result);
        return result;
    }

    std::vector<T> pre_order() const {
        std::vector<T> result;
        preOrder(root, result);
        return result;
    }

    std::vector<T> post_order() const {
        std::vector<T> result;
        postOrder(root, result);
        return result;
    }
};
