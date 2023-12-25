#include <iostream>
#include <string>
#include <functional>
using namespace std;


class CElement;
/***
 * @brief ����������
*/
class CSingleList
{
public:
    CSingleList();
    ~CSingleList();

    /**
     * @brief ����..����ĩβ����
     * @return �ɹ����طǿ�ָ��,����ʧ��
    */
    CElement* Insert(void* lpData, int iDataSize);
    /**
     * @brief ����..����ָ��λ�ò���
     * @return �ɹ����طǿ�ָ��,����ʧ��
    */
    CElement* Insert(CElement* lpElement, void* lpData, int iDataSize);
    /**
     * @brief ɾ��
    */
    void Delete(CElement*);

    /**
     * @brief ����
    */
    CElement* Begin();
    /**
     * @brief ��һ��Ԫ��
    */
    CElement* Next();
    /***
     * @brief ��β
    */
    CElement* End();

    /**
     * @brief �Ƿ��ǿ�����
     * @return �շ���TRUE�����򷵻�FALSE
    */
    bool Empty();

    /**
     * @brief ��ת
    */
    void Reverse();

    /**
     * @brief ��⻷
     * @return ����TRUEʱ��ʾ������ڻ�,���򲻴��ڻ�.
    */
    bool CheckCircle();

    /**
     * @brief �ϲ�2�����������
    */
    void Merge(CSingleList& lst, std::function<int(void* t1, void* t2)>);

    /**
     * @brief ɾ��������K�����
    */
    void DeleteLastKth(int k);
    /**
     * @brief ���м�ڵ�
    */
    CElement* Center();
private:
    void Insert(CElement* lpNewElement, CElement* lpCurElement, bool bBack = true);
    void Insert(CElement* lpNewElement);
    CElement* Tail();

	CSingleList(CSingleList const & rhs);
	CSingleList& operator= (CSingleList const& rhs);
private:
    /**ͷ���*/
    CElement* m_lpHead;
    /**�ڱ�*/
    CElement* m_lpSentinel;
    /**�ս�㣬����End()���� */
    CElement* m_lpNull;
    /**��ǰ���. ö��ʱʹ��. */
    CElement* m_lpCur;
};

/***
 * @brief ��������Ԫ��.
*/
class CElement
{
    friend class CSingleList;
protected:
    CElement();
    ~CElement();
public:
    /***
     * @brief ��ȡ����ָ��
    */
    void* GetDataPtr();
protected:
    /**��һ�����*/
    CElement* m_lpNext;
    void* m_lpData;
};


void CreateList(CSingleList& lst)
{
    //ѭ������Ԫ�ص�����β
    for(int i=1; i<10;i++)
    {
        int* p = new int();
        *p = i;
        lst.Insert(p, 4);
    }
}
void PrintList(CSingleList& lst)
{
    CElement* lpElement = lst.Begin();
    while(lpElement != lst.End())
    {
        std::cout<<*((int*)lpElement->GetDataPtr())<<std::endl;
        lpElement = lst.Next();
    }
}

