(use-modules (unit-test))

(define (square a) (* a a))
(define (excercise1.1 a b c) (+ (square a)
  (if (< b c) (square c)
        (square b))))

(assert-equal 0 (excercise1.1 0 0 0))
(assert-equal 1 (excercise1.1 1 0 0))
(assert-equal 4 (excercise1.1 2 0 0))
(assert-equal 5 (excercise1.1 2 1 0))
(assert-equal 5 (excercise1.1 1 0 2))
(assert-equal 13 (excercise1.1 2 1 3))
