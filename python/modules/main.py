#This file doesn't need to be named main, just conventional

#Somehow "import classes" does not give access to the whole classes.py...
#Need to import all contents one-by-obe
from classes import Person
from classes import Scientist
from classes import emptyClass
from classes import kneelAndDisconnect


p1 = Person("だる")
p2 = Scientist("ひやじょ",)

print(p1.name)
print(p1.x)
p1.greet()

p2.greet()
p2.introduce()
kneelAndDisconnect(p2,"Neuroscience")
p2.introduce()
