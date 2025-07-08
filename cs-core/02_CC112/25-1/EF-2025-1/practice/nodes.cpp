#include <iostream>

using std::cout;
using std::endl;

struct ListNode
{
  int data;
  ListNode *next;
  ListNode(int value) : data(value), next(nullptr) {}
};

void printList(ListNode *head)
{
  ListNode *current = head;

  // While current exists
  while (current != nullptr)
  {
    int currentData = current->data;
    cout << currentData << " " << endl;
    current = current->next;
  }

  cout << "Printed all the list node" << endl;
}

void appendList(ListNode *&head, int value)
{
  ListNode *newNode = new ListNode(value);

  if (head == nullptr)
  {
    head = newNode;
    return;
  }

  ListNode *current = head;

  while (current->next != nullptr)
  {
    current = current->next;
  }

  current->next = newNode;
}

void deleteList(ListNode *&head)
{
  while (head != nullptr)
  {
    ListNode *temp = head;
    head = head->next;
    delete temp;
  }
}

int main()
{
  ListNode *head = nullptr;

  appendList(head, 1);
  appendList(head, 2);
  appendList(head, 3);

  cout << "List after appending nodes: ";

  printList(head);
  deleteList(head);

  return 0;
}