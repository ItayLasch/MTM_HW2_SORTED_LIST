#ifndef SORTED_LIST_H
#define SORTED_LIST_H
#include <iostream>
#include <stdexcept>


namespace mtm
{
    static const std::string out_of_range_error = "out of range";
    static const int empty_list = - 1;
    template <class T>
    class SortedList;

    template <class T>
    class Node
    {
        T data;
        Node<T> *next;

    public:
        Node() = delete;
        /**
        * @brief Constructs new node wich holds type T data
        * @param data - data from a generic type.
        */
        Node(const T data);
        /**
        * Copy Constractor - default function.
        * @brief Constructs a copy of the node that given as parameter.
        * @param node - The node to make copy of himself.
        */
        Node(const Node<T> &node) = default;
        /**
        * destractur - default function.
        * @brief delete the node and all the data he contains.
        */
        ~Node() = default;
        /**
        * operator= - default function.
        * @brief delelt the existing node and constructs a copy of the node that given as parameter.
        * @param node - The node to make copy of himself.
        */
        Node &operator=(const Node<T> &node) = default;
        friend class SortedList<T>;
    };

    template <class T>
    Node<T>::Node(const T data) : data(data), next(nullptr)
    {
    }

    template <class T>
    class SortedList
    {
        Node<T> *head;
        int size;
        /**
         * @brief destroys all list elements without destroying the list itself.
         * @return (void)
         */
        void DestroyList();

    public:
        class const_iterator;
        /**
         * @brief Constructs a new empty list.
         */
        SortedList();

        /**
         * @brief Constructs a new list using another sorted_list elements.
         * @param sorted_list - list we want to copy.
         */
        SortedList(const SortedList &sorted_list);

        /**
         * @brief Dealocates a list and all it's elements.
         */
        ~SortedList();

        /**
         * @brief Copies and implements another list elements to an existing list(this).
         * @param other_list - list we copy it's elements.
         * @return this after it has changed.
         */
        SortedList &operator=(const SortedList &other_list);
        
        /**
         * @brief inserts a new data to the list while keeping it sorted.
         * @param data - new data we want to insert into the list.
         * @return (void)
         */
        void insert(const T &data);

        /**
         * @brief Removes a specific data from the list which the iterator point to.
         * @param iterator - iterator which points to the element we want to remove.
         * @return (void)
         * @possible_Exceptions - std::out_of_range - if the iterator is pointing outside of the list or if the
         * list is empty to begin with.
         */
        void remove(const SortedList<T>::const_iterator &iterator);
        /**
        * @brief Count the number of elements in the list.
        * @return The number on element in the list.
        */

        /**
         * @brief Length
         * @return Returns the number of elements in the list.
         */
        int length() const;

        /**
         * @brief Runs over the list with a boolian expression and filters the list to a new one.
         * @param c A boolian condition which filters only the elements that return true with it.
         * @return A new result list after the filter was applied.
         */
        template <class Condition>
        SortedList filter(Condition c) const;

        /**
         * @brief Runs over the list with a function and applies changes on the list elements and then 
         * inserts them to a new one.
         * @param op - A function that we apply on each element in the list.
         * @return - A new result list with the older list elements after they went threw the function operation.
         */
        template <class Operation>
        SortedList apply(Operation op);

        /**
         * @brief begin
         * @return A const iterator that points to the first element of the list
         */
        const_iterator begin() const;
        /**
         * @brief end
         * @return A const iterator that points to the end of the list - nullptr
         */
        const_iterator end() const;
    };

    template <class T>
    class SortedList<T>::const_iterator
    {
        Node<T> *node;
        int index;
        /**
         * @brief 
         * @return Returns the pointer to the node which the iterator points to.  
         */
        Node<T> *getNode() { return this->node; }
        /**
         * @brief Constructs a new const_iterator with a node to point to and an index to indicate it's location 
         * in the list.
         * @param node - node wich the iterator points to.
         * @param index - index in the list.
         */
        const_iterator(Node<T> *node, int index) : node(node), index(index) {}
        friend class SortedList<T>;

    public:
        const_iterator() = delete;

        /**
         * @brief Constructs a new iterator using another one's elemetns.
         * @param other_it - iterator we want to copy its elements.
         */
        const_iterator(const SortedList<T>::const_iterator &other_it);

        /**
         * @brief Deallocates the const_iterator.
         */
        ~const_iterator() = default;

        /**
         * @brief Copies and implements another iterator's elemtns to this.
         * @param it - iterator we copy it's elements.
         * @return this after it has changed.
         */
        const_iterator &operator=(const const_iterator &it) = default;

        /**
         * @brief 
         * @return Returns the data which the const_iterator points to, using the node that holds it.
         * @possivle_Exceptions - std::out_of_range - if the iteratot does'nt points outside the list elements.
         */
        const T &operator*() const;

        /**
         * @brief advances the iterator to the next element in the list and returns it.
         * @return this after we advanced it.
         * @possivle_Exceptions - std::out_of_range - if the iteratot does'nt points outside the list elements.
         */
        const_iterator &operator++();

        /**
         * @brief advances the iterator to the next element but returns it's location before the advancement.
         * @return this before we advanced it.
         * @possivle_Exceptions - std::out_of_range - if the iteratot does'nt points outside the list elements.
         */
        const_iterator operator++(int);
        /**
         * @brief checks if two iterators from the same list points to the same element in that list.
         * @param it - other iterator to compare with.
         * @return true - if iterators points to the same element, false - otherwise.
         */
        bool operator==(const const_iterator &it) const;
    };

