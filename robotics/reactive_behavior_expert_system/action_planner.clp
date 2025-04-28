
;************************************************
;*						*
;*	oracle.clp 				*
;*						*
;*	Jesus Savage				*
;*						*
;*		Bio-Robotics Laboratory		*
;*		UNAM, 2019			*
;*						*
;*						*
;************************************************




(deftemplate on-top-of
	(slot upper)
	(slot lower)
)


(deftemplate goal (slot move)(slot on-top-of))

(deffacts initial-state
	(block a)
	(block b)
	(block c)
	(block d)
	(block e)
	(block f)
	(on-top-of (upper nothing)(lower a))
	(on-top-of (upper a)(lower b))
	(on-top-of (upper b)(lower c))
	(on-top-of (upper c)(lower floor))
	(on-top-of (upper nothing)(lower d))
	(on-top-of (upper d)(lower e))
	(on-top-of (upper e)(lower f))
	(on-top-of (upper f)(lower floor))
	;(goal (move c)(on-top-of e))
	(goal (move f)(on-top-of c))
	(num-acc 1)
)



(defrule move-directly
	?goal <- (goal (move ?block1) (on-top-of ?block2))
	(block ?block1)
	(block ?block2)
	(on-top-of (upper nothing) (lower ?block1))
	?stack-1 <- (on-top-of (upper ?block1)(lower ?block3))
	?stack-2 <- (on-top-of (upper nothing)(lower ?block2))
	?f1 <- (num-acc ?num)
	=>
	(retract ?goal ?stack-1 ?stack-2 ?f1)
	(assert (on-top-of (upper ?block1)(lower ?block2))
       	  (on-top-of (upper nothing)(lower ?block3)))
	(printout t ?block1 " moved on top of " ?block2 "." crlf)
	(assert (OPERATOR ?num MOVE ?block1 ?block2))
	(assert (num-acc (+ 1 ?num) ) )
)


(defrule move-to-floor
	?goal <- (goal (move ?block1) (on-top-of floor))
	(block ?block1)
	(on-top-of (upper nothing) (lower ?block1))
	?stack <- (on-top-of (upper ?block1) (lower ?block2))	
	?f1 <- (num-acc ?num)
	=>
	(retract ?goal ?stack ?f1)
	(assert (on-top-of (upper ?block1)(lower floor))
        	  (on-top-of (upper nothing)(lower ?block2)))
	(printout t ?block1 " moved on top of floor. " crlf)
	(assert (OPERATOR ?num MOVE ?block1 floor))
	(assert (num-acc (+ 1 ?num) ) )

)



(defrule clear-upper-block
	(goal (move ?block1))
	(block ?block1)
	(on-top-of (upper ?block2) (lower ?block1))
	(block ?block2)
=>
	(assert (goal (move ?block2)(on-top-of floor)))
)

(defrule clear-lower-block
	(goal (on-top-of ?block1))
	(block ?block1)
	(on-top-of (upper ?block2) (lower ?block1))
	(block ?block2)
	=>
	(assert (goal (move ?block2)(on-top-of floor)))
)


(defrule number-actions
	(declare (salience -100))
        ?f <- (number-actions)
	(num-acc ?num )
        =>
        (retract ?f)
        (printout t "ROS number-actions " ?num " ROS")
)




(defrule step
        ?f <- (step ?num)
	?f1 <- (OPERATOR ?num ?action ?block1 ?block2)
        =>
        (retract ?f ?f1)
	(printout t "ROS " ?num " " ?action " " ?block1 " " ?block2 " ROS")
)


(defrule clips-alive
	(declare (salience 1000))
	?f <- (alive clips)
	=>
	(retract ?f)
	(printout t "ROS clips alive ROS")
)



