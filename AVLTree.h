//
// Created by Omer on 03/05/2018.
//

#include <exception>
#include <cmath>
#include <string>
#include "exceptions.h"

#ifndef DATASTRUCTURES_HW1_AVLTREE_H
#define DATASTRUCTURES_HW1_AVLTREE_H

#define nullptr 0

using std::string;

template<typename T, class Key>
class AVLTree {
    struct Node {
        T *data;
        Key key;
        Node *parent;
        Node *left;
        int h_left;
        Node *right;
        int h_right;

        int rank;
        Key sum_keys;

        Node() {
            data = nullptr;
            parent = nullptr;
            left = nullptr;
            right = nullptr;
            h_right = -1;
            h_left = -1;

            rank = 1;
        }

        Node(const T &data, const Key &key) {
            this->data = new T(data);
            this->key = key;
            parent = nullptr;
            left = nullptr;
            right = nullptr;
            h_right = -1;
            h_left = -1;

            rank = 1;
            sum_keys = key;
            sum_keys += key;
            sum_keys -= key;
        }

        ~Node() {
            delete this->data;
        }

        Node(const Node &node) {
            data = new T(*node.data);
            key = node.key;
            h_left = node.h_left;
            h_right = node.h_right;
            parent = nullptr;
            left = nullptr;
            right = nullptr;

            rank = node.rank;
            sum_keys = node.sum_keys;
        }

        Node &operator=(const Node &node) = delete;
    };

    Node *root;

    Node *binarySearch(Key key) {
        if (root == nullptr) return nullptr;
        Node *iterator = root;
        while (true) {
            if (iterator->key == key) break;
            else if (key < iterator->key) {
                if (iterator->left == nullptr) return iterator;
                iterator = iterator->left;
            } else {
                if (iterator->right == nullptr) return iterator;
                iterator = iterator->right;
            }
        }
        return iterator;
    }

    Node *createVertex(Node *parent, const T &data, Key key) {
        Node *new_node = new Node(data, key);
        if (key < parent->key) {
            parent->left = new_node;
        } else {
            parent->right = new_node;
        }
        new_node->parent = parent;
        return new_node;
    }

    static int getHeight(Node *vertex) {
        if (vertex == nullptr) return -1;
        if (vertex->h_left > vertex->h_right) return vertex->h_left + 1;
        return vertex->h_right + 1;
    }

    void roll_LL(Node *A) {
        Node *B;

        B = A->left; // new parent - left node of the unbalanced node
        A->left = B->right; // if new node has right children, move to to old parent
        A->h_left = B->h_right;
        if (B->right != nullptr) {
            B->right->parent = A;
        }

        if (A->parent == nullptr) {
            root = B;
        } else if (A->parent->left == A) {
            A->parent->left = B;
        } else {
            A->parent->right = B;
        }

        B->right = A;
        B->h_right = getHeight(A);
        B->parent = A->parent;
        A->parent = B;

        int A_rank = 1;
        int B_rank = 1;
        if (A->right != nullptr) A_rank += A->right->rank;
        if (A->left != nullptr) A_rank += A->left->rank;
        A->rank = A_rank;
        if (B->right != nullptr) B_rank += B->right->rank;
        if (B->left != nullptr) B_rank += B->left->rank;
        B->rank = B_rank;

        Key A_keys_sum = A->key;
        Key B_keys_sum = B->key;
        if (A->right != nullptr) A_keys_sum += A->right->sum_keys;
        if (A->left != nullptr) A_keys_sum += A->left->sum_keys;
        A->sum_keys = A_keys_sum;
        if (B->right != nullptr) B_keys_sum += B->right->sum_keys;
        if (B->left != nullptr) B_keys_sum += B->left->sum_keys;
        B->sum_keys = B_keys_sum;
    }

