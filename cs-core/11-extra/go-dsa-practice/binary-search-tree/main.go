package bst

import "golang.org/x/exp/constraints"

type Ordered interface {
    constraints.Ordered
}

type Node[K Ordered, V any] struct {
    Key   K
    Value V
    Left  *Node[K, V]
    Right *Node[K, V]
}

type BST[K Ordered, V any] struct {
    Root *Node[K, V]
    size int
}

func NewBST[K Ordered, V any]() *BST[K, V] {
    return &BST[K, V]{
        Root: nil,
        size: 0,
    }
}

func (t *BST[K, V]) Insert(key K, value V) {
    t.Root = t.insert(t.Root, key, value)
}

func (t *BST[K, V]) insert(node *Node[K, V], key K, value V) *Node[K, V] {
        if node == nil {
            t.size++
            return &Node[K, V]{
                Key:   key,
                Value: value,
                Left:  nil,
                Right: nil,
            }
        }

    if key < node.Key {
        node.Left = t.insert(node.Left, key, value)
    } else if key > node.Key {
        node.Right = t.insert(node.Right, key, value)
    } else {
        node.Value = value
    }

    return node
}

func (t *BST[K, V]) Search(key K) (V, bool) {
    node := t.search(t.Root, key)
    if node == nil {
        var zeroValue V
        return zeroValue, false
    }
    return node.Value, true
}

func (t *BST[K, V]) search(node *Node[K, V], key K) *Node[K, V] {
    if node == nil || node.Key == key {
        return node
    }

    if key < node.Key {
        return t.search(node.Left, key)
    }
    return t.search(node.Right, key)
}