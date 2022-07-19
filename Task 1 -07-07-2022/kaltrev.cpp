#include <bits/stdc++.h>
using namespace std;
class Node
{
public:
    int data;
    Node* next;
    Node(int data){
        this->data = data;
    }
};

Node *kaltrev(Node *head, int k)
{
    Node* curr = head;
    Node* next;
    Node* prev = NULL;

    int count = 0;    while (curr != NULL && count < k)
    {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
        count++;
    }

    if(head != NULL)
        head->next = curr;
    count = 0;
    while(count < k-1 && curr != NULL )
    {
        curr = curr->next;
        count++;
    }
    if(curr != NULL)
        curr->next = kaltrev(curr->next, k);
    return prev;
}

void printList(Node *node)
{
    int count = 0;
    while(node != NULL)
    {
        cout<<node->data<<" ";
        node = node->next;
        count++;
    }
}

int main(void)
{

    Node* head = new Node(1);
    int i;
    Node* temp = head;
    for(i = 2; i<10; i++)
    {
        temp->next = new Node(i);
        temp = temp->next;
    }
    temp->next = NULL;
    cout << "Original linked list ";
    printList(head);
    head = kaltrev(head, 3);
    cout<<endl;
    cout << "Modified Linked list ";
    printList(head);
    return(0);
}