    void roll_RR(Node *A) {
        Node *B;

        B = A->right; // new parent - left node of the unbalanced node
        A->right = B->left; // if new node has right children, move to to old parent
        A->h_right = B->h_left;
        if (B->left != nullptr) {
            B->left->parent = A;
        }

        if (A->parent == nullptr) {
            root = B;
        } else if (A->parent->left == A) {
            A->parent->left = B;
        } else {
            A->parent->right = B;
        }

        B->left = A;
        B->h_left = getHeight(A);
        B->parent = A->parent;
        A->parent = B;

        int A_rank = 1;
        int B_rank = 1;
        if (A->right != nullptr) A_rank += A->right->rank;
        if (A->left != nullptr) A_rank += A->left->rank;
        A->rank = A_rank;
        if (B->right != nullptr) B_rank += B->right->rank;
        if (B->left != nullptr) B_rank += B->left->rank;
        B->rank = B_rank;

        Key A_keys_sum = A->key;
        Key B_keys_sum = B->key;
        if (A->right != nullptr) A_keys_sum += A->right->sum_keys;
        if (A->left != nullptr) A_keys_sum += A->left->sum_keys;
        A->sum_keys = A_keys_sum;
        if (B->right != nullptr) B_keys_sum += B->right->sum_keys;
        if (B->left != nullptr) B_keys_sum += B->left->sum_keys;
        B->sum_keys = B_keys_sum;
    }

    void roll_RL(Node *A) {
        Node *B = A->right;
        Node *C = A->right->left;

        if (A->parent == nullptr) root = C;

        B->left = C->right;
        B->h_left = C->h_right;
        if (C->right != nullptr) C->right->parent = B;

        A->right = C->left;
        A->h_right = C->h_left;
        if (C->left != nullptr) C->left->parent = A;

        C->left = A;
        C->h_left = getHeight(A);
        C->right = B;
        C->h_right = getHeight(B);
        C->parent = A->parent;
        if (C->parent != nullptr) {
            if (A->parent->right == A) {
                A->parent->right = C;
            } else if (A->parent->left == A) {
                A->parent->left = C;
            }
        }
        A->parent = C;
        B->parent = C;

        int A_rank = 1;
        int B_rank = 1;
        int C_rank = 1;
        if (A->right != nullptr) A_rank += A->right->rank;
        if (A->left != nullptr) A_rank += A->left->rank;
        A->rank = A_rank;
        if (B->right != nullptr) B_rank += B->right->rank;
        if (B->left != nullptr) B_rank += B->left->rank;
        B->rank = B_rank;
        if (C->right != nullptr) C_rank += C->right->rank;
        if (C->left != nullptr) C_rank += C->left->rank;
        C->rank = C_rank;

        Key A_keys_sum = A->key;
        Key B_keys_sum = B->key;
        Key C_keys_sum = C->key;
        if (A->right != nullptr) A_keys_sum += A->right->sum_keys;
        if (A->left != nullptr) A_keys_sum += A->left->sum_keys;
        A->sum_keys = A_keys_sum;
        if (B->right != nullptr) B_keys_sum += B->right->sum_keys;
        if (B->left != nullptr) B_keys_sum += B->left->sum_keys;
        B->sum_keys = B_keys_sum;
        if (C->right != nullptr) C_keys_sum += C->right->sum_keys;
        if (C->left != nullptr) C_keys_sum += C->left->sum_keys;
        C->sum_keys = C_keys_sum;
    }

