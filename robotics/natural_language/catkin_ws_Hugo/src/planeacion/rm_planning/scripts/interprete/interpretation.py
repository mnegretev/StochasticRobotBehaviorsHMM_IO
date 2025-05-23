# code dependencies
import kb_services
import parsing
# network toolkit
import networkx as nx
# regular expressions 
import re


def diff(a, b):
    b = set(b)
    return [aa for aa in a if aa not in b]

def intersection(a,b):
	if isinstance(a, str):
		if " " in a:
			a = a.split(" ")
		else:
			a = [a]
	a = set(a)
	return [bb for bb in b if bb in a]
# 
meaning_mapping_patterns = [


		# patrones para TMR 2017
	############################################# GetNDeliver

	# param: [["palabras", "clave"], ["noun", "vrb", "prep_phrase"], ["categoria", "item", "place", "person"], []]
		# take from and deliver to person
	#{"params": ["Action_get", "Get_object", "Source_get", "Action_deliver", "Destination_person", "Destination_location"],
	#"Action_get": [["get", "grasp", "take"], ["vrb"], [], []],
	#"Get_object": [[], ["noun"], ["item"], []],
	#"Source_get": [[], ["noun"], ["place"], []],
	#"Action_deliver": [["bring", "carry", "deliver", "take"], ["vrb"], [], []],
	#"Destination_person": [[], ["noun", "prep_phrase"], ["person"], []],
	#"Destination_location": [[], ["noun"], ["place"], []],
	#"conceptual_dependency": "(task (plan user_speech) (action_type update_object_location) (params -Get_object- -Source_get- ) (step 1)) " +
	#						"(task (plan user_speech) (action_type get_object) (params -Get_object- -Source_get-) (step 2)) " + 
	#						"(task (plan user_speech) (action_type find_person_in_room) (params -Destination_person- -Destination_location-) (step 3))" + 
	#						"(task (plan user_speech) (action_type handover_object) (params -Get_object-) (step 4))",
	#"verbal_confirmation": '',
	#"planner_confirmed": '',
	#"planner_not_confirmed": ''},


	#navigate
	{"params": ["Action_nav", "Location"],
	"Action_nav": [["navigate", "go", "locate"], [], [], []],
	"Location": [[], [], ["place"], []],
	"conceptual_dependency": "(task (plan user_speech) (action_type ptrans) (params location -Location-) (step ))",
	"verbal_confirmation": '',
	"planner_confirmed": '',
	"planner_not_confirmed": ''},

	#question
	{"params": ["Action_talk", "Question"],
	"Action_talk": [["speak", "answer", "tell", "say"], [], [], []],
	"Question": [[], [], ["question"], []],
	"conceptual_dependency": "(task (plan user_speech) (action_type attend) (params question -Question-) (step ))",
	"verbal_confirmation": '',
	"planner_confirmed": '',
	"planner_not_confirmed": ''},
	
	#find person 1 parametro
	{"params": ["Action_find","Find_person"],
	"Action_find": [["find", "look_for", "locate"], [], [], []],
	"Find_person": [[], [], ["person"], []],
	"conceptual_dependency": "(task (plan user_speech) (action_type mtrans) (params -Find_person-) (step ))",
	"verbal_confirmation": '',
	"planner_confirmed": '',
	"planner_not_confirmed": ''},

	#find person 2 parametros
	{"params": ["Find_person", "Person", "Person_location"],
	"Find_person": [["find", "locate", "look_for"], [], [], []],
	"Person": [[], [], ["person"], []],
	"Person_location": [[], [], ["place"], []],
	"conceptual_dependency": "(task (plan user_speech) (action_type mtrans) (params -Person- -Person_location-) (step ))",
	"verbal_confirmation": '',
	"planner_confirmed": '',
	"planner_not_confirmed": ''},

	# deliver to me
	{"params": ["Action_deliver", "Person"],
	"Action_deliver": [["give", "bring", "deliver", "hand"], [], [], []],
	"Person": [["me"], [], [], []],
	"conceptual_dependency":"(task (plan user_speech) (action_type ptrans) (params location current_loc) (step ))" +
							"(task (plan user_speech) (action_type atrans) (params ) (step ))",
	"verbal_confirmation": '',
	"planner_confirmed": '',
	"planner_not_confirmed": ''},
	
	# deliver to person
	{"params": ["Action_deliver", "Person"],
	"Action_deliver": [["give", "bring", "deliver", "hand"], [], [], []],
	"Person": [[], [], ["person"], []],
	"conceptual_dependency":"(task (plan user_speech) (action_type mtrans) (params -Person-) (step ))" +
							"(task (plan user_speech) (action_type atrans) (params ) (step ))",
	"verbal_confirmation": '',
	"planner_confirmed": '',
	"planner_not_confirmed": ''},

	# deliver to person 2 parametros
	{"params": ["Action_deliver", "Person", "Location"],
	"Action_deliver": [["give", "bring", "deliver", "hand"], [], [], []],
	"Person": [[], [], ["person"], []],
	"Location": [[], [], ["place"], []],
	"conceptual_dependency":"(task (plan user_speech) (action_type mtrans) (params -Person- -Location-) (step ))" +
							"(task (plan user_speech) (action_type atrans) (params ) (step ))",
	"verbal_confirmation": '',
	"planner_confirmed": '',
	"planner_not_confirmed": ''},

	#grasp object 2 parametros
	{"params": ["Action_get", "Get_object", "Source_get"],
	"Action_get": [["get", "grasp", "take"], [], [], []],
	"Get_object": [[], [], ["item"], []],
	"Source_get": [[], [], ["place"], []],
	"conceptual_dependency": "(task (plan user_speech) (action_type grasp) (params -Get_object- -Source_get-) (step )) ", 
	"verbal_confirmation": '',
	"planner_confirmed": '',
	"planner_not_confirmed": ''},

	#grasp object 1 parametro
	{"params": ["Action_get", "Get_object"],
	"Action_get": [["get", "grasp", "take", "look for"], [], [], []],
	"Get_object": [[], [], ["item"], []],
	"conceptual_dependency": "(task (plan user_speech) (action_type grasp) (params -Get_object-) (step )) ", 
	"verbal_confirmation": '',
	"planner_confirmed": '',
	"planner_not_confirmed": ''},

	#deliver in place
	{"params": ["Action_place", "Destination_place"],
	"Action_place": [["place", "deliver", "put"], [], [], []],
	"Destination_place": [[], [], ["place"], []],
	"conceptual_dependency": "(task (plan user_speech) (action_type atrans) (params -Destination_place-) (step ))",
	"verbal_confirmation": '',
	"planner_confirmed": '',
	"planner_not_confirmed": ''},

	#####################NAGOYA 2017
	##########################
	####################### MANIPULATION

	#$take to the {placement 2}
	{"params": ["Action_take", "Object", "To", "Place"],
	"Action_take": [[ "get" , "grasp" , "take" , "pick up"], [], [], []],
	"Object": [[], [], ["item"], []],
	"To": [["to"], [], [], []],
	"Place": [[], [], ["place"], []],
	"conceptual_dependency": "(task (plan user_speech) (action_type grasp) (params -Object- default) (step )) " +
				"(task (plan user_speech) (action_type atrans) (params -Place-) (step ))",
	"verbal_confirmation": '',
	"planner_confirmed": '',
	"planner_not_confirmed": ''},

	#$vbplace the $object on the {placement 2}
	{"params": ["Action_take", "Object", "Place"],
	"Action_take": [["put", "place"], [], [], []],
	"Object": [[], [], ["item"], []],
	"Place": [[], [], ["place"], []],
	"conceptual_dependency": "(task (plan user_speech) (action_type grasp) (params -Object- default) (step )) " +
				"(task (plan user_speech) (action_type atrans) (params -Place-) (step ))",
	"verbal_confirmation": '',
	"planner_confirmed": '',
	"planner_not_confirmed": ''},

	#$deliver  = $vbbring me the $object
	{"params": ["Action_take", "Person", "Object"],
	"Action_take": [["bring", "give", "deliver"], [], [], []],
	"Person": [["me"], [], [], []],
	"Object": [[], [], ["item"], []],
	"conceptual_dependency": "(task (plan user_speech) (action_type grasp) (params -Object- default) (step )) " +
				"(task (plan user_speech) (action_type ptrans) (params location current_loc) (step ))" +
				"(task (plan user_speech) (action_type atrans) (params ) (step ))",
	"verbal_confirmation": '',
	"planner_confirmed": '',
	"planner_not_confirmed": ''},

	#$vbdeliver the $object to $someone
	{"params": ["Action_take", "Object", "Person", "Location"],
	"Action_take": [["bring", "give", "deliver"], [], [], []],
	"Object": [[], [], ["item"], []],
	"Person": [[], [], ["person"], []],
	"Location": [[], [], ["place"], []],
	"conceptual_dependency": "(task (plan user_speech) (action_type grasp) (params -Object- default) (step )) " +
				"(task (plan user_speech) (action_type mtrans) (params -Person- -Location-) (step ))" +
				"(task (plan user_speech) (action_type atrans) (params ) (step ))",
	"verbal_confirmation": '',
	"planner_confirmed": '',
	"planner_not_confirmed": ''},

	#$takefrom to the {placement 2}
	{"params": ["Action_take", "Object","Place_first","To", "Place_second"],
	"Action_take": [["get" , "grasp" , "take" , "pick up"], [], [], []],
	"Object": [[], [], ["item"], []],
	"Place_first": [[], [], ["place"], []],
	"To": [["to"], [], [], []],
	"Place_second": [[], [], ["place"], []],
	"conceptual_dependency": "(task (plan user_speech) (action_type grasp) (params -Object- -Place_first-) (step )) " +
				"(task (plan user_speech) (action_type atrans) (params -Place_second-) (step ))",
	"verbal_confirmation": '',
	"planner_confirmed": '',
	"planner_not_confirmed": ''},
	
	#$goplace, $vbfind the $object, and ($delivme | $delivat)
	#$goplace, $vbfind the $object, and $place

	#$vbfind the $object 1 parametro
	{"params": ["Action_get", "Get_object"],
	"Action_get": [["find", "look_for", "locate"], [], [], []],
	"Get_object": [[], [], ["item"], []],
	"conceptual_dependency": "(task (plan user_speech) (action_type grasp) (params -Get_object-) (step )) ", 
	"verbal_confirmation": '',
	"planner_confirmed": '',
	"planner_not_confirmed": ''},

	#$vbbring (me | to $whowhere) the {kobject} from the {placement}
	{"params": ["Action_take", "Person", "Place_first", "Object", "Place_second"],
	"Action_take": [["bring" , "give"], [], [], []],
	"Person": [[], [], ["person"], []],
	"Place_first": [[], [], ["place"], []],
	"Object": [[], [], ["item"], []],
	"Place_second": [[], [], ["place"], []],
	"conceptual_dependency": "(task (plan user_speech) (action_type grasp) (params -Object- -Place_second-) (step )) " +
				"(task (plan user_speech) (action_type mtrans) (params -Person- -Place_first-) (step ))" +
				"(task (plan user_speech) (action_type atrans) (params ) (step ))",
	"verbal_confirmation": '',
	"planner_confirmed": '',
	"planner_not_confirmed": ''},

	{"params": ["Action_take", "Person", "Object", "Place_second"],
	"Action_take": [["bring" , "give"], [], [], []],
	"Person": [["me"], [], [], []],
	"Object": [[], [], ["item"], []],
	"Place_second": [[], [], ["place"], []],
	"conceptual_dependency": "(task (plan user_speech) (action_type grasp) (params -Object- -Place_second-) (step )) " +
				"(task (plan user_speech) (action_type ptrans) (params location current_loc) (step ))" +
				"(task (plan user_speech) (action_type atrans) (params ) (step ))",
	"verbal_confirmation": '',
	"planner_confirmed": '',
	"planner_not_confirmed": ''},

	###### FIND PEOPLE

	#$talk to $whowhere    $findp in the {room} and $talk
	{"params": ["Action_talk", "Question", "Person", "Location"],
	"Action_talk": [["speak", "answer", "tell", "say"], [], [], []],
	"Question": [[], [], ["question"], []],
	"Person": [[], [], ["person"], []],
	"Location":[[], [], ["place"], []],
	"conceptual_dependency":"(task (plan user_speech) (action_type mtrans) (params -Person- -Location-) (step ))" + 
				"(task (plan user_speech) (action_type attend) (params question -Question-) (step ))",
	"verbal_confirmation": '',
	"planner_confirmed": '',
	"planner_not_confirmed": ''},

	#Tell me the name of the person at the {beacon}  Tell me the name of the person in the {room}
	{"params": ["Action_talk","Me", "Name", "Location"],
	"Action_talk": [["tell"], [], [], []],
	"Me": [["me"], [], [], []],
	"Name":[["name"], [], [], []],
	"Location":[[], [], ["place"], []],
	"conceptual_dependency":"(task (plan user_speech) (action_type mtrans) (params person -Location-) (step ))" + 
				"(task (plan user_speech) (action_type attend) (params question ask_name) (step ))" +
				"(task (plan user_speech) (action_type ptrans) (params location current_loc) (step ))" +
				"(task (plan user_speech) (action_type attend) (params question tell_name) (step ))",
	"verbal_confirmation": '',
	"planner_confirmed": '',
	"planner_not_confirmed": ''},

	#$findp in the {room}
	{"params": ["Action_get", "Person", "Location"],
	"Action_get": [["find", "look_for", "locate"], [], [], []],
	"Person": [["person", "someone"], [], [], []],
	"Location":[[], [], ["place"], []],
	"conceptual_dependency":"(task (plan user_speech) (action_type mtrans) (params person -Location-) (step ))",
	"verbal_confirmation": '',
	"planner_confirmed": '',
	"planner_not_confirmed": ''},

	#### FIND OBJECTS
	#$fndobj   = $vbfind the {kobject?} in the {room}
	{"params": ["Action_get", "Object", "Location"],
	"Action_get": [["find", "look_for", "locate"], [], [], []],
	"Object": [[], [], ["item"], []],
	"Location":[[], [], ["place"], []],
	"conceptual_dependency":"(task (plan user_speech) (action_type ptrans) (params location -Location-) (step ))"+
				"(task (plan user_speech) (action_type mtrans) (params -Object- -Location-) (step ))",
	"verbal_confirmation": '',	
	"planner_confirmed": '',
	"planner_not_confirmed": ''},
	
	#$fndobj   = Tell me how many $object there are on the {placement}
	{"params": ["Action_talk", "Person", "Many", "Object", "Location_second"],
	"Action_talk": [["tell"], [], [], []],
	"Person":[["me"],[],[],[]],
	"Many":[["many"],[],[],[]],
	"Object": [[], [], ["item"], []],
	"Location_second":[[],[],["place"],[]],
	"conceptual_dependency":"(task (plan user_speech) (action_type mtrans) (params -Object- -Location_second-) (step ))" +
				"(task (plan user_speech) (action_type ptrans) (params location current_loc) (step ))" +
				"(task (plan user_speech) (action_type attend) (params question tell_many_obj) (step ))",
	"verbal_confirmation": '',
	"planner_confirmed": '',
	"planner_not_confirmed": ''},

	######### NAGOYA 2017 CATEGORY 2

	#$vbdeliver the $object to $someone
	{"params": ["Action_take", "Object", "Gesture", "Location"],
	"Action_take": [["bring", "give", "deliver"], [], [], []],
	"Object": [[], [], ["item"], []],
	"Gesture":[["waving", "rising_left_arm", "rising_right_arm", "pointing_left", "pointing_right"],[],[],[]],
	"Location": [[], [], ["place"], []],
	"conceptual_dependency": "(task (plan user_speech) (action_type grasp) (params -Object- default_location) (step )) " +
				"(task (plan user_speech) (action_type ptrans) (params location -Location-) (step ))" +
				"(task (plan user_speech) (action_type mtrans) (params -Gesture-) (step ))" +
				"(task (plan user_speech) (action_type atrans) (params ) (step ))",
	"verbal_confirmation": '',
	"planner_confirmed": '',
	"planner_not_confirmed": ''},

	###### FIND PEOPLE

	#$fndppl   = $talk to $whowhere
	{"params": ["Action_talk", "Question", "Gesture", "Location"],
	"Action_talk": [["speak", "answer", "tell", "say"], [], [], []],
	"Question": [[], [], ["question"], []],
	"Gesture":[[],[],["gesture"],[]],
	"Location":[[], [], ["place"], []],
	"conceptual_dependency":"(task (plan user_speech) (action_type ptrans) (params location -Location-) (step ))" +
				"(task (plan user_speech) (action_type mtrans) (params -Gesture- -Location-) (step ))" + 
				"(task (plan user_speech) (action_type attend) (params question -Question-) (step ))",
	"verbal_confirmation": '',
	"planner_confirmed": '',
	"planner_not_confirmed": ''},
	
	#$findp = $vbfind a ($pgenders | $pgesture | $ppose) person
	{"params": ["Action_find", "PGG"],
	"Action_find": [["find", "locate", "look_for"], [], [], []],
	"PGG":[[],[],["gprsn", "posprs", "gesture"],[]],
	"conceptual_dependency":"(task (plan user_speech) (action_type mtrans) (params -PGG- place_loc) (step ))", 
	"verbal_confirmation": '',
	"planner_confirmed": '',
	"planner_not_confirmed": ''},
	
	#$findppl = $findp in the {room}
	{"params": ["Action_find", "PGG", "Location"],
	"Action_find": [["find", "locate", "look_for"], [], [], []],
	"PGG":[[],[],["gprsn", "posprs", "gesture"],[]],
	"Location":[[],[],["place"],[]],
	"conceptual_dependency":"(task (plan user_speech) (action_type ptrans) (params location -Location-) (step ))" +
				"(task (plan user_speech) (action_type mtrans) (params -PGG- -Location-) (step ))", 
	"verbal_confirmation": '',
	"planner_confirmed": '',
	"planner_not_confirmed": ''},

	
	#$fndppl   = Tell me the ( gender | pose) of the person at the {beacon}
	#$fndppl   = Tell me the ( gender | pose) of the person in the {room}
	{"params": ["Action_talk","Me", "Genderpose", "Location"],
	"Action_talk": [["tell"], [], [], []],
	"Me": [["me"], [], [], []],
	"Genderpose":[["gender", "pose"], [], [], []],
	"Location":[[], [], ["place"], []],
	"conceptual_dependency":"(task (plan user_speech) (action_type ptrans) (params location -Location-) (step ))" +
				"(task (plan user_speech) (action_type mtrans) (params -Genderpose- -Location-) (step ))" + 
				"(task (plan user_speech) (action_type ptrans) (params location current_loc) (step ))" +
				"(task (plan user_speech) (action_type attend) (params question tell_gender_pose) (step ))",
	"verbal_confirmation": '',
	"planner_confirmed": '',
	"planner_not_confirmed": ''},

	#$fndppl   = tell me how many people in the {room} are ($pgenderp | $pose)  
	{"params": ["Action_talk", "Person", "How", "Many", "People", "Location", "Pgender"],
	"Action_talk": [["tell"], [], [], []],
	"Person": [["me"],[],[],[]],
	"How": [["how"],[],[],[]],
	"Many": [["meany"],[],[],[]],
	"People": [["people"],[],[],[]],
	"Location":[[], [], ["place"], []],
	"Pgender":[["men", "women", "boys", "girls", "male", "famale", "sitting", "standing", "lying"], [], [], []],
	"conceptual_dependency":"(task (plan user_speech) (action_type mtrans) (params -Pgender- -Location-) (step ))" +
				"(task (plan user_speech) (action_type ptrans) (params location current_loc) (step ))" +
				"(task (plan user_speech) (action_type attend) (params question tell_how_many_people) (step ))",
	"verbal_confirmation": '',
	"planner_confirmed": '',
	"planner_not_confirmed": ''},
	

	#Tell me how many {category} there are on the {placement}
	{"params": ["Action_talk", "Person", "Many", "Category", "Location_second"],
	"Action_talk": [["tell"], [], [], []],
	"Person":[["me"],[],[],[]],
	"Many":[["many"],[],[],[]],
	"Category": [["snacks", "candies", "food", "drinks", "toiletries", "containers"], [], [], []],
	"Location_second":[[], [], ["place"], []],
	"conceptual_dependency":"(task (plan user_speech) (action_type mtrans) (params -Category- -Location_second-) (step ))" +
				"(task (plan user_speech) (action_type ptrans) (params location current_loc) (step ))" +
				"(task (plan user_speech) (action_type attend) (params question tell_many_obj) (step ))",
	"verbal_confirmation": '',
	"planner_confirmed": '',
	"planner_not_confirmed": ''},

	#$fndobj   = Tell me what's the $oprop object on the {placement}
	{"params": ["Action_talk", "Person", "Property", "Location"],
	"Action_talk": [["tell"], [], [], []],
	"Person": [["me"], [], [], []],
	"Property": [["biggest", "smallest", "heaviest", "lightest", "largest", "thinnest"], [], [], []],
	"Location":[[], [], ["place"], []],
	"conceptual_dependency":"(task (plan user_speech) (action_type ptrans) (params location -Location-) (step ))" +
				"(task (plan user_speech) (action_type mbuild) (params -Property- nil) (step ))" +
				"(task (plan user_speech) (action_type ptrans) (params location current_loc) (step ))" +
				"(task (plan user_speech) (action_type attend) (params question tell_what) (step ))",
	"verbal_confirmation": '',
	"planner_confirmed": '',
	"planner_not_confirmed": ''},

	#$fndobj   = Tell me what's the $oprop {category} on the {placement}
	{"params": ["Action_talk", "Person", "Property", "Category", "Location"],
	"Action_talk": [["tell"], [], [], []],
	"Person": [["me"],[],[],[]],
	"Property": [["biggest", "smallest", "heaviest", "lightest", "largest", "thinnest"], [], [], []],
	"Category": [["snacks", "candies", "food", "drinks", "toiletries", "containers"], [], [], []],
	"Location":[[], [], ["place"], []],
	"conceptual_dependency":"(task (plan user_speech) (action_type ptrans) (params location -Location-) (step ))" +
				"(task (plan user_speech) (action_type mbuild) (params -Property- -Category-) (step ))" +
				"(task (plan user_speech) (action_type ptrans) (params location current_loc) (step ))" +
				"(task (plan user_speech) (action_type attend) (params question tell_what_cat) (step ))",
	"verbal_confirmation": '',
	"planner_confirmed": '',
	"planner_not_confirmed": ''},
	
	#$fndobj   = $vbfind the {category} in the {room}
	{"params": ["Action_get", "Category", "Location"],
	"Action_get": [["find", "look_for", "locate"], [], [], []],
	"Category": [["snacks", "candies", "food", "drinks", "toiletries", "containers"], [], [], []],
	"Location":[[], [], ["place"], []],
	"conceptual_dependency":"(task (plan user_speech) (action_type ptrans) (params location -Location-) (step ))" +
				"(task (plan user_speech) (action_type mtrans) (params -Category- -Location-) (step )) ", 
	"verbal_confirmation": '',
	"planner_confirmed": '',
	"planner_not_confirmed": ''},

	#$follow   = $vbfollow {name 1} from the {beacon 1} to the {room 2}
	#$follow   = meet {name 1} at the {beacon 1} and $vbfollow them $fllwdest
	{"params": ["Action_follow", "Person", "Location_first", "Location_second"],
	"Action_follow": [["follow", "after"], [], [], []],
	"Person": [[], [], ["person"], []],
	"Location_first":[[], [], ["place"], []],
	"Location_second":[[], [], ["place"], []],
	"conceptual_dependency": "(task (plan user_speech) (action_type mtrans) (params -Person- -Location_first-) (step )) " +
				"(task (plan user_speech) (action_type grasp) (params man -Location_second-) (step )) ", 
	"verbal_confirmation": '',
	"planner_confirmed": '',
	"planner_not_confirmed": ''},

	#$gdcmd    = $vbguide {name 1} from the {beacon 1} to the {beacon 2}
	#$gdcmd    = meet {name 1} at the {beacon 1} and $guideto
	{"params": ["Action_guide", "Person", "Location_first", "Location_second"],
	"Action_guide": [["guide" , "escort" , "take" , "lead" , "accompany"], [], [], []],
	"Person": [[], [], ["person"], []],
	"Location_first":[[], [], ["place"], []],
	"Location_second":[[], [], ["place"], []],
	"conceptual_dependency": "(task (plan user_speech) (action_type mtrans) (params -Person- -Location_first-) (step )) " +
				"(task (plan user_speech) (action_type grasp) (params man_guide -Location_second-) (step )) ", 
	"verbal_confirmation": '',
	"planner_confirmed": '',
	"planner_not_confirmed": ''},

	#$gdcmd    = $vbguide {name 1} to the {beacon 2}, $gdwhere
	{"params": ["Action_guide", "Person", "Location_first", "May", "Action_find", "Location_second"],
	"Action_guide": [["guide" , "escort" , "take" , "lead" , "accompany"], [], [], []],
	"Person": [[], [], ["person"], []],
	"Location_first":[[], [], ["place"], []],
	"May":[["may", "can", "will"],[],[],[]],
	"Action_find":[["find"],[],[],[]],
	"Location_second":[[], [], ["place"], []],
	"conceptual_dependency": "(task (plan user_speech) (action_type mtrans) (params -Person- -Location_second-) (step )) " +
				"(task (plan user_speech) (action_type grasp) (params man_guide -Location_first-) (step )) ", 
	"verbal_confirmation": '',
	"planner_confirmed": '',
	"planner_not_confirmed": ''}
]

