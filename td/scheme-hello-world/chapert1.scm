(use-modules (unit-test))

(define (square a) (* a a))
(define (excercise1.1 a b c)
  (if (= a 0) (+ (square c) (square b))
       (+ (square a) (square b))))

(assert-equal 0 (excercise1.1 0 0 0))
(assert-equal 1 (excercise1.1 1 0 0))
(assert-equal 4 (excercise1.1 2 0 0))
(assert-equal 5 (excercise1.1 2 1 0))
(assert-equal 5 (excercise1.1 0 2 1))
