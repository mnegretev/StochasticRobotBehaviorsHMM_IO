;********************************************************
;*							*
;*	planner.clp					*
;*							*
;*							*
;*			University of Mexico		*
;*			Jesus Savage			*
;*							*
;*			4/22/05				*
;*			5/01/21				*
;*							*
;********************************************************



;************************************************
;*                                              *
;*      Rules                                   *
;*                                              *
;************************************************


(defrule exec-atrans
	(atrans (actor ?actor)(obj ?obj)(to ?person))
	(objects (name ?obj))
	(human (name ?person))
	(robots (name ?actor) (zone ?zone)(hands nil))
	(not (use vision)	)
  	=>
	(assert (ptrans (actor ?actor)(obj ?actor)(from ?zone)(to ?obj)))
	(assert (ptrans (actor ?actor)(obj ?actor)(to ?person)))
	(assert (grab (actor ?actor)(obj ?obj)))
)


(defrule exec-atrans-obj
	(atrans (actor ?actor)(obj ?obj)(to ?person))
	(objects (name ?obj))
	(human (name ?person))
	(robots (name ?actor) (zone ?zone)(hands ?obj))
	(not (use vision)	)
  	=>
	(assert (ptrans (actor ?actor)(obj ?actor)(to ?person)))
)



(defrule exec-atrans-vision
	?f <- (atrans (actor ?actor)(obj ?obj&:( neq ?obj nil))(to ?person))
	(use vision)	
  	=>
	(retract ?f)
	; it finds the representation of the object
	(bind ?message (str-cat "I will find the " ?obj))
	(assert (send-speech ?message))
	(bind ?command (str-cat "find " ?obj ))
	(assert (send-vision ?command))
	(assert (get-data-vision))
)


(defrule answer-find
	?f <- (answer-vision find ?obj ?dist ?angle ?num)
	=>
	(retract ?f)
	
	(if (eq ?num 1) then
		(bind ?message (str-cat "I found the " ?obj ))
	  else
		(bind ?message (str-cat "I could not find " ?obj))
	)

	(printout t crlf "Command: " ?message crlf)
	(assert (send-speech ?message))
)



(defrule exec-ptrans-not-in-room
	(declare (salience 100))
	?f <- (ptrans (actor ?actor)(obj ?actor)(to ?obj) )
	(objects (name ?obj) (zone ?zone))
	(not (robots (name ?actor)(hands ?obj)))
  	=>
	(retract ?f)
	; it goes to the selected zone
	(bind ?message (str-cat "I am going to " ?zone))
	(assert (send-speech ?message))
	(bind ?command (str-cat "go_to_room \"" ?zone "\""))
	(assert (send-robot ?command))
	
)

(defrule exec-ptrans-same-room
	(declare (salience 200))
	?f <- (ptrans (actor ?actor)(obj ?actor)(to ?obj) )
	(objects (name ?obj) (zone ?zone))
	(robots (name ?actor)(zone ?zone))
  	=> 
	(retract ?f)
	(assert (answer-robot go_to_room 1 ?zone 1))
)

(defrule test-exec-ptrans-same-room
        (declare (salience 200))
        ?f <- (ptrans (actor ?actor)(obj ?actor)(to ?obj) )
        (objects (name ?obj) (zone ?zone))
        (robots (name ?actor)(zone ?zone))
        =>
        (retract ?f)
        (assert (answer-robot go_to_room 1 ?zone 1))
)

(defrule test-exec-ptrans-no-same-room
        (declare (salience 200))
        ?f <- (ptrans (actor ?actor)(obj ?actor)(to ?obj) )
        (objects (name ?obj) (zone ?zone))
        (robots (name ?actor)(zone ?other &:(neq ?other ?zone)))
        =>
        (retract ?f)
        (assert (answer-robot go_to_room 1 ?zone 1))
)




(defrule exec-attend
	;(declare (salience -200))
	?f <- (attend (actor ?actor)(obj ?obj&:( neq ?obj nil) )(to robot)(from human-voice) )
  	=>
	(retract ?f)
	; it finds the representation of the object
	(bind ?message (str-cat "I will do the trainning for the " ?obj))
	(assert (send-speech ?message))
	(bind ?command (str-cat "training " ?obj ))
	(assert (send-vision ?command))
	(assert (get-data-vision))
)


