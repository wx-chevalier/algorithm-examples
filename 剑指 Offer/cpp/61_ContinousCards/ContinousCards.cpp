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

// ������61���˿��Ƶ�˳��
// ��Ŀ�����˿����������5���ƣ��ж��ǲ���һ��˳�ӣ�����5�����ǲ��������ġ�
// 2��10Ϊ���ֱ���AΪ1��JΪ11��QΪ12��KΪ13������С�����Կ����������֡�

#include <cstdio>
#include <cstdlib>

int Compare(const void *arg1, const void *arg2);

bool IsContinuous(int* numbers, int length)
{
    if(numbers == nullptr || length < 1)
        return false;

    qsort(numbers, length, sizeof(int), Compare);

    int numberOfZero = 0;
    int numberOfGap = 0;

    // ͳ��������0�ĸ���
    for(int i = 0; i < length && numbers[i] == 0; ++i)
        ++numberOfZero;

    // ͳ�������еļ����Ŀ
    int small = numberOfZero;
    int big = small + 1;
    while(big < length)
    {
        // ��������ȣ��ж��ӣ���������˳��
        if(numbers[small] == numbers[big])
            return false;

        numberOfGap += numbers[big] - numbers[small] - 1;
        small = big;
        ++big;
    }

    return (numberOfGap > numberOfZero) ? false : true;
}

int Compare(const void *arg1, const void *arg2)
{
    return *(int*) arg1 - *(int*) arg2;
}

// ====================���Դ���====================
void Test(const char* testName, int* numbers, int length, bool expected)
{
    if(testName != nullptr)
        printf("%s begins: ", testName);

    if(IsContinuous(numbers, length) == expected)
        printf("Passed.\n");
    else
        printf("Failed.\n");
}

void Test1()
{
    int numbers[] = { 1, 3, 2, 5, 4 };
    Test("Test1", numbers, sizeof(numbers) / sizeof(int), true);
}

void Test2()
{
    int numbers[] = { 1, 3, 2, 6, 4 };
    Test("Test2", numbers, sizeof(numbers) / sizeof(int), false);
}

void Test3()
{
    int numbers[] = { 0, 3, 2, 6, 4 };
    Test("Test3", numbers, sizeof(numbers) / sizeof(int), true);
}

void Test4()
{
    int numbers[] = { 0, 3, 1, 6, 4 };
    Test("Test4", numbers, sizeof(numbers) / sizeof(int), false);
}

void Test5()
{
    int numbers[] = { 1, 3, 0, 5, 0 };
    Test("Test5", numbers, sizeof(numbers) / sizeof(int), true);
}

void Test6()
{
    int numbers[] = { 1, 3, 0, 7, 0 };
    Test("Test6", numbers, sizeof(numbers) / sizeof(int), false);
}

void Test7()
{
    int numbers[] = { 1, 0, 0, 5, 0 };
    Test("Test7", numbers, sizeof(numbers) / sizeof(int), true);
}

void Test8()
{
    int numbers[] = { 1, 0, 0, 7, 0 };
    Test("Test8", numbers, sizeof(numbers) / sizeof(int), false);
}

void Test9()
{
    int numbers[] = { 3, 0, 0, 0, 0 };
    Test("Test9", numbers, sizeof(numbers) / sizeof(int), true);
}

void Test10()
{
    int numbers[] = { 0, 0, 0, 0, 0 };
    Test("Test10", numbers, sizeof(numbers) / sizeof(int), true);
}

// �ж���
void Test11()
{
    int numbers[] = { 1, 0, 0, 1, 0 };
    Test("Test11", numbers, sizeof(numbers) / sizeof(int), false);
}

// ³���Բ���
void Test12()
{
    Test("Test12", nullptr, 0, false);
}

int main(int argc, char* argv[])
{
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();
    Test6();
    Test7();
    Test8();
    Test9();
    Test10();
    Test11();
    Test12();

    return 0;
}