used_patterns = [0]*len(meaning_mapping_patterns)

verbose = True
#######################
# match the fragmented grounded sentence to a conceptual dependency 
def generate_dependency(G, sentence_dict):
	# recibe un diccionario con campos "constituents", "objects", "types", "words", 
	#la primeras dos son listas de strings y las otras son lista de listas
	print "diccionario recibido: ", sentence_dict

	print "palabras:: ", sentence_dict["words"]
	#print "Entrando a generate_dependency:.... ", sentence_dict
	used_objects = []
	solved_dependency = ''
	solved = False
	

	#print "7::       ------------------------------------" if verbose else "",
	print "matching an interpretation" 

	# list of interpretations of each meaning pattern
	# 
	#print "WTF... ", len(meaning_mapping_patterns)
	interpretations_list = []
	id_pattern = 0
	for each_pattern in meaning_mapping_patterns:
		# init template interpretation
		id_pattern += 1
		matched_elements = [[each, ""] for each in each_pattern["params"]]
		#print "hey! elementos a machear: ", matched_elements
		current_interpretation = {"id_pattern": id_pattern, "rank":0.0, "matched_elements":matched_elements, "conceptual_dependency": each_pattern["conceptual_dependency"], "verbal_confirmation": each_pattern["verbal_confirmation"], "planner_confirmed": each_pattern["planner_confirmed"], "planner_not_confirmed": each_pattern["planner_not_confirmed"]}
		used_params = []
		used_objs = []

		for each_param in each_pattern["params"]:
			params_matched = []
			
			# try fetch an element from sentence metadata to match a parameter
			#print "chaaaaa: ", sentence_dict["words"],sentence_dict["objects"], len(sentence_dict["objects"]) -1
			for object_index in range(0, len(sentence_dict["words"])) :
				current_words = sentence_dict["words"][object_index]
				current_constituent = sentence_dict["constituents"][object_index]
				current_types = sentence_dict["types"][object_index]
				current_object = sentence_dict["objects"][object_index]
				#print "trying to match ", current_object, " with ", each_param
				#print "Tamanio de la lista  ", sentence_dict["objects"][object_index]
				# verifying for each_param
				if each_param not in used_params and current_object not in used_objs:
					#check words
					veri_words = len(intersection(current_words, each_pattern[each_param][0])) > 0 or each_pattern[each_param][0] == []
					#print 'palabras clave: ', veri_words
					#check constituyente
					veri_const = current_constituent in each_pattern[each_param][1] or each_pattern[each_param][1] == []
					#print 'contituyente: ', veri_const
					#check semantic type
					veri_type = len(intersection(current_types, each_pattern[each_param][2])) > 0 or each_pattern[each_param][2] == []
					#print 'tipos semanticos: ', veri_type
					
					if veri_type and veri_const and veri_words:
						for each_element in current_interpretation["matched_elements"]:
							if each_element[0] == each_param and each_element[1] == "":
								each_element[1] = current_object
								used_params.append(each_param)
								used_objs.append(current_object)
								#print "----------USED PARAMS: ", used_params
								current_interpretation["rank"] +=  1.0/len(current_interpretation["matched_elements"])

		# rank con base a los numero de elementos en el enunciado respecto al numero de parametros requeridos

		#print "rank: ", current_interpretation["rank"]
		current_interpretation["rank"] = current_interpretation["rank"] * (1.0 - (float(abs(len(sentence_dict["objects"])- len(each_pattern["params"]))))/(len(each_pattern["params"])+len(sentence_dict["objects"])))
		#print "rank: ", current_interpretation["rank"], len(sentence_dict["objects"]),len(each_pattern["params"]),  (float(abs(len(sentence_dict["objects"])- len(each_pattern["params"]))))/(len(each_pattern["params"])+len(sentence_dict["objects"]))
		interpretations_list.append(current_interpretation)

	#print ""
	#print "- LOG: TOTAL OF PATTERNS ANALISED: ", len(interpretations_list)

	ranked_interpretations = sorted(interpretations_list, key=lambda k: k["rank"], reverse=True)

	for each_inter in ranked_interpretations:
		print "matched: " if verbose else "",
		print each_inter["matched_elements"] if verbose else "",
		print "rank: " if verbose else "",
		print each_inter["rank"] if verbose else "",
		print "____" if verbose else ""

	# hasta aqui se tienen las interpretaciones de todos los patrones ordenados por
	# porcentaje de roles tematicos aterrizados

	


	# si existe un patron interpretado completamente genero las expresiones
	# de lo contrario empiezo la interaccion para encontrar el resto 
	#print "_____________ RANKED LIST: ", ranked_interpretations
	if ranked_interpretations[0]["rank"] > 0.2:
		used_patterns[ranked_interpretations[0]["id_pattern"]-1] += 1
		#print "substitude grounded parameters" if verbose else "",
		# sustitucion de simbolos aterrizados en las expresiones
		output_expression = ranked_interpretations[0]["conceptual_dependency"]
		verbal_confirmation = ranked_interpretations[0]["verbal_confirmation"]
		planner_confirmed = ranked_interpretations[0]["planner_confirmed"]
		planner_not_confirmed = ranked_interpretations[0]["planner_not_confirmed"]

		for each_param in ranked_interpretations[0]["matched_elements"]:
			#print "labeL: ", each_param[0]
			#print "value: ", each_param[1]

			output_expression = re.sub('-'+each_param[0]+'-', each_param[1], output_expression)
			
			verbal_confirmation = re.sub('-'+each_param[0]+'-', each_param[1], verbal_confirmation)
			planner_confirmed = re.sub('-'+each_param[0]+'-', each_param[1], planner_confirmed)
			planner_not_confirmed = re.sub('-'+each_param[0]+'-', each_param[1], planner_not_confirmed)

			# falta evaluar expresiones en python


		#print ""
		print "Generated expresion: " + output_expression
		return output_expression

		#print "mensaje de confirmacion: ", verbal_confirmation

		#print "accion al planeador de ser confirmado: ", planner_confirmed

		#print "accion al planeador de no ser confirmado: ", planner_not_confirmed

	else:
		print "The sentence was not fully interpreted"
		return False