(defrule answer-training
	?f <- (answer-vision training ?obj ?num)
	=>
	(retract ?f)
	
	(if (eq ?num 1) then
		(bind ?message (str-cat "I created the pattern for " ?obj))
	  else
		(bind ?message (str-cat "I could not create the pattern for " ?obj))
	)

	(printout t crlf "Command: " ?message crlf)
	(assert (send-speech ?message))
)




(defrule exec-ptrans-object
	?f <- (ptrans (actor ?actor)(obj ?obj)(to ?place))
	(objects (name ?obj) (zone ?zone))
	(zones ?place ?x ?y)
	(not (robots (name ?actor)(hands ?obj)))
  	=>
	(assert (ptrans (actor ?actor)(obj ?actor)(to ?obj)))
	(assert (ptrans (actor ?actor)(obj ?actor)(to ?place)))
	(assert (grab (actor ?actor)(obj ?obj)))
)


(defrule exec-ptrans-object-hands
	?f <- (ptrans (actor ?actor)(obj ?obj)(to ?place))
	(objects (name ?obj) (zone ?zone))
	(zones ?place ?x ?y)
	(robots (name ?actor)(hands ?obj))
  	=>
	(assert (ptrans (actor ?actor)(obj ?actor)(to ?place)))
)



(defrule arrive-place-object
	?f <- (answer-robot go_to_room 1 ?room ?num)
	(grab (obj ?obj))
	?f2 <- (robots (name ?actor)(zone ?))
	=>
	(retract ?f)
	(modify  ?f2 (zone ?room))
	;searchs and picks an object	
	(bind ?command (str-cat "find_object \"" ?obj "\"")) 
	(assert (send-robot ?command))
	(bind ?message (str-cat "I am looking for " ?obj))
	;(printout t crlf "Command: " ?message crlf)
	(assert (send-speech ?message))
)

(defrule found-pick-obj
	?f <- (answer-robot find_object 1 ?obj ?num)
	?f1 <- (grab (obj ?obj))
	?f2 <- (robots (name ?actor)(hands nil))
	?f3 <- (human (objs $?ini_obj ?obj $?rest_obj))
	=>
	(retract ?f ?f1)
	(modify  ?f2 (hands ?obj))

	
	(bind ?message (str-cat "I grab the " ?obj))
	(assert (send-speech ?message))

	(bind ?message (str-cat "I found the " ?obj))
	(assert (send-speech ?message))

	;(printout t crlf "Command: " ?message crlf)
	;(bind ?pos_obj (member$ ?obj $?objs))
      ;(bind $?newobjs (delete$ $?objs ?pos_obj ?pos_obj ))
	(modify ?f3 (objs $?ini_obj $?rest_obj))

)

(defrule test-found-pick-obj
	(declare (salience 150))
        ;?f <- (answer-robot find_object 1 ?obj ?num)
        ?f1 <- (grab (obj ?obj))
        ?f2 <- (robots (name ?actor)(hands nil))
        ?f3 <- (human (objs $?ini_obj ?obj $?rest_obj))
        =>
        (retract ?f1)
        (modify  ?f2 (hands ?obj))


        (bind ?message (str-cat "I grab the " ?obj))
        (assert (send-speech ?message))

        (bind ?message (str-cat "I found the " ?obj))
        (assert (send-speech ?message))

        ;(printout t crlf "Command: " ?message crlf)
        ;(bind ?pos_obj (member$ ?obj $?objs))
      ;(bind $?newobjs (delete$ $?objs ?pos_obj ?pos_obj ))
        (modify ?f3 (objs $?ini_obj $?rest_obj))

)





(defrule found-pick-obj-nobody
	?f <- (answer-robot find_object 1 ?obj ?num)
	?f1 <- (grab (obj ?obj))
	?f2 <- (robots (name ?actor)(hands nil))
	(not (human (objs $?ini_obj ?obj $?rest_obj)))
	=>
	(retract ?f ?f1)
	(modify  ?f2 (hands ?obj))

	(bind ?message (str-cat "I grab the " ?obj))
	(assert (send-speech ?message))

	(bind ?message (str-cat "I found the " ?obj))
	(assert (send-speech ?message))

	;(printout t crlf "Command: " ?message crlf)
	;(bind ?pos_obj (member$ ?obj $?objs))
      ;(bind $?newobjs (delete$ $?objs ?pos_obj ?pos_obj ))
)

