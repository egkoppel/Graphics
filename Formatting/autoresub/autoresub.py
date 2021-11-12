#filename = "basic_tardis"
filename = "TARDIS"
ext = ".dae"
f = open("../" + filename + ext, "r")
data = f.readlines()
f.close()

g = open("autoresub_" + filename + ext, "w")
for line in data:
    if "<float_array" in line:
        #clever stuff
        flag = 0
        sc = 0
        numstring = ""
        numbers = []
        while True:
            g.write(line[sc])
            sc = sc + 1
            if flag == 1:
                break
            if line[sc] == ">":
                flag = 1
            pass
        
        for j in range(len(line) - sc - 15): #length of the line minus the bits in <></>
            numstring = numstring + str(line[j+sc])
            
        numbers = numstring.split(" ")
        for j in range(len(numbers)):
            g.write(str(round(float(numbers[j])*2.54)))
            if j != len(numbers) - 1:
                g.write(" ")
        #no more clever stuff
        g.write("</float_array>\n")
    else:
        g.write(line)
g.close()