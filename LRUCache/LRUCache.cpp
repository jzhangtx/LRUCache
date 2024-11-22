// LRUCache.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <unordered_map>

class LRUCache {
public:
    LRUCache(int capacity)
        : m_Capacity(capacity)
        , m_pHead(new Node(0, 0))
    {
        m_pTail = new Node(0, 0);
        m_pHead->SetNext(m_pTail);
    }

    ~LRUCache()
    {
        while (m_pHead != nullptr)
        {
            Node* pNode = m_pHead;
            m_pHead = m_pHead->GetNext();
            delete pNode;
        }
    }

    int get(int key)
    {
        if (m_Cache.contains(key))
        {
            Node* pNode = m_Cache[key];
            if (pNode != m_pHead->GetNext())
            {
                pNode->Remove();
                InsertHead(pNode);
            }

            return pNode->GetValue();
        }

        return -1;
    }

    void add(int key, int value)
    {
        Node* pNode = nullptr;
        if (m_Cache.contains(key))
        {
            pNode = m_Cache[key];
            pNode->Remove();
            pNode->SetValue(value);
        }
        else if (GetSize() == m_Capacity)
        {
            Node* pTemp = m_pTail->GetPrev();
            pTemp->Remove();
            m_Cache.erase(pTemp->GetKey());
            delete pTemp;
            pNode = new Node(key, value);
        }
        else
        {
            pNode = new Node(key, value);
        }

        m_Cache.insert(std::make_pair(key, pNode));
        InsertHead(pNode);
    }

    int GetSize()
    {
        return static_cast<int>(m_Cache.size());
    }

    void PrintCache() const
    {
        for (auto p = m_pHead->GetNext(); p != m_pTail; p = p->GetNext())
        {
            std::cout << "{" << p->GetKey() << ", " << p->GetValue() << "} ";
        }
        std::cout << std::endl;
    }

private:
    class Node
    {
    public:
        Node(int key, int value)
            : m_pNext(nullptr)
            , m_pPrev(nullptr)
            , m_Key(key)
            , m_Value(value)
        {}

        void Remove()
        {
            m_pPrev->m_pNext = m_pNext;
            m_pNext->m_pPrev = m_pPrev;
            m_pPrev = nullptr;
            m_pNext = nullptr;
        }

        int GetKey() const
        {
            return m_Key;
        }

        int GetValue() const
        {
            return m_Value;
        }

        void SetNext(Node* pNode)
        {
            m_pNext = pNode;
            pNode->m_pPrev = this;
        }

        Node* GetPrev()
        {
            return m_pPrev;
        }

        Node* GetNext()
        {
            return m_pNext;
        }

        void SetValue(int value)
        {
            m_Value = value;
        }

        void InsertAfter(Node* pToInsert)
        {
            pToInsert->m_pNext = m_pNext;
            pToInsert->m_pPrev = this;
            m_pNext->m_pPrev = pToInsert;
            m_pNext = pToInsert;
        }

    private:
        Node* m_pNext;
        Node* m_pPrev;
        int m_Key;
        int m_Value;
    };

    int m_Capacity;
    std::unordered_map<int, Node*> m_Cache;
    Node* m_pHead;
    Node* m_pTail;
    void InsertHead(Node* pNode)
    {
        m_pHead->InsertAfter(pNode);
    }
};

int main()
{
    std::cout << "LRUCache capacity: ";
    int capacity = 0;
    std::cin >> capacity;
    LRUCache cache(capacity);

    while (true)
    {
        std::cout << "Enter key-value: ";
        int key = 0, value = 0;
        std::cin >> key >> value;

        if (key == 0 && value == 0)
            break;

        if (key == -1)
        {
            std::cout << "Key = " << value << ", value = " << cache.get(value) << std::endl;
        }
        else
            cache.add(key, value);

        cache.PrintCache();
    }
}
