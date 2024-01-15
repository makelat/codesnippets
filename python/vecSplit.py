vec1=[0,1,2,3,4,5,6,7]

#Another vec with an index offset that wraps around:
vec2 = vec1[3:] + vec1[:3]

print 'Vectors before offset correction:'
print vec1
print vec2

print 'Performing offset correction:'
matched = False
for i1,v1 in enumerate(vec1):
    for i2,v2 in enumerate(vec2):
        if (not matched) and (v1==v2):
            vec2 = vec2[i2:] + vec2[:i2]
            matched = True
            break
    print vec1[i1],vec2[i1]
