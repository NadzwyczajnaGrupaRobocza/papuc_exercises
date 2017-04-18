(use-modules (unit-test))

(define (excercise1.1 a b c) a)

(assert-equal 0 (excercise1.1 0 0 0))
(assert-equal 1 (excercise1.1 1 0 0))
