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

// ������66�������˻�����
// ��Ŀ������һ������A[0, 1, ��, n-1]���빹��һ������B[0, 1, ��, n-1]����
// ��B�е�Ԫ��B[i] =A[0]��A[1]���� ��A[i-1]��A[i+1]������A[n-1]������ʹ�ó�����

#include <cstdio>
#include <vector>

using namespace std;

void BuildProductionArray(const vector<double>& input, vector<double>& output)
{
    int length1 = input.size();
    int length2 = output.size();

    if(length1 == length2 && length2 > 1)
    {
        output[0] = 1;
        for(int i = 1; i < length1; ++i)
        {
            output[i] = output[i - 1] * input[i - 1];
        }

        double temp = 1;
        for(int i = length1 - 2; i >= 0; --i)
        {
            temp *= input[i + 1];
            output[i] *= temp;
        }
    }
}

//================= Test Code =================
static bool EqualArrays(const vector<double>& input, const vector<double>& output)
{
    int length1 = input.size();
    int length2 = output.size();

    if(length1 != length2)
        return false;

    for(int i = 0; i < length1; ++i)
    {
        if(abs(input[i] - output[i]) > 0.0000001)
            return false;
    }

    return true;
}

static void test(char* testName, const vector<double>& input, vector<double>& output, const vector<double>& expected)
{
    printf("%s Begins: ", testName);

    BuildProductionArray(input, output);
    if(EqualArrays(output, expected))
        printf("Passed.\n");
    else
        printf("FAILED.\n");
}

static void test1()
{
    // ����������û��0
    double input[] = { 1, 2, 3, 4, 5 };
    double output[] = { 0, 0, 0, 0, 0 };
    double expected[] = { 120, 60, 40, 30, 24 };

    test("Test1", vector<double>(input, input + sizeof(input) / sizeof(double)),
        vector<double>(output, output + sizeof(output) / sizeof(double)),
        vector<double>(expected, expected + sizeof(expected) / sizeof(double)));
}

static void test2()
{
    // ������������һ��0
    double input[] = { 1, 2, 0, 4, 5 };
    double output[] = { 0, 0, 0, 0, 0 };
    double expected[] = { 0, 0, 40, 0, 0 };

    test("Test2", vector<double>(input, input + sizeof(input) / sizeof(double)),
        vector<double>(output, output + sizeof(output) / sizeof(double)),
        vector<double>(expected, expected + sizeof(expected) / sizeof(double)));
}

static void test3()
{
    // ����������������0
    double input[] = { 1, 2, 0, 4, 0 };
    double output[] = { 0, 0, 0, 0, 0 };
    double expected[] = { 0, 0, 0, 0, 0 };

    test("Test3", vector<double>(input, input + sizeof(input) / sizeof(double)),
        vector<double>(output, output + sizeof(output) / sizeof(double)),
        vector<double>(expected, expected + sizeof(expected) / sizeof(double)));
}

static void test4()
{
    // ��������������������
    double input[] = { 1, -2, 3, -4, 5 };
    double output[] = { 0, 0, 0, 0, 0 };
    double expected[] = { 120, -60, 40, -30, 24 };

    test("Test4", vector<double>(input, input + sizeof(input) / sizeof(double)),
        vector<double>(output, output + sizeof(output) / sizeof(double)),
        vector<double>(expected, expected + sizeof(expected) / sizeof(double)));
}

static void test5()
{
    // ����������ֻ����������
    double input[] = { 1, -2 };
    double output[] = { 0, 0 };
    double expected[] = { -2, 1 };

    test("Test5", vector<double>(input, input + sizeof(input) / sizeof(double)),
        vector<double>(output, output + sizeof(output) / sizeof(double)),
        vector<double>(expected, expected + sizeof(expected) / sizeof(double)));
}

int main(int argc, char* argv[])
{
    test1();
    test2();
    test3();
    test4();
    test5();

    return 0;
}
