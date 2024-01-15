yRegs=["y0","y1","y2","y3"]

#Standard for (auto y : yRegs) -style loop
for y in yRegs:
    print(y)
    
#Combine for (auto y : yRegs) and for (int iy=0; ...) -style loops in one:
for iy,y in enumerate(yRegs):
    for iy2,y2 in enumerate(yRegs):
        if iy2>1:
            break
        else:
            print(iy, y)
