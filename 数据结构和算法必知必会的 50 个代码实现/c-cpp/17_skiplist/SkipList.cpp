#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <cstring>
#include <random>
#include <ctime>
using namespace std;

/**
 * �����һ��ʵ�ַ�����
 * �����д洢���������������Ҵ洢���ǲ��ظ��ġ�
 *
 * �����C++�汾.
 * ����JAVA�汾 ԭ���� Author��ZHENG
 * 
 * Author��puhuaqiang
 * 
 *  ����ṹ:
 * 
 *  ��K��           1           9
 *  ��K-1��         1     5     9
 *  ��K-2��         1  3  5  7  9
 *  ...             ....
 *  ��0��(ԭʼ����)  1  2  3  4  5  6  7  8  9
 */

const int MAX_LEVEL = 16;

/**
 * @brief �ڵ�
*/
class CNode
{
public:
    CNode();
    ~CNode();

    std::string toString();
    /**
     * @brief ��ȡ��������
    */
    CNode** GetIdxList();

    /**
     * @brief ��������
    */
    void SetData(int v);
    /**
     * @brief ��ȡ����
    */
    int GetData();
    /**
    * @brief ���������������
    */
    void SetLevel(int l);
private:
    /**��ǰ�ڵ��ֵ*/
    int m_data;
    /** 
     * ��ǰ�ڵ��ÿ���ȼ�����һ���ڵ�.
     * ��2�� N1 N2
     * ��1�� N1 N2
     * ���N1�Ǳ��ڵ�,�� m_lpForwards[x] �������N2
     * 
     * [0] ����ԭʼ����.
     */
    CNode* m_lpForwards[MAX_LEVEL];
    /**��ǰ�ڵ�����ڵ������������*/
    int m_iMaxLevel;
};

/**
 * @brief ����
*/
class CSkipList
{
public:
    CSkipList();
    ~CSkipList();
    /**
     * @brief ����ָ����ֵ�Ľڵ�
     * @param v ������
    */
    CNode* Find(int v);
    /**
     * @brief ����ָ����ֵ
     * @param v ������
    */
    void Insert(int v);
    /**
     * @brief ɾ��ָ����ֵ�Ľڵ�
     * @param v ������
    */
    int Delete(int v);
    void PrintAll();
    /**
     * @brief ��ӡ����ṹ
     * @param l ����-1ʱ��ӡ���м���Ľṹ >=0ʱ��ӡָ������Ľṹ
    */
    void PrintAll(int l);
    /**
     * @brief ����ڵ�ʱ,�õ�����K�����������
     * @return K
    */
    int RandomLevel();

private:
    int levelCount;
    /**
     * ����
     * ��ͷ/����(�ڵ�)
    */
    CNode* m_lpHead;
};

int main()
{
    CSkipList skipList;
    /// ����ԭʼֵ
    for(int i=1; i< 50; i++){
        if((i%3) == 0){
            skipList.Insert(i);
        }
    }
    for(int i=1; i< 50; i++){
        if((i%3) == 1){
            skipList.Insert(i);
        }
    }
    skipList.PrintAll();
    std::cout<<std::endl;
    /// ��ӡ���еȼ��ṹ
    skipList.PrintAll(-1);
    /// ����
    std::cout<<std::endl;
    CNode* lpNode = skipList.Find(27);
    if(NULL != lpNode){
        std::cout<<"����ֵΪ27�Ľڵ�,�ҵ��ýڵ�,�ڵ�ֵ:"<<lpNode->GetData()<<std::endl;
    }else{
        std::cout<<"����ֵΪ27�Ľڵ�,δ�ҵ��ýڵ�"<<std::endl;
    }
    /// ɾ��
    std::cout<<std::endl;
    int ret = skipList.Delete(46);
    if(0 == ret){
        std::cout<<"����ֵΪ46�Ľڵ�,�ҵ��ýڵ�,��ɾ���ɹ�"<<std::endl;
    }else{
        std::cout<<"����ֵΪ46�Ľڵ�,�ҵ��ýڵ�,ɾ��ʧ��"<<std::endl;
    }
    std::cout<<std::endl;
    //��ӡ���еȼ��ṹ
    skipList.PrintAll(-1);
    std::cin.ignore();
    return 0;
}

CNode::CNode()
{
    m_data = -1;
    m_iMaxLevel = 0;
    for(int i=0; i<MAX_LEVEL; i++){
        m_lpForwards[i] = NULL;
    }
}
CNode::~CNode()
{

}
CNode** CNode::GetIdxList()
{
    return m_lpForwards;
}

void CNode::SetData(int v)
{
    m_data = v;
}
int CNode::GetData()
{
    return m_data;
}
void CNode::SetLevel(int l)
{
    m_iMaxLevel = l;
}
std::string CNode::toString()
{
    char tmp[32];
    std::string ret;

    ret.append("{ data: ");
    sprintf(tmp, "%d", m_data);
    ret.append(tmp);
    ret.append("; levels: ");
    sprintf(tmp, "%d", m_iMaxLevel);
    ret.append(tmp);
    ret.append(" }");
    return ret;
}

