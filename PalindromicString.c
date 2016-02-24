/**********************************************************************
* 版权所有 (C)2016, Zhou Zhaoxiong。
*
* 文件名称： PalindromicString.c
* 文件标识： 无
* 内容摘要： 回文判断
* 其它说明： 形如madam, php, 2992, 1234321这样的串就是回文串
* 当前版本： V1.0
* 作    者： Zhou Zhaoxiong
* 完成日期： 20160222
*
**********************************************************************/
#include <stdio.h>


// 重新定义数据类型
typedef signed   char  INT8;
typedef          int   INT32;
typedef unsigned int   UINT32;

// 全局变量声明, 用于存放汉字, 最大支持100个汉字
INT8   gszStrCharArray[101][5] = {0};  
UINT32 giCharNum               = 0;


// 函数声明
void JudgePalindromicString(INT8 *pszInputStr, UINT32 iInputStrLen, UINT32 iStrType);
void GetChineseChars(INT8 *pszInputStr);
INT32 JudgeStrFormat(INT8 *pszInputStr, UINT32 iStrType);


/**********************************************************************
* 功能描述： 主函数
* 输入参数： 无
* 输出参数： 无
* 返 回 值： 0-执行成功   其它-执行失败
* 其它说明： 无
* 修改日期        版本号     修改人            修改内容
* ---------------------------------------------------------------------
* 20160222        V1.0     Zhou Zhaoxiong      创建
***********************************************************************/
INT32 main()
{
    UINT32 iStrType        = 0;
    INT32  iRetVal         = 0;
    INT8   szInputStr[100] = {0};

    printf("Please input the string type(1:中文字符串,2:非中文字符串): \n");
    scanf("%d", &iStrType);
    
    printf("Please input the string: \n");
    scanf("%s", szInputStr);

    // 判断输入的字符串是中文字符串或者是非中文字符串
    iRetVal = JudgeStrFormat(szInputStr, iStrType);
    if (iRetVal != 0)
    {
        return -1;
    }

    if (iStrType == 1)     // 如果输入的是中文串, 则先获取各个中文字符
    {
        GetChineseChars(szInputStr);

        if (giCharNum <= 1)    // 只输入了一个字符, 直接返回
        {
            printf("%s has only one character, please check!\n", szInputStr);
            return -1; 
        }
    }
    else if (iStrType == 2)
    {
        if (strlen(szInputStr) <= 1)  // 只输入了一个字符, 直接返回
        {
            printf("%s has only one character, please check!\n", szInputStr);
            return -1; 
        }
    }
 
    // 判断输入的字符串是否为回文串
    JudgePalindromicString(szInputStr, strlen(szInputStr), iStrType);

    return 0;            
}


/**********************************************************************
* 功能描述：判断输入的字符串是否为回文串
* 输入参数：pszInputStr-输入的字符串
            iInputStrLen-输入的字符串的长度
            iStrType-输入的字符串的类型
* 输出参数：无
* 返 回 值：无
* 其它说明：无
* 修改日期       版本号        修改人          修改内容
* -------------------------------------------------------------------
* 20160222       V1.0      Zhou Zhaoxiong      创建
***********************************************************************/
void JudgePalindromicString(INT8 *pszInputStr, UINT32 iInputStrLen, UINT32 iStrType)
{
    UINT32 iPosFlag   = 0;

    if (NULL == pszInputStr)
    {
        return;
    }

    if (iStrType == 1)     // 中文字符串
    {
        for (iPosFlag = 0; iPosFlag < giCharNum/2; iPosFlag ++)
        {
            if (strcmp(gszStrCharArray[iPosFlag], gszStrCharArray[giCharNum-1-iPosFlag]) != 0)   // 有对应字符不相等
            {
                printf("%s is not a palindromic string!\n", pszInputStr);
                return;
            }
        }
    }

    if (iStrType == 2)     // 非中文字符串
    {
        // 从中间分开, 一前一后两个字符互相比较, 如果全部对应相等, 则是回文串
        for (iPosFlag = 0; iPosFlag < iInputStrLen/2; iPosFlag ++)
        {
            if (pszInputStr[iPosFlag] != pszInputStr[iInputStrLen-1-iPosFlag])   // 有对应字符不相等
            {
                printf("%s is not a palindromic string!\n", pszInputStr);
                return;
            }
        }
    }

    printf("%s is a palindromic string!\n", pszInputStr);

    return;
}


/**********************************************************************
* 功能描述：获取输入的字符串中的每个中文字符
* 输入参数：pszInputStr-输入的字符串
            iInputStrLen-输入的字符串的长度
* 输出参数：无
* 返 回 值：无
* 其它说明：无
* 修改日期       版本号        修改人          修改内容
* -------------------------------------------------------------------
* 20160222       V1.0      Zhou Zhaoxiong      创建
***********************************************************************/
void GetChineseChars(INT8 *pszInputStr)
{
    UINT32 iPosFlag = 0;
    
    if (NULL == pszInputStr)
    {
        return;
    }

    memset(gszStrCharArray, 0x00, sizeof(gszStrCharArray));
    giCharNum = 0;
    
    while (iPosFlag < strlen(pszInputStr))
    {
        snprintf(gszStrCharArray[giCharNum], sizeof(gszStrCharArray[giCharNum])-1, "%c%c", pszInputStr[iPosFlag], pszInputStr[iPosFlag+1]);

        iPosFlag = iPosFlag + 2;    // 每个中文字符占两个字节
        
        giCharNum ++;
    }
}


/**********************************************************************
* 功能描述：判断输入的字符串的格式是否正确
* 输入参数：pszInputStr-输入的字符串
            iStrType-输入的字符串的类型
* 输出参数：无
* 返 回 值：0-格式正确 其它-格式不正确
* 其它说明：无
* 修改日期       版本号        修改人          修改内容
* -------------------------------------------------------------------
* 20160222       V1.0      Zhou Zhaoxiong      创建
***********************************************************************/
INT32 JudgeStrFormat(INT8 *pszInputStr, UINT32 iStrType)
{
    UINT32 iPosFlag  = 0;
    
    if (NULL == pszInputStr)
    {
        return -1;
    }

    if (iStrType == 1)    // 先判断中文字符串
    {
        for (iPosFlag = 0; iPosFlag < strlen(pszInputStr); iPosFlag ++)
        {
            if (pszInputStr[iPosFlag] >= 0)     // 不小于0则表示含有非中文字符
            {
                printf("%s has non-Chinese character, please check!\n", pszInputStr);
                return -2;
            }
        }
    }
    else if (iStrType == 2)    // 再判断非中文字符串
    {
        for (iPosFlag = 0; iPosFlag < strlen(pszInputStr); iPosFlag ++)
        {
            if (pszInputStr[iPosFlag] < 0)     // 小于0则表示含有中文字符
            {
                printf("%s has Chinese character, please check!\n", pszInputStr);
                return -3;
            }
        }
    }
    else
    {
        printf("Please input the right string type!\n");
        return -4; 
    }

    return 0;
}
