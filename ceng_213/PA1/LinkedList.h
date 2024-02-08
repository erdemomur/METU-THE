#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

#include "Node.h"

template <class T>
class LinkedList
{
public: // DO NOT CHANGE THIS PART.
    LinkedList();
    LinkedList(const LinkedList<T> &rhs);
    ~LinkedList();

    LinkedList<T> &operator=(const LinkedList<T> &rhs);

    int getSize() const;
    bool isEmpty() const;
    bool containsNode(Node<T> *node) const;
    int getIndex(Node<T> *node) const;

    Node<T> *getFirstNode() const;
    Node<T> *getLastNode() const;
    Node<T> *getNode(const T &data) const;
    Node<T> *getNodeAtIndex(int index) const;

    void append(const T &data);
    void prepend(const T &data);
    void insertAfterNode(const T &data, Node<T> *node);
    void insertAtIndex(const T &data, int index);
    void moveToIndex(int currentIndex, int newIndex);
    void mergeNodes(int sourceIndex, int destIndex);

    void removeNode(Node<T> *node);
    void removeNode(const T &data);
    void removeNodeAtIndex(int index);
    void removeAllNodes();

    void print() const;

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.

private: // DO NOT CHANGE THIS PART.
    Node<T> *head;
    int size;
};

template<class T>
LinkedList<T>::LinkedList()
{
    /* TODO */
    head=new Node<T>(T());
    size=0;
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T> &rhs)
{
    /* TODO */
    size = rhs.size;
    head = new Node<T>(T());
    
    Node<T>* current1;
    current1 = head;
    
    Node<T>* current2;
    current2 = rhs.head->next;
    
    while(current2 != NULL){
        Node<T>*newNode = new Node<T>(T());
        newNode->data = current2->data;
        current1->next = newNode;
        newNode->prev = current1;
        current1 = current1->next;
        current2 = current2->next;
    }
}

template<class T>
LinkedList<T>::~LinkedList()
{
    /* TODO */
    removeAllNodes();
    delete head;
}

template<class T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &rhs)
{
    /* TODO */
    removeAllNodes();
    size = 0;
        
    Node<T>* current1 = rhs.head->next;
    Node<T>* current2 = head;
    while(current1!= NULL){
        
        Node<T>*newNode = new Node<T>(T());
        newNode->data = current1->data;
        newNode->prev = current2;
        current2->next = newNode;
        newNode->next = NULL;
        
        current1 = current1->next;
        current2 = newNode;
        size = size+1;
        }
    return *this;
}


template<class T>
int LinkedList<T>::getSize() const
{
    /* TODO */
    int list_size=0;
    Node<T>* current = head->next;
    while(current != NULL){
        current = current->next;
        list_size = list_size + 1;
    }
    return list_size;
}

template<class T>
bool LinkedList<T>::isEmpty() const
{
    /* TODO */
    if(head->next==NULL) return true;
    else return false;
}

template<class T>
bool LinkedList<T>::containsNode(Node<T> *node) const
{
    /* TODO */
    Node<T>* current = head->next;
    while(current != NULL){
        if(current->data==node->data &&  current->prev==node->prev && current->next==node->next) return true;
        current=current->next;
    }
    return false;
}

template<class T>
Node<T> *LinkedList<T>::getFirstNode() const
{
    /* TODO */
    Node<T>* current = head;
    if(current->next != NULL) return current->next;
    else return NULL;
}

template<class T>
Node<T> *LinkedList<T>::getLastNode() const
{
    /* TODO */
    if(head->next!=NULL){
        Node<T>* current = head->next;
        while(current->next!=NULL){
            current = current->next;
        }
        return current;
    }
    else{
        return NULL;
    }
}

template<class T>
Node<T> *LinkedList<T>::getNode(const T &data) const
{
    /* TODO */
    if(head->next != NULL){
        Node<T>* current = head->next;
        while (current!=NULL){
            if(current->data==data) return current;
            current=current->next;
        }
    }
    return NULL;
}