int main()
{
    {
        /// ����Ļ�������������/ö��/ɾ��
        CSingleList lst;
        CElement* lpElement = NULL;
        CreateList(lst);

        std::cout<<"ö������ǰ��Ԫ��"<<std::endl;
        PrintList(lst);

        std::cout<<"����ָ��Ԫ��,����ָ��Ԫ�غ��������Ԫ��"<<std::endl;
        lpElement = lst.Begin();
        while(lpElement != lst.End())
        {
            if(*((int*)lpElement->GetDataPtr()) == 5)
            {
                int* p = new int();
                *p = 55;
                lst.Insert(lpElement,p, 4);
                break;
            }else{
                lpElement = lst.Next();
            }
        }

        std::cout<<"ö������ǰ��Ԫ��"<<std::endl;
        PrintList(lst);

        std::cout<<"����ָ��Ԫ��(������7��Ԫ��),��ɾ��ָ��Ԫ��"<<std::endl;
        lpElement = lst.Begin();
        while(lpElement != lst.End())
        {
            if(*((int*)lpElement->GetDataPtr()) == 7)
            {
                lst.Delete(lpElement);
                break;
            }else{
                lpElement = lst.Next();
            }
        }
        std::cout<<"ö������ǰ��Ԫ��"<<std::endl;
        PrintList(lst);
    }

    std::cout<<"--------------------------"<<std::endl;
    {
        /// ����ķ�ת
        CSingleList lst;
        CElement* lpElement = NULL;
        CreateList(lst);
        std::cout<<"��ת"<<std::endl;
        lst.Reverse();
        PrintList(lst);
    }

    std::cout<<"--------------------------"<<std::endl;
    {
        /// ��⻷
        CSingleList lst;
        CElement* lpElement = NULL;
        CreateList(lst);
        std::cout<<"��⻷"<<std::endl;
        bool bRet = lst.CheckCircle();
        if(bRet){
            std::cout<<"���ڻ�."<<std::endl;
        }else{
            std::cout<<"�����ڻ�."<<std::endl;
        }
    }

    std::cout<<"--------------------------"<<std::endl;
    {
        /// ��������ϲ�
        CSingleList lst,lst2;
        CElement* lpElement = NULL;
        for(int i=1; i<30;i++)
        {
            int* p = new int();
            *p = i;
            if(i%4){
                lst2.Insert(p, 4);
            }else{
                lst.Insert(p, 4);
            }
        }
        std::cout<<"ö������ǰ��Ԫ��"<<std::endl;
        PrintList(lst);
        std::cout<<"......"<<std::endl;
        PrintList(lst2);
        lst.Merge(lst2,[](void* lpT1, void* lpT2) -> int{
            if(*((int*)lpT1) < *((int*)lpT2)){
                return -1;
            }else if(*((int*)lpT1) == *((int*)lpT2)){
                return 0;
            }else if(*((int*)lpT1) > *((int*)lpT2)){
                return 1;
            }
            return 0;
        });
        std::cout<<"�ϲ�֮�󣬴�ӡ��ǰ����."<<std::endl;
        PrintList(lst);
    }
    std::cout<<"--------------------------"<<std::endl;
    {
        /// ɾ��������K�����,���鿴�м�ڵ�
        CSingleList lst;
        CreateList(lst);
        std::cout<<"ɾ��������0�����"<<std::endl;
        lst.DeleteLastKth(0);
        PrintList(lst);
        CElement* lpCenter = lst.Center();
        std::cout<<"�м�ڵ�:"<<*((int*)lpCenter->GetDataPtr())<<std::endl;

        std::cout<<"ɾ��������1�����"<<std::endl;
        lst.DeleteLastKth(1);
        PrintList(lst);
        lpCenter = lst.Center();
        std::cout<<"�м�ڵ�:"<<*((int*)lpCenter->GetDataPtr())<<std::endl;

        std::cout<<"ɾ��������3�����"<<std::endl;
        lst.DeleteLastKth(3);
        PrintList(lst);
        lpCenter = lst.Center();
        std::cout<<"�м�ڵ�:"<<*((int*)lpCenter->GetDataPtr())<<std::endl;
    }
    std::cin.ignore();

    return 0;
}

CSingleList::CSingleList()
{
    m_lpHead = new CElement();
    m_lpSentinel = new CElement();
    m_lpNull = new CElement();
    m_lpCur = NULL;
    m_lpHead->m_lpNext = m_lpSentinel;
}
CSingleList::~CSingleList()
{
    if(NULL != m_lpSentinel)
    {
        delete m_lpSentinel;
        m_lpSentinel = NULL;
    }
    if(NULL != m_lpNull)
    {
        delete m_lpNull;
        m_lpNull = NULL;
    }
    if(NULL != m_lpHead)
    {
        delete m_lpHead;
        m_lpHead = NULL;
    }
}
CElement* CSingleList::Insert(void* lpData, int iDataSize)
{
    CElement* lpNewElement = new CElement();
    if(NULL == lpNewElement)
    {
        return NULL;
    }
    lpNewElement->m_lpData = lpData;
    Insert(lpNewElement, Tail());
    return lpNewElement;
}
CElement* CSingleList::Insert(CElement* lpElement, void* lpData, int iDataSize)
{
    if((NULL == lpElement) || (End() == lpElement))
    {
        return NULL;
    }
    CElement* lpNewElement = new CElement();
    if(NULL == lpNewElement)
    {
        return NULL;
    }
    lpNewElement->m_lpData = lpData;
    Insert(lpNewElement, lpElement);
    return lpNewElement;
}
void CSingleList::Insert(CElement* lpNewElement, CElement* lpCurElement, bool bBack /*= true*/)
{
    if(bBack){//���뵽ָ��Ԫ�صĺ���
        lpNewElement->m_lpNext = lpCurElement->m_lpNext;
        lpCurElement->m_lpNext = lpNewElement;
    }else{//���뵽ָ��Ԫ�ص�ǰ��
        CElement* lpIter = m_lpSentinel;
        while(NULL != lpIter)
        {
            if(lpIter->m_lpNext == lpCurElement)
            {
                lpNewElement->m_lpNext = lpIter->m_lpNext;
                lpIter->m_lpNext = lpNewElement;
                break;
            }else{
                lpIter = lpIter->m_lpNext;
            }
        }
    }
}

void CSingleList::Delete(CElement* lpElement)
{
    if((NULL == lpElement) || (End() == lpElement))
    {
        return;
    }
    CElement* lpCurElement = m_lpHead->m_lpNext;
    while(NULL != lpCurElement->m_lpNext)
    {
        if(lpCurElement->m_lpNext == lpElement)
        {
            lpCurElement->m_lpNext = lpCurElement->m_lpNext->m_lpNext;
            break;
        }else{
            lpCurElement = lpCurElement->m_lpNext;
        }
    }
}

CElement* CSingleList::Tail()
{
    CElement* lpCurElement = m_lpHead->m_lpNext;
    while(NULL != lpCurElement->m_lpNext)
    {
        lpCurElement = lpCurElement->m_lpNext;
    }
    return lpCurElement;
}