    template <class T>
    SortedList<T>::SortedList()
    {

        this->head = nullptr;
        this->size = 0;
    }

    template <class T>
    SortedList<T>::SortedList(const SortedList &sorted_list) : head(nullptr), size(empty_list)
    {
        Node<T> *tmp = sorted_list.head;

        while (tmp != nullptr)
        {
            this->insert(tmp->data);
            tmp = tmp->next;
        }
        this->size++;
    }

    template <class T>
    void SortedList<T>::DestroyList()
    {
        Node<T> *toDelete, *tmp = this->head;
        while (tmp != nullptr)
        {
            toDelete = tmp;
            tmp = tmp->next;
            delete toDelete;
        }
    }

    template <class T>
    SortedList<T>::~SortedList()
    {
        DestroyList();
    }

    template <class T>
    SortedList<T> &SortedList<T>::operator=(const SortedList<T> &other_list)
    {
        if(this == &other_list)
        {
            return *this;
        }
        this->size = 0;
        DestroyList();
        this->head = nullptr;
        Node<T> *tmp = other_list.head;
        while (tmp != nullptr)
        {
            this->insert(tmp->data);
            tmp = tmp->next;
        }
        return *this;
    }

    template <class T>
    void SortedList<T>::insert(const T &data)
    {
        T copy_data = data;
        Node<T> *new_node = new Node<T>(copy_data);
        if (this->head == nullptr || copy_data < this->head->data)
        {
            new_node->next = this->head;
            this->head = new_node;
        }
        else
        {
            Node<T> *ptr = this->head;
            while (ptr->next != nullptr)
            {
                if (copy_data < ptr->next->data)
                {
                    new_node->next = ptr->next;
                    ptr->next = new_node;
                    this->size++;
                    return;
                }
                ptr = ptr->next;
            }

            new_node->next = ptr->next;
            ptr->next = new_node;
        }
        this->size++;
    }

    template <class T>
    void SortedList<T>::remove(const SortedList<T>::const_iterator &iterator)
    {
        if(iterator.node == nullptr){
            throw std::out_of_range(out_of_range_error);
        }
        
        if(this->head == nullptr){
            return;
        }

        SortedList<T>::const_iterator prev = begin();
        if (prev == iterator)
        {
            Node<T> *tmp = this->head;
            this->head = this->head->next;
            delete tmp;
            this->size--;
            return;
        }

        for (SortedList<T>::const_iterator it = begin(); !(it == end()); ++it)
        {
            if (it == iterator)
            {
                prev.getNode()->next = it.getNode()->next;
                delete it.getNode();
                this->size--;
                return;
            }
            prev = it;
        }
    }

    template <class T>
    int SortedList<T>::length() const
    {
        return this->size;
    }

    template <class T>
    template <class Condition>
    SortedList<T> SortedList<T>::filter(Condition c) const
    {
        SortedList<T> result;
        for (SortedList<T>::const_iterator it = begin(); !(it == end()); ++it)
        {
            if (c(*it))
            {
                result.insert(*it);
            }
        }
        return result;
    }

    template <class T>
    template <class Operation>
    SortedList<T> SortedList<T>::apply(Operation op)
    {
        SortedList<T> result;
        for (SortedList<T>::const_iterator it = begin(); !(it == end()); ++it)
        {
            result.insert(op(*it));
        }
        return result;
    }

    template <class T>
    typename SortedList<T>::const_iterator SortedList<T>::begin() const
    {
        if (this->head == nullptr)
        {
            return const_iterator(this->head, empty_list);
        }
        return const_iterator(this->head, empty_list + 1);
    }

    template <class T>
    typename SortedList<T>::const_iterator SortedList<T>::end() const
    {
        Node<T> *tmp = this->head;
        if (tmp == nullptr)
        {
            return const_iterator(tmp, empty_list);
        }

        while (tmp->next != nullptr)
        {
            tmp = tmp->next;
        }

        return const_iterator(tmp->next, this->size);
    }

    /*==============================ITERATOR CLASS==============================*/
    template <class T>
    SortedList<T>::const_iterator::const_iterator(const SortedList<T>::const_iterator &other_it)
    {
        this->node = other_it.node;
        this->index = other_it.index;
    }

    template <class T>
    bool SortedList<T>::const_iterator::operator==(const const_iterator &other_iter) const
    {
        if (this->index == other_iter.index)
        {
            return true;
        }

        return false;
    }

    template <class T>
    const T &SortedList<T>::const_iterator::operator*() const
    {
        if (this->node == nullptr)
        {
            throw std::out_of_range(out_of_range_error);
        }

        return this->node->data;
    }

    template <class T>
    typename SortedList<T>::const_iterator &SortedList<T>::const_iterator::operator++()
    {
        if (this->node == nullptr)
        {
            throw std::out_of_range(out_of_range_error);
        }

        this->node = this->node->next;
        this->index++;
        return *this;
    }

    template <class T>
    typename SortedList<T>::const_iterator SortedList<T>::const_iterator::operator++(int)
    {
        if (this->node == nullptr)
        {
            throw std::out_of_range(out_of_range_error);
        }
        const_iterator result = *this;
        this->node = this->node->next;
        this->index++;
        return result;
    }
}
#endif