(use-modules (unit-test))

(define epsilon 0.0001)

(define (inc n) (+ n 1))
(define (dec n) (- n 1))

(define (square a) (* a a))
(define (cube a) (* a a a))
(define (sum-of-squares a b) (+ (square a) (square b)))

(define (sum-squares-of-larger-two a b c)
  (cond ((and (> a b) (> b c)) (sum-of-squares a b))
        ((and (> a b) (> c b)) (sum-of-squares a c))
        )
  )

(define (average x y)
  (/ (+ x y) 2))

(define (close-enough? a b)
  (< (abs (- a b)) epsilon))

(define (sqrt x)
  (define (good-enough? guess)
    (< (abs (- (square guess) x)) epsilon))
  (define (improve guess)
    (average guess (/ x guess)))
  (define (sqrt-iter guess)
    (if (good-enough? guess)
        guess
        (sqrt-iter (improve guess))))
  (sqrt-iter 1.0))

(define (sqrt-sa x)
  (define (improve guess)
    (average guess (/ x guess)))
  (define (sqrt-stabilizing-approx guess prev-guess)
    (if (close-enough? guess prev-guess)
        guess
        (sqrt-stabilizing-approx (improve guess) guess)))
  (sqrt-stabilizing-approx 1.0 0.0))

(define (test-sqrt-implementation sqrt-fun)
  (assert-numeric-= 5.0 (sqrt-fun 25.0) 0.0001)
  (assert-numeric-= 1.414 (sqrt-fun 2.0)  0.001))

(test-sqrt-implementation sqrt)
(test-sqrt-implementation sqrt-sa)

;;; Ex. 1.8
(define (cube-rt-reverse-checked x guess)
  (if (good-enough-cube? x guess)
      guess
      (cube-rt-reverse-checked x (improve-cube x guess))))

(define (good-enough-cube? x guess)
  (< (abs (- (cube guess) x)) epsilon))

(define (improve-cube x guess)
  (/ (+ (/ x (square guess)) (* 2 guess)) 3))

(define (cube-rt-stabilizing-approx x guess prev-guess)
  (if (close-enough? guess prev-guess)
      guess
      (cube-rt-stabilizing-approx x (improve-cube x guess) guess)))

(define (cube-rt-rc x)
  (cube-rt-reverse-checked x 1.0))

(define (cube-rt-sa x)
  (cube-rt-stabilizing-approx x 1.0 0.0))

(define (test-cube-rt-implementation cube-rt-fun)
  (assert-numeric-= 5.0 (cube-rt-fun 125.0) epsilon)
  (assert-numeric-= 3.0 (cube-rt-fun 27.0)  epsilon))

(test-cube-rt-implementation cube-rt-rc)
(test-cube-rt-implementation cube-rt-sa)

;;;; Section 1.2

;;; Factorial example

(define (factorial n)
  (define (fact-iter product counter max-count)
    (if (> counter max-count)
        product
        (fact-iter (* counter product)
                   (+ counter 1)
                   max-count)))
  (fact-iter 1 1 n))

(define (test-factorial-implementation fac-fun)
  (assert-equal 1 (fac-fun 0))
  (assert-equal 1 (fac-fun 1))
  (assert-equal 720 (fac-fun 6)))

(test-factorial-implementation factorial)

;;; Exercise 1.10

(define (A x y)
  (cond ((= y 0) 0)
        ((= x 0) (* 2 y))
        ((= y 1) 2)
        (else (A (- x 1)
                 (A x (- y 1))))))

;;; Subsection 1.2.2

(define (fib-r n)
  (cond ((= n 0) 0)
        ((= n 1) 1)
        (else (+ (fib-r (- n 1))
                 (fib-r (- n 2))))))

(define (fib-i n)
  (define (fib-iter a b count)
    (if (= count 0)
        b
        (fib-iter (+ a b) a (- count 1))))
  (fib-iter 1 0 n))

(define (test-fibbonaci-implementation fib)
  (assert-equal 0 (fib 0))
  (assert-equal 1 (fib 1))
  (assert-equal 5 (fib 5))
  (assert-equal 34 (fib 9))
  (assert-equal 55 (fib 10)))

(test-fibbonaci-implementation fib-r)
(test-fibbonaci-implementation fib-i)

;; consider adding timing to unit test
;; consider adding "define-test" procedure that would take care of bookkeeping

(define-syntax-rule (time expr ...)
  (let ((timing-begin (current-time))
         )
    (display "Computed result: ")
    (display expr ...)
    (newline)
    (display "Operation took: ")
    (display (- (current-time) timing-begin))
    (newline)
    ))
;;; Example: Counting change