    void roll_LR(Node *A) {
        Node *B = A->left;
        Node *C = A->left->right;

        if (A->parent == nullptr) root = C;

        B->right = C->left;
        B->h_right = C->h_left;
        if (C->left != nullptr) C->left->parent = B;

        A->left = C->right;
        A->h_left = C->h_right;
        if (C->right != nullptr) C->right->parent = A;

        C->right = A;
        C->h_right = getHeight(A);
        C->left = B;
        C->h_left = getHeight(B);
        C->parent = A->parent;
        if (C->parent != nullptr) {
            if (A->parent->right == A) {
                A->parent->right = C;
            } else if (A->parent->left == A) {
                A->parent->left = C;
            }
        }
        A->parent = C;
        B->parent = C;

        int A_rank = 1;
        int B_rank = 1;
        int C_rank = 1;
        if (A->right != nullptr) A_rank += A->right->rank;
        if (A->left != nullptr) A_rank += A->left->rank;
        A->rank = A_rank;
        if (B->right != nullptr) B_rank += B->right->rank;
        if (B->left != nullptr) B_rank += B->left->rank;
        B->rank = B_rank;
        if (C->right != nullptr) C_rank += C->right->rank;
        if (C->left != nullptr) C_rank += C->left->rank;
        C->rank = C_rank;

        Key A_keys_sum = A->key;
        Key B_keys_sum = B->key;
        Key C_keys_sum = C->key;
        if (A->right != nullptr) A_keys_sum += A->right->sum_keys;
        if (A->left != nullptr) A_keys_sum += A->left->sum_keys;
        A->sum_keys = A_keys_sum;
        if (B->right != nullptr) B_keys_sum += B->right->sum_keys;
        if (B->left != nullptr) B_keys_sum += B->left->sum_keys;
        B->sum_keys = B_keys_sum;
        if (C->right != nullptr) C_keys_sum += C->right->sum_keys;
        if (C->left != nullptr) C_keys_sum += C->left->sum_keys;
        C->sum_keys = C_keys_sum;
    }

    static int getSize(Node *vertex) {
        if (vertex == nullptr) return 0;
        return 1 + getSize(vertex->left) + getSize(vertex->right);
    }

    static void sortToArray(Node *vertex, Node ***result) {
        if (vertex == nullptr) return;
        sortToArray(vertex->left, result);
        **result = vertex;
        (*result)++;
        sortToArray(vertex->right, result);
    }

    static Node *buildEmptyCompleteTree(int height) {
        if (height == -1) return nullptr;

        Node *left = buildEmptyCompleteTree(height - 1);
        Node *right = buildEmptyCompleteTree(height - 1);

        Node *root = new Node();
        if (right != nullptr) {
            root->right = right;
            root->h_right = getHeight(right);
            right->parent = root;
        }
        if (left != nullptr) {
            root->left = left;
            root->h_left = getHeight(left);
            left->parent = root;
        }

        return root;
    }

    static void
    removeVerticesFromCompleteTree(Node *root, int *leaves_to_remove) {
        if (root == nullptr) return;

        removeVerticesFromCompleteTree(root->right, leaves_to_remove);
        Node *left_son = root->left;
        if (root->left == nullptr && root->right == nullptr &&
            *leaves_to_remove > 0) {
            Node *parent = root->parent;
            if (parent->left == root) {
                parent->left = nullptr;
                parent->h_left--;
            } else {
                parent->right = nullptr;
                parent->h_right--;
            }
            (*leaves_to_remove)--;
            delete root;
        }
        removeVerticesFromCompleteTree(left_son, leaves_to_remove);
    }

    static void
    putValuesInEmptyIncompleteTree(Node *root, Node ***sorted_array) {
        if (root == nullptr) return;

        putValuesInEmptyIncompleteTree(root->left, sorted_array);
        Node *current = *(*sorted_array);
        root->data = current->data;
        root->key = current->key;
        (*sorted_array)++;
        putValuesInEmptyIncompleteTree(root->right, sorted_array);
    }

    static void swapNodesData(Node *v1, Node *v2) {
        T *temp_data = v1->data;
        Key temp_key = v1->key;

        v1->data = v2->data;
        v1->key = v2->key;

        v2->data = temp_data;
        v2->key = temp_key;
    }

    void deleteVertexLeaf(Node *node) {
        Node *parent = node->parent;
        if (parent == nullptr) {
            root = nullptr;
        } else if (parent->left == node) {
            parent->left = nullptr;
        } else {
            parent->right = nullptr;
        }
        delete node;
    }

