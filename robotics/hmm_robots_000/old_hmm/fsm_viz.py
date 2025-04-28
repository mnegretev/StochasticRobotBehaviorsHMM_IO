import sys

def convert_to_num(s):
        n = 0
	i = 1
	for d in reversed(s):
		if d == "1":
			n = n + i
		i=i*2		
	return n

def main(argv):

	action_label = ["SP","FW","BW","LE","RI","INV","INV","INV"]

	fin = open(argv[1], "r")

	fout = open(argv[2], "w+")

	content = fin.readlines()

        print(content)

	header = content[0]

	params = header.split(" ")

	num_states = pow(2,int(params[0]))
	num_actions = pow(2,int(params[1]))
	num_observations = pow(2,int(params[2]))

	fout.write("digraph D {\n")
	print(num_states) 
	line_index = 1

	for s in range(1,num_states+1):
		fout.write("%d\n"%(s))
		for o in range(1,num_observations+1):
			bits = content[line_index].split(" ")
			print("----------------")
			print(bits)
			print(bits[0:int(params[0])])
			state = convert_to_num(bits[0:int(params[0])]) + 1
			print(state)
			action = convert_to_num(bits[int(params[0]):int(params[0])+int(params[1])])
			print(bits[int(params[0]):int(params[0])+int(params[1])])
			print(action)
			line_index = line_index + 1
			fout.write("%d->%d [label=\"o=%d,a=%s\"]\n"%(s,state,o,action_label[action]))

	fout.write("}\n")

if __name__ == "__main__":
   main(sys.argv)

