filename = "tardiscoords"
ext = ".txt"
f = open("../" + filename + ext, "r")
data = f.readlines()
data = str(data)
data = data.replace("\'", "")
data = data.replace("[", "")
data = data.replace("]", "")
li = data.split(" ")
out = []
temp = 0.0
for i in li:
    temp = round(float(i) * 2.54, 0)
    out.append(temp)
f.close()

g = open("export_" + filename + ext, "w")
for i in range(len(out)):
    g.write(str(out[i]))
    if i != len(out) - 1:
        g.write(",")
        if i % 3 == 2:
            g.write("\n")
        else:
            g.write(" ")
g.close()