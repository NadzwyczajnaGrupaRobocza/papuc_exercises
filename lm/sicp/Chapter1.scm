(use-modules (unit-test))

(define epsilon 0.0001)

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
        (value (lambda () expr ...)))
    (display "Computed result: ")
    (display value)
    (newline)
    (display "Operation took: ")
    (display (- (current-time) timing-begin))
    (newline)
    ))