# Break multiple commands in the same phrase
def break_sentence(sentence_string):
	commands = []
	words = sentence_string.split(" ")
	# break when comma
	for each in words:
		if "," in each:
			commands.append(" ".join(words[0:words.index(each)]+[re.sub(',', '', each)]))
			words = words[words.index(each)+1:len(words)]
	
	# break when "and"
	if "and" in words:
		commands.append(" ".join(words[0:words.index("and")]))
		commands.append(" ".join(words[words.index("and")+1:len(words)]))
	return commands






# grounds every np from the sentence
# 1) mapping words to ontology vocabulary
# 2) sintactical analisys
# 3) solve syntactical well formed noun phrases
def sentence_grounder(G, sentence):
	sentence = parsing.ontology_words_mapping(sentence)
	print "keywords substitution: " + sentence 
	
	words, ranked_tags = parsing.pos_tagger(G, sentence)	
	#print "2::       ------------------------------------" if verbose else ""
	#print "part-of-speech tags: " + " ".join(ranked_tags[0]) if verbose else ""
	
	np_interpretation = parsing.constituent_chunker(parsing.grammar_np_simple, words, ranked_tags[0])
	#print "3::       ------------------------------------" if verbose else "",
	#print "noun phrases segmentation" if verbose else ""
	#print "chunked pos: " + " ".join(np_interpretation[0]) if verbose else ""
	#print "chunked words: " + " ".join(np_interpretation[1]) if verbose else ""
	#print "noun phrases: " if verbose else "",
	#print np_interpretation[2] if verbose else ""
	
	# constituent level
	constituent_level = np_interpretation[1][:]

	solved_nps = []
	solved_nps_types = []
	solved = True
	print "np_interpretation: ", np_interpretation[2]
	for each in np_interpretation[2]:
		ontology_type, names = noun_phrase_grounder(G, each[0], each[1]) 
		if names == []:
			solved = False
			print "noun phrase can not be grounded"
		solved_nps.append(names)
		solved_nps_types.append(ontology_type)
		print "ontology_type: ", ontology_type
		print "solved_nps_types: ", solved_nps_types
	
	#print "4::       ------------------------------------" if verbose else ""
	#print "grounded noun phrases: " if verbose else "",
	#print solved_nps if verbose else ""

	if solved: 
		# obtain all combinations using solved noun phrases
		# subtitutes solved noun phrases into the sentence
		words_np_solved = []
		chunked_constituents = []
		i = 0
		for each_word in np_interpretation[1]:
			if re.match('NOUN_PHRASE_[0-9]+', each_word):
				words_np_solved.append(solved_nps[i])
				chunked_constituents.append(np_interpretation[2][0])
				i += 1
			else:
				words_np_solved.append(each_word)
				chunked_constituents.append(each_word)
		#print "substituted solved nps: ", words_np_solved
		packed_words = []
		for each_word in words_np_solved:
			if not isinstance(each_word, list):
				packed_words.append([each_word])
			else:
				packed_words.append(each_word)

		#print "packed in lists:::: ", packed_words
		all_words = parsing.all_combinations(packed_words)

		#print "5::       ------------------------------------" if verbose else ""
		print "All sentences: " if verbose else "",
		print  all_words if verbose else ""
		#print "-----> all combinations POS: ", np_interpretation[0]
		
		# up to here all direct grounded commands are contructed therefore
		# they can be further separated in NPs and PPs for verb pattern matching
		analized_sentences = []
		for each_utterance in all_words:
			pp_interpretation = parsing.pp_chunker(parsing.grammar_pp, each_utterance, np_interpretation[0], [])
			


			#print ":XX:D:D:DD:D::D:D:D:D::D:D:D:D::DD::D:D------------"
			#print "constituent_level: ", pp_interpretation[0]
			#print "chunked words: ", pp_interpretation[1]
			#print "noun phrases: ", pp_interpretation[2]
			#print "prepositional phrases: ", pp_interpretation[3]

			object_level = []
			# solving prepositional phrases
			pp_names = []
			for each_pp in pp_interpretation[3]:
				pp_names.append(prepositional_phrase_grounder(G, each_pp[0], each_pp[1])[0]) 
				if pp_names == []:
					solved = False
					print "prepositional phrase: " + each + " can not be grounded"
				#solved_nps.append(names)
			#print "-----------PPPPPP", pp_names
			if solved: 
				# obtain all combinations using solved prep phrases
				# subtitutes solved prep phrases into the sentence
				i = 0
				for each_word in pp_interpretation[1]:
					if re.match('PREP_PHRASE_[0-9]+', each_word):
						object_level.append(pp_names[i])
						i += 1
					else:
						object_level.append(each_word)

			# semantic classes
			# pointer alias
			pos_tags_pp = pp_interpretation[0]
			words_pp = pp_interpretation[1]

			print "-------- pos_tags_pp:, ", pos_tags_pp
			print "solved_nps_types: ", solved_nps_types

			k=0
			#print "generando lista de tipos:"
			semantic_types = []
			for iterator in range(0,len(object_level)):
				#print "consultando tipo del objeto: ", object_level[iterator]
				if object_level[iterator] in G:
					#print "padre en la ontologia"
					semantic_types.append(kb_services.all_superclasses(G, object_level[iterator]))
				elif pp_interpretation[0][iterator] == 'noun' or pp_interpretation[0][iterator] == 'prep_phrase':
					print "buscando tipos de: ", solved_nps_types[k]
					print "super clases are: ", kb_services.all_superclasses(G,solved_nps_types[k])
					semantic_types.append(kb_services.all_superclasses(G,solved_nps_types[k]))
					k = k + 1
				else:
					#print "aca se pone lista vacia"
					semantic_types.append([])

			#semantic_types = [kb_services.all_superclasses(G, each) for each in object_level]
			
			#print "----->  object_level: ", object_level
			#print "----->  constituent_level: ", pp_interpretation[0] 
			#print "----->  semantic types: ", semantic_types

			## cut
			# packing words into constituents
			i=0
			#print "original words:", words
			pp_chunked = parsing.pp_chunker(parsing.grammar_pp, each_utterance, np_interpretation[0], [])
			chunked_final_words = []
			#print "....", pp_chunked[1]
			for each_word in pp_chunked[1]:
					if re.match('PREP_PHRASE_[0-9]+', each_word):
						chunked_final_words.append(pp_chunked[3][i][0])
						i += 1
					else:
						chunked_final_words.append(each_word)
			#print "------------chunked pp final words", chunked_final_words
			np_chunked = parsing.constituent_chunker(parsing.grammar_np_simple, chunked_final_words, pp_chunked[0])
			chunked_final_words = []
			i=0
			sin = 0
			constituent_level =[] #np_chunked[0][:]
			for each_word in np_chunked[1]:
					if isinstance(each_word, str) and re.match('NOUN_PHRASE_[0-9]+', each_word):
						if len(np_chunked[2][i][0]) > 1:
							chunked_final_words.append(np_chunked[2][i][0][0])
							chunked_final_words.append(np_chunked[2][i][0][1])
							constituent_level.append(np_chunked[0][sin])
							constituent_level.append(np_chunked[0][sin])
							print "-------------- np chunked final words ", sin
							sin += 1
							
							print "-------------- np chunked final words ", np_chunked[2][i][0]
							print "-------------- np chunked final words ", len(np_chunked[2][i][0][1])
							print "-------------- FINALWORDS ", chunked_final_words 
						else:
							chunked_final_words.append(np_chunked[2][i][0])
							constituent_level.append(np_chunked[0][sin])
							sin += 1
						
						i += 1
					else:
						chunked_final_words.append(each_word)
						constituent_level.append(np_chunked[0][sin])
						sin += 1
			
			

			## cut

			print "Resumen::       ------------------------------------" if verbose else ""
			print "Words: ", chunked_final_words 
			print "Sintax: ", constituent_level 
			print "Objects:", object_level 
			print "Object type", semantic_types


			analized_sentences.append({"words":chunked_final_words, "constituents": constituent_level, "objects": object_level, "types":semantic_types})
		

		# return a list of dicionaries that
		return analized_sentences
	else:
		print "SOMETHING WRONG! no object matched with the noun phrase"
		sem_types = []
		return []


