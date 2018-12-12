---
layout: post
title: Y-combinator
category: [scheme]
---

# Y 组合子
lambda函数是匿名函数，也就是没有名字的函数，那么如何用lambda函数实现递归呢？

下面看一个递归求阶乘的函数：

```scheme
(define fac
  (lambda (x)
    (if (= 0 x)
        1
        (* x (fac (- x 1))))))
```
如果不要第一行的命名，那如何递归？稍作思考，我们不难想到在lambda函数里面嵌套一个lambda函数，里面的函数用外面的函数的参数来递归，如下：

```scheme
(lambda (fac)
  (lambda (x)
    (if (= 0 x)
        1
        (* x (fac (- x 1))))))
```
问题来了，这个匿名函数需要两个参数，第一个是fac，第二个是x，x是我们要计算的数字，那fac是什么？根据最后一行，我们可知fac应该是一个函数，我们赋予它一个什么函数比较好呢？因为我们在做的是递归，所以凭直觉我们把他自己赋值给他自己（对真的就是直觉，毕竟递归就是引用自己）。那么我们得到了下面这个东西：

```scheme
((lambda (fac)
     (lambda (x)
       (if (= 0 x)
           1
           (* x (fac (- x 1))))))
   ((lambda (fac)
     (lambda (x)
       (if (= 0 x)
           1
           (* x (fac (- x 1))))))
    (lambda(..)(...)))
```
通过观察，我们发现这个函数其实等价于下面这个函数：

```scheme
((lambda (f)
     (f f))
   (lambda (fac)
     (lambda (x)
       (if (= 0 x)
           1
           (* x (fac (- x 1)))))))
```
上面的

```scheme
((lambda (f)
     (f f)))
```
实际上是让跟在后面的函数调用自己，这样函数被大大简化，而且不再需要在末尾加上一个不知道应该是什么的打了省略号的函数（其实真要填充的话还是填它自己，可这样下去就无穷无尽了）。
此外，如果试着运行一下上面的匿名函数就会发现，这个函数只能算0的阶乘，没有简化前的也是。如果要算1的阶乘，对于未简化的函数，我们需要在省略号处重复变量为fac的匿名函数，而对于简化后的函数我们可以这样写：

```scheme
((lambda (f)
     (f (f f)))  ;;这里把f多嵌套一层，如果要算2的阶乘就(f (f (f f)))，以此类推
   (lambda (fac)
     (lambda (x)
       (if (= 0 x)
           1
           (* x (fac (- x 1)))))))
```
这样显然是不行的，那要怎么改才行呢？首先我们知道fac和f都是形参，没有本质区别，所以可以写成：

```scheme
((lambda (f)
     (f f))
   (lambda (f)
     (lambda (x)
       (if (= 0 x)
           1
           (* x (f (- x 1)))))))
```
根据前面提到的算1的阶乘的方法，我们得知要想算更大的数，需要让f调用自己，而函数的最后一行中f只是调用下一次的数字，所以无法无限循环 
，因此有如下改动：

```scheme
((lambda (f)
     (f f))
   (lambda (f)
     (lambda (x)
       (if (= 0 x)
           1
           (* x ((f f) (- x 1))))))) ;; 变f为(f f)
```
这样，这个函数就可以计算任何一个数字的阶乘，而且它没有名字！
这东西被称为“穷人的Y组合子”，它和真正的Y组合子仍然有差距，它并不具有普遍性，只能算阶乘。为了得到更普遍的函数，我们需要继续抽象。

首先我们考虑到，不管这个函数有什么功能，它递归时一定要有(f f)，然后才是参与递归的变量。因为这是一个通用的函数，我们把它抽象出来：

```scheme
(lambda (x) 
  ((f f) x))
```
这个函数接受一个变量，并且返回(f f)和这个变量，那么最后一行就可以写成：

```
(* x (lambda (x) ((f f) (- x 1)))
```
想一想，我们最终的目的是什么？是把fac这个函数从“穷人的Y组合子”里面剥离出来，而fac的最后一步不就是

```scheme
(* x (fac (- x 1))
```
吗？前面抽象出的那个函数正好可以用在这里，然后在前面再加上变量为fac的函数，得到：

```scheme
((lambda (f)
    (f f))
   (lambda (f)
     ((lambda (fac)
       (lambda (x)
         (if (= 0 x)
             1
             (* x (fac (- x 1))))))
      (lambda (x) ((f f) x)))))
```
在这个函数里面，第4到第8行的函数和其它部分互不影响，可以抽出来。这样我们就可以得到下面的函数：

```scheme
(lambda (func)
    ((lambda(f)
       (f f))
     (lambda (f)
       (func (lambda (x)
             ((f f) x))))))
```
func替代了前面的可剥离部分，现在，我们就得到了所谓的Y组合子。它接受两个变量，第一个是函数，第二个是用来计算的参数。下面是Y组合子表示的阶乘：

```scheme
(define Y
  (lambda (func)
    ((lambda(f)
       (f f))
     (lambda (f)
       (func (lambda (x)
             ((f f) x)))))))
;; 上面的函数体中没有用到Y，Y只是为了方便使用而绑定的
(Y (lambda (fac)
      (lambda (x)
        (if (= 0 x)
            1
            (* x (fac (- x 1)))))))
;; 带入4
((Y (lambda (fac)
      (lambda (x)
        (if (= 0 x)
            1
            (* x (fac (- x 1)))))))
 4)
;; 运行得到24,正确
```

Q.E.D