(define (count-change amount)
  (define (cc amount kinds-of-coins)
    (cond ((= amount 0) 1)
          ((or (< amount 0)
               (= kinds-of-coins 0))
           0)
          (else (+ (cc amount (- kinds-of-coins 1))
                   (cc (- amount (first-denomination kinds-of-coins))
                       kinds-of-coins)))))
  (define (first-denomination kinds-of-coins)
    (cond ((= kinds-of-coins 1) 1)
          ((= kinds-of-coins 2) 5)
          ((= kinds-of-coins 3) 10)
          ((= kinds-of-coins 4) 25)
          ((= kinds-of-coins 5) 50)))
  (cc amount 5))

;;; Exercise 1.11

(define (fib3-r n)
  (cond ((< n 3) n)
        (else (+ (fib3-r (- n 1)) (* 2 (fib3-r (- n 2)))
                 (* 3 (fib3-r (- n 3)))))))

(define (fib3-i n)
  (define (fib3-linear-comb a b c)
    (+ a (* 2 b) (* 3 c)))
  (define (fib3-iter f3 f2 f1 ct)
    (if (= ct n)
        f3
        (fib3-iter (fib3-linear-comb f3 f2 f1)
                   f3
                   f2
                   (+ ct 1))))
  (if (< n 3)
      n
      (fib3-iter 2 1 0 2)))

(define (test-fib3-comparative f1 f2)
  (assert-equal (f1 5) (f2 5))
  (assert-equal (f1 10) (f2 10))
  (assert-equal (f1 20) (f2 20)))

(test-fib3-comparative fib3-r fib3-i)

;;; Exercise 1.12

(define (pascal n k)
  (define (pascal-impl a b)
    (cond ((or (< a 0) (< b 0)) 0)
          ((= a 0) 1)
          ((= b 0) 1)
          (else (+ (pascal-impl (dec a) b)
                   (pascal-impl a (dec b))))))
  (if (< n k)
      0
      (pascal-impl (- n k) k)))

(define (test-pascal-implementation p)
  (assert-equal 3 (p 3 1))
  (assert-equal 6 (p 4 2))
  (assert-equal 10 (p 5 3))
  (assert-equal 10 (p 5 2))
  (assert-equal 1 (p 100 0))
  (assert-equal 100 (p 100 1))
  (assert-equal 1 (p 100 100))
  (assert-equal 1 (p 6 0))
  (assert-equal 6 (p 6 1))
  (assert-equal 15 (p 6 2))
  (assert-equal 20 (p 6 3))
  (assert-equal 15 (p 6 4))
  (assert-equal 6 (p 6 5))
  (assert-equal 1 (p 6 6)))

(test-pascal-implementation pascal)

;;; Exercise 1.15

(define (sine angle)
  (define (sine-reduction-outer x)
    (- (* 3 x) (* 4 (cube x))))
  (if (not (> (abs angle) 0.01))
      angle
      (sine-reduction-outer (sine (/ angle 3.0)))))

;;;; Subsection 1.2.4

(define (expt-r b n)
  (if (= n 0)
      1
      (* b (expt-r b (dec n)))))

(define (expt-i b n)
  (define (expt-iter counter product)
    (if (= counter 0)
        product
        (expt-iter (dec counter) (* product b))))
  (expt-iter n 1.0))

(define (test-expt-implementation expt)
  (assert-numeric-= 125.0 (expt 5.0 3) epsilon)
  (assert-numeric-= 1024.0 (expt 2.0 10) epsilon)
  (assert-numeric-= 1.0 (expt 1234.5 0) epsilon))

(test-expt-implementation expt-r)
(test-expt-implementation expt-i)

(define (fast-expt-r b n)
  (cond ((= n 0) 1)
        ((even? n) (square (fast-expt-r b (/ n 2))))
        (else (* b (fast-expt-r b (- n 1))))))

(test-expt-implementation fast-expt-r)

;;; Exercise 1.16

(define (fast-expt-i b n)
  (define (iter-step base result exp)
    (cond ((= exp 0) result)
          ((even? exp) (iter-step (* base base) result (/ exp 2)))
          (else (iter-step base (* result base) (dec exp)))))
  (iter-step b 1.0 n))

(test-expt-implementation fast-expt-i)

;;; Exercise 1.19

(define (fast-fib n)
  (define (fib-iter a b p q count)
    (cond ((= count 0) b)
          ((even? count)
           (fib-iter a
                     b
                     (+ (square p) (square q))
                     (+ (square q) (* 2 p q))
                     (/ count 2)))
          (else
           (fib-iter (+ (* b q)
                        (* a q)
                        (* a p))
                     (+ (* b p)
                        (* a q))
                     p
                     q
                     (- count 1)))))
  (fib-iter 1 0 0 1 n))

(define (test-fib-implementation fib)
  (assert-equal 0 (fib 0))
  (assert-equal 1 (fib 1))
  (assert-equal 1 (fib 2))
  (assert-equal 2 (fib 3))
  (assert-equal 144 (fib 12)))

(test-fib-implementation fast-fib)