(defrule test-found-pick-obj-nobody
	(declare (salience 150))
        ;?f <- (answer-robot find_object 1 ?obj ?num)
        (not (human (objs $?ini_obj ?obj $?rest_obj)))
        ?f1 <- (grab (obj ?obj))
        ?f2 <- (robots (name ?actor)(hands nil)(zone ?zone))
	(objects (name ?obj) (zone ?zone))
        =>
        (retract ?f1)
        (modify  ?f2 (hands ?obj))

        (bind ?message (str-cat "I grab the " ?obj))
        (assert (send-speech ?message))

        (bind ?message (str-cat "I found the " ?obj))
        (assert (send-speech ?message))

        ;(printout t crlf "Command: " ?message crlf)
        ;(bind ?pos_obj (member$ ?obj $?objs))
      ;(bind $?newobjs (delete$ $?objs ?pos_obj ?pos_obj ))
)





(defrule go-person-atrans
	(atrans (actor ?actor)(obj ?obj)(to ?person))
	?f <- (ptrans (actor ?actor)(obj ?actor)(to ?person))
	(robots (name ?actor)(hands ?obj))
	(human (name ?person) (zone ?zone))
	=>
	(retract ?f)
	; it sends the robot to the asqued zone
	(bind ?command (str-cat "go_to_room \"" ?zone "\""))
	(assert (send-robot ?command))
	(bind ?message (str-cat "I am going to " ?zone))
	(assert (send-speech ?message))
	;(printout t crlf "Command: " ?message crlf)

)

(defrule test-go-person-atrans
	(declare (salience 10))
        (atrans (actor ?actor)(obj ?obj)(to ?person))
        ;?f <- (ptrans (actor ?actor)(obj ?obj &:(neq ?actor ?obj))(to ?person))
	?f <- (ptrans (actor ?actor)(obj ?actor)(to ?person))
        (robots (name ?actor)(hands ?obj))
        (human (name ?person) (zone ?zone))
        =>
        (retract ?f)
        ; it sends the robot to the asqued zone
        (bind ?command (str-cat "go_to_room \"" ?zone "\""))
        (assert (send-robot ?command))
        (bind ?message (str-cat "I am going to " ?zone))
        (assert (send-speech ?message))
        ;(printout t crlf "Command: " ?message crlf)
	(assert (ptrans (actor ?actor)(obj ?actor)(to ?zone)))
)




(defrule go-person
	?f <- (ptrans (actor ?actor)(obj ?actor)(to ?person))
	(human (name ?person) (zone ?zone))
	(not (atrans ))
	=>
	(retract ?f)
	; it sends the robot to the asqued zone
	(bind ?command (str-cat "go_to_room \"" ?zone "\""))
	(assert (send-robot ?command))
	(bind ?message (str-cat "I am going to " ?zone))
	(assert (send-speech ?message))
	;(printout t crlf "Command: " ?message crlf)

)


;(defrule test-go-person
	;(declare (salience 160))
        ;?f <- (ptrans (actor ?actor)(obj ?actor)(to ?person))
        ;(human (name ?person) (zone ?zone))
        ;;(not (atrans ))
        ;=>
        ;(retract ?f)
        ;; it sends the robot to the asqued zone
        ;(bind ?command (str-cat "go_to_room \"" ?zone "\""))
        ;(assert (send-robot ?command))
        ;(bind ?message (str-cat "I am going to " ?zone))
        ;(assert (send-speech ?message))
        ;;(printout t crlf "Command: " ?message crlf)

;)



(defrule go-zone-not-same-zone
	?f <- (ptrans (actor ?actor)(obj ?actor)(to ?zone))
	(robots (name ?actor)(zone ?zone1&:(neq ?zone ?zone1)))
	(zones ?zone ?x ?y)
	=>
	(retract ?f)
	; it sends the robot to the asqued zone
	(bind ?command (str-cat "go_to_room \"" ?zone "\""))
	(assert (send-robot ?command))
	(bind ?message (str-cat "I am going to " ?zone))
	(assert (send-speech ?message))
	;(printout t crlf "Command: " ?message crlf)
)

