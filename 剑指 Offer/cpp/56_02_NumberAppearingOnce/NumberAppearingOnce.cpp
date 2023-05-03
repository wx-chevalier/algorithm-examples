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

// ������56��������������Ψһֻ����һ�ε�����
// ��Ŀ����һ�������г���һ������ֻ����һ��֮�⣬�������ֶ����������Ρ���
// �ҳ��Ǹ��Գ���һ�ε����֡�

#include <cstdio>
#include <exception>

int FindNumberAppearingOnce(int numbers[], int length)
{
    if(numbers == nullptr || length <= 0)
        throw new std::exception("Invalid input.");

    int bitSum[32] = {0};
    for(int i = 0; i < length; ++i)
    {
        int bitMask = 1;
        for(int j = 31; j >= 0; --j)
        {
            int bit = numbers[i] & bitMask;
            if(bit != 0)
                bitSum[j] += 1;

            bitMask = bitMask << 1;
        }
    }

    int result = 0;
    for(int i = 0; i < 32; ++i)
    {
        result = result << 1;
        result += bitSum[i] % 3;
    }

    return result;
}

// ====================���Դ���====================
void Test(const char* testName, int numbers[], int length, int expected)
{
    int result = FindNumberAppearingOnce(numbers, length);
    if(result == expected)
        printf("%s passed.\n", testName);
    else
        printf("%s FAILED.\n", testName);
}

// �������ֶ���������Ψһ����������С��
void Test1()
{
    int numbers[] = { 1, 1, 2, 2, 2, 1, 3 };
    int expected = 3;
    Test("Test1", numbers, sizeof(numbers) / sizeof(int), expected);
}

// �������ֶ���������Ψһ�����ֵĴ�Сλ���м�
void Test2()
{
    int numbers[] = { 4, 3, 3, 2, 2, 2, 3 };
    int expected = 4;
    Test("Test2", numbers, sizeof(numbers) / sizeof(int), expected);
}

// �������ֶ���������Ψһ������������
void Test3()
{
    int numbers[] = { 4, 4, 1, 1, 1, 7, 4 };
    int expected = 7;
    Test("Test3", numbers, sizeof(numbers) / sizeof(int), expected);
}

// Ψһ�������Ǹ���
void Test4()
{
    int numbers[] = { -10, 214, 214, 214 };
    int expected = -10;
    Test("Test4", numbers, sizeof(numbers) / sizeof(int), expected);
}

// ����Ψһ�����֣��������ֶ��Ǹ���
void Test5()
{
    int numbers[] = { -209, 3467, -209, -209 };
    int expected = 3467;
    Test("Test5", numbers, sizeof(numbers) / sizeof(int), expected);
}

// �ظ�������������Ҳ�и���
void Test6()
{
    int numbers[] = { 1024, -1025, 1024, -1025, 1024, -1025, 1023 };
    int expected = 1023;
    Test("Test6", numbers, sizeof(numbers) / sizeof(int), expected);
}

// �������ֶ��Ǹ���
void Test7()
{
    int numbers[] = { -1024, -1024, -1024, -1023 };
    int expected = -1023;
    Test("Test7", numbers, sizeof(numbers) / sizeof(int), expected);
}

// Ψһ��������0
void Test8()
{
    int numbers[] = { -23, 0, 214, -23, 214, -23, 214 };
    int expected = 0;
    Test("Test8", numbers, sizeof(numbers) / sizeof(int), expected);
}

// ����Ψһ�����֣��������ֶ���0
void Test9()
{
    int numbers[] = { 0, 3467, 0, 0, 0, 0, 0, 0 };
    int expected = 3467;
    Test("Test9", numbers, sizeof(numbers) / sizeof(int), expected);
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

    return 0;
}
