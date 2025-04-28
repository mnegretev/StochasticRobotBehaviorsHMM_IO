
;******************************************************
;*									*
;*	Deftemplates definitions				*
;*									*
;*			J.Savage, UNAM				*
;*			4/18/05					*
;*			4/22/07					*
;*									*
;******************************************************

(deftemplate atrans
	(field actor
		 (type SYMBOL)
		 (default nil)
	)
	(field obj
		 (type SYMBOL)
		 (default nil)
	)
	(field from
		 (type SYMBOL)
		 (default nil)
	)
 	(field to
		 (type SYMBOL)
		 (default nil)
	)
)

(deftemplate ptrans
	(field actor
		 (type SYMBOL)
		 (default nil)
	)
	(field obj
		 (type SYMBOL)
		 (default nil)
	)
	(field from
		 (type SYMBOL)
		 (default nil)
	)
 	(field to
		 (type SYMBOL)
		 (default nil)
	)
)


(deftemplate mtrans
	(field actor
		 (type SYMBOL)
		 (default nil)
	)
	(field obj
		 (type SYMBOL)
		 (default nil)
	)
	(field from
		 (type SYMBOL)
		 (default nil)
	)
 	(field to
		 (type SYMBOL)
		 (default nil)
	)
)

(deftemplate attend
	(field actor
		 (type SYMBOL)
		 (default nil)
	)
	(field obj
		 (type SYMBOL)
		 (default nil)
	)
	(field from
		 (type SYMBOL)
		 (default nil)
	)
 	(field to
		 (type SYMBOL)
		 (default nil)
	)
)




(deftemplate grab
	(field actor
		 (type SYMBOL)
		 (default nil)
	)
	(field obj
		 (type SYMBOL)
		 (default nil)
	)
	(field from
		 (type SYMBOL)
		 (default nil)
	)
 	(field to
		 (type SYMBOL)
		 (default nil)
	)
)

(deftemplate human
	(field name
		 (type SYMBOL)
		 (default nil)
	)
	(multifield objs
		 (type SYMBOL)
	)
	(field zone
		 (type SYMBOL)
	)
 )


(deftemplate robots
	(field name
		 (type SYMBOL)
		 (default nil)
	)
	(field hands
		 (type SYMBOL)
		 (default nil)
	)
	(field zone
		 (type SYMBOL)
	)
 )


(deftemplate objects
	(field name
		 (type SYMBOL)
		 (default nil)
	)
	(multifield attributes
		 (type SYMBOL)
	)
	(field zone
		 (type SYMBOL)
	)
 )



(deftemplate qtrans
	(field actor
		 (type SYMBOL)
		 (default nil)
	)
	(field question
		 (type SYMBOL)
		 (default nil)
	)
 	(field aux-verb
		 (type SYMBOL)
		 (default nil)
	)
	(field verb
		 (type SYMBOL)
		 (default nil)
	)
	(field human
		 (type SYMBOL)
		 (default nil)
	)
	(field obj
		 (type SYMBOL)
		 (default nil)
	)
	(field answer
		 (type SYMBOL)
		 (default nil)
	)
)