(defrule test-go-zone-not-same-zone
	(declare (salience 100))
        ?f <- (ptrans (actor ?actor)(obj ?actor)(to ?zone))
        (robots (name ?actor)(zone ?zone1&:(neq ?zone ?zone1)))
        (zones ?zone ?x ?y)
        =>
        (retract ?f)
        ; it sends the robot to the asqued zone
        (bind ?command (str-cat "go_to_room \"" ?zone "\""))
        (assert (send-robot ?command))
        (bind ?message (str-cat "I am going to " ?zone))
        (assert (send-speech ?message))
        ;(printout t crlf "Command: " ?message crlf)
	 (assert (answer-robot go_to_room 1 ?zone 1))
)


(defrule go-zone-same-zone
	?f <- (ptrans (actor ?actor)(obj ?actor)(to ?zone))
	(robots (name ?actor)(zone ?zone))
	=>
	(retract ?f)
	(assert (answer-robot go_to_room 1 ?zone 1))
	; it sends the robot to the asqued zone
	(bind ?message (str-cat "I am already in the " ?zone))
	(assert (send-speech ?message))
	;(printout t crlf "Command: " ?message crlf)
)

(defrule test-go-zone-same-zone
        ?f <- (ptrans (actor ?actor)(obj ?actor)(to ?zone))
        (robots (name ?actor)(zone ?))
        =>
        (retract ?f)
        (assert (answer-robot go_to_room 1 ?zone 1))
        ; it sends the robot to the asqued zone
        (bind ?message (str-cat "I am already in the " ?zone))
        (assert (send-speech ?message))
        ;(printout t crlf "Command: " ?message crlf)
)


(defrule arrive-place
	?f <- (answer-robot go_to_room 1 ?room ?num)
	(not (atrans (actor ?actor)(obj ?obj)(to ?person)))
	?f2 <- (robots (name ?actor)(zone ?))
	=>
	(retract ?f)
	(modify  ?f2 (zone ?room))
	(bind ?message (str-cat "I arrive to the " ?room))
	(assert (send-speech ?message))
	;(printout t crlf "Command: " ?message crlf)
)

(defrule test-arrive-place
	(declare (salience 165))
        ?f <- (answer-robot go_to_room 1 ?room ?num)
        (not (atrans (actor ?actor)(obj ?obj)(to ?person)))
        ?f2 <- (robots (name ?actor)(zone ?))
        =>
        (retract ?f)
        (modify  ?f2 (zone ?room))
        (bind ?message (str-cat "I arrive to the " ?room))
        (assert (send-speech ?message))
       ;(printout t crlf "Command: " ?message crlf)
)




(defrule did-not-arrive-place
	(declare (salience 200))
	?f <- (answer-robot go_to_room 0 ?room ?num)
	=>
	(retract ?f)

	(bind ?command (str-cat "get_room \"" ?room"\""))
	(assert (send-robot ?command))
	(printout t crlf "send robot: " ?command crlf)

	(bind ?message (str-cat "I did not arrive to the " ?room))
	(assert (send-speech ?message))
	;(printout t crlf "Command: " ?message crlf)
)


(defrule get-room
	?f <- (answer-robot get_room 1 ?room ?num)
	?f2 <- (robots (name ?actor)(zone ?))
	=>
	(retract ?f)
	(modify  ?f2 (zone ?room))
	(bind ?message (str-cat "I am in the " ?room))
	(assert (send-speech ?message))
	;(printout t crlf "Command: " ?message crlf)
)



(defrule arrive-place-person
	?f <- (answer-robot go_to_room 1 ?room ?num)
	(atrans (actor ?actor)(obj ?obj)(to ?person))
	?f2 <- (robots (name ?actor)(zone ?))
	=>
	(retract ?f)
	(modify  ?f2 (zone ?room))
	; it search for the person and releases the object
	
	(bind ?message (str-cat "I am looking for the " ?person))
	(assert (send-speech ?message))

	(bind ?command (str-cat "find_human \"" ?person"\""))
	(assert (send-robot ?command))

	;(printout t crlf "Command: " ?message crlf)
)


