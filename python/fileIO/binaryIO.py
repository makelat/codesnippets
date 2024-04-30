#Init a matrix of data to be written into a file
ndim=100
matrix=[[x for x in range(ndim)] for _ in range(ndim)]

#Write into a human-readable text file
ftxt = open('test.txt','w')
for row in matrix: 
    for i,l in enumerate(row): 
        ftxt.write(str(l))
        if i<len(row)-1: ftxt.write(' ')
        else: ftxt.write('\n')
ftxt.close()

#Write into binary file -- this takes significantly less space, but matrix is flattened i.e. row/column information is lost
fbin = open('test.bin','wb')
for row in matrix: fbin.write(bytearray(row))
fbin.close()

#Read binary file and print contents in human-readable format,
#although w/o/ row/column information
fin = open('test.bin', 'rb')
bytedata = fin.read()
print([byte for byte in bytedata])
fin.close()
