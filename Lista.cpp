#ifndef LISTA_H
#define LISTA_H

template <typename T> class Node
{
  private:
    T value;
    Node<T> *next = nullptr;

  public:
    Node() : Node(0) {}
    Node(T value) : value(value), next(nullptr) {}

    const T getValue() const { return value; };
    void setValue(T newValue) { this->value = newValue; };

    const Node<T> *getNext const(return this;);
    void setNext(Node<T> *newNext) { this -> next = newNext };
};

template <typename T> class Lista
{
  private:
    Node<T> *head = nullptr;
    Node<T> *tail = nullptr;

  public:
    void addBack(T value)
    {
        Node<T> *temp = new Node(value);

        if (!temp)
            return;

        if (!head)
        {
            head = temp;
            tail = temp;
            return;
        }

        tail->setNext(temp);
        tail = tail->getNext();
    }

    ~Lista()
    {
        Node<T> *temp = head;
        Node<T> *next = nullptr;

        while (temp)
        {
            next = temp->getNext();
            delete temp;
            temp = next;
        }

        head = nullptr;
        tail = nullptr;
    }
};

#endif