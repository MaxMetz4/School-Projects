#lang racket

#|-------------------------------------------------------------------------------
 | Name: Maxwell Metzner
 | Pledge: I pledge my honor that I have abided by he Stevens Honor System.
 |-------------------------------------------------------------------------------|#

#|-------------------------------------------------------------------------------
 |                           Tree Method Extra Credit
 |-------------------------------------------------------------------------------|#

;; AND == &
;; OR == |
;; NOT == !
;; bi == biconditional
;; imp == implies

;;syntax- each part of proposition should be a function,
;; (conc (& (p (imp p q)))


(define (proposition prop)
  (cond
    [(equal? '() prop) "No proposition entered"]
    [else '()]))

(define (!!) #f)


