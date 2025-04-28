# romanos.py 
'''
@author: Eva Savage, UNAM-FI, 9-2020
'''




TRUE = 1


def romanos_str(data):
    unidades = ["","I","II","III","IV","V","VI","VII","VIII","IX"]
    docenas = ["","X","XX","XXX","XL","L","LX","LXX","LXXX","XC"]
    cientos = ["","C","CC","CCC","CD","D","DC","DCC","DCCC","CM"]

    
    c = cientos[data // 100 % 10]
    d = docenas[data // 10 % 10]
    u =  unidades[data % 10]
    
    return c+d+u


#-----------------------------------------------------
#  MAIN


if __name__ == '__main__':
   while TRUE:
	print "Type a number betwwen 1 and 1000: "
	num = int(input())
	print(romanos_str(num))

