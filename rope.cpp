#include <cstdio>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

struct Node {
    char character;
    int size;
    Node* left;
    Node* right;
    Node* parent;

    Node(char ch) : character(ch), size(1), left(nullptr), right(nullptr), parent(nullptr) {}
};

int getSize(Node* v) {
    return v ? v->size : 0;
}

void update(Node* v) {
    if (!v) return;
    v->size = 1 + getSize(v->left) + getSize(v->right);
    if (v->left) v->left->parent = v;
    if (v->right) v->right->parent = v;
}

void small_rotation(Node* v) {
    Node* parent = v->parent;
    if (!parent) return;
    Node* grandparent = parent->parent;
    if (parent->left == v) {
        Node* m = v->right;
        v->right = parent;
        parent->left = m;
    } else {
        Node* m = v->left;
        v->left = parent;
        parent->right = m;
    }
    update(parent);
    update(v);
    v->parent = grandparent;
    if (grandparent) {
        if (grandparent->left == parent) grandparent->left = v;
        else grandparent->right = v;
    }
}

void big_rotation(Node* v) {
    if (v->parent->left == v && v->parent->parent->left == v->parent) {
        small_rotation(v->parent);
        small_rotation(v);
    } else if (v->parent->right == v && v->parent->parent->right == v->parent) {
        small_rotation(v->parent);
        small_rotation(v);
    } else {
        small_rotation(v);
        small_rotation(v);
    }
}

void splay(Node*& root, Node* v) {
    if (!v) return;
    while (v->parent) {
        if (!v->parent->parent) {
            small_rotation(v);
            break;
        }
        big_rotation(v);
    }
    root = v;
}

// Find node at 1-based index k (rank-based lookup)
Node* find(Node*& root, int k) {
    Node* v = root;
    while (v) {
        int left_size = getSize(v->left);
        if (k == left_size + 1) {
            splay(root, v);
            return v;
        } else if (k <= left_size) {
            v = v->left;
        } else {
            k -= (left_size + 1);
            v = v->right;
        }
    }
    return nullptr;
}

// Splits root into left (contains first k elements) and right trees
void split(Node* root, int k, Node*& left, Node*& right) {
    if (k <= 0) {
        left = nullptr;
        right = root;
        return;
    }
    if (k >= getSize(root)) {
        left = root;
        right = nullptr;
        return;
    }
    Node* rem = find(root, k);
    right = rem->right;
    if (right) right->parent = nullptr;
    rem->right = nullptr;
    left = rem;
    update(left);
}

Node* merge(Node* left, Node* right) {
    if (!left) return right;
    if (!right) return left;
    Node* max_node = left;
    while (max_node->right) {
        max_node = max_node->right;
    }
    splay(left, max_node);
    left->right = right;
    right->parent = left;
    update(left);
    return left;
}

class Rope {
    Node* root;

    void traverse_and_build_string(Node* v, string& s) {
        if (!v) return;
        traverse_and_build_string(v->left, s);
        s += v->character;
        traverse_and_build_string(v->right, s);
    }

public:
    Rope(const string &s) {
        root = nullptr;
        for (char ch : s) {
            root = merge(root, new Node(ch));
        }
    }

    void process(int i, int j, int k) {
        Node* left = nullptr;
        Node* middle = nullptr;
        Node* right = nullptr;

        // Extract target substring S[i..j]
        split(root, i, left, middle);
        split(middle, j - i + 1, middle, right);

        // Recombine remaining framework
        Node* remainder = merge(left, right);

        Node* rem_left = nullptr;
        Node* rem_right = nullptr;

        // Insert string chunk back into position k
        split(remainder, k, rem_left, rem_right);
        root = merge(merge(rem_left, middle), rem_right);
    }

    string result() {
        string s = "";
        traverse_and_build_string(root, s);
        return s;
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    string s;
    if (cin >> s) {
        Rope rope(s);
        int actions;
        cin >> actions;
        for (int action_index = 0; action_index < actions; ++action_index) {
            int i, j, k;
            cin >> i >> j >> k;
            rope.process(i, j, k);
        }
        cout << rope.result() << "\n";
    }
    return 0;
}