    void deleteVertexOneSon(Node *node, string flag) {
        Node *parent = node->parent;
        Node *son;
        if (flag.compare("right") == 0) {
            son = node->right;
        } else { // "left"
            son = node->left;
        }

        if (parent == nullptr) {
            root = son;
            son->parent = nullptr;
        } else if (parent->right == node) {
            parent->right = son;
        } else {
            parent->left = son;
        }
        son->parent = parent;
        delete node;

    }

    Node *deleteVertex(Node *node) {
        Node *parent = node->parent;
        if (node->left == nullptr && node->right == nullptr) {
            deleteVertexLeaf(node);
        } else if (node->left == nullptr && node->right != nullptr) {
            deleteVertexOneSon(node, "right");
        } else if (node->right == nullptr && node->left != nullptr) {
            deleteVertexOneSon(node, "left");
        } else { // Two sons
            Node *iterator = node->right;
            while (iterator->left != nullptr) iterator = iterator->left;
            swapNodesData(iterator, node);
            parent = iterator->parent;
            deleteVertex(iterator); // one son or a leaf
        }
        return parent;
    }

    static int getBalanceFactor(Node *vertex) {
        return vertex->h_left - vertex->h_right;
    }

    static void deleteTreeRecursive(Node *root) {
        if (root == nullptr) {
            return;
        }
        deleteTreeRecursive(root->right);
        deleteTreeRecursive(root->left);



        delete root;
    }

    static Node *copyTreeRecursive(Node *root) {
        if (root == nullptr) return nullptr;

        Node *copy_node = new Node(*root);

        copy_node->right = copyTreeRecursive(root->right);
        if (copy_node->right != nullptr) copy_node->right->parent = copy_node;

        copy_node->left = copyTreeRecursive(root->left);
        if (copy_node->left != nullptr) copy_node->left->parent = copy_node;

        return copy_node;
    }

    static void inOrderToArrayRecursive(Node *root, T **array) {
        if (root == nullptr) return;
        inOrderToArrayRecursive(root->left, array);
        **array = *root->data;
        (*array)++;
        inOrderToArrayRecursive(root->right, array);
    }

    static void preOrderToArrayRecursive(Node *root, T **array) {
        if (root == nullptr) return;
        **array = *root->data;
        (*array)++;
        preOrderToArrayRecursive(root->left, array);
        preOrderToArrayRecursive(root->right, array);
    }

    static void updateRanks(Node *node, char flag) {
        while (node != nullptr) {
            if (flag == '+') node->rank++;
            if (flag == '-') node->rank--;
            node = node->parent;
        }
    }

    static void updateSumKeys(Node *parent, Key temp, char flag) {
        while (parent != nullptr) {
            if (flag == '+') parent->sum_keys += temp;
            if (flag == '-') parent->sum_keys -= temp;
            parent = parent->parent;
        }
    }

    static Key getTopKeys(Node *node, int k) {
        Key result;

        while (k != 0 && node != nullptr) {
            if (node->right != nullptr) {
                if (node->right->rank + 1 < k) {
                    result += node->right->sum_keys;
                    result += node->key;
                    k -= node->right->rank + 1;
                    node = node->left;
                } else if (node->right->rank + 1 > k) {
                    node = node->right;
                } else { // ==
                    result += node->right->sum_keys;
                    result += node->key;
                    k = 0;
                }
            } else if (node->left != nullptr) {
                if (k == 1) {
                    result += node->key;
                    k = 0;
                } else {
                    result += node->key;
                    k--;
                    node = node->left;
                }
            } else {
                result += node->key;
                break;
            }
        }

        return result;
    }

public:
    AVLTree() {
        root = nullptr;
    }

    AVLTree(const AVLTree &tree) {
        root = copyTreeRecursive(tree.root);
    }

    ~AVLTree() {
        deleteTreeRecursive(root);
    }

    AVLTree &operator=(const AVLTree &tree) {
        deleteTreeRecursive(root);
        root = copyTreeRecursive(tree.root);
        return *this;
    }

