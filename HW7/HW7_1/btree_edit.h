#include <memory>
#include <iostream>
#include <utility>
using std::make_unique;
using std::unique_ptr;
using std::move;
using std::cout;

struct node {
    node(int val): key_value(val), left(nullptr), right(nullptr) {}
    int key_value;
    unique_ptr<node> left;
    unique_ptr<node> right;
};

class btree
{
    public:
		btree() {
			root = nullptr;
		}
		~btree() {
			destroy_tree();
		}

		void insert(int key) {
			if (root != nullptr) {
                insert(key, root);
            } else {
				root = make_unique<node>(key);
			}
		}
		unique_ptr<node>* search(int key) {
			return search(key, root);
		}

		void destroy_tree() {
			destroy_tree(root);
		}


    private:
		void destroy_tree(unique_ptr<node>& leaf) {
			if (leaf != nullptr)
			{
				destroy_tree(leaf->left);
				destroy_tree(leaf->right);
			}
		}
		void insert(int key, unique_ptr<node>& leaf) {
			if (key< leaf->key_value)
			{
				if (leaf->left != nullptr)
					insert(key, leaf->left);
				else
				{
					leaf->left = make_unique<node>(key);
				}
			}
			else if (key >= leaf->key_value)
			{
				if (leaf->right != nullptr)
					insert(key, leaf->right);
				else
				{
					leaf->right = make_unique<node>(key);
				}
			}
		}
		unique_ptr<node>* search(int key, unique_ptr<node>& leaf) {
			if (leaf != nullptr)
			{
				if (key == leaf->key_value)
					return &leaf;
				if (key<leaf->key_value)
					return search(key, leaf->left);
				else
					return search(key, leaf->right);
			}
			else return nullptr;
		}

        unique_ptr<node> root;
};
