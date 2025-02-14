package main

import "fmt"

type DLink struct {
	key   int
	value int
	next  *DLink
	prev  *DLink
}

func NewCache() *DLink {
	pHead := &DLink{0, 0, nil, nil}
	pTail := &DLink{0, 0, nil, nil}
	pHead.Insert(pTail)
	return pHead
}

func (n *DLink) Insert(pNode *DLink) {
	pNode.next = n.next
	pNode.prev = n
	n.next = pNode
	if pNode.next != nil {
		pNode.next.prev = pNode
	}
}

func (n *DLink) Remove() {
	if n.next == nil {
		return
	}

	n.prev.next = n.next
	n.next.prev = n.prev
}

type Priority struct {
	pHead, pTail *DLink
}

func NewPriority() *Priority {
	head := NewCache()
	tail := head.next
	return &Priority{head, tail}
}

func (p *Priority) SetPriority(pNode *DLink) {
	if p.pHead.next == pNode {
		return
	}

	pNode.Remove()
	p.pHead.Insert(pNode)
}

func (p *Priority) RemoveLowPriority() int {
	key := p.pTail.prev.key
	p.pTail.prev.Remove()
	return key
}

type LRUCache struct {
	capacity int
	size     int
	priority *Priority
	cache    map[int]*DLink
}

func NewLRUCache(capacity int) *LRUCache {
	return &LRUCache{capacity, 0, NewPriority(), make(map[int]*DLink)}
}

func (l *LRUCache) Get(key int) int {
	pNode, exists := l.cache[key]
	if !exists {
		return -1
	}

	l.priority.SetPriority(pNode)
	return pNode.value
}

func (l *LRUCache) Add(key, value int) {
	pNode, exists := l.cache[key]
	if exists {
		pNode.value = value
		l.priority.SetPriority(pNode)
		return
	}

	pNode = &DLink{key, value, nil, nil}
	if l.size == l.capacity {
		k := l.priority.RemoveLowPriority()
		delete(l.cache, k)
		l.size--
	}
	l.priority.SetPriority(pNode)
	l.cache[key] = pNode
	l.size++
}

func (l *LRUCache) PrintPriority() {
	i := 0
	for p := l.priority.pHead.next; p != l.priority.pTail; p = p.next {
		if i != 0 {
			fmt.Print(", ")
		}
		fmt.Print(p.value)
		i++
	}
	fmt.Print(" The map: map:[")
	for key, value := range l.cache {
		fmt.Print("[", key, ", ", value.value, "]")
	}
	fmt.Println("]")
}

func main() {
	fmt.Print("LRUCache capacity: ")
	var capacity int
	fmt.Scan(&capacity)

	cache := NewLRUCache(capacity)

	for {
		fmt.Print("Key-value pair (key == -1 do a get): ")
		var key, value int
		fmt.Scan(&key, &value)
		if key == 0 && value == 0 {
			break
		}

		if key == -1 {
			fmt.Print(key, ", ", cache.Get(value))
			fmt.Print(" => The priority: ")
		} else {
			cache.Add(key, value)
			fmt.Print("The priority: ")
		}
		cache.PrintPriority()
	}
}
