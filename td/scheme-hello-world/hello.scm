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
