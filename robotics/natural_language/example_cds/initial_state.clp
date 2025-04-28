

;******************************************************
;*									*
;*	Initial Facts						*
;*									*
;******************************************************

(deffacts Initial-state

; Zones definition

	(zones livingroom 60 15)
	(zones kitchen 15 50)
	;(zones bathroom 15 40)
	(zones bedroom 50 55)
	;(zones deck 15 65)
	;(zones middle 38 38)
	(zones diningroom 20 10)
	;(zones garden 50 10)
	(zones maindoor 50 10)
	;(zones table 15 58)
	;(zones chair 10 59)
	;(zones bed 55 50)
	;(zones stove 10 20)
	;(zones fridge 40 20)
	;(zones cupboard 5 15)
	;(zones tv 75 60)
	;(zones sofa 52 40)
	;(zones bookshelf 30 60)
	;(zones lamp 52 70)
	;(zones plant 50 20)
	(zones corridor 38 30)
	
	(present-place nil)
	(prev-time 0)




; Actors definition
	(robots-hands nil)
	(human (name Father)(zone livingroom))
	(human (name Mother)(zone diningroom))
	(robots (name robot)(zone bedroom))
	(present-actor robot)
	(present-recepient Mother)

; Objects definition
	(objects (name newspaper)(zone maindoor)(attributes entertainment information))
	(objects (name milk)(zone kitchen )(attributes veberage))
	(objects (name book)(zone bedroom )(attributes entertainment information))
	;(objects (name box 1)(zone kitchen)(attributes work))
	;(objects (name box 6)(zone bathroom)(attributes work))
	(present-object nil)

; Network definition
	(open-network ROBOT)
	(open-network SPEECH-GENERATION)
	(open-network SPEECH-RECOGNITION)
	(open-network IMAGE-RECOGNITION)
	;(open-network SPEECH-RECOGNITION-ERRORS)
	(open-network FACE)

; Vision definitions
	;(use vision)	
	
)


(deffacts init-skts-robot
	(robot_address "localhost")
	;(robot_address "192.168.2.2")
	(robot_port_out 2001)
	(robot_port_in  2006)

)

(deffacts init-skts-speech-generation
	;(speech_generation-address "192.168.2.3" )
	(speech_generation-address "localhost" )
	(speech_generation_port_out 2666)
	;(speech_generation_port_in  2002)
)

(deffacts init-skts-speech-recognition
	(speech_recognition-address "localhost" )
	(speech_recognition_port_in  2010)
	;(speech_recognition_errors_port_in  2020)
	
	;(speech_recognition_port_out  2030)
)

(deffacts init-skts-image-recognition
	(image_recognition-address "localhost" )
	(image_recognition_port_in  2080)
	(image_recognition_port_out  2070)

)



(deffacts init-skts-face
	(face-address "localhost" )
	;(face_port_in  2030)
	(face_port_out  2040)
)


