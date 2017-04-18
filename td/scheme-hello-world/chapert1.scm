(use-modules (unit-test))

(define (square a) (* a a))
(define (excercise1.1 a b c) (square a))

(assert-equal 0 (excercise1.1 0 0 0))
(assert-equal 1 (excercise1.1 1 0 0))
(assert-equal 4 (excercise1.1 2 0 0))
