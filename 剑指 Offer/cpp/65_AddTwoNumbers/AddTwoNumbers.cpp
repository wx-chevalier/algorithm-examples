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

// ������65�����üӼ��˳����ӷ�
// ��Ŀ��дһ������������������֮�ͣ�Ҫ���ں������ڲ���ʹ�ã�������������
// ����������š�

#include <cstdio>

int Add(int num1, int num2)
{
    int sum, carry;
    do
    {
        sum = num1 ^ num2;
        carry = (num1 & num2) << 1;

        num1 = sum;
        num2 = carry;
    }
    while(num2 != 0);

    return num1;
}

// ====================���Դ���====================
void Test(int num1, int num2, int expected)
{
    int result = Add(num1, num2);
    if(result == expected)
        printf("%d + %d is %d. Passed\n", num1, num2, result);
    else
        printf("%d + %d is %d. FAILED\n", num1, num2, result);
}

int main(int argc, char* argv[])
{
    Test(1, 2, 3);
    Test(111, 899, 1010);

    Test(-1, 2, 1);
    Test(1, -2, -1);

    Test(3, 0, 3);
    Test(0, -4, -4);

    Test(-2, -8, -10);

    return 0;
}