template<class T>
Node<T> *LinkedList<T>::getNodeAtIndex(int index) const
{
    /* TODO */
    if(head->next != NULL){
        if (index<size && index>=0){
            int i=0;
            Node<T>* current = head;
            for(i=0; i<index+1; i++){
                current=current->next;
            }
            return current;
        }
    }
    return NULL;
}

template<class T>
void LinkedList<T>::append(const T &data)
{
    /* TODO */
    Node<T>* current1 = new Node<T>(T());
    current1->data = data;
    
    Node<T>* current2 = head;
    
    while(current2->next != NULL){
        current2 = current2->next;
    }
    current2->next = current1;
    current1->prev = current2;
    current1->next = NULL;
    size = size + 1;
}

template<class T>
void LinkedList<T>::prepend(const T &data)
{
    /* TODO */
    Node<T>* current1 = new Node<T>(T());
    current1->data=data;
    
    if(head->next==NULL){
        head->next=current1;
        current1->prev=head;
        current1->next = NULL;
        size = size + 1;
    }
    else{
        current1->next=head->next;
        current1->prev=head;
        head->next=current1;
        current1->next->prev=current1;
        size = size + 1;
    }
}

template<class T>
void LinkedList<T>::insertAfterNode(const T &data, Node<T> *node)
{
    /* TODO */
    
    Node<T>* current2 = head->next;
    
    while(current2 != NULL){
        if(current2==node){
            if(current2->next!=NULL){
                Node<T>* current1 = new Node<T>(T());
                current1->data = data;
                current1->next = current2->next;
                current1->prev = current2;
                current2->next->prev = current1;
                current2->next = current1;
                size=size+1;
            }
            else if(current2->next == NULL){
                Node<T>* current1 = new Node<T>(T());
                current1->data = data;
                current2->next = current1;
                current1->prev = current2;
                current1->next = NULL;
                size=size+1;
            }
        }
        current2=current2->next;
    }
    
}

template<class T>
void LinkedList<T>::insertAtIndex(const T &data, int index)
{
    /* TODO */
    
    if ( (index<size) && (index>=0) ){
        Node<T>* current1 = new Node<T>(T());
        current1->data = data;
        Node<T>* current2 = head;
        
        if(index==0){
            current2 = head->next;
            head->next=current1;
            current1->prev = head;
            current1->next = current2;
            current2->prev = current1;
            size = size + 1;
        }
        else{
            for (int i=0;i<=index;i++){
                current2=current2->next;
            }
            current2->prev->next = current1;
            current1->prev=current2->prev;
            current1->next = current2;
            current2->prev = current1;
            size = size + 1;
        }
    }
    
}

template<class T>
int LinkedList<T>::getIndex(Node<T> *node) const
{
    /* TODO */
    Node<T>* current;
    current = head->next;
    
    for (int i=0;i<size;i++){
        if(current==node) return i;
        current=current->next;
    }
    return -1;
}

template<class T>
void LinkedList<T>::moveToIndex(int currentIndex, int newIndex)
{
    /* TODO */
    if (currentIndex == newIndex) return;
    if(currentIndex<size){
        
        Node<T>* current;
        Node<T>* current2;
        current = head->next;
        current2 = head;
        
        for(int i=0 ; i<currentIndex ; i++){
            current=current->next;
        }
        if (current->next != NULL){
            current->prev->next=current->next;
            current->next->prev=current->prev;
            current->next=NULL;
            current->prev=NULL;
        }
        else{
            current->prev->next = NULL;
            current->next=NULL;
            current->prev=NULL;
        }
        
        if( (newIndex) >= (size - 1) ){
            while(current2->next != NULL){
                current2=current2->next;
            }
            current2->next = current;
            current->prev = current2;
            current->next = NULL;
        }
        else{
            for(int k=0 ; k<newIndex + 1 ; k++){
                current2=current2->next;
            }
                current2->next->prev=current;
                current->prev = current2;
                current->next = current2->next;
                current2->next = current;
        }
    }
    
}