# solve noun phrases
def noun_phrase_grounder(G, words, pos):	
	
	ontology_type, grounded_objs = solve_np(G, words, pos)
	# get a quantifier three cases all, one or defined by a integer
	if grounded_objs != []:
		if 'existencial' in pos:
			return ontology_type, [grounded_objs[0]]
		elif 'universal' in pos:
			return ontology_type, grounded_objs
		elif 'number' in pos:
			if int(words[pos.index('number')]) < len(grounded_objs):
				return ontology_type, grounded_objs[0:int(words[pos.index('number')])]
			else:
				return ontology_type, grounded_objs
		elif 'idf_pro' in pos:
			return ontology_type, [grounded_objs[0]]
		else:
			return ontology_type, grounded_objs
	else:
		print 'Las palabras subespecificadas se resuelven a nivel del planeador'

		return ontology_type, [ontology_type]


# solve noun phrases
def prepositional_phrase_grounder(G, words, pos):	
	if len(pos) == 2 and pos[1] == "noun":
		return [words[1]]
	else:
		return []
		

def solve_np(G, words, pos):
	#print "solving np: " + " ".join(words) if verbose else "",
	nouns = []
	adjs = []
	atts = []
	vrbs = []
	objs = []
	nums = []
	for i in range(len(words)):
		if pos[i] == 'noun':
			if  len(nouns) == 0:
				nouns.append(words[i])
			else:
				adjs.append(words[i])
		elif pos[i] == 'adj':
			adjs.append(words[i])
		elif pos[i] == 'att':
			atts.append(words[i])
		elif pos[i] == 'vrb':
			vrbs.append(words[i])
		elif pos[i] == 'number':
			nums.append(words[i])
		elif pos[i] == 'idf_pro':
			nouns.append('stuff')
	print 'nouns: ' , nouns , '   adjs: ' , adjs , '   vrbs: ' , vrbs , '   atts: ' , atts 
	# collect all objects of class
	if len(nouns) > 0:
		obj_candidates = kb_services.all_objects(G, nouns[0])
		print 'candidate objects: ', obj_candidates
		# filter objects that has correct properties
		if len(adjs) > 0:
			for each_obj in obj_candidates:
				if kb_services.verify_satisfability_of_objclss(G, each_obj, adjs):
					objs.append(each_obj)
		# filter objects that are object of action verb
		elif len(vrbs) > 0:
			for each_obj in obj_candidates:
				obj_actions = kb_services.get_attribute(G, each_obj, 'is_object_of_action')
				if "is_object_of_action" in obj_actions and vrbs[0] in obj_actions["is_object_of_action"]:
					objs.append(each_obj)		
		
	return nouns[0], objs




