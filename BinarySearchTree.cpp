#include <iostream>
#include <vector>

struct BinaryTreeNode
{
    int _val;
    BinaryTreeNode *_left;
    BinaryTreeNode *_right;

    BinaryTreeNode() : _left(nullptr), _right(nullptr) {}
    BinaryTreeNode(int val) : _val(val), _left(nullptr), _right(nullptr) {}
};

class BinarySearchTree
{
public:
    BinarySearchTree() : _root(nullptr) {}
    BinarySearchTree(const std::vector<int> &list) : _root(nullptr)
    {
        for (auto e : list)
            insert(e);
    }
    bool insert(int val)
    {
        if (!_root) {
            _root = new BinaryTreeNode(val);
            return true;
        }
        // 在树中插入val
        // 若已存在相同值的节点，则不再插入，返回false
        // 查找失败的情况下，p指向可插入val的节点
        // 若不存在，则按照val和p->_val的大小关系成为p的左孩子或右孩子
        BinaryTreeNode *p = nullptr;
        if (search(val, p))
            return false;
        if (val < p->_val)
            p->_left = new BinaryTreeNode(val);
        if (val > p->_val)
            p->_right = new BinaryTreeNode(val);
        return true;
    }
    bool remove(int val)
    {
        return _remove(_root, val, nullptr, false);
    }
    bool search(int val, BinaryTreeNode *&p)
    {
        // 查找值为val的节点
        // 查找成功，返回true，指针p指向该节点
        // 查找失败，返回false，指针p指向最后一个访问的节点，即可以插入val的位置
        return _search(_root, val, nullptr, p);
    }
    ~BinarySearchTree()
    {
        // TODO: Improve performance
        while (_root != nullptr)
        {
            remove(_root->_val);
        }
    }
    void inOrder()
    {
        std::cout << "In Order  :";
        _inOrder(_root);
        std::cout << std::endl;
    }
    void preOrder()
    {
        std::cout << "Pre Order :";
        _preOrder(_root);
        std::cout << std::endl;
    }
    void postOrder()
    {
        std::cout << "Post Order:";
        _postOrder(_root);
        std::cout << std::endl;
    }

private:
    BinaryTreeNode *_root;
    bool _search(BinaryTreeNode *root, int val, BinaryTreeNode *parent, BinaryTreeNode *&p)
    {
        // 查找值为val的节点
        // 查找成功，返回true，指针p指向该节点
        // 查找失败，返回false，指针p指向最后一个访问的节点，即可以插入val的位置
        // 指针parent指向root的父亲节点
        if (root == nullptr)
        {
            p = parent;
            return false;
        }
        if (root->_val == val)
        {
            p = root;
            return true;
        }
        if (root->_val > val)
            return _search(root->_left, val, root, p);
        return _search(root->_right, val, root, p);
    }
    bool _remove(BinaryTreeNode *root, int val, BinaryTreeNode *parent, bool left)
    {
        if (root == nullptr)
            return false;
        if (val < root->_val)
            return _remove(root->_left, val, root, true);
        if (val > root->_val)
            return _remove(root->_right, val, root, false);

        // if val == root->_val
        // 如果左右子树均不空，则让root左子树的最右子节点替代root的位置
        if (root->_left != nullptr && root->_right != nullptr)
        {
            BinaryTreeNode *rightmost = root->_left;
            BinaryTreeNode *rightmost_parent = nullptr;
            while (rightmost->_right != nullptr)
            {
                rightmost_parent = rightmost;
                rightmost = rightmost->_right;
            }
            rightmost->_right = root->_right;
            if (rightmost_parent != nullptr)
                rightmost_parent->_right = nullptr;
            if (parent != nullptr)
            {
                if (left)
                    parent->_left = rightmost;
                else
                    parent->_right = rightmost;
            }
            else
                _root = rightmost;

            delete root;
            return true;
        }
        // 只有左子树
        else if (root->_left != nullptr)
        {
            if (parent != nullptr)
            {
                if (left)
                    parent->_left = root->_left;
                else
                    parent->_right = root->_left;
            }
            else
                _root = root->_left;
            delete root;
            return true;
        }
        // 只有右子树
        else if (root->_right != nullptr)
        {
            if (parent != nullptr)
            {
                if (left)
                    parent->_left = root->_right;
                else
                    parent->_right = root->_right;
            }
            else
                _root = root->_right;
            delete root;
            return true;
        }
        // 无孩子
        else
        {
            // Leaf node
            if (parent != nullptr)
            {
                if (left)
                    parent->_left = nullptr;
                else
                    parent->_right = nullptr;
            }
            // Root node
            else
                _root = nullptr;
            delete root;
            return true;
        }
    }
    void _inOrder(BinaryTreeNode *root)
    {
        if (!root)
            return;
        _inOrder(root->_left);
        std::cout << root->_val << " ";
        _inOrder(root->_right);
    }
    void _preOrder(BinaryTreeNode *root)
    {
        if (!root)
            return;
        std::cout << root->_val << " ";
        _preOrder(root->_left);
        _preOrder(root->_right);
    }
    void _postOrder(BinaryTreeNode *root)
    {
        if (!root)
            return;
        _postOrder(root->_left);
        _postOrder(root->_right);
        std::cout << root->_val << " ";
    }
};

int main()
{
    std::vector<int> list{88, 47, 19, 55, 50, 98};
    BinarySearchTree bst(list);
    bst.inOrder();
    bst.preOrder();
    bst.insert(66);
    bst.inOrder();
    bst.preOrder();
    
    bst.remove(47);
    bst.inOrder();
    bst.preOrder();
}