template<class T>
void LinkedList<T>::mergeNodes(int sourceIndex, int destIndex)
{
    /* TODO */
    
    if( (sourceIndex>=0) && (sourceIndex<=size-1) && (destIndex>=0) && (destIndex<=size-1) ){
        Node<T>* current;
        current=head->next;
        
        Node<T>* current2;
        current2=head->next;
        
        for(int i=0 ; i<destIndex ; i++){
            current2=current2->next;
        }
        
        for(int i=0 ; i<sourceIndex ; i++){
            current=current->next;
        }
        /*if(current->next != NULL){
            current->prev->next=current->next;
            current->next->prev=current->prev;
            current->next=NULL;
            current->prev=NULL;
        }
        else{
            current->prev->next = NULL;
            current->prev = NULL;
        }*/
            
        
        current2->data = current2->data + current->data;
        removeNode(current);
        //delete current;
        //size = size - 1 ;
    }
    
}

template<class T>
void LinkedList<T>::removeNode(Node<T> *node)
{
    /* TODO */
    Node<T>* current = NULL;
    if (this->containsNode(node)) current = node;
    if (current!=NULL){
        /* son node silme */
        if(current->next==NULL){
            current->prev->next=NULL;
            current->prev=NULL;
            delete current;
            size = size-1;
        }
        else{
            current->prev->next = current->next;
            current->next->prev = current->prev;
            current->next=NULL;
            current->prev=NULL;
            delete current;
            size = size-1;
        }
    }
}

template<class T>
void LinkedList<T>::removeNode(const T &data)
{
    /* TODO */
    Node<T>* current;
    current=head->next;
    while(current->data != data){
        current=current->next;
        if (current == NULL) break;
    }
    while(current){
        if (current!=NULL){
        /* son node silme */
            if(current->next==NULL){
                current->prev->next=NULL;
                current->prev=NULL;
                current->next=NULL;
                delete current;
                size = size-1;
            }
            else{
                current->prev->next = current->next;
                current->next->prev = current->prev;
                current->next=NULL;
                current->prev=NULL;
                delete current;
                size = size-1;
            }
        }
        current=head->next;
        while(current->data != data){
            current=current->next;
            if (current == NULL) break;
        }
    }
    
}

template<class T>
void LinkedList<T>::removeNodeAtIndex(int index)
{
    /* TODO */
    if( (head->next != NULL) && (index<size) && (index>=0) ){
        
        Node<T>* current;
        current=head;
        
        if (index == 0){
            if (size == 1){
                current = current->next;
                head->next = NULL;
                current->prev=NULL;
                current->next=NULL;
                delete current;
            }
            else{
                current = current->next;
                head->next = current->next;
                current->next->prev = head;
                current->prev=NULL;
                current->next=NULL;
                delete current;
            }
        }
        else if (index==size-1){
            for (int i=0; i<index+1 ; i++){
                current=current->next;
            }
            current->prev->next=NULL;
            current->prev=NULL;
            current->next=NULL;
            delete current;
        }
        else{
            for (int i=0; i<index+1 ; i++){
                current=current->next;
            }
            current->prev->next = current->next;
            current->next->prev = current->prev;
            current->next=NULL;
            current->prev=NULL;
            delete current;
        }
        size = size-1;
    }
}

template<class T>
void LinkedList<T>::removeAllNodes()
{
    /* TODO */
    if (head->next != NULL){
        Node<T>* current;
        while(head->next != NULL){
            if(head->next->next != NULL){
                current=head->next;
                current->prev->next = current->next;
                current->next->prev = current->prev;
                current->next=NULL;
                current->prev=NULL;
                delete current;
                size = size-1;
            }
            else{
                current=head->next;
                current->prev->next = NULL;
                current->next=NULL;
                current->prev=NULL;
                delete current;
                size = size-1;
            }
        }
    }
    size = 0;
}

template<class T>
void LinkedList<T>::print() const
{
    if (this->isEmpty()) {
        std::cout << "The list is empty." << std::endl;
        return;
    }

    Node<T> *node = this->getFirstNode();

    while(node)
    {
        std::cout << *node << std::endl;
        node = node->next;
    }

}

#endif //LINKEDLIST_H
