filename = "basic_tardis"
#filename = "TARDIS"
ext = ".dae"
oxt = ".txt"
e = open("../" + filename + ext, "r")
data = e.readlines()
e.close()

f = open("concat_vertex_" + filename + oxt, "w")
g = open("concat_normal_" + filename + oxt, "w")
count = 0
for line in data:
    if "<float_array" in line:
        #clever stuff
        flag = 0
        sc = 0
        numstring = ""
        numbers = []
        while True:
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
            if count% 2 == 0:
                f.write(str(round(float(numbers[j])*2.54)))
            else:
                g.write(str(round(float(numbers[j])*2.54)))
            if j != len(numbers) - 1:
                if count % 2 == 0:
                    f.write(",")
                else:
                    g.write(",")
            if j % 3 == 2:
                if count % 2 == 0:
                    f.write("\n")
                else:
                    g.write("\n")
            else:
                if count % 2 == 0:
                    f.write(" ")
                else:
                    g.write(" ")
        count = count + 1
        #no more clever stuff
    pass
f.close()
g.close()

#read tags in <p></p>
indices = []
for line in data:
    if "<p>" in line:
        #clever stuff
        flag = 0
        sc = 0
        numstring = ""
        while True:
            sc = sc + 1
            if flag == 1:
                break
            if line[sc] == ">":
                flag = 1
            pass
        for j in range(len(line) - sc - 5): #length of the line minus the bits in <></>
            numstring = numstring + str(line[j+sc])
        indices.append(numstring)
    pass
maxi = 0
liout = []
hold = []
for part in indices:
    hold = part.split(" ")
    for k in range(len(hold)):
        liout.append(int(hold[k])+maxi)
    maxi = max(liout) + 1

h = open("concat_index_" + filename + oxt, "w")
for j in range(len(liout)):
    h.write(str(liout[j]))
    if j != len(liout) - 1:
        h.write(",")
        if j % 3 == 2:
            h.write("\n")
        else:
            h.write(" ")
h.close()