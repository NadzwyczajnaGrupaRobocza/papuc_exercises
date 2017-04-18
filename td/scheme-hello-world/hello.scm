;;; Hello world program
(define name "World")
(display (string-append "Hello " name "!" ))
(newline)
(display (/ 10 4))
(newline)

(define name "Another world")
(display (string-append "Hello " name "!" ))
(newline)

(define (fancy_calulation a b c) 42)
(display "Fancy calulation result: ")
(display(fancy_calulation  "a" 10 4))
(newline)

(define (another_fancy_calulation a b c) (* b 42))
(display "Another fancy calulation result: ")
(display(another_fancy_calulation  "a" 10 4))
(newline)

(define (abs x) (
                 cond ((> x 0) x)
                      ((>= x -1) 1024)
                      ((< x 0) (- x))))

(display "abs: ")
(display(abs 4))
(display " ")
(display(abs 0))
(display " ")
(display(abs -4))
(display " ")
(display(abs -1))
(newline)