    T &find(Key key) {
        Node *node = binarySearch(key);
        if (node == nullptr || key != node->key) {
            throw AVLElementNotFound();
        }
        return *node->data;
    }

    bool insert(const T &data, Key key) {
        Node *parent = binarySearch(key);
        Node *new_node;
        if (parent != nullptr) {
            if (parent->key == key) return false;
            new_node = createVertex(parent, data, key);
        } else {
            new_node = new Node(data, key);
            root = new_node;
        }

        Node *p, *v = new_node;
        while (v != root) {
            p = v->parent;

            if (getHeight(p) >= getHeight(v) + 1) {
                if (p->right == v) {
                    p->h_right++;
                } else {
                    p->h_left++;
                }
                updateRanks(p, '+');
                updateSumKeys(p, new_node->key, '+');
                return true;
            }

            if (p->right == v) {
                p->h_right++;
            } else {
                p->h_left++;
            }
            p->rank++;
            p->sum_keys += new_node->key;

            if (abs(getBalanceFactor(p)) > 1) {
                updateRanks(p->parent, '+');
                updateSumKeys(p->parent, new_node->key, '+');
                if (getBalanceFactor(p) < 0) {
                    if (getBalanceFactor(p->right) < 0) {
                        roll_RR(p);
                    } else if (getBalanceFactor(p->right) > 0) {
                        roll_RL(p);
                    }
                } else if (getBalanceFactor(p) > 0) {
                    if (getBalanceFactor(p->left) < 0) {
                        roll_LR(p);
                    } else if (getBalanceFactor(p->left) > 0) {
                        roll_LL(p);
                    }
                }
                break;
            } else {
                v = p;
            }
        }
        return true;
    }

    bool remove(Key key) {
        Node *node = binarySearch(key);
        if (node == nullptr) return false;
        if (node->key != key) return false;

        Key deleted_key = node->key;
        Node *v = deleteVertex(node);
        Node *p = nullptr;
        while (v != nullptr) {
            p = v->parent;

            v->h_right = getHeight(v->right);
            v->h_left = getHeight(v->left);
            v->rank--;
            v->sum_keys -= deleted_key;

            if (abs(getBalanceFactor(v)) > 1) {
                updateRanks(v->parent, '-');
                updateSumKeys(v->parent, deleted_key, '-');
                int old_v_height = getHeight(v);
                if (getBalanceFactor(v) < 0) {
                    if (getBalanceFactor(v->right) < 0) {
                        roll_RR(v);
                    } else if (getBalanceFactor(v->right) > 0) {
                        roll_RL(v);
                    }
                } else if (getBalanceFactor(v) > 0) {
                    if (getBalanceFactor(v->left) < 0) {
                        roll_LR(v);
                    } else if (getBalanceFactor(v->left) > 0) {
                        roll_LL(v);
                    }
                }
                if (old_v_height == getHeight(v)) break;
                if (v == root) break;
            } else {
                if (v == root) break;
                v = p;
            }
        }
        return true;
    }

    static char getWeakTree(AVLTree &tree1, AVLTree &tree2, int k1, int k2) {
        Key sum_tree1 = getTopKeys(tree1.root, k1);
        Key sum_tree2 = getTopKeys(tree2.root, k2);
        if (sum_tree1 > sum_tree2) return '2';
        else if (sum_tree1 < sum_tree2) return '1';
        else return '=';
    }

    T *inOrderToArray() const {
        if (root == nullptr) return nullptr;
        T *result = new T[getSize(root)];
        T *temp = result;
        inOrderToArrayRecursive(root, &temp);
        return result;
    }

    T *preOrderToArray() const {
        if (root == nullptr) return nullptr;
        T *result = new T[getSize(root)];
        T *temp = result;
        preOrderToArrayRecursive(root, &temp);
        return result;
    }
};

#endif //DATASTRUCTURES_HW1_AVLTREE_H