(defrule deliver-obj
	?f <- (answer-robot find_human 1 ?hum ?num)
	?f1 <- (robots (name ?actor)(hands ?obj))
	?f2 <- (human (name ?person)(objs $?objects)(zone ?room))
	?f3 <- (atrans (actor ?actor)(obj ?obj)(to ?person))
	?f4 <- (objects (name ?obj))
	=> 
	(retract ?f ?f3)
	(modify ?f1 (hands nil))
	(modify ?f2 (objs ?obj $?objects ))
	(modify ?f4 (zone ?room))
	(bind ?command (str-cat "release \"" ?obj "\""))
	(assert (send-robot ?command))

	
	(bind ?message (str-cat "I deliver the " ?obj " to the " ?person))
	(assert (send-speech ?message))

	(bind ?message (str-cat "I found the " ?person))
	(assert (send-speech ?message))


	;(printout t crlf "Command: " ?message crlf)
)




(defrule test-deliver-obj
	(declare (salience 100))
        ;?f <- (answer-robot find_human 1 ?hum ?num)
        ?f1 <- (robots (name ?actor)(hands ?obj)(zone ?room))
        ?f2 <- (human (name ?person)(objs $?objects)(zone ?room))
        ?f3 <- (atrans (actor ?actor)(obj ?obj)(to ?person))
        ?f4 <- (objects (name ?obj))
        =>
        (retract ?f3)
        (modify ?f1 (hands nil))
        (modify ?f2 (objs ?obj $?objects ))
        (modify ?f4 (zone ?room))
        (bind ?command (str-cat "release \"" ?obj "\""))
        (assert (send-robot ?command))


        (bind ?message (str-cat "I deliver the " ?obj " to the " ?person))
        (assert (send-speech ?message))

        (bind ?message (str-cat "I found the " ?person))
        (assert (send-speech ?message))


        ;(printout t crlf "Command: " ?message crlf)
)



(defrule deliver-obj-ptrans
	(declare (salience 100))
	?f <- (answer-robot go_to_room 1 ?room ?num)
	?f1 <- (robots (name ?actor)(hands ?obj))
	?f3 <- (ptrans (actor ?actor)(obj ?obj)(to ?room))
	?f4 <- (objects (name ?obj))
	=>
	(modify  ?f1  (hands nil) (zone ?room))
	(retract ?f3 ?f)	
	(modify ?f4 (zone ?room))
	(bind ?command (str-cat "release \"" ?obj "\""))
	(assert (send-robot ?command))
	(bind ?message (str-cat "I deliver the " ?obj " to " ?room))
	(assert (send-speech ?message))
	;(printout t crlf "Command: " ?message crlf)
	(bind ?message (str-cat "I arrive to the room"))
	(assert (send-speech ?message))
	;(printout t crlf "Command: " ?message crlf)
)


(defrule answer-where-obj-qtrans
	(declare (salience 100))
	?f <- (qtrans (actor ?actor)(question where)(aux-verb is)
		    (verb nil)(human nil)(obj ?obj)(answer nil))
	(objects (name ?obj) (zone ?zone))
	?f1 <- (present-place ?place)
  	=>
	(retract ?f1)
	(modify ?f (answer ?zone))
	(assert (present-place ?zone))
)



(defrule answer-where-human-qtrans
	(declare (salience 100))
	?f <- (qtrans (actor ?actor)(question where)(aux-verb is)
		    (verb nil)(human ?human)(obj nil)(answer nil))
	 (human (name ?human)(zone ?loc-human))
	?f1 <- (present-place ?place)
  	=>
	(retract ?f1)
	(modify ?f (answer ?loc-human))
	(assert (present-place ?loc-human))
)

(defrule answer-where-robot-qtrans
	(declare (salience 100))
	?f <- (qtrans (actor ?actor)(question where)(aux-verb are)
		    (verb nil)(human you)(obj nil)(answer nil))	
	(robots (name ?actor) (zone ?zone))
  	=>
	(modify ?f (answer ?zone))
)



(defrule speek-answer-qtrans-where
	?f <- (qtrans (actor ?actor)(question where)(aux-verb ?aux)
		    (verb ?nil)(human ?human)(obj ?obj)(answer ?zone&:(neq ?zone nil)) )
  	=>
	(retract ?f )
	
	(if (neq ?human nil) then 
		(bind ?item ?human)
	  else
		(bind ?item ?obj)
	)
	(if (eq ?item you) then
		(bind ?message (str-cat "I am in the " ?zone) )
	 else
		(bind ?message (str-cat "The " ?item " " ?aux " in the " ?zone) )
	)

	(assert (send-speech ?message))
)


