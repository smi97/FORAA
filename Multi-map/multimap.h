#include <iostream>
#include <vector>
namespace smi
{
    template <class Key, class T>
    struct Node
    {
        Key key;
        std::vector <T> data;
        Node *right, *left, *parent;
        bool _end;

        Node(): key(0), left(nullptr), parent(nullptr), right(nullptr), _end(false) { }

        Node( Key k, std::vector<T> d) :key(k), data(d), left(nullptr), parent(nullptr), right(nullptr)
        {    }

        Node( Key k, T d) :key(k), left(nullptr), parent(nullptr), right(nullptr), _end(false)
        {
            data.push_back(d);
        }

        Node(Key k, Node * _left, Node * _right, Node * _parent, bool end)
        : key(k), left(_left), right(_right), parent(_parent), _end(end)
        {}

        Node & operator=(const Node & noda)
        {
            if (this == &noda)
                return (*this);
            key = noda.key;
            data = noda.data;
            return *this;
        }

        bool operator!=(const Node & noda)
        {
            return ((key != noda.key) && (data !=noda.data));
        }

        friend std::ostream& operator<<(std::ostream& out, const Node<Key, T> & noda)
        {
            out << noda.key << std::endl;
            for (std::vector<int>::const_iterator i = noda.data.begin(); i != noda.data.end(); ++i)
                out << *i << ' ';
            return out;
        }
        ~Node() {}
    };