# pack information for interpretation
def semantic_type_of_nps(G, pos, words, nps):
	np_count = 0
	semantic_types = words[:]
	for i in range(0,len(words)):
		if re.match('NOUN_PHRASE_[0-9]+', words[i]):
			#print "lol found", nps[np_count][0]
			semantic_types[i] = kb_services.semantic_type(G, nps[np_count][0])
			np_count += 1
		else:
			semantic_types[i] = kb_services.semantic_type(G, words[i])
	return semantic_types


# generate message from dictionary
def generate_nl_response_from_dict(dictio):
	response = ""
	if dictio == {}:
		response = "not information about that, sorry"
	else:
		for each in dictio:
			print "HEY " + each + "  " + dictio[each] if verbose else "",
			response +=" is " + each + " " + " and ".join(dictio[each])
	return response

def generate_nl_response_from_list(ls):
	response = ""
	if ls == []:
		response = "not any known object, sorry"
	else:
		if len(ls) == 1:
			response = ls.pop() + " is "
		else:
			for i in range(0, len(ls) - 1):
				response += ls.pop() + ", "
			response += "and " + ls.pop() + " are "
	return response


def test_solver(sentence_string):
	G = kb_services.load_semantic_network()
	grounded_commands = sentence_grounder(G, sentence_string)
	print "grounded command: ", grounded_commands
	for each_command in grounded_commands:
		expression = generate_dependency(G, each_command)
		print "generated expression to planner: ", expression



#test_solver("deliver an asadkasdale to the kitchen")

