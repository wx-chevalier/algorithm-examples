/*******************************************************************
Copyright(c) 2016, Harry He
All rights reserved.

Distributed under the BSD license.
(See accompanying file LICENSE.txt at
https://github.com/zhedahht/CodingInterviewChinese2/blob/master/LICENSE.txt)
*******************************************************************/

//==================================================================
// ����ָOffer�����������Թپ������ͱ���⡷����
// ���ߣ��κ���
//==================================================================

// ������8������������һ�����
// ��Ŀ������һ�ö����������е�һ����㣬����ҳ��������˳�����һ����㣿
// ���еĽ������������ֱ�ָ�������ӽ���ָ�����⣬����һ��ָ�򸸽���ָ�롣

#include <stdio.h>

struct BinaryTreeNode
{
    int                    m_nValue;
    BinaryTreeNode*        m_pLeft;
    BinaryTreeNode*        m_pRight;
    BinaryTreeNode*        m_pParent;
};

BinaryTreeNode* GetNext(BinaryTreeNode* pNode)
{
    if(pNode == nullptr)
        return nullptr;

    BinaryTreeNode* pNext = nullptr;
    if(pNode->m_pRight != nullptr)
    {
        BinaryTreeNode* pRight = pNode->m_pRight;
        while(pRight->m_pLeft != nullptr)
            pRight = pRight->m_pLeft;

        pNext = pRight;
    }
    else if(pNode->m_pParent != nullptr)
    {
        BinaryTreeNode* pCurrent = pNode;
        BinaryTreeNode* pParent = pNode->m_pParent;
        while(pParent != nullptr && pCurrent == pParent->m_pRight)
        {
            pCurrent = pParent;
            pParent = pParent->m_pParent;
        }

        pNext = pParent;
    }

    return pNext;
}

// ==================== ���������������������� ====================
BinaryTreeNode* CreateBinaryTreeNode(int value)
{
    BinaryTreeNode* pNode = new BinaryTreeNode();
    pNode->m_nValue = value;
    pNode->m_pLeft = nullptr;
    pNode->m_pRight = nullptr;
    pNode->m_pParent = nullptr;

    return pNode;
}

void ConnectTreeNodes(BinaryTreeNode* pParent, BinaryTreeNode* pLeft, BinaryTreeNode* pRight)
{
    if(pParent != nullptr)
    {
        pParent->m_pLeft = pLeft;
        pParent->m_pRight = pRight;

        if(pLeft != nullptr)
            pLeft->m_pParent = pParent;
        if(pRight != nullptr)
            pRight->m_pParent = pParent;
    }
}

void PrintTreeNode(BinaryTreeNode* pNode)
{
    if(pNode != nullptr)
    {
        printf("value of this node is: %d\n", pNode->m_nValue);

        if(pNode->m_pLeft != nullptr)
            printf("value of its left child is: %d.\n", pNode->m_pLeft->m_nValue);
        else
            printf("left child is null.\n");

        if(pNode->m_pRight != nullptr)
            printf("value of its right child is: %d.\n", pNode->m_pRight->m_nValue);
        else
            printf("right child is null.\n");
    }
    else
    {
        printf("this node is null.\n");
    }

    printf("\n");
}

void PrintTree(BinaryTreeNode* pRoot)
{
    PrintTreeNode(pRoot);

    if(pRoot != nullptr)
    {
        if(pRoot->m_pLeft != nullptr)
            PrintTree(pRoot->m_pLeft);

        if(pRoot->m_pRight != nullptr)
            PrintTree(pRoot->m_pRight);
    }
}

void DestroyTree(BinaryTreeNode* pRoot)
{
    if(pRoot != nullptr)
    {
        BinaryTreeNode* pLeft = pRoot->m_pLeft;
        BinaryTreeNode* pRight = pRoot->m_pRight;

        delete pRoot;
        pRoot = nullptr;

        DestroyTree(pLeft);
        DestroyTree(pRight);
    }
}

// ====================���Դ���====================
void Test(char* testName, BinaryTreeNode* pNode, BinaryTreeNode* expected)
{
    if(testName != nullptr)
        printf("%s begins: ", testName);

    BinaryTreeNode* pNext = GetNext(pNode);
    if(pNext == expected)
        printf("Passed.\n");
    else
        printf("FAILED.\n");
}

//            8
//        6      10
//       5 7    9  11
void Test1_7()
{
    BinaryTreeNode* pNode8 = CreateBinaryTreeNode(8);
    BinaryTreeNode* pNode6 = CreateBinaryTreeNode(6);
    BinaryTreeNode* pNode10 = CreateBinaryTreeNode(10);
    BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);
    BinaryTreeNode* pNode7 = CreateBinaryTreeNode(7);
    BinaryTreeNode* pNode9 = CreateBinaryTreeNode(9);
    BinaryTreeNode* pNode11 = CreateBinaryTreeNode(11);

    ConnectTreeNodes(pNode8, pNode6, pNode10);
    ConnectTreeNodes(pNode6, pNode5, pNode7);
    ConnectTreeNodes(pNode10, pNode9, pNode11);

    Test("Test1", pNode8, pNode9);
    Test("Test2", pNode6, pNode7);
    Test("Test3", pNode10, pNode11);
    Test("Test4", pNode5, pNode6);
    Test("Test5", pNode7, pNode8);
    Test("Test6", pNode9, pNode10);
    Test("Test7", pNode11, nullptr);

    DestroyTree(pNode8);
}

//            5
//          4
//        3
//      2
void Test8_11()
{
    BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);
    BinaryTreeNode* pNode4 = CreateBinaryTreeNode(4);
    BinaryTreeNode* pNode3 = CreateBinaryTreeNode(3);
    BinaryTreeNode* pNode2 = CreateBinaryTreeNode(2);

    ConnectTreeNodes(pNode5, pNode4, nullptr);
    ConnectTreeNodes(pNode4, pNode3, nullptr);
    ConnectTreeNodes(pNode3, pNode2, nullptr);

    Test("Test8", pNode5, nullptr);
    Test("Test9", pNode4, pNode5);
    Test("Test10", pNode3, pNode4);
    Test("Test11", pNode2, pNode3);

    DestroyTree(pNode5);
}

//        2
//         3
//          4
//           5
void Test12_15()
{
    BinaryTreeNode* pNode2 = CreateBinaryTreeNode(2);
    BinaryTreeNode* pNode3 = CreateBinaryTreeNode(3);
    BinaryTreeNode* pNode4 = CreateBinaryTreeNode(4);
    BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);

    ConnectTreeNodes(pNode2, nullptr, pNode3);
    ConnectTreeNodes(pNode3, nullptr, pNode4);
    ConnectTreeNodes(pNode4, nullptr, pNode5);

    Test("Test12", pNode5, nullptr);
    Test("Test13", pNode4, pNode5);
    Test("Test14", pNode3, pNode4);
    Test("Test15", pNode2, pNode3);

    DestroyTree(pNode2);
}

void Test16()
{
    BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);

    Test("Test16", pNode5, nullptr);

    DestroyTree(pNode5);
}

int main(int argc, char* argv[])
{
    Test1_7();
    Test8_11();
    Test12_15();
    Test16();
}