    template < class Key, // multimap::key_type
    class T, // multimap::mapped_type
    class Compare = std::less<Key> // multimap::key_compare
    > class multimap
    {
    public:
        multimap(const Compare& c = Compare()) : root(nullptr), quantity(0), Comp(c)
        {    }

        template<class Iterator>
        multimap(Iterator begin, Iterator end, const Compare& c = Compare()) : root(nullptr), Comp(c)
        {
            for (Iterator it = begin; it != end; it++)
                this->insert(it.el->key, it.el->data);
        }

        multimap(const multimap& mltmp) : quantity(0), maxSize(mltmp.max_size()), Comp(mltmp.Comp), root(nullptr)
        {
            for (multimap::iterator it = mltmp.begin(); it != mltmp.end(); ++it)
            {
                for (std::vector<int>::const_iterator i = it.el->data.begin(); i != it.el->data.end(); ++i)
                insert(it.el->key, *i);
            }
            
        }

        multimap & operator=(const multimap & mltmp)
        {
            if (this == &mltmp)
                return *this;
            if (!empty())
                clear();
            for (multimap::iterator it = mltmp.begin(); it != mltmp.end(); ++it)
            {
                for (std::vector<int>::const_iterator i = it.el->data.begin(); i != it.el->data.end(); ++i)
                    insert(it.el->key, *i);
            }
            return *this;
        }

        class iterator
        {
        public:
            friend class multimap;
            iterator(const Compare& c = Compare()) : el(nullptr), Comp(c)
            {}

            iterator(Node<Key, T> * ptr, const Compare& c = Compare()) : el(ptr), Comp(c)
            {}

            iterator(const iterator & it) :el(it.el)
            {}

            iterator operator=(const iterator & it)
            {
                if (el == it.el)
                    return *this;
                el = it.el;
                return (*this);
            }

            Node<Key, T> & operator*()
            {
                if (el == nullptr)
                    std::cerr << "Wrong iter";
                return (*el);
            }

            Node<Key, T> * operator->()
            {
                if (el == nullptr)
                    std::cerr << "Wrong iter";
                return (el);
            }

            bool operator==(const iterator & it)
            {
                return (it.el == el);
            }

            bool operator!=(const iterator & it)
            {
                return (it.el != el);
            }

            iterator operator++()
            {
                if (!el)
                    return *this;
                if(find_next(el))
                {
                    el = find_next(el);
                    return *this;
                }
                else
                {
                    el = el->right;
                    return *this;
                }
            }

            iterator operator--()
            {
                if (!el)
                    return *this;
                if(find_prev(el))
                {
                    el = find_prev(el);
                    return *this;
                }
                else
                {
                    el = el->left;
                    return *this;
                }

                return *this;
            }

            iterator operator++(int)
            {
                iterator it(*this);
                ++it;
                el = it.el;
                return *this;
            }

            iterator operator--(int)
            {
                iterator it(*this);
                --it;
                el = it.el;
                return *this;
            }


            ~iterator() = default;

        private:
            Node<Key, T> * el;
            Compare Comp;

            Node<Key, T> * find_prev(Node<Key, T> * x)
            {
                Node<Key, T> * y;
                if(x->left != 0)
                    return find_max(x->left);
                y=x->parent;
                while(y!=0 && x == y->left)
                {
                    x = y;
                    y = y->parent;
                }
                return y;
            }

            Node<Key, T> * find_max(Node<Key, T> * x)
            {
                while(x->right != 0)
                    x = x->right;
                return x;
            }

            Node<Key, T> * find_next(Node<Key, T> * x)
            {
                Node<Key, T> * y;
                if(x->right != 0)
                    return find_min(x->right);
                y = x->parent;
                while(y != 0 && x == y->right)
                {
                    x = y;
                    y = y->parent;
                }
                return y;
            }

            Node<Key, T> * find_min(Node<Key, T> * x)
            {
                while(x->left != 0)
                    x = x->left;
                return x;
            }

        };

        iterator begin() const
        {
            Node<Key, T> * pi = root;
            while (pi->left != nullptr)
                pi = pi->left;
            return iterator(pi);
        }

        iterator end() const
        {
            Node<Key, T> * pi = root;
            while (pi->right != 0)
                pi = pi->right;
            if (!(pi->_end))
            {
                pi->right = new Node<Key,T>(0, 0, 0, pi, true);
                return iterator(pi->right);
            }
            return iterator(pi);
        }
        
        iterator find(const Key& val)
        {
            return iterator(find_node(root, val));
        }

        int insert(Key x, T _data)
        {
            if (quantity == maxSize)
                return 1;
            ++quantity;
            Node<Key, T>* ptr = root;
            Node<Key, T>* ptr1 = 0;
            while(ptr!=0)
            {
                ptr1=ptr;
                if(x == ptr->key)
                {
                    ptr->data.push_back(_data);
                    return 0;
                }
                else if (Comp(x, ptr->key))
                    ptr=ptr->left;
                else
                    ptr=ptr->right;
            }
            Node<Key, T>* n=new Node<Key, T>(x, _data);

            n->parent = ptr1;

            if(ptr1 == 0)
                root=n;
            else
            {
                if(Comp(x, ptr1->key))
                    ptr1->left=n;
                else
                    ptr1->right=n;
            }
            return 0;
        }

        template<class Iterator>
        void insert(Iterator begin, Iterator end)
        {
            for (Iterator it = begin; it != end; it++)
                insert(it.el->key, it.el->data);
        }

        Node<Key, T> * erase(const Key & k)
        {
            --quantity;

            if (quantity == 0)
            {
                root = nullptr;
                return root;
            }

            if (root == nullptr)
                throw std::invalid_argument("multimap is empty");

            Node<Key, T> * y;
            Node<Key, T> * x;
            Node<Key, T> * z = find_node(root, k);

            if(z->left == 0 || z->right == 0)
                y=z;
            else
                y=find_next(z->key);
            if(y->left!=0)
                x=y->left;
            else
                x=y->right;
            if(x!=0)
                x->parent=y->parent;
            if(y->parent == 0)
                root=x;
            else
            {
                if (y== (y->parent)->left)
                    (y->parent)->left=x;
                else
                    (y->parent)->right=x;
            }
            if(y!=z)      {
                z->key=y->key;
                z->data=y->data;
            }
            return y;
        }
        template<class Iterator>
        void erase(Iterator begin, Iterator end)
        {
            for (Iterator it = begin; it != end; it++)
                erase(it.el->key);
        }
        void print() const
        {
            walk(root);
            std::cout << std::endl;
        }

        size_t size() const
        {
            return quantity;
        }

        size_t max_size() const
        {
            return maxSize;
        }

        bool empty() const
        {
            return (root == nullptr);
        }

        void swap(multimap & mltmp)
        {
            multimap buf(*this);
            clear();
            *this = mltmp;
            mltmp = buf;
        }

        size_t count (const Key & k) const
        {
            Node<Key, T> * n = find_node(root, k);
            return n->data.size();
        }

        friend std::ostream& operator<<(std::ostream& out, const multimap & mltmp)
        {
            mltmp.walk(mltmp.root);
            return out;
        }

        void clear()
        {
            quantity = 0;
            del(root);
            root = nullptr;
        }

        bool operator==(multimap<Key, T>& second)
        {
            if (size() != second.size())
                return false;
            iterator it1 = second.begin();
            for (iterator it = begin(); it != end(); ++it)
            {
                if (*it != *it1)
                    return false;
                ++it1;
            }
            return true;
        }

        bool operator!=(multimap<Key, T>& second)
        {
            return (!(*this == second));
        }

        ~multimap()
        {
            this->clear();
        }
    private:
        iterator it;
        size_t quantity;
        size_t maxSize = 1000000;
        Compare Comp;
        Node<Key, T> *root;
        
        Node<Key, T>* find_next(Key val)
        {
            Node<Key, T> * x = find_node(root, val);
            Node<Key, T> * y;
            if(x == 0)
                return 0;
            if(x->right!=0)
                return find_min(x->right);
            y=x->parent;
            while(y!=0 && x == y->right)
            {
                x=y;
                y=y->parent;
            }
            return y;
        }
        
        Node<Key, T> * find_min(Node<Key, T> * x)
        {
            while(x->left!=0)
                x=x->left;
            return x;
        }
        
        Node<Key, T> * find_node(Node<Key, T> * n, const Key & val)
        {
            Node<Key, T>* ptr = root;
            while(ptr != nullptr)
            {
                if(val == ptr->key)
                    return ptr;
                else
                    if (Comp(val, ptr->key))
                        ptr=ptr->left;
                    else
                        ptr=ptr->right;
            }
            std::cout << "error!!!" << std::endl;
            return nullptr;
        }
        
        void walk(Node<Key, T> * n) const
        {
            if(n!=0)
            {
                walk(n->left);
                std::cout << n->key << std::endl;
                for (std::vector<int>::const_iterator i = n->data.begin(); i != n->data.end(); ++i)
                    std::cout << *i << ' ';
                std::cout <<  std::endl;
                walk(n->right);
            }
        }
        
        void del(Node<Key, T> * x)
        {
            if (x)
            {
                del(x->left);
                del(x->right);
                delete x;
            }
        }
        
    };


}
