filename = "tardiscoords2"
ext = ".txt"
g = open("output_" + filename + ext, "w")
count = 0
with open("../" + filename + ext) as f:
  while True:
    c = f.read(1)
    if not c:
      print("End of file")
      break
    if c == " ":
        g.write(",")
        count = count + 1
    if count == 3:
        g.write("\n")
        count = 0
    if not(count == 0 and c == " "):
        g.write(c)
g.close()

#tardiscoords
#55.11811 * 2.54 = 140.00177994                        140
#94.48819 * 2.54 = 240.00000260000002     240
#27.55906 * 2.54 = 70.0000124                    070
#106.2992 * 2.54 =269.999968                       270

#tardiscoords2
#0.3939193 * 2.54 = 1.000555022                 001
#0.919145 * 2.54 = 2.3346283                        002.3