CSkipList::CSkipList()
{
    levelCount = 1;
    m_lpHead = new CNode();
}
CSkipList::~CSkipList()
{

}
CNode* CSkipList::Find(int v)
{
    CNode* lpNode = m_lpHead;
    /**
     * �� �����������ʼ����.
     * K -> k-1 -> k-2 ...->0
    */
    for(int i=levelCount-1; i>=0; --i){
        /**
         * ����С��v�Ľڵ�(lpNode).
        */
        while((NULL != lpNode->GetIdxList()[i]) && (lpNode->GetIdxList()[i]->GetData() < v)){
            lpNode = lpNode->GetIdxList()[i];
        }
    }
    /**
     * lpNode ��С��v�Ľڵ�, lpNode����һ���ڵ�͵��ڻ����v�Ľڵ�
    */
    if((NULL != lpNode->GetIdxList()[0]) && (lpNode->GetIdxList()[0]->GetData() == v)){
        return lpNode->GetIdxList()[0];
    }
    return NULL;
}
void CSkipList::Insert(int v)
{
    /// �½ڵ�
    CNode* lpNewNode = new CNode();
    if(NULL == lpNewNode){
        return;
    }

    /**
     * �½ڵ����ֲ��ڵ��������������
     * ������� 3,�� �µĽڵ��������1��2��3�ϵ���������
    */
    int level = RandomLevel();
    lpNewNode->SetData(v);
    lpNewNode->SetLevel(level);

    /**
     * ��ʱ��������
     * ��Ҫ�ǵõ��µĽڵ���ÿ�����������ϵ�λ��
    */
    CNode *lpUpdateNode[level];
    for(int i=0; i<level; i++){
        /// ÿ�����������ͷ�ڵ�
        lpUpdateNode[i] =m_lpHead;
    }
    CNode* lpFind = m_lpHead;
    for(int i= level-1; i >= 0; --i){
        /**
         * ����λ��
         *   eg.  ��1��  1  7  10
         *   ���������� 6
         *   lpFind->GetIdxList()[i]->GetData() : ��ʾ�ڵ�lpFind�ڵ�1����������һ���ڵ������
         *   �� "lpFind->GetIdxList()[i]->GetData() < v"��������ʱ��,
         *   �½ڵ��Ҫ���뵽 lpFind�ڵ�ĺ���, lpFind->GetIdxList()[i] �ڵ��ǰ��
         *   �������� lpFind����1  lpFind->GetIdxList()[i] ����7
        */
        while((NULL != lpFind->GetIdxList()[i]) && (lpFind->GetIdxList()[i]->GetData() < v)){
            lpFind = lpFind->GetIdxList()[i];
        }
        /// lpFind ���½ڵ��� ��i����������ĺ�һ���ڵ�
        lpUpdateNode[i] = lpFind;
    }

    for(int i=0; i<level; ++i){
        /**
         * ������������ָ��λ��
         *   eg  ��1������ 1  7  10
         *      ����6.
         *      lpUpdateNode[i] �ڵ���1; lpUpdateNode[i]->GetIdxList()[i]�ڵ���7
         *  
         *  ��2�������� ��6���� 1��7֮��
        */
        lpNewNode->GetIdxList()[i] = lpUpdateNode[i]->GetIdxList()[i];
        lpUpdateNode[i]->GetIdxList()[i] = lpNewNode;
    }
    if(levelCount < level){
        levelCount = level;
    }
}
int CSkipList::Delete(int v)
{
    int ret = -1;
    CNode *lpUpdateNode[levelCount];
    CNode *lpFind = m_lpHead;
    for(int i=levelCount-1; i>= 0; --i){
        /**
         * ����С��v�Ľڵ�(lpFind).
        */
        while((NULL != lpFind->GetIdxList()[i]) && (lpFind->GetIdxList()[i]->GetData() < v)){
            lpFind = lpFind->GetIdxList()[i];
        }
        lpUpdateNode[i] = lpFind;
    }
    /**
     * lpFind ��С��v�Ľڵ�, lpFind����һ���ڵ�͵��ڻ����v�Ľڵ�
    */
    if((NULL != lpFind->GetIdxList()[0]) && (lpFind->GetIdxList()[0]->GetData() == v)){
        for(int i=levelCount-1; i>=0; --i){
            if((NULL != lpUpdateNode[i]->GetIdxList()[i]) && (v == lpUpdateNode[i]->GetIdxList()[i]->GetData())){
                lpUpdateNode[i]->GetIdxList()[i] = lpUpdateNode[i]->GetIdxList()[i]->GetIdxList()[i];
                ret = 0;
            }
        }
    }
    return ret;
}
void CSkipList::PrintAll()
{
    CNode* lpNode = m_lpHead;
    while(NULL != lpNode->GetIdxList()[0]){
        std::cout<<lpNode->GetIdxList()[0]->toString().data()<<std::endl;
        lpNode = lpNode->GetIdxList()[0];
    }
}
void CSkipList::PrintAll(int l)
{
    for(int i=MAX_LEVEL-1; i>=0;--i){
        CNode* lpNode = m_lpHead;
        std::cout<<"��"<<i<<"��:"<<std::endl;
        if((l < 0) || ((l >= 0) && (l == i))){
            while(NULL != lpNode->GetIdxList()[i]){
                std::cout<<lpNode->GetIdxList()[i]->GetData()<<" ";
                lpNode = lpNode->GetIdxList()[i];
            }
            std::cout<<std::endl;
            if(l >= 0){
                break;
            }
        }
    }
}
int GetRandom()
{
    static int _count = 1;
	std::default_random_engine generator(time(0) + _count);
	std::uniform_int_distribution<int> distribution(1,99999/*0x7FFFFFFF*/);
	int dice_roll = distribution(generator);
    _count += 100;
	return dice_roll;
}
int CSkipList::RandomLevel()
{
    int level = 1;
    for(int i=1; i<MAX_LEVEL; ++i){
        if(1 == (GetRandom()%3)){
            level++;
        }
    }
    return level;
}