CElement* CSingleList::Begin()
{
    m_lpCur = NULL;
    if(NULL == m_lpHead->m_lpNext->m_lpNext)
    {
        m_lpCur = End();
    }else{
        m_lpCur = m_lpHead->m_lpNext->m_lpNext;
    }
    return m_lpCur;
}

CElement* CSingleList::Next()
{
    if((NULL == m_lpCur) || (End() == m_lpCur))
    {
        return m_lpCur;
    }
    m_lpCur = m_lpCur->m_lpNext;
    if(NULL == m_lpCur)
    {
        m_lpCur = End();
    }
    return m_lpCur;
}

CElement* CSingleList::End()
{
    return m_lpNull;
}

bool CSingleList::Empty()
{
    return Begin() == End();
}

void CSingleList::Reverse()
{
    if(Empty())
    {
        return;
    }
    CElement* lpPre = NULL;
    CElement* lpTmp = NULL;
    CElement* lpCurElement = m_lpSentinel->m_lpNext;
    while(1)
    {
        lpTmp = lpCurElement->m_lpNext;
        lpCurElement->m_lpNext = lpPre;
        if(NULL == lpTmp)
        {
            break;
        }
        lpPre = lpCurElement;
        lpCurElement = lpTmp;
    }
    m_lpSentinel->m_lpNext = lpCurElement;
}

bool CSingleList::CheckCircle()
{
    if(Empty())
    {
        return false;
    }
    CElement* lpFast = m_lpSentinel->m_lpNext;
    CElement* lpSlow = m_lpSentinel->m_lpNext;
    while ((NULL != lpFast) && (NULL != lpFast->m_lpNext)) 
    {
        lpFast = lpFast->m_lpNext->m_lpNext;
        lpSlow = lpSlow->m_lpNext;
        if (lpFast == lpSlow)
        {
            return true;
        }
    }
    return false;
}

/**
 * �ϲ���2����������������
*/
void CSingleList::Merge(CSingleList& lst, std::function<int(void* t1, void* t2)> fnCompare)
{
    CElement* lpL1 = Begin();
    CElement* lpL2 = lst.Begin();

    if(!fnCompare)
    {
        return;
    }
    int iRet = 0;
    while((lpL2 != lst.End()))
    {
        if(lpL1 != End())
        {
            /**
             * ������Ҫ�������ȷλ��
             * 
             * ����1,����2; ����1 <- ����2, ����2���ϲ�������1��
             * 
             * �������1��Ԫ��С������2�е�Ԫ�أ���ѭ����������1�д�������2�еĵ�ǰԪ�ص�Ԫ��
             * ���������1���ҵ��������������ĵ�Ԫ��λ��[A]ʱ���������2�еĵ�ǰԪ�ز��뵽Ԫ��λ��[A]��ǰ��;
             * ���������1�в��������λ����������1��ĩλ����Ԫ��
            */
            iRet = fnCompare(lpL1->GetDataPtr(), lpL2->GetDataPtr());
            if(iRet < 0){
                lpL1 = Next();
                while(lpL1 != End()){
                    iRet = fnCompare(lpL1->GetDataPtr(), lpL2->GetDataPtr());
                    if(iRet > 0){
                        break;
                    }
                    lpL1 = Next();
                }
            }
        }else{
            iRet = -1;
        }
        CElement* lpNewElement = new CElement();
        if(NULL != lpNewElement)
        {
            lpNewElement->m_lpData = lpL2->GetDataPtr();
            if(lpL1 != End())
            {
                Insert(lpNewElement,lpL1, iRet < 0);
            }else{
                CElement* lpTail = Tail();
                Insert(lpNewElement,lpTail);
            }
        }
        lpL2 = lst.Next();
    }
}

void CSingleList::DeleteLastKth(int k)
{
    int i = 1;
    if(k <= 0)
    {
        return;
    }
    CElement* lpFast = Begin();
    while((lpFast != End()) && (i < k))
    {
        lpFast = Next();
        ++i;
    }
    if (lpFast == End())
    {
        return;
    }
    CElement* lpSlow = Begin();
    CElement* lpPrev = NULL;
    while (NULL != lpFast->m_lpNext)
    {
        lpFast = lpFast->m_lpNext;
        lpPrev = lpSlow;
        lpSlow = Next();
    }
    if(NULL != lpPrev)
    {
        lpPrev->m_lpNext = lpPrev->m_lpNext->m_lpNext;
    }
}

CElement* CSingleList::Center()
{
    CElement* lpFast = Begin();
    CElement* lpSlow = lpFast;
    while((NULL != lpFast->m_lpNext) && (NULL != lpFast->m_lpNext->m_lpNext))
    {
        lpFast = lpFast->m_lpNext->m_lpNext;
        lpSlow = lpSlow->m_lpNext;
    }
    return lpSlow;
}

CElement::CElement()
{
    m_lpNext = NULL;
    m_lpData = NULL;
}
CElement::~CElement()
{

}

void* CElement::GetDataPtr()
{
    return m_lpData;
}