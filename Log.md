﻿##### 这里是日志信息,记载着整个程序的新增完善与修改.  

全局内容:
- [x] 录入
- [x] 查询
- [x] 修改
- [x] 删除
- [x] 导入
- [x] 导出
- [x] 设置错误状态并合理处理
- [x] 建立输入样例
# Mar 14:
>### 在 csdn 上搜索相关二叉排序树代码,并对其内容与编程逻辑进行优化与修改(一言难尽啊)QAQ
- [x] 实现了bstree.h 与 相应的函数
- [x] 完成重载操作符相关代码
#### 后续
- [X] 将bstree进行封装成class (暂未学习) || (Mar15 finished)
- [X] 将bstree的内存管理进行提升，同时完善接口与类型安全（原代码并没有实现） || (Mar15 finished)
- [x] 完成主函数相关代码

# Mar 15:
>## 凌晨:
- [x] 在 cpp 中 删去 using namespace std 防止污染全局命名空间
- [x] 错误处理改进（使用标准异常处理机制）
- [x] 将类定义和实现合并到.hpp文件 
- [x] 为每个函数增加注释
>### 改出问题了，不知道是自己改的还是本身有的
- [x] Issue: 方法 remove 存在一定问题, 当 删除节点为root时触发空指针问题，产生数据丢失。
``` cpp

static inline void updateParentPointer(BTNode *&root, BTNode *parent, BTNode *target, BTNode *newChild)

```
>## 下午:
- [X] 将功能函数进行细分,保证数据安全. 已全部将bstree进行封装成class => bstree.hpp
- [x] 完成功能打印 `void printMainFuction()`
- [x] 录入 (Mar16 finished)
### 具体身份证检查
- [x] 长度
- [x] 字符类型
- [ ] 地区检查
- [x] 日期
- [x] 校验码
  
# Mar 16
>### 发现没做手机号码验证, 立马询问deepseek怎么检查号码正确, 于是得到了
- [ ] 号段
- [x] 长度
- [x] 干扰字符
- [ ] 国际号码处理
- [x] 国际码处理
>### 同时学了一下正则表达式验证(没学过之前都)
- [x] 录入
- [x] 查询
- [x] 删除
- [x] 修改
### 将所有函数实现在了hpp中(这是错误的),应该把声明留在hpp中,在cpp中具体实现重新调整代码逻辑

#### 同时我想,现在正在使用着github仓库托管,但关于git之类的东西几乎不太懂(在两台设备中进行着编写程序),诸如fork,branch之类,同时不明白一个团队几个人同时编写工程是如何通过git来进行协同的?

# Mar17
>### 打开了vscode的代码分析发现全部cpp文件报错，主力机mingw64版本过低了。。。。而轻薄本没有。。 
- [x] 导入
- [x] 导出 
>### 想新增一个功能，打印所有数据来更好的debug BSTREE的crud是否正常
- [x] 完成 ``` printAllData() ```
### 用了cmake对代码进行编译
>### 更改操作未完善,输入号码查询即结束,并没有提示更改操作
- [x] 完善更改操作
#### 或许一个人可以有不同的手机号码, 因为我们每个人的身份证不一样, 所以我们不应该对一个人多存信息(会造成重复)
- [ ] 一人多号
- [x] 改善输入输出卡死,当输入一个数字的时候输入了非法字符导致cin卡死.
  
# Mar18
>### 想做一个返回的操作选项
- [x] 输入身份证时可以输入quit指令让程序终止当前操作
>### !!修改操作能把人改没了 ?!?!
- [x] 修复修改操作会丢失身份证信息