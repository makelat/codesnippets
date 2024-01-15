try:
    print(x)
except NameError:
    print("ERROR: x is not defined")
finally:
    print("Hey at least I didn't crash")
